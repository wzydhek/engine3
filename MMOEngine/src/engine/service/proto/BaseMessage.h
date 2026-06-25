/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/service/DatagramServiceClient.h"
#include "BasePacket.h"

namespace engine {
  namespace service {
    namespace proto {

	class BaseMessage : public BasePacket {
	public:
		BaseMessage();

		BaseMessage(int size);

		BaseMessage(const Packet* pack, int start);

		BaseMessage(const Packet* pack, int startoffs, int endoffs);

		virtual ~BaseMessage() {
		}

		BaseMessage* clone(int startoffs = 0);

	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
