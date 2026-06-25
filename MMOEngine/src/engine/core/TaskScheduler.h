/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include <atomic>
#include "system/util/SynchronizedHashTable.h"
#include "engine/log/Logger.h"
#include "Task.h"
#include "TimedTaskQueue.h"

namespace engine {
  namespace core {

	class TaskScheduler : public Thread, public Object, public Logger {
		TaskManager* taskManager;

		TimedTaskQueue tasks;

		AtomicBoolean doRun;

		Mutex blockMutex;

		HashTable<String, uint64> tasksCount;
		ReadWriteLock tasksCountGuard;
		AtomicBoolean pause;

	protected:
		void prepareTask(Task* task);

	public:
		TaskScheduler();
		TaskScheduler(const String& s);

		virtual ~TaskScheduler();

		void start();

		void run();

		void stop();

		void setPause(bool val);

		bool scheduleTask(Task* task, uint64 delay = 0);
		bool scheduleTask(Task* task, const Time& time);

		bool cancelTask(Task* task);

		void addSchedulerTasks(TaskScheduler* scheduler);

		HashTable<String, uint64> getTasksCount();

		void flushTasks();

		void clearTasks();

		void fixQueue();

		int getQueueSize() const;

		uint64 getPushedTasks() const;

		uint64 getPoppedTasks() const;

		uint64 getRemovedTasks() const;

		void printTasks();

		TaskManager* getTaskManager();

		void setTaskManager(TaskManager* manager);

		Mutex* getBlockMutex();
	};

  } // namespace core
} // namespace engine

using namespace engine::core;
