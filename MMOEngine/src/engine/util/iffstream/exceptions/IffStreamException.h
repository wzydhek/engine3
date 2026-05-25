/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/lang.h"
#include "engine/util/iffstream/IffStream.h"

class IffStreamException : public Exception {
protected:
	IffStream* iffStream;

public:
	IffStreamException(IffStream* stream) : Exception("IffStreamException\n") {
		iffStream = stream;
	}

	IffStream* getIffStream() {
		return iffStream;
	}

};
