/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/core/Task.h"
#include "engine/service/proto/BaseClient.h"

namespace engine {
  namespace service {
    namespace proto {

	class BasePacketChekupEvent;

    } // namespace proto
  } // namespace service
} // namespace engine

namespace engine {
  namespace service {
    namespace proto {
	class BaseClient;
	class BasePacket;

	class BasePacketChekupEvent : public Task {
		WeakReference<BaseClient*> client;
		Reference<BasePacket*> packet;

		uint32 checkupTime;
		uint32 minCheckupTime;
		uint32 maxCheckupTime;
		Time lastUpdateTimeStamp;

	public:
		BasePacketChekupEvent(BaseClient* cl, uint32 time = 5000, uint32 minCheckupTime = 100, uint32 maxCheckupTime = 500);

		void run();

		// setters and getters
		void update(BasePacket* pack);

		void setCheckupTime(uint32 time);

		void increaseCheckupTime(uint32 time);

		void decreaseCheckupTime(uint32 time);

		uint32 getCheckupTime();

		int64 getElapsedTimeMs();

	};

    } // namespace proto
  } // namespace service
} // namespace engine

using namespace engine::service::proto;
