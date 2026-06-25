#include "DeadlockException.h"

DeadlockException::DeadlockException() : lockable(nullptr) {
}

DeadlockException::DeadlockException(const String& msg) : lockable(nullptr), message(msg) {
}

DeadlockException::DeadlockException(Lockable* lock, const String& msg) : lockable(lock), message(msg) {
}

StackTrace* DeadlockException::getStackTrace() {
	return &trace;
}

void DeadlockException::printStackTrace() {
	trace.print();
}

Lockable* DeadlockException::getLockable() {
	return lockable;
}

String DeadlockException::getMessage() {
	return message;
}