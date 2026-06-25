#include "StreamIndexOutOfBoundsException.h"

StreamIndexOutOfBoundsException::StreamIndexOutOfBoundsException(const Stream* strm, int index) : Exception(), stream(strm) {
	StringBuffer str;
	str << "StreamIndexOutOfBoundsException at " << index << "\n";
	message = str.toString();
	// System::out << message;
}

const Stream* StreamIndexOutOfBoundsException::getStream() const {
	return stream;
}
