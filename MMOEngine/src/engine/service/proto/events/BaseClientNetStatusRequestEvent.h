/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * BaseClientNetStatusRequestEvent.h
 *
 *  Created on: Sep 5, 2009
 *      Author: theanswer
 */

#pragma once

#include "engine/service/proto/BasePacket.h"
#include "engine/service/proto/BaseClient.h"

namespace engine {
  namespace service {
    namespace proto {

	class BaseClientNetStatusRequestEvent : public Task {
		Reference<BaseClient*> client;
		Mutex lock;

	public:
		BaseClientNetStatusRequestEvent(BaseClient* cl);

		void run();

		void clearClient();
	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
