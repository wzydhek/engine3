/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

namespace sys {
  namespace io {

  	class FileDescriptor;

  	class IOHandler {
  	public:
  		virtual void handleInput(FileDescriptor* descriptor) {
  		}

  		virtual void handleOutput(FileDescriptor* descriptor) {
  		}

  		virtual void handleHangup(FileDescriptor* descriptor) {
  		}

  		virtual void handleError(FileDescriptor* descriptor) {
  		}

  	};

  } // namespace io
} // namespace sys

using namespace sys::io;
