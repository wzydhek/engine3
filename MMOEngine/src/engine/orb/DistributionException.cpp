#include "DistributionException.h"

DistributionException::DistributionException() : Exception() {
	message = "remote node is unreachable";
	assert(0);
}

DistributionException::DistributionException(uint64 objectID) : Exception() {
	message = "object 0x" + String::valueOf(objectID) + " is unreachable";
	assert(0);
}

DistributionException::DistributionException(const String& name) : Exception() {
	message = "object \'" + name + "\' is unreachable";
	assert(0);
}

DistributionException::DistributionException(DistributedObjectStub* stub) : Exception() {
	message = "object \'" + stub->_getName() + "\' is unreachable";
	assert(0);
}