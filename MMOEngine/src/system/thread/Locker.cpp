#include "Locker.h"

Locker::Locker(Locker&& locker) : lockable(locker.lockable) {
	locker.lockable = nullptr;
}

Locker::Locker(Lockable* lock) ACQUIRE(lock) {
	const auto doLock = !lock->isLockedByCurrentThread();

	if (doLock) {
		lockable = lock;

		lock->lock();
	} else {
		lockable = nullptr;
	}
}

Locker::Locker(Mutex* lock) ACQUIRE(lock) {
	const auto doLock = !lock->isLockedByCurrentThread();

	if (doLock) {
		lockable = lock;

		lock->lock();
	} else {
		lockable = nullptr;
	}
}

Locker::Locker(ReadWriteLock* lock) ACQUIRE(lock) {
	const auto doLock = !lock->isLockedByCurrentThread();

	if (doLock) {
		lockable = lock;

		lock->lock();
	} else {
		lockable = nullptr;
	}
}

Locker::Locker(Mutex* lock, Mutex* cross) ACQUIRE(lock) {
	const auto doLock = !lock->isLockedByCurrentThread();

	if (doLock) {
		lockable = lock;

		if (lock != cross) {
			assert(cross->isLockedByCurrentThread());

			lock->lock(cross);
		} else {
			lock->lock();
		}
	} else {
		lockable = nullptr;
	}
}

Locker::Locker(ReadWriteLock* lock, ReadWriteLock* cross) ACQUIRE(lock) {
	const auto doLock = !lock->isLockedByCurrentThread();

	if (doLock) {
		lockable = lock;

		if (lock != cross) {
			assert(cross->isLockedByCurrentThread());

			lock->lock(cross);
		} else {
			lock->lock();
		}
	} else {
		lockable = nullptr;
	}
}

Locker::Locker(ReadWriteLock* lock, Mutex* cross) ACQUIRE(lock) {
	const auto doLock = !lock->isLockedByCurrentThread();

	if (doLock) {
		lockable = lock;

		if (static_cast<Lockable*>(lock) != static_cast<Lockable*>(cross)) {
			assert(cross->isLockedByCurrentThread());

			lock->lock(cross);
		} else {
			lock->lock();
		}
	} else {
		lockable = nullptr;
	}
}

Locker::Locker(Mutex* lock, ReadWriteLock* cross) ACQUIRE(lock) {
	const auto doLock = !lock->isLockedByCurrentThread();

	if (doLock) {
		lockable = lock;

		if (static_cast<Lockable*>(lock) != static_cast<Lockable*>(cross)) {
			assert(cross->isLockedByCurrentThread());

			lock->lock(cross);
		} else {
			lock->lock();
		}
	} else {
		lockable = nullptr;
	}
}

Locker::Locker(Lockable* lock, Lockable* cross) ACQUIRE(lock) {
	const auto doLock = !lock->isLockedByCurrentThread();

	if (doLock) {
		lockable = lock;

		if (lock != cross) {
			assert(cross->isLockedByCurrentThread());

			lock->lock(cross);
		} else {
			lock->lock();
		}
	} else {
		lockable = nullptr;
	}
}

Locker::~Locker() RELEASE() {
	if (lockable != nullptr) {
		lockable->unlock();
	}
}

void Locker::release() RELEASE() {
	if (lockable != nullptr) {
		lockable->unlock();

		lockable = nullptr;
	}
}