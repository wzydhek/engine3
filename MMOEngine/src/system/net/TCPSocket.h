/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Socket.h"

namespace sys {
  namespace net {

	class TCPSocket : public Socket {
	public:
		TCPSocket();
	
	};

  } // namespace net
} // namespace sys

using namespace sys::net;
