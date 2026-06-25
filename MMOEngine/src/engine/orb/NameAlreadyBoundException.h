/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang/Exception.h"
#include "object/DistributedObjectStub.h"

namespace engine {
  namespace ORB {

	class NameAlreadyBoundException : public sys::lang::Exception {
	public:
		NameAlreadyBoundException(DistributedObjectStub* stub);
		
	};

  } // namespace ORB
} // namespace engine

using namespace engine::ORB;
