/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/orb/DistributedObjectBroker.h"
#include "DOBMessage.h"

namespace engine {
  namespace ORB {

	class LookUpObjectMessage : public DOBMessage {
		String name;

		bool found;
		String className;
		uint64 objectID;

	public:	
		LookUpObjectMessage(const String& name);

		LookUpObjectMessage(Packet* message);

		void execute();

		void handleReply(Packet* message);

		bool isFound();

		const String& getClassName();

		uint64 getObjectID();
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
