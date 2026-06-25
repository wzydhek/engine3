/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"

#ifndef PLATFORM_WIN
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
#else
	#include <winsock2.h>
#endif

#include "system/lang/String.h"

namespace sys {
  namespace net {

	class InetAddress {
		String ipaddress;
		String hostname;

	public:
		InetAddress(const String& address);

		~InetAddress() {
		}

		// setters
		void setHostName(const String& host);

		// getters
		const String& getHostAddress() const;

		const String& getHostName() const;

	};

  } // namespace net
} // namespace sys

using namespace sys::net;
