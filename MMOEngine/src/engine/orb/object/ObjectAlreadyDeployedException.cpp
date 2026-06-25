#include "ObjectAlreadyDeployedException.h"

ObjectAlreadyDeployedException::ObjectAlreadyDeployedException(DistributedObjectStub* stub) : Exception() {
	message = "\'" + stub->_getName() + "\' (0x" + String::valueOf(stub->_getObjectID()) + ") is already deployed";
}