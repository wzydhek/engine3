#include "AtomicTime.h"

AtomicTime::AtomicTime(const AtomicTime& time) : Variable(), ts(time.ts.load(std::memory_order_relaxed)) {
}

AtomicTime::AtomicTime(const Time& time) : Variable(), ts(time.ts) {
}

bool AtomicTime::toString(String& str) const {
	auto ts = this->ts.load(std::memory_order_relaxed);

	StringBuffer msg;
	msg << ts.tv_sec << "," << ts.tv_nsec;

	str = msg.toString();
	return true;
}

bool AtomicTime::parseFromString(const String& str, int version) {
	int separator = str.indexOf(',');

	if (separator == -1)
		return false;

	String sec = str.subString(0, separator);
	String nsec = str.subString(separator + 1);

	struct timespec ts;

	ts.tv_sec = Integer::valueOf(sec);
	ts.tv_nsec = Integer::valueOf(nsec);

	this->ts.store(ts, std::memory_order_relaxed);

	return true;
}

bool AtomicTime::toBinaryStream(ObjectOutputStream* stream) {
	auto ts = this->ts.load(std::memory_order_relaxed);

	stream->writeLong(ts.tv_sec);
	stream->writeLong(ts.tv_nsec);

	return true;
}

bool AtomicTime::parseFromBinaryStream(ObjectInputStream* stream) {
	struct timespec ts;

	ts.tv_sec = stream->readLong();
	ts.tv_nsec = stream->readLong();

	this->ts.store(ts, std::memory_order_relaxed);

	return true;
}

void AtomicTime::updateToCurrentTime(ClockType type) {
	struct timespec ts;

#if !defined(PLATFORM_WIN) && !defined(PLATFORM_MAC)
	clock_gettime(type, &ts);
#else
	switch (type) {
		case REAL_TIME:
			ts = timepointToTimespec(std::chrono::system_clock::now());
			break;
		case MONOTONIC_TIME:
			ts = timepointToTimespec(std::chrono::steady_clock::now());
			break;
		default:
			ts = timepointToTimespec(std::chrono::high_resolution_clock::now());
			break;
	}
#endif

	this->ts.store(ts, std::memory_order_relaxed);
}

void AtomicTime::addMiliTime(uint64 mtime) {
	auto ts = this->ts.load(std::memory_order_relaxed);

	ts.tv_sec += (long)(mtime / 1000);
	ts.tv_nsec += (long)((mtime % 1000) * 1000000);

	checkForOverflow(ts);

	this->ts.store(ts, std::memory_order_relaxed);
}

void AtomicTime::addMikroTime(uint64 utime) {
	auto ts = this->ts.load(std::memory_order_relaxed);

	ts.tv_sec += (long)(utime / 1000000);
	ts.tv_nsec += (long)((utime % 1000000) * 1000);

	checkForOverflow(ts);

	this->ts.store(ts, std::memory_order_relaxed);
}

void AtomicTime::addNanoTime(uint64 ntime) {
	auto ts = this->ts.load(std::memory_order_relaxed);

	ts.tv_sec += (long)(ntime / 1000000000);
	ts.tv_nsec += (long)(ntime % 1000000000);

	checkForOverflow(ts);

	this->ts.store(ts, std::memory_order_relaxed);
}

AtomicTime& AtomicTime::operator=(const AtomicTime& t) {
	if (this == &t)
		return *this;

	this->ts.store(t.ts.load(std::memory_order_relaxed), std::memory_order_relaxed);

	return *this;
}

AtomicTime& AtomicTime::operator=(const Time& t) {
	this->ts.store(t.ts, std::memory_order_relaxed);

	return *this;
}

AtomicTime& AtomicTime::operator=(uint32 seconds) {
	struct timespec ts;

	ts.tv_sec = seconds;
	ts.tv_nsec = 0;

	this->ts.store(ts, std::memory_order_relaxed);

	return *this;
}

int AtomicTime::compareTo(const AtomicTime& t) const {
	auto ts = this->ts.load(std::memory_order_relaxed);
	auto tsr = t.ts.load(std::memory_order_relaxed);

	if (ts.tv_sec < tsr.tv_sec)
		return 1;
	else if (ts.tv_sec > tsr.tv_sec)
		return -1;
	else {
		if (ts.tv_nsec < tsr.tv_nsec)
			return 1;
		else if (ts.tv_nsec > tsr.tv_nsec)
			return -1;
		else
			return 0;
	}
}

