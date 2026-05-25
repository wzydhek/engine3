/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "Exception.h"

namespace sys {
  namespace lang {

	class IllegalStateException : public Exception {
	public:
		IllegalStateException() : Exception("IllegalStateException") {
		}

		IllegalStateException(String s) : Exception("IllegalStateException") {
			message = message + " - " + s;
		}
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
