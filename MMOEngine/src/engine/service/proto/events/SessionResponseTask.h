/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * SessionResponseTask.h
 *
 *  Created on: 23/06/2012
 *      Author: victor
 */

#pragma once

#include "engine/service/proto/BaseClient.h"

namespace engine {
namespace service {
namespace proto {

class SessionResponseTask : public Task {
	Reference<BaseClient*> client;
	uint32 seed;

public:
	SessionResponseTask(BaseClient* cl, uint32 seed);

	void run();
};

} // namespace proto
} // namespace service
} // namespace engine

using namespace engine::service::proto;
