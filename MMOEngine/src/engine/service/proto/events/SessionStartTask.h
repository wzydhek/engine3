/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * SessionStartTask.h
 *
 *  Created on: 23/06/2012
 *      Author: victor
 */

#pragma once

#include "engine/service/proto/BaseClient.h"

namespace engine {
namespace service {
namespace proto {

class SessionStartTask : public Task {
	Reference<BaseClient*> client;
	uint32 connectionID;

public:
	SessionStartTask(BaseClient* cl, uint32 cid);

	void run();
};

} // namespace proto
} // namespace service
} // namespace engine

using namespace engine::service::proto;
