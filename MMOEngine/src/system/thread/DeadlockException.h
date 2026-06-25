/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * DeadlockException.h
 *
 *  Created on: 03/09/2013
 *      Author: victor
 */

#pragma once

#include "system/lang/Exception.h"

namespace sys {
  namespace thread {
  	  class Lockable;

  	  class DeadlockException {
  		  Lockable* lockable;
  		  String message;
  		  StackTrace trace;

  	  public:
		  DeadlockException();

  		  DeadlockException(const String& msg);

  		  DeadlockException(Lockable* lock, const String& msg = "");

  		  StackTrace* getStackTrace();

  		  void printStackTrace();

  		  Lockable* getLockable();

  		  String getMessage();
  	  };
  }
}

using namespace sys::thread;
