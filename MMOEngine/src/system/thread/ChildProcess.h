/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Process.h"

namespace sys {
  namespace thread {

  	class ChildProcess : public Process {
  	public:
  		ChildProcess();

  		void initialize();

  		void start();

  		virtual bool isDeadlocked();

  		virtual void handleCrash() {
  		}

  		virtual void handleDeadlock() {
  		}

  		void printCrash();
  		void printDeadlock();
  	};

  } // namespace thread
} // namespace sys

using namespace sys::thread;
