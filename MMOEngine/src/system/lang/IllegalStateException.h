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
		IllegalStateException();

		IllegalStateException(String s);
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
