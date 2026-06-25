/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "File.h"
#include "OutputStream.h"
#include "FileNotFoundException.h"

namespace sys {
  namespace io {

  	class FileOutputStream : public OutputStream {
  		File* file;

  	public:
		FileOutputStream(File* file);

  		void close();

  		void flush();

  		int write(byte* buf, int len);

  		int write(byte* buf, uint32 off, int len);

  		int write(char ch);

  		int write(int val);

  		int write(uint32 val);

  		int write(long val);

  		int write(int64 val);

  		int write(uint64 val);

  		int write(float val);

  		int write(const char* str);

  		int write(const String& str);

  		FileOutputStream& operator<<(char ch);

  		FileOutputStream& operator<<(int val);

  		FileOutputStream& operator<<(uint32 val);

  		FileOutputStream& operator<<(long val);

  		FileOutputStream& operator<<(int64 val);

  		FileOutputStream& operator<<(uint64 val);

  		FileOutputStream& operator<<(float val);

  		FileOutputStream& operator<<(const char* str);

  		FileOutputStream& operator<<(const String& str);

  	protected:
		void validateWriteable();
  	};
  } // namespace io
} // namespace sys

using namespace sys::io;
