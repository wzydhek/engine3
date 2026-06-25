#include "NoChunksException.h"

NoChunksException::NoChunksException(IffStream* iffstream) : IffStreamException(iffstream) {
	StringBuffer sstr;
	sstr << "NoChunksException on file:[" << iffstream->getFileName() << "]\n";
	message = sstr.toString();
}