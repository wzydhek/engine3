/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "mersenne/MersenneTwister.h"
#include "system/platform.h"
#include "system/io/TextStream.h"
#include "system/thread/ThreadLocal.h"
#include <thread>

namespace sys {
  namespace lang {

	#ifndef CLK_TCK // Fix for undefined CLK_TCK under linux.
		#define CLK_TCK CLOCKS_PER_SEC
	#endif // CLK_TCK

	class System {
		static ThreadLocal<MTRand*> mtrand;

	public:
		static TextStream out; //stdout
		static TextStream err; //stderr

		static time_t getTime();

		static void flushStreams();

		static void flushStream(FILE* stream);

		static void setStreamBuffer(FILE* str, char* buffer);

		[[noreturn]] static void abort();

		static auto getOnlineProcessors() {
			auto val = std::thread::hardware_concurrency();

			E3_ASSERT(val);

			return val;
		}

	#ifndef PLATFORM_WIN
		static uint64 getMiliTime();

		static uint64 getMikroTime();
	#else
		static uint64 getMiliTime();

		static uint64 getMikroTime();
	#endif

		static uint32 random(); // integer in [0,2^32-1]
		static uint32 random(uint32 bucket); //integer in [0,n] for n < 2^32
		static double frandom(const double& n); // real number in [0, n]
		static double frandom(); // real number in [0, 1]

		static MTRand* getMTRand();
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
