#include "ObjectNotLocalException.h"

ObjectNotLocalException::ObjectNotLocalException(const DistributedObjectStub* stub) : Exception() {
	message = "\'" + stub->_getName() + "\' is not implemented locally";
}