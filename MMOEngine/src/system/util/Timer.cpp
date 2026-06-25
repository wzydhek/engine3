#include "Timer.h"

uint64 Timer::run(const sys::lang::Function<void()>& function) {
	start();

	function();

	return stop();
}

uint64 Timer::run(Runnable* runnable) {
	start();

	runnable->run();

	return stop();
}

void Timer::start() {
	E3_ASSERT(startTime == 0);

	startTime = Time::currentNanoTime(clockType);
}

uint64 Timer::stop() {
	E3_ASSERT(startTime != 0);

	elapsedTime = elapsedToNow();
	startTime = 0;

	totalTime += elapsedTime;

	return elapsedTime;
}

void Timer::clear() {
	startTime = 0;
	elapsedTime = 0;
	totalTime = 0;
}

uint64 Timer::stopMs() {
	return stop() / 1000000;
}

uint64 Timer::elapsedToNow() const {
	if (startTime != 0)
		return Time::currentNanoTime(clockType) - startTime;
	else
		return 0;
}

uint64 Timer::elapsedMs() const {
	return elapsedToNow() / 1000000;
}

uint64 Timer::getStartTime() const {
	return startTime;
}

uint64 Timer::getElapsedTime() const {
	return elapsedTime;
}

uint64 Timer::getTotalTime() const {
	return totalTime;
}

uint64 Timer::getStartTimeMs() const {
	return startTime / 1000000;
}

uint64 Timer::getElapsedTimeMs() const {
	return elapsedTime / 1000000;
}

uint64 Timer::getTotalTimeMs() const {
	return totalTime / 1000000;
}

Time::ClockType Timer::getClockType() const {
	return clockType;
}