int AtomicTime::compareTo(const Time& t) const {
	auto ts = this->ts.load(std::memory_order_relaxed);
	const auto& tsr = *t.getTimeSpec();

	if (ts.tv_sec < tsr.tv_sec)
		return 1;
	else if (ts.tv_sec > tsr.tv_sec)
		return -1;
	else {
		if (ts.tv_nsec < tsr.tv_nsec)
			return 1;
		else if (ts.tv_nsec > tsr.tv_nsec)
			return -1;
		else
			return 0;
	}
}

String AtomicTime::getFormattedTime() const {
#ifndef PLATFORM_WIN
	char str[100];
	auto ts = this->ts.load(std::memory_order_relaxed);
	char* ret = ctime_r(&ts.tv_sec, str);

	if (ret != nullptr)
		return String(ret, strlen(str) - 1);
	else
		return String("");
#else
	auto ts = this->ts.load(std::memory_order_relaxed);
	char* str = ctime(&ts.tv_sec);

	if (str != nullptr)
		return String(str, strlen(str) - 1);
	else
		return String("");
#endif
}

String AtomicTime::getFormattedTimeFull() const {
	int ret;
	struct tm t;
	String value;
	char buf[128];
	int len = sizeof(buf);
	auto ts = this->ts.load(std::memory_order_relaxed);

#ifndef PLATFORM_WIN
	if (localtime_r(&(ts.tv_sec), &t) == nullptr)
		return value;
#else
	auto retval = localtime(&(ts.tv_sec));
	if (retval == nullptr)
		return value;

	t = *retval;
#endif

	ret = strftime(buf, len, "%Y-%m-%dT%H:%M:%S", &t);
	if (ret <= 0)
		return value;

	len -= ret - 1;

	ret = snprintf(&buf[strlen(buf)], len, ".%09ld", ts.tv_nsec);
	if (ret < 0 || ret >= len)
		return value;

	len -= ret;

	char tz[32];

	strftime(tz, sizeof(tz), "%z", &t);

	snprintf(&buf[strlen(buf)], len, "%s", tz);

	value = buf;

	return value;
}

int AtomicTime::compareMiliTo(const Time& t) const {
	uint64 t1 = getMiliTime();
	uint64 t2 = t.getMiliTime();

	if (t1 < t2)
		return 1;
	else if (t1 > t2)
		return -1;
	else
		return 0;
}

uint64 AtomicTime::currentNanoTime(ClockType type) {
#if !defined(PLATFORM_WIN) && !defined(PLATFORM_MAC)
	struct timespec cts;
	clock_gettime(type, &cts);

	uint64 time;

	time = cts.tv_sec;
	time = (time * 1000000000) + (uint64)cts.tv_nsec;

	return time;
#else
	switch (type) {
		case REAL_TIME:
			return convertTimePointToNanos(std::chrono::system_clock::now());
		case MONOTONIC_TIME:
			return convertTimePointToNanos(std::chrono::steady_clock::now());
		default:
			return convertTimePointToNanos(std::chrono::high_resolution_clock::now());
	}
#endif
}

bool AtomicTime::isPast() const {
	Time t;
	return compareTo(t) > 0;
}

bool AtomicTime::isPresent() const {
	Time t;
	return compareTo(t) == 0;
}

bool AtomicTime::isFuture() const {
	Time t;
	return compareTo(t) < 0;
}

void AtomicTime::checkForOverflow(struct timespec& ts) {
	if (ts.tv_nsec >= 1000000000) {
		ts.tv_sec++;
		ts.tv_nsec -= 1000000000;
	}
}

uint32 AtomicTime::getTime() const {
	return ts.load(std::memory_order_relaxed).tv_sec;
}

Time AtomicTime::getTimeObject() const {
	Time val(0);
	val.ts = ts.load(std::memory_order_relaxed);

	return val;
}

uint64 AtomicTime::getMiliTime() const {
	struct timespec ts = this->ts.load(std::memory_order_relaxed);

	uint64 time;

	time = ts.tv_sec;
	time = (time * 1000) + (uint64)(ts.tv_nsec / 1000000.f);

	return time;
}

uint64 AtomicTime::getMikroTime() const {
	struct timespec ts = this->ts.load(std::memory_order_relaxed);

	uint64 time;

	time = ts.tv_sec;
	time = (time * 1000000) + (uint64)(ts.tv_nsec / 1000.f);

	return time;
}

uint64 AtomicTime::getNanoTime() const {
	struct timespec ts = this->ts.load(std::memory_order_relaxed);
	uint64 time;

	time = ts.tv_sec;
	time = (time * 1000000000) + (uint64)ts.tv_nsec;

	return time;
}

int64 AtomicTime::miliDifference(Time& t) const {
	return t.getMiliTime() - getMiliTime();
}

int64 AtomicTime::miliDifference() const {
	return Time().getMiliTime() - getMiliTime();
}