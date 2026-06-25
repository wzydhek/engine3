/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * BaseClientEvent.h
 *
 *  Created on: 29/12/2009
 *      Author: victor
 */

#pragma once

namespace engine {
  namespace service {
    namespace proto {

	class BaseClientEvent;

    } // namespace proto
  } // namespace service
} // namespace engine

#include "engine/service/proto/BaseClient.h"

namespace engine {
  namespace service {
    namespace proto {

	class BaseClientEvent : public Task {
		WeakReference<BaseClient*> client;

	public:
		BaseClientEvent(BaseClient* cl);

		void run();

	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
