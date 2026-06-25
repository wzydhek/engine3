#include "NoOpenedChunkException.h"

NoOpenedChunkException::NoOpenedChunkException(IffStream* iffstream) : IffStreamException(iffstream) {
	StringBuffer sstr;
	sstr << "NoOpenedChunkException on file:[" << iffstream->getFileName() << "]\n";
	message = sstr.toString();
}