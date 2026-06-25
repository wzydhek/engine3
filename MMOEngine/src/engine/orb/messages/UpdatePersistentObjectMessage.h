/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * UpdatePersistentObjectMessage.h
 *
 *  Created on: 21/08/2009
 *      Author: victor
 */

#pragma once

#include "engine/orb/DistributedObjectBroker.h"
#include "DOBMessage.h"

namespace engine {
  namespace ORB {

	  class UpdatePersistentObjectMessage : public DOBMessage {
		  uint64 objectID;

		  uint32 success;

	  public:
		  UpdatePersistentObjectMessage(DistributedObject* object);

		  UpdatePersistentObjectMessage(Packet* message);

		  void execute();

		  void handleReply(Packet* response);
	  };

  }
}

using namespace engine::ORB;
