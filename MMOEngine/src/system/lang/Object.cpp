/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "ref/Reference.h"

#include "engine/core/ManagedReference.h"

#ifdef TRACE_REFERENCES
AtomicInteger ReferenceIdCounter::nextID;
#endif

Object::Object() : Variable() {
#ifdef MEMORY_PROTECTION
	_destroying = new AtomicBoolean(false);
#else
#endif

	referenceCounters = nullptr;

	//MemoryManager::getInstance()->create(this);

#ifdef TRACE_REFERENCES
	/*referenceHolders = new VectorMap<uint64, StackTrace*>();
	referenceHolders->setNullValue(nullptr);*/
	referenceHolders = nullptr;
#endif
}

Object::Object(const Object& obj) : Variable() {
#ifdef MEMORY_PROTECTION
	_destroying = new AtomicBoolean(false);
#else
#endif

	referenceCounters = nullptr;

	//MemoryManager::getInstance()->create(this);

#ifdef TRACE_REFERENCES
	/*referenceHolders = new VectorMap<uint64, StackTrace*>();
	referenceHolders->setNullValue(nullptr);*/
	referenceHolders = nullptr;
#endif
}

Object::~Object() NO_THREAD_SAFETY_ANALYSIS {
#ifdef TRACE_REFERENCES
	if (referenceHolders != nullptr) {
		for (int i = 0; i < referenceHolders->size(); ++i)
			delete referenceHolders->get(i);
	}
#endif

	auto counters = referenceCounters;

	if (counters != nullptr) {
		E3_ASSERT((counters->getStrongReferenceCount() % 2) != 0);

		if (counters->decrementAndTestAndSetWeakCount() != 0) {
			referenceCounters = nullptr;

			delete counters;
			//referenceCounters = nullptr;
		}

	}

#ifdef MEMORY_PROTECTION
	delete _destroying;
	_destroying = nullptr;
#endif

	finalize();

#ifdef TRACE_REFERENCES
	delete referenceHolders;
	referenceHolders = nullptr;
#endif

	//deletedByTrace = new StackTrace();
}

/*
bool Object::tryAcquire() {
	WMB();

	if (_destroying && getReferenceCount() == 0) {
		printf("try Acquire failed\n");

		return false;
	} else
		increaseCount();

	return true;
}
*/
/*
void Object::acquire() {
	if (referenceCounters == nullptr) {
		StrongAndWeakReferenceCount* newCount = new StrongAndWeakReferenceCount(0, 1);

		if (!referenceCounters.compareAndSet(nullptr, newCount)) {
			delete newCount;
		}
	}

	referenceCounters->increaseStrongCount();
}

void Object::release() {
	if (referenceCounters->decrementAndTestAndSetStrongCount() != 0) {
		if (notifyDestroy()) {
#ifdef WITH_STM
			MemoryManager::getInstance()->reclaim(this);
#else
			destroy();
#endif
		}
	}
}
*/
void Object::_destroyIgnoringCount() {
	if (notifyDestroy()) {
#ifdef WITH_STM
		MemoryManager::getInstance()->reclaim(this);
#else
		destroy();
#endif
	}
}

void Object::destroy() NO_THREAD_SAFETY_ANALYSIS {
#ifdef MEMORY_PROTECTION
	_destroying->set(true);
#else
#endif

	//printf("deleting in ::destroy\n");

#ifdef WITH_STM
	free();
#else
	Object::free();
#endif
}

void Object::free() {
	delete this;
}

#ifdef TRACE_REFERENCES
void Object::addHolder(uint64 obj) const {
#ifndef WITH_STM
	Locker locker(&referenceMutex);
#endif

	StackTrace* trace = new StackTrace();

	if (referenceHolders == nullptr) {
		referenceHolders = new VectorMap<uint64, StackTrace*>();
		referenceHolders->setNullValue(nullptr);
	}

	referenceHolders->put(obj, trace);
}

