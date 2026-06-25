/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "engine/core/TaskManagerImpl.h"
#include "engine/core/TaskScheduler.h"
#include "engine/core/TaskWorkerThread.h"

#include "LocalTaskManager.h"

TaskReference::TaskReference() {
	task = nullptr;
}

TaskReference::TaskReference(const Task* t) {
	task = const_cast<Task*>(t);
}

TaskReference::TaskReference(const TaskReference& t) {
	task = t.task;
}

bool TaskReference::toBinaryStream(ObjectOutputStream* stream) {
	return false;
}

bool TaskReference::parseFromBinaryStream(ObjectInputStream* stream) {
	return false;
}

TaskReference& TaskReference::operator=(const TaskReference& t) {
	if (this == &t)
		return *this;

	task = t.task;

	return *this;
}

int TaskReference::compareTo(const TaskReference& ref) const {
	if (task == ref.task)
		return 0;
	else if (task < ref.task)
		return 1;
	else
		return -1;
}

TaskReference::operator Task*() {
	return task;
}

Task* TaskReference::operator->() {
	return task;
}

Task* TaskReference::getTask() {
	return task;
}

TaskAction::TaskAction(const TaskAction& a) : Object() {
	type = a.type;
	task = a.task;
	nextExecutionTime = a.nextExecutionTime;
}

TaskAction::TaskAction(int type, Reference<Task*> task, const AtomicTime& nextExecutionTime) {
	TaskAction::type = type;
	TaskAction::task = task;
	TaskAction::nextExecutionTime = nextExecutionTime;
}

TaskAction& TaskAction::operator=(const TaskAction& a) {
	if (this == &a)
		return *this;

	type = a.type;
	task = a.task;
	nextExecutionTime = a.nextExecutionTime;

	return *this;
}

int TaskAction::getType() const {
	return type;
}

Task* TaskAction::getTask() const {
	return task;
}

AtomicTime& TaskAction::getNextExecutionTime() {
	return nextExecutionTime;
}

LocalTaskManager::LocalTaskManager() {
	merging = false;

	/*executedTasks.setNoDuplicateInsertPlan();
	scheduledTasks.setNoDuplicateInsertPlan();
	cancelledTasks.setNoDuplicateInsertPlan();*/

	lastTaskAction.setAllowOverwriteInsertPlan();
	lastTaskAction.setNullValue(nullptr);
}

void LocalTaskManager::initialize() {
}

void LocalTaskManager::start() {
}

void LocalTaskManager::shutdown() {
}

/*void LocalTaskManager::executeTask(Task* task) {
	if (executedTasks.put(task) != -1) {
		task->acquire();
	}
}*/

void LocalTaskManager::executeTask(Task* task) {
	/*int find = lastTaskAction.find(task);

	if (find != -1) {
		TaskAction* action = lastTaskAction.elementAt(find).getValue();

		if (action->getType() != action->EXECUTE) {
			task->acquire();
			executedTasks.add(task);
		}
	} else {
		task->acquire();
		executedTasks.add(task);
	}

	lastTaskAction.put(task, new TaskAction(TaskAction::EXECUTE, task, task->getNextExecutionTime()));*/

	executedTasks.add(task);
	task->acquire();

	/*if (executedTasks.put(task) != -1) {
		task->acquire();
	}*/

}

#ifdef CXX11_COMPILER

void LocalTaskManager::executeTask(Function<void()>&& function, const char* name) {
	TaskManager::executeTask(std::move(function), name);
}

void LocalTaskManager::executeTask(const Function<void()>& function, const char* name) {
	TaskManager::executeTask(function, name);
}

void LocalTaskManager::scheduleTask(Function<void()>&& function, const char* name, uint64 delay) {
	TaskManager::scheduleTask(std::move(function), name, delay);
}

void LocalTaskManager::scheduleTask(const Function<void()>& function, const char* name, uint64 delay) {
	TaskManager::scheduleTask(function, name, delay);
}

#endif


bool LocalTaskManager::getNextExecutionTime(const Task* task, AtomicTime& nextExecutionTime) {
	TaskAction* action = lastTaskAction.get(task);

	if (action == nullptr)
		return false;

	nextExecutionTime = action->getNextExecutionTime();

	return true;
}

void LocalTaskManager::scheduleTask(Task* task, uint64 delay) {
	if (task->isScheduled())
		throw IllegalArgumentException("task already scheduled");

	AtomicTime nextTime;

	if (delay != 0)
		nextTime.addMiliTime(delay);

	lastTaskAction.put(task, new TaskAction(TaskAction::SCHEDULE, task, nextTime));
}

/*void LocalTaskManager::scheduleTask(Task* task, uint64 delay) {
	if (task->isScheduled())
		throw IllegalArgumentException("task already scheduled");

	if (scheduledTasks.put(task) != -1) {
		task->acquire();

		if (delay != 0)
			task->updateExecutionTime(delay);

	#ifdef TRACE_TASKS
		task->setScheduleTrace();
	#endif
	}

	cancelledTasks.removeElement(task);
}*/

/*void LocalTaskManager::scheduleTask(Task* task, Time& time) {
	if (task->isScheduled())
		throw IllegalArgumentException("task already scheduled");

	if (scheduledTasks.put(task) != -1) {
		task->acquire();

		task->setExecutionTime(time);

	#ifdef TRACE_TASKS
		task->setScheduleTrace();
	#endif
	}

	cancelledTasks.removeElement(task);
}*/

