/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "engine/util/iffstream/chunks/Chunk.h"

namespace engine {
 namespace util {

	class Data : public Chunk {
	protected:

	public:
		Data(Chunk* parent, uint32 id, uint32 size, char* buffer);

	};

 }
}

using namespace engine::util;
