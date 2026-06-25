/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#include "Core.h"

#include "engine/db/ObjectDatabaseManager.h"

#include "engine/stm/TransactionalMemoryManager.h"

#ifdef CXX11_COMPILER
#include <chrono>
#endif


Task::Task() : PriorityQueueEntry() {
	initialize();
}

Task::Task(uint64 mtime) : PriorityQueueEntry() {
	initialize();

	nextExecutionTime.addMiliTime(mtime);
}

Task::Task(const Time& time) : PriorityQueueEntry() {
	initialize();

	nextExecutionTime = time;
}

Task::~Task() {
	E3_ASSERT(!isQueued());

#ifdef TRACE_TASKS
	if (scheduleTrace != nullptr) {
		delete scheduleTrace;
		scheduleTrace = nullptr;
	}
#endif
}

void Task::initialize() {
	priority = 3;
	period = 0;

#ifdef TRACE_TASKS
	scheduleTrace = nullptr;
#endif

#ifdef COLLECT_TASKSTATISTICS
	statsSampleRate = 1;
#endif
}

void Task::execute() {
	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->executeTask(this);
}

void Task::executeInThread() {
	doExecute();
}

void Task::doExecute() {
#ifdef WITH_STM
	//Logger::console.info("executing " + TypeInfo<Task>::getClassName(this), true);

	try {
		int commitAttempts = 0;

		Reference<engine::stm::Transaction*> transaction;

		while (true) {
			transaction = TransactionalMemoryManager::instance()->startTransaction();
			//engine::stm::Transaction* transaction = engine::stm::Transaction::currentTransaction();

			++commitAttempts;

			if (transaction->start(this) && transaction->commit()) {
				break;
			} else {
				Thread* thisThread = Thread::getCurrentThread();

				if (thisThread != nullptr && taskManager->getSerialWorker() != thisThread) {
					taskManager->retryTaskInSerial(this);

					TransactionalMemoryManager::instance()->retryTransaction();

					return;
				}
			}

			if (commitAttempts > 1)
				TransactionalMemoryManager::instance()->retryTransaction();
		}

		/*if (transaction->getReferenceCount() > 1)
			Logger::console.info("refs left of transaction " + String::valueOf(transaction->getReferenceCount()), true);*/

	} catch (Exception& e) {
		Logger::console.error("exception caught while running a task");
		e.printStackTrace();
	} catch (TransactionAbortedException& e) {
		Logger::console.error("in TASK");
	}
#else
	ObjectDatabaseManager::instance()->startLocalTransaction();

	Timer executionTimer;
	executionTimer.start();

	try {
		run();
	} catch (const Exception& e) {
		Logger::console.error("exception caught while running a task");
		e.printStackTrace();
	} catch (...) {
		Logger::console.error("unreported exception caught while running a task");
	}

	lastElapsedTime = executionTimer.stop();

	ObjectDatabaseManager::instance()->commitLocalTransaction();
#endif
}

bool Task::isScheduled() const {
  	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return false;
	}

	return taskManager->isTaskScheduled(this);
}

bool Task::cancel() {
	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return true;
	}

	return taskManager->cancelTask(this);
}

bool Task::cancelNonTransactionally() {
#ifdef WITH_STM
	return TransactionalMemoryManager::instance()->getTaskManager()->getTaskManagerImpl()->cancelTask(this);
#else
	return cancel();
#endif
}

void Task::schedule(uint64 delay) {
	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->scheduleTask(this, delay);
}

void Task::scheduleInIoScheduler(uint64 delay) {
	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->scheduleIoTask(this, delay);
}

void Task::scheduleInIoScheduler(Time& time) {
	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->scheduleIoTask(this, time);
}

void Task::scheduleNonTransactionally(uint64 delay) {
#ifdef WITH_STM
	TransactionalMemoryManager::instance()->getTaskManager()->getTaskManagerImpl()->scheduleTask(this, delay);
#else
	schedule(delay);
#endif

}

void Task::schedule(Time& time) {
	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->scheduleTask(this, time);
}

void Task::schedulePeriodic(uint64 delay, uint64 period) {
	setPeriod(period);

	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->scheduleTask(this, delay);
}

