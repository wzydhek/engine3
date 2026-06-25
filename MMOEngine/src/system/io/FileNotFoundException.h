/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "IOException.h"
#include "File.h"

namespace sys {
  namespace io {

	class FileNotFoundException : public IOException {
	public:
		FileNotFoundException(File* file);
	};

  } // namespace io
} // namespace sys

using namespace sys::io;
