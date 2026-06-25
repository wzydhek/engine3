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

namespace engine {
namespace lua {

class LuaPanicException : public Exception {
public:
	LuaPanicException(const String& msg);
};

} // namespace lua
} // namespace engine

using namespace engine::lua;
