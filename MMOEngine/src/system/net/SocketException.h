/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"

#ifndef PLATFORM_WIN
	#include <errno.h>
#else
	#include <winsock2.h>
	#include <windows.h>
#endif

#include "system/lang/Exception.h"
#include "system/lang/StringBuffer.h"

namespace sys {
  namespace net {

	class SocketException : public sys::lang::Exception {
	public:
		SocketException();

		SocketException(const String& msg);

		int getErrorCode();

	};

  } // namespace net
} // namespace sys

using namespace sys::net;
