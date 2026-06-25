/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "system/mm/MemoryManager.h"
#include "engine/util/Singleton.h"
#include "engine/stm/task/TransactionalTaskManager.h"
#include "engine/stm/orb/TransactionalObjectManager.h"
#include "engine/stm/service/TransactionalSocketManager.h"
#include "engine/stm/service/TransactionalBaseClientManager.h"
#include "Transaction.h"
#include "TransactionalReference.h"
#include "TransactionalWeakReference.h"

namespace engine {
  namespace stm {

	class TransactionalMemoryManager : public Singleton<TransactionalMemoryManager>, public MemoryManager, public Logger {
		TransactionalTaskManager* taskManager;

		TransactionalObjectManager* objectManager;

		TransactionalSocketManager* socketManager;

		TransactionalBaseClientManager* baseClientManager;

		ThreadLocal<Reference<Transaction*>* > currentTransaction;

		AtomicLong transactionID;

		AtomicInteger startedTransactions;
		AtomicInteger commitedTransactions;
		AtomicInteger totalCommitedTransactions;
		AtomicInteger abortedTransactions;
		AtomicInteger retryConflicts;
		AtomicInteger deletedTransactions;
		AtomicInteger failedOnAcquireRW;
		AtomicInteger failedToResolveConflict;
		AtomicInteger failedToResolveConflictReleasedTransaction;
		AtomicInteger failedToNotUNDECIDED;
		AtomicInteger failedToExceptions;
		AtomicInteger failedCompetingCommited;

		/*AtomicInteger createdHandles;
		AtomicInteger deletedHandles;*/

#ifdef	MEMORY_PROTECTION
		ProtectedHeap objectHeap;
#endif
		Mutex heapLock;

		bool reclaiming;

		ThreadLocal<Vector<Object*>* > reclamationList;

		ReadWriteLock blockLock;

	public:
		static void commitPureTransaction(Transaction* transaction);

		static void closeThread();

		Object* create(size_t size);
		void destroy(Object* object);

		Transaction* startTransaction();

		void printStatistics();

		TransactionalTaskManager* getTaskManager();

		TransactionalObjectManager* getObjectManager();

		TransactionalSocketManager* getSocketManager();

		TransactionalBaseClientManager* getBaseClientManager();

		void blockTransactions() ACQUIRE(Transaction::blockLock);

		void increaseFailedByExceptions();

		/*inline void increaseCreatedHandles() {
			createdHandles.increment();
		}

		inline void increaseDeletedHandles() {
			deletedHandles.increment();
		}*/

		void increaseFailedByObjectChanged();

		void increaseFailedByCompetingCommited();

		void unblockTransactions() RELEASE(Transaction::blockLock);

		void retryTransaction();

		void setKernelMode();
		void setUserMode();

	protected:
		TransactionalMemoryManager();

		~TransactionalMemoryManager();

		Transaction* getTransaction();

		void commitTransaction();

		void abortTransaction();

		void setCurrentTransaction(Transaction* transaction);

		void reclaim(Object* object);

		void reclaimObjects(int objectsToSpare = 0, int maxObjectsToReclaim = 0);

		void increaseDeletedTransactions();

		Vector<Object*>* getReclamationList();

		friend class SingletonWrapper<TransactionalMemoryManager>;
		friend class Transaction;
};

  } // namespace stm
} // namespace engine

using namespace engine::stm;

#include "TransactionalObjectHeader.h"
#include "engine/stm/mm/TransactionalObjectCloner.h"
