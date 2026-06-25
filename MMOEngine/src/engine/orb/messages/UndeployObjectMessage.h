/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/orb/DistributedObjectBroker.h"
#include "engine/orb/object/DistributedObjectStub.h"
#include "engine/orb/messages/RemoteObjectBroker.h"
#include "DOBMessage.h"

namespace engine {
  namespace ORB {

	class UndeployObjectMessage : public DOBMessage {
		String name;

		uint64 objectID;

	public:	
		UndeployObjectMessage(const String& name);
	
		UndeployObjectMessage(Packet* message);

		void execute();

		void handleReply(Packet* message);

		uint64 getObjectID();
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
