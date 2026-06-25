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

	class DeployObjectMessage : public DOBMessage {
		String name;
		String className;

		uint64 requestedObjectID;

		bool deployed;
		uint64 objectID = 0;

	public:
		DeployObjectMessage(const String& name, const String& classname, uint64 requestedObjectID);
		DeployObjectMessage(Packet* message);

		void execute();

		void handleReply(Packet* message);

		bool isDeployed() const;

		uint64 getObjectID() const;
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
