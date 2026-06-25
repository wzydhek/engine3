/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/platform.h"
#include "String.h"
#include "StackTrace.h"

namespace sys {
  namespace lang {

	class Exception {
	protected:
		String message;

		StackTrace trace;

	public:
		Exception();
		Exception(const String& msg);

		virtual ~Exception();

		void printStackTrace() const;
		void printMessage() const;

		// setters and getters
		void setMessage(const String& msg);

	 	const String& getMessage() const;

		const StackTrace& getStackTrace() const;

		const char* what() const;

	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;
