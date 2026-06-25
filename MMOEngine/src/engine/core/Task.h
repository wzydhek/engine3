/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include <csignal>
#include "system/lang.h"
#include "system/util/Timer.h"
#include "system/thread/atomic/AtomicTime.h"

//#define COLLECT_TASKSTATISTICS

namespace engine {

  namespace stm {
  	  class LocalTaskManager;
  	  class TransactionalTaskManager;
  }

  namespace core {

	class TaskManager;
	class TaskScheduler;
	class TimedTaskQueue;
	class TaskManagerImpl;

	class Task : public PriorityQueueEntry, public Runnable, public Object {
	protected:
		AtomicReference<TaskScheduler*> taskScheduler;

		Time nextExecutionTime;

		String customTaskQueue;

	#ifdef TRACE_TASKS
		StackTrace* scheduleTrace;
	#endif

		AtomicLong period;

	#ifdef COLLECT_TASKSTATISTICS
		int statsSampleRate;
	#endif

		uint64 lastElapsedTime = 0;
		String taskName;

		int priority;
		bool runInScheduler = false;

	  public:
		Task();
		Task(uint64 mtime);
		Task(const Time& time);

		~Task();

		bool isScheduled() const;

		bool cancel();
		bool cancelNonTransactionally();

		void schedule(uint64 delay = 0);
		void schedule(Time& time);

		void scheduleInIoScheduler(uint64 delay = 0);
		void scheduleInIoScheduler(Time& time);

		void scheduleNonTransactionally(uint64 delay = 0);

		void schedulePeriodic(uint64 delay, uint64 period);
		void schedulePeriodic(Time& time, uint64 period);

		void reschedule(uint64 delay = 0);
		void rescheduleNonTransactionally(uint64 delay = 0);
		void reschedule(Time& time);

		void rescheduleInIoScheduler(uint64 delay = 0);
		void rescheduleInIoScheduler(Time& time);

		void execute();
		void executeInThread();

		virtual const char* getTaskName();

		int compareTo(const PriorityQueueEntry* node) const;

		virtual String toStringData() const;

	protected:
		void initialize();

		void doExecute();

		void setExecutionTime(const Time& time);

		void updateExecutionTime(uint64 mtime = 0);

		const Time& getNextExecutionTime() const;

	public:
		TaskScheduler* getTaskScheduler();

		const TaskScheduler* getTaskScheduler() const;

		int getPriroty() const;

		bool isPeriodic() const;

		bool doRunInScheduler() const;

		void setRunInScheduler(bool val);

		bool setTaskScheduler(TaskScheduler* scheduler);

		bool clearTaskScheduler();

		void setPriority(int priority);

		uint64 getPeriod() const;

		void setPeriod(uint64 per);

		void setCustomTaskQueue(const String& queue);

		void setCustomTaskQueue(String&& queue);

		const String& getCustomTaskQueue() const;

		void setTaskName(const char* name);

		void setTaskName(const String& name);

		void setTaskName(String&& name);

	#ifdef COLLECT_TASKSTATISTICS
		void setStatsSample(bool val);

		int getStatsSampleRate() const;
	#endif

		uint64 getLastElapsedTime() const;

	#ifdef TRACE_TASKS
		void setScheduleTrace();

		void printScheduleTrace();
	#endif

		friend class TimedTaskQueue;
		friend class TaskScheduler;
		friend class TaskWorkerThread;
		friend class engine::stm::LocalTaskManager;
		friend class engine::stm::TransactionalTaskManager;
		friend class engine::core::Core;
		friend class engine::core::TaskManagerImpl;
	};

  } // namespace core
} // namespace engine

using namespace engine::core;
