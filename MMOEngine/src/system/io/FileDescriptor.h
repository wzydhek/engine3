/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"

namespace sys {
  namespace io {

  	class IOHandler;

	class FileDescriptor {
	protected:
		int fileDescriptor;

		IOHandler* handler;

	public:
		FileDescriptor();

		virtual ~FileDescriptor() {
		}

		void setBlocking(bool b);

		int getFileDescriptor() const;

		IOHandler* getHandler() const;

		void setHandler(IOHandler* hand);
	};

  } // namespace io
} // namespace sys

using namespace sys::io;
