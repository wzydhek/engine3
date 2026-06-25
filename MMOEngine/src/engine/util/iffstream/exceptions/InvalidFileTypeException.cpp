#include "InvalidFileTypeException.h"

InvalidFileTypeException::InvalidFileTypeException(IffStream* iffstream) : IffStreamException(iffstream) {
	StringBuffer sstr;
	sstr << "InvalidFileTypeException on file:[" << iffstream->getFileName() << "]\n";
	message = sstr.toString();
}