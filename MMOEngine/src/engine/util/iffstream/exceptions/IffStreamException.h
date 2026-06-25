/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/util/iffstream/IffStream.h"

namespace engine {
namespace util {

class IffStreamException : public Exception {
protected:
	IffStream* iffStream;

public:
	IffStreamException(IffStream* stream);

	IffStream* getIffStream();

};

} // namespace util
} // namespace engine

using namespace engine::util;
