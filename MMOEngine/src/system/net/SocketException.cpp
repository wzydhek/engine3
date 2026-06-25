#include "SocketException.h"

SocketException::SocketException() : Exception() {
	StringBuffer str;
	str << "Socket Exception " << " (errno " << getErrorCode() << ")";

	message = str.toString();
}

SocketException::SocketException(const String& msg) : Exception(msg) {
	StringBuffer str;
	str << msg << " (errno " << getErrorCode() << ")";

	message = str.toString();
}

int SocketException::getErrorCode() {
#ifndef PLATFORM_WIN
	return errno;
#else
	return WSAGetLastError();
#endif
}