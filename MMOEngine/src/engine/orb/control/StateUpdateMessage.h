/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/orb/messages/RemoteObjectBroker.h"
#include "engine/orb/messages/DOBMessage.h"
#include "ObjectBrokerDirector.h"

namespace engine {
  namespace ORB {

	class StateUpdateMessage : public DOBMessage {
		int state;

	public:
		StateUpdateMessage(int state);

		StateUpdateMessage(Packet* message);

		void execute();
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
