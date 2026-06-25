/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "File.h"
#include "InputStream.h"
#include "FileNotFoundException.h"

namespace sys {
  namespace io {

  	class FileInputStream : public InputStream {
  	protected:
  		File* file;

  	public:
		FileInputStream(File* file);

  		void close();

  		int read(byte* buf, int len);

  		int read(byte* buf, uint32 off, int len);

  		int skip(int n);

  	protected:
		void validateReadable();
  	};

  } // namespace io
} // namespace sys

using namespace sys::io;
