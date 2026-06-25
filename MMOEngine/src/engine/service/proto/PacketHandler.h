/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/net/Packet.h"

namespace engine {
  namespace service {
    namespace proto {

	class PacketHandler {
	public:
		virtual void handlePacket(Packet* pack) = 0;
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
