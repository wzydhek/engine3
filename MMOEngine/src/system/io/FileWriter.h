/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
#pragma once

#include "File.h"
#include "Writer.h"
#include "FileNotFoundException.h"
#include "IOException.h"

namespace sys {
  namespace io {

	class FileWriterMkDirException : public IOException {
	public:
		FileWriterMkDirException(const String& msg);
	};

	class FileWriterOpenException : public IOException {
	public:
		FileWriterOpenException(const String& msg);
	};

  	class FileWriter : public Writer {
	protected:
  		File* file;
		mutable Mutex validateMutex;
		mutable AtomicBoolean isOpen = false;
		bool append = false;

  	public:
		constexpr const static int bufferLength = 64;

		FileWriter(File* file, bool append = false, bool delayOpen = false);

  		void close() override;

  		void flush() override;

  		int write(const char* str, int len) override;

  		int write(const char* str, uint32 off, int len) override;

  		int write(char ch);

  		int write(int val);

  		int write(uint32 val);

  		int write(long val);

  		int write(int64 val);

  		int write(uint64 val);

  		int write(float val);

  		int write(const char* str);

  		int write(const String& str);

  		int writeLine(const String& str);

  		FileWriter& operator<<(char ch);

  		FileWriter& operator<<(int val);

  		FileWriter& operator<<(uint32 val);

  		FileWriter& operator<<(long val);

  		FileWriter& operator<<(int64 val);

  		FileWriter& operator<<(uint64 val);

  		FileWriter& operator<<(float val);

  		FileWriter& operator<<(const char* str);

  		FileWriter& operator<<(const String& str);

		FileWriter& operator<<(const StringBuffer& str);

  		File* getFile();

		inline const File* getFile() const;

  	protected:
		void validateWriteable();
  	};
  } // namespace io
} // namespace sys

using namespace sys::io;
