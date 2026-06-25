/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include <cerrno>
#include <string.h>
#include "system/lang/Exception.h"

namespace sys {
  namespace io {

	class IOException : public Exception {
	public:
		IOException(const String& msg);

	};

  } // namespace io
} // namespace sys

using namespace sys::io;

