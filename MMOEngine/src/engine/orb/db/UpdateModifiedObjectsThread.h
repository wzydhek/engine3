/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/engine.h"
#include "system/thread/atomic/AtomicBoolean.h"
#include "DOBObjectManager.h"

namespace engine {
	namespace ORB {

	class UpdateModifiedObjectsThread : public Thread {
		DOBObjectManager* objectManager;

		ArrayList<DistributedObject*>* objectsToUpdate;
		ArrayList<DistributedObject*>* objectsToDelete;
		int startOffset;
		int endOffset;
		int threadId;

		Mutex blockMutex;
		Condition waitCondition;
		Condition finishedWorkCondition;
		Condition waitMasterTransaction;

		AtomicBoolean copyRAMFinished;
		AtomicBoolean doRun;
		AtomicBoolean working;
		AtomicBoolean finishedCommiting;
		AtomicBoolean waitingToCommit;
		AtomicBoolean waitingToStart;
		AtomicBoolean loadedDBHandles;

		engine::db::berkeley::Transaction* transaction;

		int cpu;

	public:
		UpdateModifiedObjectsThread(int id, DOBObjectManager* manager, int cpu);

		void run() NO_THREAD_SAFETY_ANALYSIS;

		void commitObjectsToDatabase();
		void commitTransaction() NO_THREAD_SAFETY_ANALYSIS;

		void setObjectsToUpdateVector(ArrayList<DistributedObject*>* objectsToUpdate);

		void setObjectsToDeleteVector(ArrayList<DistributedObject*>* objectsToDelete);

		void setTransaction(engine::db::berkeley::Transaction* trans);

		void setStartOffset(int offset);

		void setEndOffset(int offset);

		void stopWork();

		void setRAMCopyFinished(bool val);

		bool hasFinishedCommiting() const;

		void signalMasterTransactionFinish();

		void signalCopyFinished();

		void signalActivity();

		void waitFinishedWork();
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
