#include "SignalException.h"

AbortedException::AbortedException(int cause) : Exception() {
	System::err << "Exception aborted with cause " << cause << " at\n" << flush;
	printStackTrace();

	exit(1);
}

int AbortedException::GetSignalNumber() {
	return SIGABRT;
}

FloatingPointException::FloatingPointException(int) : Exception() {
	printStackTrace();
}

int FloatingPointException::GetSignalNumber() {
	return SIGFPE;
}