/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#include "RunStatistics.h"

int RunStatistics::compareTo(const RunStatistics& t) const {
	if (totalRunTime < t.totalRunTime)
		return 1;
	else if (totalRunTime > t.totalRunTime)
		return -1;
	else {
		if (maxRunTime < t.maxRunTime)
			return 1;
		else if (maxRunTime > t.maxRunTime)
			return -1;
		else {
			if (totalRunCount < t.totalRunCount)
				return 1;
			else if (totalRunCount > t.totalRunCount)
				return -1;
			else
				return 0;
		}
	}
}

bool RunStatistics::toBinaryStream(ObjectOutputStream* stream) {
	return true;
}

bool RunStatistics::parseFromBinaryStream(ObjectInputStream* stream) {
	return true;
}

RunStatisticsOrderedByMaxTime::RunStatisticsOrderedByMaxTime(const RunStatistics& r) : totalRunTime(r.totalRunTime), maxRunTime(r.maxRunTime), totalRunCount(r.totalRunCount), minRunTime(r.minRunTime) {
}

int RunStatisticsOrderedByMaxTime::compareTo(const RunStatisticsOrderedByMaxTime& t) const {
	if (maxRunTime < t.maxRunTime)
		return 1;
	else if (maxRunTime > t.maxRunTime)
		return -1;
	else {
		if (totalRunTime < t.totalRunTime)
			return 1;
		else if (totalRunTime > t.totalRunTime)
			return -1;
		else {
			if (totalRunCount < t.totalRunCount)
				return 1;
			else if (totalRunCount > t.totalRunCount)
				return -1;
			else
				return 0;
		}
	}
}

bool RunStatisticsOrderedByMaxTime::toBinaryStream(ObjectOutputStream* stream) {
	return true;
}

bool RunStatisticsOrderedByMaxTime::parseFromBinaryStream(ObjectInputStream* stream) {
	return true;
}


