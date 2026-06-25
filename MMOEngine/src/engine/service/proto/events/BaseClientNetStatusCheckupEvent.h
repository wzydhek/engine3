/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/service/proto/BasePacket.h"
#include "engine/service/proto/BaseClient.h"

namespace engine {
  namespace service {
    namespace proto {

	class BaseClientNetStatusCheckupEvent : public Task {
		Reference<BaseClient*> client;
		Mutex lock;

	public:
		BaseClientNetStatusCheckupEvent(BaseClient* cl);

		void run();

		void clearClient();
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
