/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"
#include "system/lang/Exception.h"
#include "system/lang/UnicodeString.h"
#include "system/lang/StringBuffer.h"

namespace sys {
  namespace io {

	class UnicodeTokenizer {
		UnicodeString str;

		int index;
		UnicodeString delimeter;

	public:
		UnicodeTokenizer(const UnicodeString& u);
		UnicodeTokenizer(const String& s);
		UnicodeTokenizer(const char* ascii);
		UnicodeTokenizer(const char* ascii, int len);

		int getIntToken();
		uint32 getHexIntToken();
		int64 getLongToken();
		uint64 getUnsignedLongToken();

		float getFloatToken();

		void getStringToken(String& token);
		void getStringToken(StringBuffer& token);
		void getUnicodeToken(UnicodeString& token);

		void finalToken(String& s);
		void finalToken(UnicodeString& u);

		UnicodeString getRemainingString();

		void shiftTokens(int count);

		bool hasMoreTokens() const;

		void setDelimeter(const String& del);

		void setDelimiter(const UnicodeString& del);

		void setDelimiter(const char* ascii);

	private:
		void nextToken(UnicodeString& s);

	};

  } // namespace io
} // namespace sys

using namespace sys::io;
