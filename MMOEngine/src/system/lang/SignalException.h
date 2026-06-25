/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#ifndef __CYGWIN__

#include "Exception.h"
#include "System.h"
#include <signal.h>

namespace sys {
	namespace lang {

template <class SignalExceptionClass> class SignalTranslator {
	private:
		class SingleTonTranslator {
			public:
				SingleTonTranslator() {
					signal(SignalExceptionClass::GetSignalNumber(), SignalHandler);
				}

				static void SignalHandler(int cause) {
					throw SignalExceptionClass(cause);
				}
		};

	public:
		SignalTranslator() {
			static SingleTonTranslator s_objTranslator;
		}
};

template <class SignalCallbackClass> class SignalCallbackTranslator {
	private:
		class SingleTonTranslator {
			public:
				SingleTonTranslator() {
					signal(SignalCallbackClass::GetSignalNumber(), SignalCallbackClass::SignalHandler);
				}
		};

	public:
		SignalCallbackTranslator() {
			static SingleTonTranslator s_objTranslator;
		}
};

	class AbortedException : public Exception {
	public:
		AbortedException(int cause);

		static int GetSignalNumber();
	};

	class FloatingPointException : public Exception {
	public:
		FloatingPointException(int);

		static int GetSignalNumber();
	};

	}
}

using namespace sys::lang;

#endif

