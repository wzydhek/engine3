/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * DisconnectTask.h
 *
 *  Created on: 23/06/2012
 *      Author: victor
 */

#pragma once

#include "engine/service/proto/BaseClient.h"

namespace engine {
namespace service {
namespace proto {

class DisconnectTask : public Task {
	Reference<BaseClient*> client;
public:
	DisconnectTask(BaseClient* cl);

	void run();
};

} // namespace proto
} // namespace service
} // namespace engine

using namespace engine::service::proto;
