/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/service/proto/BaseProtocol.h"

namespace engine {
  namespace service {
    namespace proto {

	class SessionIDRequestMessage : public Packet {
	public:
		SessionIDRequestMessage();
	
		static void parse(Packet* pack, BaseProtocol* prot);

		static uint32 parse(Packet* pack);
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
