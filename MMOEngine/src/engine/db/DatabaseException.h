/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"

namespace engine {
  namespace db {

	class DatabaseException : public Exception {
	public:
		DatabaseException(const String& msg) : Exception(msg) {
		}
		
	};

  } // namespace db
} // namespace engine

using namespace engine::db;
