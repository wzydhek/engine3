/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "IffStreamException.h"

namespace engine {
namespace util {

class InvalidFileTypeException : public IffStreamException {
public:
	InvalidFileTypeException(IffStream* iffstream);
};

} // namespace util
} // namespace engine

using namespace engine::util;
