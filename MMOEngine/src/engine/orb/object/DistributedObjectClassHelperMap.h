/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "DistributedObjectClassHelper.h"

namespace engine {
  namespace ORB {

	class DistributedObjectClassHelperMap : public HashTable<String, DistributedObjectClassHelper*> {
	public:
		DistributedObjectClassHelperMap();

		~DistributedObjectClassHelperMap();

	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
