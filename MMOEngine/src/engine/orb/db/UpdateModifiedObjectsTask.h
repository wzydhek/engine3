/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/orb/DistributedObjectBroker.h"
#include "engine/orb/db/DOBObjectManager.h"

namespace engine {
	namespace ORB {

	class UpdateModifiedObjectsTask : public Task {
	public:
		UpdateModifiedObjectsTask();

		void run();
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
