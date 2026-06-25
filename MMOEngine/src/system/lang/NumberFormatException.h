/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Exception.h"
#include "StringBuffer.h"

namespace sys {
  namespace lang {

	class NumberFormatException : public Exception {
	public:
		NumberFormatException();

		NumberFormatException(int index);

		NumberFormatException(int index, const String& num);

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
