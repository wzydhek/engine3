/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * OutOfOrderTask.h
 *
 *  Created on: 23/06/2012
 *      Author: victor
 */

#pragma once

#include "engine/service/proto/BaseClient.h"

namespace engine {
namespace service {
namespace proto {

class OutOfOrderTask : public Task {
	Reference<BaseClient*> client;
	uint16 seq;

public:
	OutOfOrderTask(BaseClient* cl, uint16 sequence);

	void run();
};

} // namespace proto
} // namespace service
} // namespace engine

using namespace engine::service::proto;
