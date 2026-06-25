/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/service/proto/BaseProtocol.h"

namespace engine {
  namespace service {
    namespace proto {

	class SessionIDResponseMessage : public Packet {
	public:
		SessionIDResponseMessage(BaseProtocol* prot);
	
		static unsigned int parse(Packet* pack);
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
