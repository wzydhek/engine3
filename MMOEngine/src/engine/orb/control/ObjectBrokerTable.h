/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/orb/ObjectBroker.h"

namespace engine {
  namespace ORB {

	class ObjectBrokerTable {
		HashSet<ObjectBroker*> objectBrokers;
	
	public:
		void add(ObjectBroker* broker);
	
		void remove(ObjectBroker* broker);

		HashSetIterator<ObjectBroker*> iterator();

		int getBrokerCount();
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
