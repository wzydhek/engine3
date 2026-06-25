#include "Bool.h"

Bool::Bool() : BaseTypeVariable<bool>(false) {
}

Bool::Bool(bool val) : BaseTypeVariable<bool>(val) {
}

Bool::Bool(const Bool& val) : BaseTypeVariable<bool>(val) {
}

Bool& Bool::operator=(const Bool& val) {
	if (this == &val) {
		return *this;
	}

	BaseTypeVariable<bool>::operator=(val);

	return *this;
}

bool Bool::toString(String& str) const {
	if (get() == true)
		str = String("true");
	else
		str = String("false");

	return true;
}

bool Bool::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeBoolean(get());

	return true;
}

bool Bool::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readBoolean();

	return true;
}

bool Bool::parseFromString(const String& str, int version) {
	*this = valueOf(str);

	return true;
}

bool Bool::valueOf(const String& str) {
	if (str == "true") {
		return true;
	} else {
		return false;
	}
}

uint32 Bool::hashCode(bool value) {
	return (uint32)value;
}