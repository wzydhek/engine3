#include "Time.h"

#ifdef PLATFORM_WIN

 static int conv_num(const char** buf, int* dest, int llim, int ulim)
{
	int result = 0;
	int count = 0;

	while (**buf && std::isdigit((unsigned char)**buf))
	{
		result *= 10;
		result += *(*buf)++ - '0';
		count++;
	}

	if (count == 0 || result < llim || result > ulim)
		return 0;

	*dest = result;
	return 1;
 }

 char* strptime(const char* buf, const char* fmt, struct tm* tm)
{
	while (*fmt && *buf)
	{
		if (*fmt == '%')
		{
			fmt++;

			int val = 0;

			switch (*fmt)
			{
			case 'Y':
				if (!conv_num(&buf, &val, 0, 9999))
					return nullptr;
				tm->tm_year = val - 1900;
				break;

			case 'm':
				if (!conv_num(&buf, &val, 1, 12))
					return nullptr;
				tm->tm_mon = val - 1;
				break;

			case 'd':
				if (!conv_num(&buf, &val, 1, 31))
					return nullptr;
				tm->tm_mday = val;
				break;

			case 'H':
				if (!conv_num(&buf, &val, 0, 23))
					return nullptr;
				tm->tm_hour = val;
				break;

			case 'M':
				if (!conv_num(&buf, &val, 0, 59))
					return nullptr;
				tm->tm_min = val;
				break;

			case 'S':
				if (!conv_num(&buf, &val, 0, 60))
					return nullptr;
				tm->tm_sec = val;
				break;

			default:
				return nullptr;
			}

			fmt++;
		}
		else
		{
			if (*fmt != *buf)
				return nullptr;

			fmt++;
			buf++;
		}
	}

	if (*fmt != '\0')
		return nullptr;

	return const_cast<char*>(buf);
 }

#endif

