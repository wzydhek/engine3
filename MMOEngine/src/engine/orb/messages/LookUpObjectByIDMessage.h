/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/orb/DistributedObjectBroker.h"
#include "engine/orb/db/DOBObjectManager.h"
#include "DOBMessage.h"

namespace engine {
  namespace ORB {

	class LookUpObjectByIDMessage : public DOBMessage {
		uint64 objectid;

		String name;
		String className;
		bool found;

	public:
		LookUpObjectByIDMessage(uint64 objectid);

		LookUpObjectByIDMessage(Packet* message);

		void execute();

		void handleReply(Packet* message);

		const String& getClassName() const;

		const String& getName() const;

		bool isFound() const;
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
