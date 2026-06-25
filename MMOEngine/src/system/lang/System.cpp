/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "System.h"

ThreadLocal<MTRand*> System::mtrand;

TextStream System::out(stdout);
TextStream System::err(stderr);

uint32 System::random(uint32 bucket) {
   	return getMTRand()->randInt(bucket);
}

uint32 System::random() {
   	return getMTRand()->randInt();
}

double System::frandom(const double& n) {
   	return getMTRand()->rand(n);
}

double System::frandom() {
   	return getMTRand()->rand();
}

MTRand* System::getMTRand() {
	MTRand* localMT = mtrand.get();

	if (localMT == nullptr) {
		localMT = new MTRand();

		mtrand.set(localMT);
	}

	return localMT;
}

time_t System::getTime() {
	return time(nullptr);
}

void System::flushStreams() {
	::fflush(nullptr);
}

void System::flushStream(FILE* stream) {
	::fflush(stream);
}

void System::setStreamBuffer(FILE* str, char* buffer) {
	::setbuf(str, buffer);
}

void System::abort() {
	::abort();
}

#ifndef PLATFORM_WIN
uint64 System::getMiliTime() {
	uint64 time_in_ms;

	struct timeval tm;
	gettimeofday(&tm, nullptr);

	time_in_ms = tm.tv_sec; // Avoid overflow by doing mul in 64 bit int
	time_in_ms = (time_in_ms * 1000) + (uint64)(tm.tv_usec / 1000.f);

	return time_in_ms;
}

uint64 System::getMikroTime() {
	uint64 time_in_ms;

	struct timeval tm;
	gettimeofday(&tm, nullptr);

	time_in_ms = tm.tv_sec; // Avoid overflow by doing mul in 64 bit int
	time_in_ms = (time_in_ms * 1000000) + tm.tv_usec;

	return time_in_ms;
}
#else
uint64 System::getMiliTime() {
	return uint64(((float)clock() / (float)CLOCKS_PER_SEC) * 1000.f);
}

uint64 System::getMikroTime() {
	return uint64(((double)clock() / (double)CLOCKS_PER_SEC) * 1000000.f);
}
#endif
