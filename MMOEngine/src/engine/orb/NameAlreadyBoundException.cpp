#include "NameAlreadyBoundException.h"

NameAlreadyBoundException::NameAlreadyBoundException(DistributedObjectStub* stub) : Exception() {
	message = "\'" + stub->_getName() + "\' is already deployed";
}