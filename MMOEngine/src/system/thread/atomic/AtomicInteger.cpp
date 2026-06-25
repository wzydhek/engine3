#include "AtomicInteger.h"

AtomicInteger::AtomicInteger() {
}

AtomicInteger::AtomicInteger(uint32 val) : value(val) {
}

AtomicInteger::AtomicInteger(const AtomicInteger& v) : value{v.value.load(std::memory_order_relaxed)} {
}

AtomicInteger::~AtomicInteger() {
}

AtomicInteger& AtomicInteger::operator=(const AtomicInteger& val) {
	value.store(val.value.load(std::memory_order_relaxed));

	return *this;
}

uint32 AtomicInteger::add(uint32 val) {
	return value += val;
}

uint32 AtomicInteger::increment() {
	return ++value;
}

uint32 AtomicInteger::postIncrement() {
	return value++;
}

uint32 AtomicInteger::decrement() {
	return --value;
}

uint32 AtomicInteger::postDecrement() {
	return value--;
}

uint32 AtomicInteger::compareAndSetReturnOld(uint32 oldval, uint32 newval) {
	uint32 val = oldval;

	value.compare_exchange_strong(val, newval);

	return val;
}

bool AtomicInteger::compareAndSet(uint32 oldval, uint32 newval) {
	uint32 val = oldval;

	return value.compare_exchange_strong(val, newval);
}

uint32 AtomicInteger::get(std::memory_order m) const {
	return value.load(m);
}

void AtomicInteger::set(uint32 val, std::memory_order m) {
	value.store(val, m);
}

uint32 AtomicInteger::operator=(const uint32 val) {
	return value = val;
}

bool AtomicInteger::operator==(const int val) const {
	return (uint32)val == value.load(std::memory_order_relaxed);
}

AtomicInteger::operator uint32() const {
	return value.load(std::memory_order_relaxed);
}

bool AtomicInteger::toBinaryStream(sys::io::ObjectOutputStream* stream) {
	stream->writeInt(value);

	return true;
}

bool AtomicInteger::parseFromBinaryStream(sys::io::ObjectInputStream* stream) {
	*this = stream->readInt();

	return true;
}