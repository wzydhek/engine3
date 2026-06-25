/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "system/lang/Time.h"

#include "Thread.h"

#include "Lockable.h"

Lockable::Lockable() {
	threadLockHolder = nullptr;

#ifdef TRACE_LOCKS
	trace = nullptr;
	unlockTrace = nullptr;

	doTrace = true;
#endif

	//lockTime = new Time();

#ifdef LOG_LOCKS
	currentCount = 0;

	lockCount = 0;

	doLog = true;
#endif
}

Lockable::Lockable(const String& s) {
	threadLockHolder = nullptr;

	//lockName = s;

#ifdef TRACE_LOCKS
	trace = nullptr;
	unlockTrace = nullptr;

	doTrace = true;
#endif

	//lockTime = new Time();

#ifdef LOG_LOCKS
	currentCount = 0;

	lockCount = 0;

	doLog = true;
#endif
}

Lockable::~Lockable() {
#ifdef TRACE_LOCKS
	if (trace != nullptr) {
		delete trace;
		trace = nullptr;
	}

	if (unlockTrace != nullptr) {
		delete unlockTrace;
		unlockTrace = nullptr;
	}
#endif

	//delete lockTime;
}

void Lockable::traceDeadlock(const char* modifier) {
#ifdef TRACE_LOCKS
	System::out << "[" << Thread::getCurrentThread()->getName() << "] (" << Time::currentNanoTime() << " nsec) WARNING" << "[" << lockName << "] unable to access "
				<< modifier << "lock #" << currentCount << " at\n";
#endif

	StackTrace::printStackTrace();

#ifdef TRACE_LOCKS
	if (trace != nullptr) {
		System::out << "[" << threadLockHolder->getName() << "] locked at " << lockTime.getMiliTime() << " by\n";
		trace->print();
	} else {
		System::out << "no previous stackTrace created\n";
	}
#endif

	while (true) {
		Thread::sleep(100);
	}
}

uint64 Lockable::lockAcquiring(const char* modifier) {
#ifdef LOG_LOCKS
	int cnt = lockCount.increment();

	if (doLog)
		System::out << "(" << Time::currentNanoTime() << " nsec) [" << lockName << "] acquiring " << modifier << "lock #" << cnt << "\n";
#endif

#ifdef TRACE_BLOCK_TIME
	return Time::currentNanoTime(Time::MONOTONIC_TIME);
#else
	return 0;
#endif
}

uint64 Lockable::lockAcquiring(Lockable* lockable, const char* modifier) {
#ifdef LOG_LOCKS
	int cnt = lockCount.increment();

	if (doLog)
		System::out << "(" << Time::currentNanoTime() << " nsec) [" << lockName << " (" << lockable->lockName << ")] acquiring cross " << modifier << "lock #" << cnt << "\n";
#endif

#ifdef TRACE_BLOCK_TIME
	return Time::currentNanoTime(Time::MONOTONIC_TIME);
#else
	return 0;
#endif
}

uint64 Lockable::lockAcquired(const char* modifier) {
#ifdef LOG_LOCKS
	currentCount = cnt;

	if (doLog)
		System::out << "(" << Time::currentNanoTime() << " nsec) [" << lockName << "] acquired " << modifier << "lock #" << cnt << "\n";
#endif

#ifdef TRACE_LOCKS
	if (modifier[0] != 'r')
		refreshTrace();
#endif

	if (modifier[0] != 'r')
		threadLockHolder.set(Thread::getCurrentThread(), std::memory_order_relaxed);

#ifdef TRACE_BLOCK_TIME
	return Time::currentNanoTime(Time::MONOTONIC_TIME);
#else
	return 0;
#endif
}

uint64 Lockable::lockAcquired(Lockable* lockable, const char* modifier) {
#ifdef LOG_LOCKS
	currentCount = cnt;

	if (doLog)
		System::out << "(" << Time::currentNanoTime() << " nsec) [" << lockName << " (" << lockable->lockName << ")] acquired cross " << modifier << "lock #" << cnt << "\n";
#endif

#ifdef TRACE_LOCKS
	if (modifier[0] != 'r')
		refreshTrace();
#endif

	if (modifier[0] != 'r')
		threadLockHolder.set(Thread::getCurrentThread(), std::memory_order_relaxed);

#ifdef TRACE_BLOCK_TIME
	return Time::currentNanoTime(Time::MONOTONIC_TIME);
#else
	return 0;
#endif
}

void Lockable::lockReleasing(const char* modifier) {
	if (modifier[0] != 'r') {
		threadLockHolder.set(nullptr, std::memory_order_relaxed);
	}

#ifdef TRACE_LOCKS
	if (modifier[0] != 'r') {
		deleteTrace();

		refreshUnlockTrace();
	}
#endif

#ifdef LOG_LOCKS
	if (doLog)
		System::out << "(" << Time::currentNanoTime() << " nsec) [" << lockName << "] releasing " << modifier << "lock #" << currentCount << "\n";
#endif
}

void Lockable::lockReleased(const char* modifier) {
#ifdef LOG_LOCKS
	if (doLog)
		System::out << "(" << Time::currentNanoTime() << " nsec) [" << lockName << "] released " << modifier << "lock #" << currentCount << "\n";
#endif
}

void Lockable::refreshTrace() {
#ifdef TRACE_LOCKS
	if (doTrace) {
		if (trace != nullptr)
			delete trace;

		trace = new StackTrace();
	}
#endif
}

void Lockable::deleteTrace() {
#ifdef TRACE_LOCKS
	if (doTrace) {
		if (trace != nullptr) {
			delete trace;
			trace = nullptr;
		}
	}
#endif
}

void Lockable::refreshUnlockTrace() {
#ifdef TRACE_LOCKS
	if (doTrace) {
		if (unlockTrace != nullptr)
			delete unlockTrace;

		unlockTrace = new StackTrace();
	}
#endif
}

void Lockable::deleteUnlockTrace() {
#ifdef TRACE_LOCKS
	if (doTrace) {
		if (unlockTrace != nullptr) {
			delete unlockTrace;
			unlockTrace = nullptr;
		}
	}
#endif
}

void Lockable::clearCurrentLockHolder() {
	threadLockHolder.set(nullptr, std::memory_order_relaxed);
}

void Lockable::setCurrentLockHolder(Thread* thread) {
	threadLockHolder.set(thread, std::memory_order_relaxed);
}

bool Lockable::isLockedByCurrentThread() const {
	return threadLockHolder.get() == Thread::getCurrentThread();
}

bool Lockable::isReadLocked() const {
	return readLockCount > 0;
}

Thread* Lockable::getLockHolderThread() {
	return threadLockHolder.get();
}

// setters
void Lockable::setLockName(const String& s) {
	// lockName = s;
}

void Lockable::setLockLogging(bool dolog) {
#ifdef LOG_LOCKS
	doLog = dolog;
#endif
}

void Lockable::setLockTracing(bool tracing) {
#ifdef TRACE_LOCKS
	doTrace = tracing;
#endif
}