/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang/Exception.h"

namespace engine {
  namespace service {

	class ServiceException : public sys::lang::Exception {
	public:
		ServiceException();

		ServiceException(const String& msg);
	};

  } // namespace service
} // namespace engine

using namespace engine::service;
