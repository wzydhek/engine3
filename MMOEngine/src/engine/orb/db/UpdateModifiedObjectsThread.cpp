/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "UpdateModifiedObjectsThread.h"

UpdateModifiedObjectsThread::UpdateModifiedObjectsThread(int id, DOBObjectManager* manager, int cpu) {
	objectManager = manager;
	objectsToUpdate = nullptr;
	objectsToDelete = nullptr;
	startOffset = 0;
	endOffset = 0;
	doRun = true;
	waitingToStart = true;
	threadId = id;
	working = false;
	finishedCommiting = false;
	waitingToCommit = false;
	loadedDBHandles = false;

	transaction = nullptr;

	this->cpu = cpu;
}

void UpdateModifiedObjectsThread::run() NO_THREAD_SAFETY_ANALYSIS {
	assignToCPU(cpu);

	while (doRun) {
		blockMutex.lock();

		while (!copyRAMFinished) {
			waitingToStart = true;

			waitCondition.wait(&blockMutex);

			waitingToStart = false;

			working = true;
			finishedCommiting = false;

			commitObjectsToDatabase();

			if (!loadedDBHandles) {
				auto dbManager = ObjectDatabaseManager::instance();
				auto dbCount = dbManager->getTotalDatabaseCount();

				for (int i = 0; i < dbCount; i++) {
					dbManager->getDatabase(i)->getDatabaseHandle();
				}

				loadedDBHandles = true;
			}

			working = false;

			objectsToUpdate = nullptr;
			objectsToDelete = nullptr;

			finishedWorkCondition.broadcast(&blockMutex);
		}

		commitTransaction();
	}
}

void UpdateModifiedObjectsThread::commitTransaction() NO_THREAD_SAFETY_ANALYSIS {
	bool rootBroker = DistributedObjectBroker::instance()->isRootBroker();

	if (transaction != nullptr) {
		waitingToCommit = true;

		waitMasterTransaction.wait(&blockMutex);

		Timer clockTimer(Time::MONOTONIC_TIME);
		clockTimer.start();

		ObjectDatabaseManager::instance()->commitLocalTransaction(transaction);

		uint64 delta = clockTimer.stop();

		objectManager->info(true) << "thread " << threadId << " commited objects into database in " << delta / 1000000 << " ms";

		transaction = nullptr;

		copyRAMFinished = false;

		finishedCommiting = true;

		blockMutex.unlock();
	} else {
		finishedCommiting = true;

		copyRAMFinished = false;

		blockMutex.unlock();

		if (rootBroker) {
			ObjectDatabaseManager::instance()->commitLocalTransaction();
		}
	}
}

void UpdateModifiedObjectsThread::commitObjectsToDatabase() {
	try {
		Time start(Time::MONOTONIC_TIME);

		if (objectsToUpdate != nullptr) {
			int j = 0;

			for (int i = startOffset; i < endOffset; ++i) {
				DistributedObject* object = objectsToUpdate->get(i);

				if (object->isPersistent() && objectManager->commitUpdatePersistentObjectToDB(object) == 0)
					++j;
			}

			objectManager->info(true) << "thread " << threadId << " copied "
				<< commas << j << " modified objects into ram in " << start.miliDifference(Time::MONOTONIC_TIME) << " ms";
		}

		start.updateToCurrentTime(Time::MONOTONIC_TIME);

		if (objectsToDelete != nullptr) {
			for (int i = 0; i < objectsToDelete->size(); ++i) {
				DistributedObject* object = objectsToDelete->getUnsafe(i);

				if (!object->_isDeletedFromDatabase()) {
					objectManager->commitDestroyObjectToDB(object->_getObjectID());
					object->_setDeletedFromDatabase(true);
				}
			}

			objectManager->info(true) << "thread " << threadId << " commited "
				<< commas << objectsToDelete->size() <<  " objects for deletion into ram in " << start.miliDifference(Time::MONOTONIC_TIME) << " ms";
		}
	} catch (const Exception& e) {
		objectManager->error(e.getMessage());
	} catch (...) {
		objectManager->error("unreported exception caught");

		throw;
	}
}

void UpdateModifiedObjectsThread::setObjectsToUpdateVector(ArrayList<DistributedObject*>* objectsToUpdate) {
	this->objectsToUpdate = objectsToUpdate;
}

void UpdateModifiedObjectsThread::setObjectsToDeleteVector(ArrayList<DistributedObject*>* objectsToDelete) {
	this->objectsToDelete = objectsToDelete;
}

void UpdateModifiedObjectsThread::setTransaction(engine::db::berkeley::Transaction* trans) {
	transaction = trans;
}

void UpdateModifiedObjectsThread::setStartOffset(int offset) {
	startOffset = offset;
}

void UpdateModifiedObjectsThread::setEndOffset(int offset) {
	endOffset = offset;
}

void UpdateModifiedObjectsThread::stopWork() {
	doRun = false;

	signalCopyFinished();

	waitFinishedWork();

	join();
}

void UpdateModifiedObjectsThread::setRAMCopyFinished(bool val) {
	copyRAMFinished = val;
}

bool UpdateModifiedObjectsThread::hasFinishedCommiting() const {
	return finishedCommiting;
}

void UpdateModifiedObjectsThread::signalMasterTransactionFinish() {
	blockMutex.lock();

	waitMasterTransaction.broadcast(&blockMutex);

	blockMutex.unlock();
}

void UpdateModifiedObjectsThread::signalCopyFinished() {
	blockMutex.lock();

	setRAMCopyFinished(true);

	waitCondition.broadcast(&blockMutex);

	blockMutex.unlock();
}

void UpdateModifiedObjectsThread::signalActivity() {
	blockMutex.lock();

	working = true;

	waitCondition.broadcast(&blockMutex);

	blockMutex.unlock();
}

void UpdateModifiedObjectsThread::waitFinishedWork() {
	blockMutex.lock();

	while (doRun && waitingToStart && objectsToUpdate != nullptr) {
		waitCondition.broadcast(&blockMutex);
		blockMutex.unlock();
		blockMutex.lock();
	}

	if (working)
		finishedWorkCondition.wait(&blockMutex);

	blockMutex.unlock();
}