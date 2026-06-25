/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"
#include "system/lang/Exception.h"
#include "system/lang/String.h"
#include "system/lang/StringBuffer.h"

namespace sys {
  namespace io {

	class StringTokenizer {
		String str;

		int index;
		String delimiter;

	public:
		StringTokenizer(const String& s);

		int getIntToken();
		uint32 getHexIntToken();
		int64 getLongToken();
		uint64 getUnsignedLongToken();
		float getFloatToken();

		void getStringToken(String& token);

		String getStringToken();

		void getStringToken(StringBuffer& token);

		void finalToken(String& s);

		String getRemainingString();

		void shiftTokens(int count);

		bool hasMoreTokens() const;

		void setDelimeter(const String& del);

		void setDelimiter(const String& del);

	private:
		void nextToken(String& s);
		void nextToken(StringBuffer& s);

	};

  } // namespace io
} // namespace sys

using namespace sys::io;
