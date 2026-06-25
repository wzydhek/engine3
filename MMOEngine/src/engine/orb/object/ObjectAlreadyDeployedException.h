/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang/Exception.h"
#include "DistributedObjectStub.h"

namespace engine {
  namespace ORB {

	class ObjectAlreadyDeployedException : public sys::lang::Exception {
	public:
		ObjectAlreadyDeployedException(DistributedObjectStub* stub);

	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
