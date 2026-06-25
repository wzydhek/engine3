#include "ReferenceCounter.h"

ReferenceCounter::ReferenceCounter() {
}

ReferenceCounter::ReferenceCounter(uint32 count) : _references(count) {
}

ReferenceCounter::ReferenceCounter(const ReferenceCounter& counter) : _references(counter._references.load(std::memory_order_relaxed)) {
}

ReferenceCounter& ReferenceCounter::operator=(const ReferenceCounter& counter) {
	_references.store(counter._references.load(std::memory_order_relaxed));

	return *this;
}

uint32 ReferenceCounter::increaseCount() volatile {
	return _references.fetch_add(2, std::memory_order_acq_rel) + 2;
}

void ReferenceCounter::setLowestBit() volatile {
	uint32 oldVal, newVal;

	do {
		oldVal = _references.load(std::memory_order_acquire);

		newVal = oldVal | 1;
	} while (!_references.compare_exchange_weak(oldVal, newVal, std::memory_order_release, std::memory_order_relaxed));
}

void ReferenceCounter::clearLowestBit() volatile {
	uint32 oldVal, newVal;

	do {
		oldVal = _references.load(std::memory_order_acquire);

		newVal = oldVal & uint64(0xFFFFFFFFFFFFFFFE);
	} while (!_references.compare_exchange_weak(oldVal, newVal, std::memory_order_release, std::memory_order_relaxed));
}

bool ReferenceCounter::tryFinalDecrement() volatile {
	uint32 oldVal, newVal;

	oldVal = _references.load(std::memory_order_acquire);

	if (oldVal != 2)
		return false;

	newVal = 1;

	return _references.compare_exchange_weak(oldVal, newVal, std::memory_order_release, std::memory_order_relaxed);
}

uint32 ReferenceCounter::decrementAndTestAndSet() volatile {
	uint32 oldVal, newVal;

	do {
		oldVal = _references.load(std::memory_order_acquire);

		newVal = oldVal - 2;

		if (newVal == 0)
			newVal = 1;
	} while (!_references.compare_exchange_weak(oldVal, newVal, std::memory_order_release, std::memory_order_relaxed));

	return ((oldVal - newVal) & 1);
}

uint32 ReferenceCounter::getReferenceCount(std::memory_order o) volatile const {
	return _references.load(o);
}

void ReferenceCounter::reset() volatile {
	_references.store(0);
}