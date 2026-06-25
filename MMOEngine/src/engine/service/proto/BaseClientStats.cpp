#include "BaseClientStats.h"

BaseClientStats::BaseClientStats(bool local) {
	isLocal = local;
	reset();
}

void BaseClientStats::reset() {
	needsCalculation = false;
	totalPacketsSent = 0;
	totalPacketsReceived = 0;
	tickDelta = 0;
	lastAckMs = 0;
	totalAckMs = 0;
	countAcks = 0;
	minAckMs = ULLONG_MAX;
	maxAckMs = 0;
	maxPacketsSentPerSecond = 0;
	maxPacketsReceivedPerSecond = 0;
	lastTotalPacketsSent = 0;
	lastTotalPacketsReceived = 0;
	packetsSentPerSecond = 0;
	packetsReceivedPerSecond = 0;
	avgAckMs = 0;
}

uint64 BaseClientStats::getTotalPacketsSent() const {
	return totalPacketsSent;
}

void BaseClientStats::setTotalPacketsSent(uint64 newTotalPacketsSent) {
	totalPacketsSent = newTotalPacketsSent;
	needsCalculation = true;
}

uint64 BaseClientStats::getTotalPacketsReceived() const {
	return totalPacketsReceived;
}

void BaseClientStats::setTotalPacketsReceived(uint64 newTotalPacketsReceived) {
	totalPacketsReceived = newTotalPacketsReceived;
	needsCalculation = true;
}

void BaseClientStats::setTimeStamp(const Time& timeStamp) {
	calculationTimeStamp = timeStamp;
	needsCalculation = true;
}

uint16 BaseClientStats::getPacketsSentPerSecond() {
	updateCalculatedStats(false);
	return packetsSentPerSecond;
}

uint16 BaseClientStats::getPacketsReceivedPerSecond() {
	updateCalculatedStats(false);
	return packetsReceivedPerSecond;
}

uint16 BaseClientStats::getTickDelta() const {
	return tickDelta;
}

void BaseClientStats::setTickDelta(uint16 newTickDelta) {
	tickDelta = newTickDelta;
}

uint64 BaseClientStats::getLastAckMs() const {
	return lastAckMs;
}

uint64 BaseClientStats::getTotalAckMs() const {
	return totalAckMs;
}

uint64 BaseClientStats::getCountAcks() const {
	return countAcks;
}

uint64 BaseClientStats::getMinAckMs() const {
	return minAckMs == ULLONG_MAX ? 0 : minAckMs;
}

uint64 BaseClientStats::getMaxAckMs() const {
	return maxAckMs;
}

uint16 BaseClientStats::getAvgAckMs() {
	avgAckMs = countAcks > 0 ? totalAckMs / countAcks : 0;
	return avgAckMs;
}

void BaseClientStats::updateAckStats(int64 elapsedMs) {
	++countAcks;

	totalAckMs += elapsedMs;
	avgAckMs = countAcks > 0 ? totalAckMs / countAcks : 0;

	lastAckMs = elapsedMs;

	if (lastAckMs > 0 && lastAckMs < minAckMs) {
		minAckMs = elapsedMs;
	}

	if (lastAckMs > maxAckMs) {
		maxAckMs = lastAckMs;
	}
}

void BaseClientStats::updateCalculatedStats(bool resetPeriod, bool forceCalculation) {
	if (needsCalculation || forceCalculation) {
		auto elapsedSeconds = (calculationTimeStamp.miliDifference(Time::MONOTONIC_TIME) / 1000);

		if (elapsedSeconds > 0) {
			packetsSentPerSecond = (totalPacketsSent - lastTotalPacketsSent) / elapsedSeconds;
			lastTotalPacketsSent = totalPacketsSent;

			if (packetsSentPerSecond > maxPacketsSentPerSecond) {
				maxPacketsSentPerSecond = packetsSentPerSecond;
			}

			packetsReceivedPerSecond = (totalPacketsReceived - lastTotalPacketsReceived) / elapsedSeconds;
			lastTotalPacketsReceived = totalPacketsReceived;

			if (packetsReceivedPerSecond > maxPacketsReceivedPerSecond) {
				maxPacketsReceivedPerSecond = packetsReceivedPerSecond;
			}
		}

		needsCalculation = false;
	}

	if (resetPeriod) {
		calculationTimeStamp.updateToCurrentTime(Time::MONOTONIC_TIME);
	}
}

String BaseClientStats::asJSONFragment(bool resetTimePeriod) {
	updateCalculatedStats();

	StringBuffer buf;
	String prefix = isLocal ? "local" : "remote";

	auto packetStatsAge = (calculationTimeStamp.miliDifference(Time::MONOTONIC_TIME) / 1000);

	buf << ", \"" << prefix << "TotalPacketsSent\":" << totalPacketsSent << ", \"" << prefix << "TotalPacketsReceived\":" << totalPacketsReceived << ", \"" << prefix << "PacketsSentPerSecond\":" << packetsSentPerSecond << ", \"" << prefix << "PacketsReceivedPerSecond\":" << packetsReceivedPerSecond << ", \"" << prefix
		<< "MaxPacketsSentPerSecond\":" << maxPacketsSentPerSecond << ", \"" << prefix << "MaxPacketsReceivedPerSecond\":" << maxPacketsReceivedPerSecond << ", \"" << prefix << "PacketStatsAge\":" << (packetStatsAge < 0 ? 0 : packetStatsAge) << ", \"" << prefix << "TickDelta\":" << tickDelta << ", \"" << prefix
		<< "LastAckMs\":" << lastAckMs << ", \"" << prefix << "MinAckMs\":" << (minAckMs == ULLONG_MAX ? 0 : minAckMs) << ", \"" << prefix << "AvgAckMs\":" << avgAckMs << ", \"" << prefix << "MaxAckMs\":" << maxAckMs << ", \"" << prefix << "CountAcks\":" << countAcks << ", \"" << prefix << "TotalAckMs\":" << totalAckMs;

	return buf.toString();
}