#include "ObjectNotDeployedException.h"

ObjectNotDeployedException::ObjectNotDeployedException(const DistributedObjectStub* stub) : Exception() {
	message = "\'" + stub->_getName() + "\' is not deployed";

	System::out << message << "\n";

	stub->printReferenceTrace();

	Logger::closeGlobalFileLogger();

	raise(SIGSEGV);
}