/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang/Exception.h"
#include "system/lang/System.h"
#include "system/lang/StringBuffer.h"

namespace sys {
  namespace io {

	class StreamIndexOutOfBoundsException : public Exception {
		class Stream const* stream;

	public:
		StreamIndexOutOfBoundsException(const Stream* strm, int index);

		const Stream* getStream() const;

	};

  } // namespace io
} // namespace sys

using namespace sys::io;
