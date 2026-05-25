/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/**
 * @author      : theanswer (theanswer@Victors-MacBook-Pro.local)
 * @file        : Optional
 * @created     : Monday Apr 01, 2019 19:39:52 CEST
 */

#pragma once

#include "optional.hpp"

namespace sys {
namespace util {
	template<typename T>
	using Optional = std::experimental::optional<T>;
 }
}

using namespace sys::util;
