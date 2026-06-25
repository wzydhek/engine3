/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * AcknowledgeTask.h
 *
 *  Created on: 23/06/2012
 *      Author: victor
 */

#pragma once

namespace engine {
namespace service {
namespace proto {

class AcknowledgeTask : public Task {
	Reference<BaseClient*> client;
	uint16 seq;

public:
	AcknowledgeTask(BaseClient* cl, uint16 sequence);

	void run();
};

} // namespace proto
} // namespace service
} // namespace engine

using namespace engine::service::proto;
