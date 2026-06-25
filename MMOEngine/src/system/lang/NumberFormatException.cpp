#include "NumberFormatException.h"

NumberFormatException::NumberFormatException() : Exception("NumberFormatException\n") {
}

NumberFormatException::NumberFormatException(int index) : Exception() {
	StringBuffer str;
	str << "NumberFormatException at " << index << "\n";
	message = str.toString();
}

NumberFormatException::NumberFormatException(int index, const String& num) : Exception() {
	StringBuffer str;
	str << "NumberFormatException at " << index << " while converting String:[ " << num << "]\n";
	message = str.toString();
}
