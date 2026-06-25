/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/util/iffstream/chunks/Chunk.h"

namespace engine {
 namespace util {

	class Form : public Chunk {
	protected:
		uint32 formType = 0;

	public:
		Form(Chunk* parent, uint32 type, uint32 size, char* data);
		~Form();

		void parseData();
		void parseSubObjects();

		uint32 getFormType();

	};

 }
}

using namespace engine::util;
