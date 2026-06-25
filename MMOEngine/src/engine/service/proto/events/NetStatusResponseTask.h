/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * NetStatusResponseTask.h
 *
 *  Created on: 23/06/2012
 *      Author: victor
 */

#pragma once

#include "engine/log/Logger.h"
#include "engine/service/proto/BaseClient.h"

namespace engine {
namespace service {
namespace proto {

class NetStatusResponseTask : public Task {
	Reference<BaseClient*> client;
	Packet* pack;
public:

	NetStatusResponseTask(BaseClient* cl, Packet* inPack);

	~NetStatusResponseTask();

	void run();
};

} // namespace proto
} // namespace service
} // namespace engine

using namespace engine::service::proto;
