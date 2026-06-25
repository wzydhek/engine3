#include "StrongAndWeakReferenceCount.h"

StrongAndWeakReferenceCount::StrongAndWeakReferenceCount(uint32 strongCount, uint32 weakCount, Object* obj) : strongReferenceCount(strongCount), weakReferenceCount(weakCount), object(obj) {
}

StrongAndWeakReferenceCount::StrongAndWeakReferenceCount(const StrongAndWeakReferenceCount& r) : strongReferenceCount(r.strongReferenceCount), weakReferenceCount(r.weakReferenceCount), object(r.object) {
}

StrongAndWeakReferenceCount& StrongAndWeakReferenceCount::operator=(const StrongAndWeakReferenceCount& r) {
	if (this == &r)
		return *this;

	strongReferenceCount = r.strongReferenceCount;
	weakReferenceCount = r.weakReferenceCount;
	object = r.object;

	return *this;
}

void StrongAndWeakReferenceCount::markAsDestroyed() volatile {
	strongReferenceCount.increaseCount();
	strongReferenceCount.setLowestBit();
}

uint32 StrongAndWeakReferenceCount::increaseStrongCount() volatile {
	return strongReferenceCount.increaseCount();
}

uint32 StrongAndWeakReferenceCount::increaseWeakCount() volatile {
	return weakReferenceCount.increaseCount();
}

uint32 StrongAndWeakReferenceCount::decrementAndTestAndSetStrongCount() {
	uint32 ret = strongReferenceCount.decrementAndTestAndSet();

	if (ret != 0) {
		object = nullptr;
	}

	return ret;
}

bool StrongAndWeakReferenceCount::tryStrongFinalDecrement() {
	bool ret = strongReferenceCount.tryFinalDecrement();

	if (ret) {
		object = nullptr;
	}

	return ret;
}

uint32 StrongAndWeakReferenceCount::decrementAndTestAndSetWeakCount() volatile {
	return weakReferenceCount.decrementAndTestAndSet();
}

void StrongAndWeakReferenceCount::clearStrongCountLowestBit() volatile {
	strongReferenceCount.clearLowestBit();
}

uint32 StrongAndWeakReferenceCount::getStrongReferenceCount() volatile const {
	return strongReferenceCount.getReferenceCount();
}

void StrongAndWeakReferenceCount::setObject(Object* obj) {
	object = obj;
}

Object* StrongAndWeakReferenceCount::getObject() const {
	return object;
}

void StrongAndWeakReferenceCount::resetCountsToZero() {
	strongReferenceCount.reset();
	weakReferenceCount.reset();
}