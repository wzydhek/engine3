#include "InvalidChunkTypeException.h"

InvalidChunkTypeException::InvalidChunkTypeException(IffStream* iffstream) : IffStreamException(iffstream) {
	StringBuffer sstr;
	sstr << "InvalidChunkTypeException on file:[" << iffstream->getFileName() << "]\n";
	message = sstr.toString();
}