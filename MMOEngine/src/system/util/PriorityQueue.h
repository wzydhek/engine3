/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include <atomic>
#include "system/platform.h"
#include "system/lang/Exception.h"

namespace sys {
  namespace util {

	class PriorityQueue;

	class PriorityQueueEntry {
		PriorityQueueEntry* parentNode;

		PriorityQueueEntry* leftNode;
		PriorityQueueEntry* rightNode;

		int	npl{};

		std::atomic<bool> enqueued{false};

	public:
		PriorityQueueEntry(PriorityQueueEntry* parent = nullptr, PriorityQueueEntry* lnode = nullptr,
				PriorityQueueEntry* rnode = nullptr, int np = 0);

		virtual ~PriorityQueueEntry() {
			//enqueued = false;
		}

		virtual int compareTo(const PriorityQueueEntry* node) const = 0;

		void clear();

		void setQueued();

		void setUnqueued();

		bool isQueued() const;

		friend class PriorityQueue;
	};

	class PriorityQueue {
	private:
		PriorityQueueEntry* root;

		int count;

		uint64 pushedEntries;
		uint64 poppedEntries;
		uint64 removedEntries;

	public:
		PriorityQueue();
		PriorityQueue(const PriorityQueue& heap);

		virtual ~PriorityQueue();

		void add(PriorityQueueEntry* node);

		void merge(PriorityQueue& heap);

		const PriorityQueueEntry* peak() const;
		PriorityQueueEntry* poll();

		bool remove(PriorityQueueEntry* node);

		void clear();
		void clearWithoutTraverse();

		bool isEmpty() const;

		bool isFull() const;

		int size() const NO_THREAD_SAFETY_ANALYSIS;

		uint64 getPushedEntries() const;

		uint64 getPoppedEntries() const;

		uint64 getRemovedEntries() const;

	private:
		PriorityQueueEntry* merge(PriorityQueueEntry* h1, PriorityQueueEntry* h2) const;
		PriorityQueueEntry* merge1(PriorityQueueEntry* h1, PriorityQueueEntry* h2) const;

		void swapChildren(PriorityQueueEntry* node) const;
		void reclaimMemory(PriorityQueueEntry* node) const;
	};

  } // namespace util
} // namespace sys;

using namespace sys::util;
