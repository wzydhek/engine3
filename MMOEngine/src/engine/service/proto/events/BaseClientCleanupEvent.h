/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "system/lang.h"
#include "engine/service/proto/BaseClient.h"

namespace engine {
namespace service {
namespace proto {

class BaseClientCleanupEvent : public Task {
	Reference<BaseClient*> client;

public:
	BaseClientCleanupEvent(BaseClient* cl);

	void run();

};

} // namespace proto
} // namespace service
} // namespace engine

using namespace engine::service::proto;