void Task::schedulePeriodic(Time& time, uint64 period) {
	setPeriod(period);

	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->scheduleTask(this, time);
}

void Task::reschedule(uint64 delay) {
	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->rescheduleTask(this, delay);
}

void Task::rescheduleInIoScheduler(uint64 delay) {
	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->rescheduleIoTask(this, delay);
}

void Task::rescheduleInIoScheduler(Time& time) {
	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->rescheduleIoTask(this, time);
}

void Task::rescheduleNonTransactionally(uint64 delay) {
#ifdef WITH_STM
	TransactionalMemoryManager::instance()->getTaskManager()->getTaskManagerImpl()->rescheduleTask(this, delay);
#else
	reschedule(delay);
#endif
}

void Task::reschedule(Time& time) {
	auto taskManager = Core::getTaskManager();

	if (!taskManager) {
		return;
	}

	taskManager->rescheduleTask(this, time);
}

const char* Task::getTaskName() {
	if (!taskName.isEmpty()) {
		return taskName.toCharArray();
	} else {
		return typeid(*this).name();
	}
}

int Task::compareTo(const PriorityQueueEntry* node) const {
	const Task* task = static_cast<const Task*>(node);

	if (task == this)
		return 0;

	int cmp = nextExecutionTime.compareTo(task->nextExecutionTime);
	if (cmp == 0) {
		if (std::less<const Task*>()(this, task))
			return 1;
		else
			return -1;
	} else
		return cmp;
}

String Task::toStringData() const {
	StringBuffer s;
	s << nextExecutionTime.getMiliTime() << "(ptr = " << this << ")";
	return s.toString();
}

void Task::setExecutionTime(const Time& time) {
	nextExecutionTime = time;
}

void Task::updateExecutionTime(uint64 mtime) {
	nextExecutionTime.updateToCurrentTime();

	if (mtime != 0)
		nextExecutionTime.addMiliTime(mtime);
}

const Time& Task::getNextExecutionTime() const {
	return nextExecutionTime;
}

TaskScheduler* Task::getTaskScheduler() {
	return taskScheduler;
}

const TaskScheduler* Task::getTaskScheduler() const {
	return taskScheduler;
}

int Task::getPriroty() const {
	return priority;
}

bool Task::isPeriodic() const {
	return period != 0;
}

bool Task::doRunInScheduler() const {
	return runInScheduler;
}

void Task::setRunInScheduler(bool val) {
	runInScheduler = val;
}

bool Task::setTaskScheduler(TaskScheduler* scheduler) {
	return taskScheduler.compareAndSet(nullptr, scheduler);
}

bool Task::clearTaskScheduler() {
	TaskScheduler* scheduler = taskScheduler.get();

	return taskScheduler.compareAndSet(scheduler, nullptr);
}

void Task::setPriority(int priority) {
	Task::priority = priority;
}

uint64 Task::getPeriod() const {
	return period;
}

void Task::setPeriod(uint64 per) {
	period = per;
}

void Task::setCustomTaskQueue(const String& queue) {
	customTaskQueue = queue;
}

void Task::setCustomTaskQueue(String&& queue) {
	customTaskQueue = std::move(queue);
}

const String& Task::getCustomTaskQueue() const {
	return customTaskQueue;
}

void Task::setTaskName(const char* name) {
	taskName = name;
}

void Task::setTaskName(const String& name) {
	taskName = name;
}

void Task::setTaskName(String&& name) {
	taskName = std::move(name);
}

#ifdef COLLECT_TASKSTATISTICS
void Task::setStatsSample(bool val) {
	statsSampleRate = val;
}

int Task::getStatsSampleRate() const {
	return statsSampleRate;
}
#endif

uint64 Task::getLastElapsedTime() const {
	return lastElapsedTime;
}

#ifdef TRACE_TASKS
void Task::setScheduleTrace() {
	if (scheduleTrace != nullptr)
		delete scheduleTrace;

	scheduleTrace = new StackTrace();
}

void Task::printScheduleTrace() {
	assert(scheduleTrace != nullptr);

	scheduleTrace->print();
}
#endif