Time::Time(const Time& time) {
	 ts = time.ts;
 }

 bool Time::toString(String& str) const {
	 StringBuffer msg;
	 msg << ts.tv_sec << "," << ts.tv_nsec;

	 str = msg.toString();
	 return true;
 }

 bool Time::parseFromString(const String& str, int version) {
	 int separator = str.indexOf(',');

	 if (separator == -1)
		 return false;

	 String sec = str.subString(0, separator);
	 String nsec = str.subString(separator + 1);

	 ts.tv_sec = Integer::valueOf(sec);
	 ts.tv_nsec = Integer::valueOf(nsec);

	 return true;
 }

 bool Time::toBinaryStream(ObjectOutputStream* stream) {
	 stream->writeLong(ts.tv_sec);
	 stream->writeLong(ts.tv_nsec);

	 return true;
 }

 bool Time::parseFromBinaryStream(ObjectInputStream* stream) {
	 ts.tv_sec = stream->readLong();
	 ts.tv_nsec = stream->readLong();

	 return true;
 }

 void Time::updateToCurrentTime(ClockType type) {
#if !defined(PLATFORM_WIN) && !defined(PLATFORM_MAC)
	 clock_gettime(type, &ts);
#else
	switch (type) {
		case REAL_TIME:
			this->ts = timepointToTimespec(std::chrono::system_clock::now());
			break;
		case MONOTONIC_TIME:
			this->ts = timepointToTimespec(std::chrono::steady_clock::now());
			break;
		default:
			this->ts = timepointToTimespec(std::chrono::high_resolution_clock::now());
			break;
	}
#endif
 }

 void Time::addMiliTime(uint64 mtime) {
	 ts.tv_sec += (long)(mtime / 1000);
	 ts.tv_nsec += (long)((mtime % 1000) * 1000000);

	 checkForOverflow();
 }

 void Time::addMikroTime(uint64 utime) {
	 ts.tv_sec += (long)(utime / 1000000);
	 ts.tv_nsec += (long)((utime % 1000000) * 1000);

	 checkForOverflow();
 }

 void Time::addNanoTime(uint64 ntime) {
	 ts.tv_sec += (long)(ntime / 1000000000);
	 ts.tv_nsec += (long)(ntime % 1000000000);

	 checkForOverflow();
 }

 Time& Time::operator=(const Time& t) {
	 if (this == &t) {
		 return *this;
	 }

	 ts = t.ts;

	 return *this;
 }

 Time& Time::operator=(uint32 seconds) {
	 ts.tv_sec = seconds;
	 ts.tv_nsec = 0;

	 return *this;
 }

 int Time::compareTo(const Time& t) const {
	 if (ts.tv_sec < t.ts.tv_sec)
		 return 1;
	 else if (ts.tv_sec > t.ts.tv_sec)
		 return -1;
	 else {
		 if (ts.tv_nsec < t.ts.tv_nsec)
			 return 1;
		 else if (ts.tv_nsec > t.ts.tv_nsec)
			 return -1;
		 else
			 return 0;
	 }
 }

 String Time::getFormattedTime() const {
#ifndef PLATFORM_WIN
	 char str[100];

	 char* ret = ctime_r(&ts.tv_sec, str);

	 if (ret != nullptr)
		 return String(ret, strlen(str) - 1);
	 else
		 return String("");
#else
	 char* ret = ctime(&ts.tv_sec);

	 if (ret != nullptr)
		 return String(ret, strlen(ret) - 1);
	 else
		 return String("");
#endif
 }

 String Time::getFormattedTimeShort() const {
	 return getFormattedTimeFull(false);
 }

 String Time::getFormattedTimeFull(bool include_ms) const {
	 int ret;
	 struct tm t;
	 String value;
	 char buf[128];
	 int len = sizeof(buf);

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

	 if (ret <= 0 || !include_ms) {
		 value = buf;

		 return value;
	 }

	 len -= ret - 1;

	 auto ret2 = snprintf(&buf[ret], len, ".%09ld", ts.tv_nsec);
	 if (ret2 < 0 || ret2 >= len)
		 return value;

	 len -= ret2;

	 char tz[32];

	 strftime(tz, sizeof(tz), "%z", &t);

	 snprintf(&buf[ret + ret2], len, "%s", tz);

	 value = buf;

	 return value;
 }

 String Time::getFormattedTime(const String& format) const {
	 struct tm t;
	 String value;
	 char buf[4096];

#ifndef PLATFORM_WIN
	 if (localtime_r(&(ts.tv_sec), &t) == nullptr)
		 return value;
#else
	 auto retval = localtime(&(ts.tv_sec));
	 if (retval == nullptr)
		 return value;

	 t = *retval;
#endif

	 int ret = strftime(buf, sizeof(buf), format.toCharArray(), &t);

	 if (ret <= 0)
		 return value;

	 value = buf;

	 return value;
 }

 int Time::compareMiliTo(const Time& t) const {
	 uint64 t1 = getMiliTime();
	 uint64 t2 = t.getMiliTime();

	 if (t1 < t2)
		 return 1;
	 else if (t1 > t2)
		 return -1;
	 else
		 return 0;
 }

 Time Time::fromISO8601(const String& isoString) {
	 struct tm tm = {};
	 const char* str = isoString.toCharArray();

	 // Parse ISO 8601 basic format: "2025-10-03T10:25:30" (with optional Z or timezone)
	 // Note: This handles the basic format, not all ISO 8601 variations
	 char* result = strptime(str, "%Y-%m-%dT%H:%M:%S", &tm);

	 if (result == nullptr) {
		 // Failed to parse, return epoch
		 return Time(0);
	 }

#ifndef PLATFORM_WIN
	 // Use timegm() for UTC conversion (GNU extension, available on Linux/BSD)
	 time_t timestamp = timegm(&tm);
#else
	 // Windows fallback: use mktime and adjust for timezone
	 time_t timestamp = mktime(&tm);
	 timestamp -= _timezone;
#endif

	 if (timestamp == -1) {
		 // Invalid time
		 return Time(0);
	 }

	 // Note: Still limited to 2038 due to uint32 cast in Time constructor
	 return Time((uint32)timestamp);
 }

 uint64 Time::currentNanoTime(ClockType type) {
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

 bool Time::isPast() const {
	 Time t;
	 return compareTo(t) > 0;
 }

 bool Time::isPresent() const {
	 Time t;
	 return compareTo(t) == 0;
 }

 bool Time::isFuture() const {
	 Time t;
	 return compareTo(t) < 0;
 }

 void Time::checkForOverflow() {
	 if (ts.tv_nsec >= 1000000000) {
		 ts.tv_sec++;
		 ts.tv_nsec -= 1000000000;
	 }
 }

 // getters
 uint32 Time::getTime() const {
	 return ts.tv_sec;
 }

 uint64 Time::getMiliTime() const {
	 uint64 time;

	 time = ts.tv_sec;
	 time = (time * 1000) + (uint64)(ts.tv_nsec / 1000000.f);

	 return time;
 }

 uint64 Time::getMikroTime() const {
	 uint64 time;

	 time = ts.tv_sec;
	 time = (time * 1000000) + (uint64)(ts.tv_nsec / 1000.f);

	 return time;
 }

 uint64 Time::getNanoTime() const {
	 uint64 time;

	 time = ts.tv_sec;
	 time = (time * 1000000000) + (uint64)ts.tv_nsec;

	 return time;
 }

 int64 Time::miliDifference(const Time& t) const {
	 return t.getMiliTime() - getMiliTime();
 }

 int64 Time::miliDifference(ClockType type) const {
	 return Time(type).getMiliTime() - getMiliTime();
 }

 struct timespec* Time::getTimeSpec() {
	 return &ts;
 }

 const struct timespec* Time::getTimeSpec() const {
	 return &ts;
 }

 SerializableTime::SerializableTime() : Time(), Variable() {
 }

 SerializableTime::SerializableTime(const SerializableTime& time) : Time(time), Variable() {
 }

 SerializableTime& SerializableTime::operator=(const SerializableTime& time) {
	 if (this == &time) {
		 return *this;
	 }

	 Time::operator=(time);

	 return *this;
 }

 SerializableTime& SerializableTime::operator=(const Time& time) {
	 Time::operator=(time);

	 return *this;
 }

 bool SerializableTime::parseFromBinaryStream(ObjectInputStream* stream) {
	 return Time::parseFromBinaryStream(stream);
 }

 bool SerializableTime::toBinaryStream(ObjectOutputStream* stream) {
	 return Time::toBinaryStream(stream);
 }