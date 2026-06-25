/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/core/Task.h"
#include "engine/core/TaskManager.h"

namespace engine {
    namespace core {
        class TaskManagerImpl;
    }
}

namespace engine {
  namespace stm {

   class TaskReference {
	   Task* task;

   public:
	   TaskReference();

	   TaskReference(const Task* t);

	   TaskReference(const TaskReference& t);

	   bool toBinaryStream(ObjectOutputStream* stream);

	   /*static bool parseFromString(T* address, const sys::lang::String& value, int version = 0) {
	   		return address->parseFromString(value, version);
	   	}*/

	   bool parseFromBinaryStream(ObjectInputStream* stream);

	   TaskReference& operator=(const TaskReference& t);

	   int compareTo(const TaskReference& ref) const;

	   operator Task*();

	   Task* operator->();

	   Task* getTask();


   };

    class TaskAction : public Object {
    	int type;
    	Reference<Task*> task;
    	AtomicTime nextExecutionTime;

    public:
    	const static int CANCEL = 1;
    	const static int SCHEDULE = 2;
    	const static int EXECUTE = 3;
    	const static int RESCHEDULE = 4;

    public:
		TaskAction(const TaskAction& a);

    	TaskAction(int type, Reference<Task*> task, const AtomicTime& nextExecutionTime);

    	TaskAction& operator=(const TaskAction& a);

    	int getType() const;

    	Task* getTask() const;

    	AtomicTime& getNextExecutionTime();

    };

  	class LocalTaskManager : public TaskManager {
  		Vector<Task*> executedTasks;

  		/*SortedVector<Task*> scheduledTasks;
  		SortedVector<Task*> cancelledTasks;*/

  		//Vector<TaskAction*> taskLog;
  		VectorMap<TaskReference, Reference<TaskAction*> > lastTaskAction;

  		bool merging;

  	  public:
  		LocalTaskManager();

  		void initialize();

  		void start();

  		void shutdown();

  		void executeTask(Task* task);

#ifdef CXX11_COMPILER
		void executeTask(Function<void()>&& function, const char* name);

		void executeTask(const Function<void()>& function, const char* name);

		void scheduleTask(Function<void()>&& function, const char* name, uint64 delay);

		void scheduleTask(const Function<void()>& function, const char* name, uint64 delay);
#endif

  		void scheduleTask(Task* task, uint64 delay);
  		void scheduleTask(Task* task, const Time& time);

  		void rescheduleTask(Task* task, uint64 delay);
  		void rescheduleTask(Task* task, const Time& time);

  		bool cancelTask(Task* task);

  		Task* getTask();

  		bool isTaskScheduled(const Task* task);

  		bool isTaskCancelled(const Task* task);

		void mergeTasks(TaskManagerImpl* manager);

  		void flushTasks();

  		void undoTasks();

  		String getInfo(bool print);

  		int getScheduledTaskSize();

  		int getExecutingTaskSize();

  		bool getNextExecutionTime(const Task* task, AtomicTime& nextExecutionTime);

  		bool isMerging();
  	  };

  } // namespace stm
} // namespace engine

using namespace engine::stm;
