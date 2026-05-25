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
		FileDescriptor() : fileDescriptor(-1), handler(nullptr) {
		}

		virtual ~FileDescriptor() {
		}

		void setBlocking(bool b);

		int getFileDescriptor() const {
			return fileDescriptor;
		}

		IOHandler* getHandler() const {
			return handler;
		}

		void setHandler(IOHandler* hand) {
			handler = hand;
		}
	};

  } // namespace io
} // namespace sys

using namespace sys::io;
