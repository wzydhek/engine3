/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/**
 * @author      : theanswer (theanswer@Victors-MacBook-Pro.local)
 * @file        : JSONSerializationType
 * @created     : Saturday Nov 10, 2018 16:12:29 CET
 */

#pragma once

#include "json.hpp"

namespace engine {

	namespace util {
		typedef nlohmann::json JSONSerializationType;
	}
}

using namespace engine::util;
