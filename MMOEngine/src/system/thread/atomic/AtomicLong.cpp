#include "AtomicLong.h"

AtomicLong::AtomicLong() : value{0} {
}

AtomicLong::AtomicLong(uint64 val) : value{val} {
}

AtomicLong::AtomicLong(const AtomicLong& val) : value{val.value.load(std::memory_order_relaxed)} {
}

AtomicLong& AtomicLong::operator=(const AtomicLong& v) {
	value.store(v.value.load(std::memory_order_relaxed));

	return *this;
}

AtomicLong& AtomicLong::operator=(const uint64 val) {
	value.store(val);

	return *this;
}

uint64 AtomicLong::increment() {
	return ++value;
}

uint64 AtomicLong::decrement() {
	return --value;
}

uint64 AtomicLong::add(uint64 val) {
	return value += val;
}

uint64 AtomicLong::compareAndSetReturnOld(uint64 oldval, uint64 newval) {
	uint64 val = oldval;

	value.compare_exchange_strong(val, newval);

	return val;
}

bool AtomicLong::compareAndSet(uint64 oldval, uint64 newval) {
	uint64 val = oldval;

	return value.compare_exchange_strong(val, newval);
}

uint64 AtomicLong::get() const {
	return value.load(std::memory_order_relaxed);
}

void AtomicLong::set(uint64 val) {
	while (!compareAndSet(value, val))
		;
}

AtomicLong::operator uint64() const {
	return value.load(std::memory_order_relaxed);
}

bool AtomicLong::operator==(const uint64 val) const {
	return val == value.load(std::memory_order_relaxed);
}

bool AtomicLong::toBinaryStream(sys::io::ObjectOutputStream* stream) {
	stream->writeLong(value);

	return true;
}

bool AtomicLong::parseFromBinaryStream(sys::io::ObjectInputStream* stream) {
	value = stream->readLong();

	return true;
}