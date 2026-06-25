/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : BaseClientStats.h
 * @created     : Mon Jan 24 12:40:12 UTC 2022
 */

#pragma once

#include "system/lang.h"

namespace engine {
 namespace service {
  namespace proto {
	class BaseClient;

	class BaseClientStats {
		// State
		bool isLocal;
		bool needsCalculation;
		Time calculationTimeStamp;

		// Facts
		uint64 totalPacketsSent;
		uint64 totalPacketsReceived;
		uint16 tickDelta;
		uint64 lastAckMs;
		uint64 totalAckMs;
		uint64 countAcks;
		uint64 minAckMs;
		uint64 maxAckMs;
		uint16 maxPacketsSentPerSecond;
		uint16 maxPacketsReceivedPerSecond;

		// Calculations
		uint64 lastTotalPacketsSent;
		uint64 lastTotalPacketsReceived;
		uint16 packetsSentPerSecond;
		uint16 packetsReceivedPerSecond;
		uint16 avgAckMs;

	public:
		BaseClientStats(bool local = false);

		void reset();

		uint64 getTotalPacketsSent() const;

		void setTotalPacketsSent(uint64 newTotalPacketsSent);

		uint64 getTotalPacketsReceived() const;

		void setTotalPacketsReceived(uint64 newTotalPacketsReceived);

		void setTimeStamp(const Time& timeStamp);

		uint16 getPacketsSentPerSecond();

		uint16 getPacketsReceivedPerSecond();

		uint16 getTickDelta() const;

		void setTickDelta(uint16 newTickDelta);

		uint64 getLastAckMs() const;

		uint64 getTotalAckMs() const;

		uint64 getCountAcks() const;

		uint64 getMinAckMs() const;

		uint64 getMaxAckMs() const;

		uint16 getAvgAckMs();

		void updateAckStats(int64 elapsedMs);

		void updateCalculatedStats(bool resetPeriod = false, bool forceCalculation = false);

		String asJSONFragment(bool resetTimePeriod = true);
	};
}
}
}

using namespace engine::service::proto;
