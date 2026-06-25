#include "ObjectBroker.h"

DistributedObjectPOD* ObjectBroker::createObjectPOD(const String& className) {
	return nullptr;
}

int ObjectBroker::compareTo(ObjectBroker*& b) {
	if (this < b)
		return 1;
	else if (this > b)
		return -1;
	else
		return 0;
}