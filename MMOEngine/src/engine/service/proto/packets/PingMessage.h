/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/service/proto/BaseProtocol.h"

namespace engine {
  namespace service {
    namespace proto {

	class PingMessage : public BasePacket {
	public:
		PingMessage() : BasePacket(7) {
			insertShort(0x0600);
		}
	
		static void parse(Packet* pack) {
		}
		
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
