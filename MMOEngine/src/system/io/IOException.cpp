#include "IOException.h"

IOException::IOException(const String& msg) {
#ifdef PLATFORM_MAC
	char str[256];

	int val = strerror_r(errno, str, 256);

	message = msg + " (" + String::valueOf(errno) + ": " + str + ")";
#else
#ifndef PLATFORM_WIN
	char str[256];

	char* val = strerror_r(errno, str, 256);
#else
	auto val = "";// strerror_s(str, 256, errno);
#endif

	message = msg + " (" + String::valueOf(errno) + ": " + val + ")";
#endif


}
