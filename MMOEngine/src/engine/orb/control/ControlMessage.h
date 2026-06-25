/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/orb/messages/DOBMessage.h"
#include "ObjectBrokerAgent.h"

namespace engine {
  namespace ORB {

	class ControlMessage : public DOBMessage {
		int command;
		int flags;

	public:
		ControlMessage(int command, int flags);

		ControlMessage(Packet* message);

		void execute();
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