void Object::removeHolder(uint64 obj) const {
#ifndef WITH_STM
	Locker locker(&referenceMutex);
#endif
	if (referenceHolders == nullptr) {
		return;
	}

	StackTrace* trace = referenceHolders->get(obj);

	if (trace != nullptr) {
		delete trace;
		referenceHolders->drop(obj);
	}
}

void Object::printReferenceHolders() const {
	if (referenceHolders == nullptr) {
		return;
	}

	for (int i = 0; i < referenceHolders->size(); ++i) {
		StackTrace* trace = referenceHolders->get(i);

		trace->print();
	}
}
#endif

String Object::toString() const {
	char buf[20];

	snprintf(buf, 20, "%p", reinterpret_cast<const void*>(this));

	return String(buf);
}

#ifdef CXX11_COMPILER
Object::Object(Object&& o) : referenceCounters(nullptr) {
	E3_ASSERT(o.referenceCounters == nullptr && "Cant move objects that are referenced");

#ifdef TRACE_REFERENCES
	referenceHolders = nullptr;
#endif
}

Object& Object::operator = (Object && o) {
	if (this == &o)
		return *this;

	E3_ASSERT(o.referenceCounters == nullptr && "Cant move objects that are referenced");

	return *this;
}
#endif

Object& Object::operator = (const Object& o) {
	if (this == &o)
		return *this;

	return *this;
}

Object* Object::clone() {
	E3_ABORT("clone method not declared");

	return nullptr;
}

Object* Object::clone(void* object) {
	return clone();
}

int Object::compareTo(Object* object) {
	if (this == object)
		return 0;
	else if (this < object)
		return 1;
	else
		return -1;
}

bool Object::notifyDestroy() {
	return true;
}

bool Object::toBinaryStream(ObjectOutputStream* stream) {
	return false;
}

bool Object::parseFromBinaryStream(ObjectInputStream* stream) {
	return false;
}

void Object::createStrongAndWeakReferenceCount() const {
	auto newCount = new StrongAndWeakReferenceCount(0, 2, const_cast<Object*>(this));

	if (!referenceCounters.compareAndSet(nullptr, newCount)) {
		delete newCount;

		referenceCounters->increaseStrongCount();
	} else {
		newCount->increaseStrongCount();
	}
}

void Object::acquire() const {
	auto counters = referenceCounters.get();

	if (counters == nullptr) {
		createStrongAndWeakReferenceCount();
	} else {
		counters->increaseStrongCount();
	}
}

bool Object::release() const {
	if (referenceCounters->decrementAndTestAndSetStrongCount() != 0) {
		if (const_cast<Object*>(this)->notifyDestroy()) {
#ifdef WITH_STM
			MemoryManager::getInstance()->reclaim(this);
#else
			const_cast<Object*>(this)->destroy();

			return true;
#endif
		}
	}

	return false;
}

bool Object::tryFinalRelease() const {
	if (referenceCounters->tryStrongFinalDecrement()) {
		if (const_cast<Object*>(this)->notifyDestroy()) {
#ifdef WITH_STM
			MemoryManager::getInstance()->reclaim(this);
#else
			const_cast<Object*>(this)->destroy();

			return true;
#endif
		}
	}

	return false;
}

void Object::_markAsDestroyed() {
	if (referenceCounters != nullptr)
		referenceCounters->markAsDestroyed();
}

uint32 Object::getReferenceCount() {
	if (referenceCounters == nullptr)
		return 0;
	else
		return referenceCounters->getStrongReferenceCount();
}

StrongAndWeakReferenceCount* Object::requestWeak() {
	if (referenceCounters == nullptr) {
		auto newCount = new StrongAndWeakReferenceCount(0, 2, this);

		if (!referenceCounters.compareAndSet(nullptr, newCount))
			delete newCount;
	}

	return referenceCounters.get();
}
