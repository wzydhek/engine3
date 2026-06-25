/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Socket.h"

namespace sys {
  namespace net {

	class UDPSocket : public Socket {
	public:
		UDPSocket();
		
	};

  } // namespace net
} // namespace sys

using namespace sys::net;
