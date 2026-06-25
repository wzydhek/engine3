#include "Long.h"

Long::Long() : BaseTypeVariable<int64>(0) {
}

Long::Long(int64 val) : BaseTypeVariable<int64>(val) {
}

Long::Long(const Long& val) : BaseTypeVariable<int64>(val) {
}

Long& Long::operator=(const Long& val) {
	if (this == &val) {
		return *this;
	}

	BaseTypeVariable<int64>::operator=(val);

	return *this;
}

bool Long::toString(String& str) const {
	str = String::valueOf(*this);

	return true;
}

bool Long::parseFromString(const String& str, int version) {
	*this = valueOf(str);

	return true;
}

bool Long::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeSignedLong(get());

	return true;
}

bool Long::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readSignedLong();

	return true;
}

uint32 Long::hashCode(uint64 value) {
	uint64 key = value;

	key = (~key) + (key << 18); // key = (key << 18) - key - 1;
	key = key ^ (key >> 31);
	key = key * 21; // key = (key + (key << 2)) + (key << 4);
	key = key ^ (key >> 11);
	key = key + (key << 6);
	key = key ^ (key >> 22);

	return (uint32)key;
}

int64 Long::valueOf(const String& str) {
	int64 val = 0;
	int64 mul = 1;

	for (int i = str.length() - 1; i >= 0; --i) {
		char ch = str.charAt(i);

		if (i == 0 && ch == '-') {
			val *= -1;
			break;
		}

		val += Integer::valueOf(ch) * mul;

		mul *= 10;
	}

	return val;
}

uint64 Long::unsignedvalueOf(const String& str) {
	uint64 val = 0;
	uint64 mul = 1;

	for (int i = str.length() - 1; i >= 0; --i) {
		int digit = Integer::valueOf(str.charAt(i));

		val += digit * mul;

		mul *= 10;
	}

	return val;
}

String Long::toString(int64 val) {
	String str;

	toString(str, val);

	return str;
}

void Long::toString(String& str, int64 val) {
	char buf[32];

#ifdef PLATFORM_WIN
	int written = snprintf(buf, 32, "%I64d", val);
#else
	int written = snprintf(buf, 32, "%lld", val);
#endif
	E3_ASSERT(written >= 0 && written < 32);

	str = String(buf, written);
}

String Long::toString(uint64 val) {
	String str;

	toString(str, val);

	return str;
}

void Long::toString(String& str, uint64 val) {
	char buf[32];

#ifdef PLATFORM_WIN
	int written = snprintf(buf, 32, "%I64u", val);
#else
	int written = snprintf(buf, 32, "%llu", val);
#endif
	E3_ASSERT(written >= 0 && written < 32);

	str = String(buf, written);
}

UnsignedLong::UnsignedLong() : BaseTypeVariable<uint64>(0) {
}

UnsignedLong::UnsignedLong(uint64 val) : BaseTypeVariable<uint64>(val) {
}

UnsignedLong::UnsignedLong(const UnsignedLong& val) : BaseTypeVariable<uint64>(val) {
}

UnsignedLong& UnsignedLong::operator=(const UnsignedLong& val) {
	if (this == &val) {
		return *this;
	}

	BaseTypeVariable<uint64>::operator=(val);

	return *this;
}

bool UnsignedLong::toString(String& str) const {
	str = String::valueOf(*this);

	return true;
}

bool UnsignedLong::parseFromString(const String& str, int version) {
	*this = valueOf(str);

	return true;
}

bool UnsignedLong::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeLong(BaseTypeVariable<uint64>::get());

	return true;
}

bool UnsignedLong::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readLong();

	return true;
}

uint64 UnsignedLong::hexvalueOf(const String& str) {
	return std::strtoull(str.toCharArray(), nullptr, 16);
}

uint64 UnsignedLong::valueOf(const String& str) {
	uint64 val = 0;
	uint64 mul = 1;

	for (int i = str.length() - 1; i >= 0; --i) {
		int digit = Integer::valueOf(str.charAt(i));

		val += digit * mul;

		mul *= 10;
	}

	return val;
}

uint32 UnsignedLong::hashCode(int64 value) {
	return Long::hashCode(value);
}
