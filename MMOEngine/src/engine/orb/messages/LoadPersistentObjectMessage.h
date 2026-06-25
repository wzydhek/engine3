/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * LoadPersistentObjectMessage.h
 *
 *  Created on: 20/08/2009
 *      Author: victor
 */

#pragma once

#include "engine/orb/DistributedObjectBroker.h"
#include "DOBMessage.h"

namespace engine {
  namespace ORB {

	class LoadPersistentObjectMessage : public DOBMessage {
		uint64 objectID;

		bool found;

	public:
		LoadPersistentObjectMessage(uint64 objectid);

		LoadPersistentObjectMessage(Packet* message);

		void execute();

		void handleReply(Packet* response);

		bool isFound();
	};

  }
}

using namespace engine::ORB;
