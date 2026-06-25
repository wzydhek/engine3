/**
 * @author      : theanswer (theanswer@hyperv)
 * @file        : ConstString
 * @created     : Monday Sep 02, 2019 12:18:09 UTC
 */

#include "ConstString.h"
#include "String.h"

constexpr uint32 sys::lang::ConstString::crctable[];

constexpr ConstString::ConstString(const char* a) : p_(a), sz_(strlen(a)) {
}

constexpr ConstString::ConstString(const char* a, std::size_t len) : p_(a), sz_(len) {
}

String ConstString::toString() const {
	return String(p_, sz_);
}

constexpr std::size_t ConstString::indexOf(const char ch) const {
	for (std::size_t i = 0; i < sz_; ++i) {
		if (p_[i] == ch)
			return i;
	}

	return npos;
}

constexpr bool ConstString::contains(const char* str) const {
	return indexOf(str) != npos;
}

constexpr int ConstString::strlen(const char* a) {
	int s = 0;

	while (a[s]) {
		++s;
	}

	return s;
}

constexpr int ConstString::compare(const char* x, const char* y) {
	while (*x && *y) {
		if (*x != *y)
			return 0;

		x++;
		y++;
	}

	return (*y == '\0');
}

// naive impl
constexpr const char* ConstString::strstr(const char* X, const char* Y) {
	while (*X != '\0') {
		if ((*X == *Y) && compare(X, Y))
			return X;
		X++;
	}

	return nullptr;
}

constexpr std::size_t ConstString::indexOf(const char* str, std::size_t fromIndex) const {
	if (fromIndex >= size())
		return npos;

	auto position = strstr(begin() + fromIndex, str);

	if (position != nullptr)
		return position - begin();
	else
		return npos;
}

constexpr char ConstString::operator[](std::size_t n) const {
	return n < sz_ ? p_[n] : throw std::out_of_range("");
}

constexpr std::size_t ConstString::length() const {
	return sz_;
}

constexpr const char* ConstString::end() const {
	return p_ + sz_;
}

constexpr uint32 ConstString::hashCode(const char* string, uint32 startCRC) {
	return *string ? hashCode(string + 1, crctable[((startCRC >> 24) ^ (byte)(*string)) & 0xFF] ^ (startCRC << 8)) : ~startCRC;
}

constexpr uint32 ConstString::hashCode() const {
	return hashCode(p_);
}
//
//constexpr std::size_t ConstString::size() const {
//	return sz_;
//}
//
//constexpr const char* ConstString::begin() const {
//	return p_;
//}