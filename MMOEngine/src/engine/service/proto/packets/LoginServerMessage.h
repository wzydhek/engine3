/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/service/proto/BaseProtocol.h"

namespace engine {
  namespace service {
    namespace proto {

	class LoginServerMessage : public BasePacket {
	public:
		LoginServerMessage();
	
		/*static uint16 parse(Packet* pack) {
			return 0;
		}*/
		
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
