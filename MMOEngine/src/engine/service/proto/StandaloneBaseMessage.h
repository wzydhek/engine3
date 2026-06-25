/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "BasePacket.h"

namespace engine {
  namespace service {
    namespace proto {

	class StandaloneBaseMessage : public BasePacket {
	public:
		StandaloneBaseMessage();
	
		StandaloneBaseMessage(int size);
	
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
