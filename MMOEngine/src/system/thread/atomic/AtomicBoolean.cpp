#include "AtomicBoolean.h"

AtomicBoolean::AtomicBoolean() {
}

AtomicBoolean::AtomicBoolean(bool val) : value(val) {
}

AtomicBoolean::AtomicBoolean(AtomicBoolean&& val) : value(val.value.load(std::memory_order_seq_cst)) {
}

AtomicBoolean::AtomicBoolean(const AtomicBoolean& val) : value(val.value.load(std::memory_order_seq_cst)) {
}

AtomicBoolean::~AtomicBoolean() {
}

bool AtomicBoolean::compareAndSet(bool oldval, bool newval) {
	return value.compare_exchange_strong(oldval, newval);
}

bool AtomicBoolean::get(std::memory_order m) const {
	return value.load(m);
}

void AtomicBoolean::set(bool val, std::memory_order m) {
	value.store(val, m);
}

AtomicBoolean& AtomicBoolean::operator=(const bool val) {
	value = val;

	return *this;
}

bool AtomicBoolean::operator==(const bool val) const {
	return val == value.load(std::memory_order_relaxed);
}

AtomicBoolean::operator bool() const {
	return value.load(std::memory_order_seq_cst);
}

bool AtomicBoolean::toBinaryStream(sys::io::ObjectOutputStream* stream) NO_THREAD_SAFETY_ANALYSIS {
	stream->writeInt(value);

	return true;
}

bool AtomicBoolean::parseFromBinaryStream(sys::io::ObjectInputStream* stream) NO_THREAD_SAFETY_ANALYSIS {
	*this = stream->readInt();

	return true;
}