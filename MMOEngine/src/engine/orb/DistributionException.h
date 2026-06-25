/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang/Exception.h"
#include "object/DistributedObjectStub.h"

namespace engine {
  namespace ORB {

	class DistributionException : public sys::lang::Exception {
	public:
		DistributionException();

		DistributionException(uint64 objectID);

		DistributionException(const String& name);

		DistributionException(DistributedObjectStub* stub);
		
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
