/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * LuaPanicException.h
 *
 *  Created on: 23/01/2012
 *      Author: victor
 */

#pragma once

#include <lua.hpp>
#include "system/lang/Exception.h"

namespace engine {
namespace lua {

class LuaCallbackException : public Exception {
public:
	LuaCallbackException(lua_State* L, const String& msg);
};

} // namespace lua
} // namespace engine

using namespace engine::lua;
