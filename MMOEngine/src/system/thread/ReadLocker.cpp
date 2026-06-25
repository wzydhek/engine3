#include "ReadLocker.h"

ReadLocker::ReadLocker(ReadLocker&& locker) : lockable(locker.lockable) {
	locker.lockable = nullptr;
}

ReadLocker::ReadLocker(const ReadWriteLock* lock) ACQUIRE_SHARED(lock) {
	const auto doLock = !lock->isLockedByCurrentThread();

	if (doLock) {
		lockable = lock;

		const_cast<ReadWriteLock*>(lock)->rlock();
	} else {
		lockable = nullptr;
	}
}

ReadLocker::~ReadLocker() RELEASE() {
	if (lockable != nullptr) {
		const_cast<ReadWriteLock*>(lockable)->runlock();
	}
}

void ReadLocker::release() RELEASE() {
	if (lockable != nullptr) {
		const_cast<ReadWriteLock*>(lockable)->runlock();

		lockable = nullptr;
	}
}