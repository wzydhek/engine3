#include "TickTimer.h"

TickTimer::TickTimer() {
	clearStartTicks();
	clearElapsedTicks();
}

void TickTimer::start() {
	assert(startTicks.tms_utime == 0);
	times(&startTicks);

	clearElapsedTicks();
}

void TickTimer::stop() {
	assert(startTicks.tms_utime != 0);

	times(&elapsedTicks);
}

uint64 TickTimer::elapsedUserTicks() const {
	if (startTicks.tms_utime != 0)
		return elapsedTicks.tms_utime - startTicks.tms_utime;
	else
		return 0;
}

uint64 TickTimer::elapsedSystemTicks() const {
	if (startTicks.tms_utime != 0)
		return elapsedTicks.tms_stime - startTicks.tms_stime;
	else
		return 0;
}

void TickTimer::clearStartTicks() {
	startTicks.tms_utime = 0;
	startTicks.tms_stime = 0;
}

void TickTimer::clearElapsedTicks() {
	elapsedTicks.tms_utime = 0;
	elapsedTicks.tms_stime = 0;
}

uint64 TickTimer::getTicksPerSec() {
	return sysconf(_SC_CLK_TCK);
}