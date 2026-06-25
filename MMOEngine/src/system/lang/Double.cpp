#include "Double.h"

Double::Double() : BaseTypeVariable<double>(0) {
}

Double::Double(double val) : BaseTypeVariable<double>(val) {
}

Double::Double(const Double& val) : BaseTypeVariable<double>(val) {
}

Double& Double::operator=(const Double& val) {
	if (this == &val) {
		return *this;
	}

	BaseTypeVariable<double>::operator=(val);

	return *this;
}

bool Double::parseFromString(const String& str, int version) {
	*this = valueOf(str);

	return true;
}

bool Double::toString(String& str) const {
	str = String::valueOf(*this);

	return true;
}

bool Double::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeFloat(get());

	return true;
}

bool Double::parseFromBinaryStream(ObjectInputStream* stream) {
	*this = stream->readFloat();

	return true;
}

float Double::valueOf(const String& str) {
	return atof(str.toCharArray());
}

uint32 Double::hashCode(double value) {
	return (uint32)std::hash<double>{}(value);
}
