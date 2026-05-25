/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Exception.h"

namespace sys {
  namespace lang {

	class DivisionByZeroException : public Exception {
	public:
		DivisionByZeroException() : Exception("DivisionByZeroException") {
		}
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
