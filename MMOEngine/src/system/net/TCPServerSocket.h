/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Socket.h"

namespace sys {
  namespace net {

	class TCPServerSocket : public Socket {
	public:
		TCPServerSocket(SocketAddress* addr) : Socket() {
			fileDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
			if (fileDescriptor < 0)
				throw SocketException("unable to create server socket");
	
			bindTo(addr);
		}
		
	};

  } // namespace net
} // namespace sys

using namespace sys::net;