void LocalTaskManager::scheduleTask(Task* task, const Time& time) {
	if (task->isScheduled())
		throw IllegalArgumentException("task already scheduled");

	lastTaskAction.put(task, new TaskAction(TaskAction::SCHEDULE, task, time));
}

/*void LocalTaskManager::rescheduleTask(Task* task, uint64 delay) {
	cancelTask(task);

	scheduleTask(task, delay);
}*/

void LocalTaskManager::rescheduleTask(Task* task, uint64 delay) {
	AtomicTime nextTime;

	if (delay != 0)
		nextTime.addMiliTime(delay);

	lastTaskAction.put(task, new TaskAction(TaskAction::RESCHEDULE, task, nextTime));
}

void LocalTaskManager::rescheduleTask(Task* task, const Time& time) {
	lastTaskAction.put(task, new TaskAction(TaskAction::RESCHEDULE, task, AtomicTime(time)));
}


/*void LocalTaskManager::rescheduleTask(Task* task, Time& time) {
	cancelTask(task);

	scheduleTask(task, time);
}*/

/*bool LocalTaskManager::cancelTask(Task* task) {
	if (!task->isScheduled())
		return false;

	if (scheduledTasks.removeElement(task)) {
		task->release();
	}

	return cancelledTasks.put(task) != -1;
}*/

bool LocalTaskManager::cancelTask(Task* task) {
	if (!task->isScheduled())
		return false;

	/*if (scheduledTasks.removeElement(task)) {
		task->release();
	}

	return cancelledTasks.put(task) != -1;*/

	//if

	TaskAction* action = lastTaskAction.get(task);

	if (action != nullptr) {
		if (action->getType() == TaskAction::CANCEL)
			return false;
	}

	lastTaskAction.put(task, new TaskAction(TaskAction::CANCEL, task, task->getNextExecutionTime()));

	return true;
}

Task* LocalTaskManager::getTask() {
	return nullptr;
}

bool LocalTaskManager::isTaskScheduled(const Task* task) {
	//return scheduledTasks.contains(task);

	const TaskAction* action = lastTaskAction.get(task);

	if (action == nullptr)
		return false;

	if (action->getType() == TaskAction::SCHEDULE ||
			action->getType() == TaskAction::RESCHEDULE)
		return true;

	return false;
}

bool LocalTaskManager::isTaskCancelled(const Task* task) {
	//return cancelledTasks.contains(task);

	const TaskAction* action = lastTaskAction.get(task);

	if (action == nullptr)
		return false;

	if (action->getType() == TaskAction::CANCEL)
		return true;

	return false;
}

void LocalTaskManager::mergeTasks(TaskManagerImpl* manager) {
	merging = true;

	/*manager->debug("executing " + String::valueOf(executedTasks.size()) +
			", adding " + String::valueOf(scheduledTasks.size()) +
			", canceling " + String::valueOf(cancelledTasks.size()) +" tasks");*/

	manager->executeTasks(executedTasks);

	executedTasks.removeAll();

	try {
		for (int i = 0; i < lastTaskAction.size(); ++i) {
			Task* task = lastTaskAction.elementAt(i).getKey();
			TaskAction* action = lastTaskAction.elementAt(i).getValue();

			switch (action->getType()) {
			case TaskAction::EXECUTE:
				//manager->executeTask(task);
				break;
			case TaskAction::SCHEDULE: {
				try {
					manager->scheduleTask(task, action->getNextExecutionTime().getTime());
				} catch (IllegalArgumentException& e) {
					//manager->error(e.getMessage() + " for " + task->toStringData());

					manager->rescheduleTask(task, action->getNextExecutionTime().getTime());
				}
				break;
			} case TaskAction::RESCHEDULE:
				manager->rescheduleTask(task, action->getNextExecutionTime().getTime());
				break;
			case TaskAction::CANCEL:
				manager->cancelTask(task);
				break;

			}
		}
	} catch (Exception& e) {
		Logger::console.error(e.getMessage());
	}

	/*manager->executeTasks(executedTasks);

	for (int i = 0; i < cancelledTasks.size(); ++i) {
		Task* task = cancelledTasks.get(i);

		manager->cancelTask(task);
	}

	cancelledTasks.removeAll();

	//Vector<Reference<Task*> > tasks = scheduledTasks;

	//scheduledTasks.removeAll();

	for (int i = 0; i < scheduledTasks.size(); ++i) {
		Task* task = scheduledTasks.get(i);

		try {
			manager->scheduleTask(task, task->getNextExecutionTime());
		} catch (IllegalArgumentException& e) {
			//manager->error(e.getMessage() + " for " + task->toStringData());

			manager->rescheduleTask(task, task->getNextExecutionTime());
		}

		task->release();
	}*/

	flushTasks();

	merging = false;
}

void LocalTaskManager::undoTasks() {
	for (int i = 0; i < executedTasks.size(); ++i)
		executedTasks.get(i)->release();

	/*for (int i = 0; i < scheduledTasks.size(); ++i)
		scheduledTasks.get(i)->release();*/


	flushTasks();
}

void LocalTaskManager::flushTasks() {
	executedTasks.removeAll();

	lastTaskAction.removeAll();

	/*scheduledTasks.removeAll();
	cancelledTasks.removeAll();*/
}

String LocalTaskManager::getInfo(bool print) {
	return "";
}

int LocalTaskManager::getScheduledTaskSize() {
	//return scheduledTasks.size();
	return 0;
}

int LocalTaskManager::getExecutingTaskSize() {
	//return executedTasks.size();
	return 0;
}

bool LocalTaskManager::isMerging() {
	return merging;
}