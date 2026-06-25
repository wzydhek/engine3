/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "File.h"
#include "Reader.h"
#include "FileNotFoundException.h"

namespace sys {
  namespace io {

  	class FileReader : public Reader {
  		File* file;

  	public:
		FileReader(File* file);

  		void close();

  		int read(char* buf, int len);

  		int read(char* buf, uint32 off, int len);

  		bool readLine(String& line);

  		int skip(int n);

  	protected:
		void validateReadable();
  	};

  } // namespace io
} // namespace sys

using namespace sys::io;
