#include "IffStreamException.h"

IffStreamException::IffStreamException(IffStream* stream) : Exception("IffStreamException\n") {
	iffStream = stream;
}

IffStream* IffStreamException::getIffStream() {
	return iffStream;
}