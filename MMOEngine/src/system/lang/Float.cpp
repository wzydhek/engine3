#include "Float.h"

Float::Float() : BaseTypeVariable<float>(0.f) {
}

Float::Float(float val) : BaseTypeVariable<float>(val) {
}

Float::Float(const Float& val) : BaseTypeVariable<float>(val) {
}

Float& Float::operator=(const Float& val) {
	if (this == &val) {
		return *this;
	}

	BaseTypeVariable<float>::operator=(val);

	return *this;
}

bool Float::parseFromString(const String& str, int version) {
	*this = valueOf(str);

	return true;
}

bool Float::toString(String& str) const {
	str = String::valueOf(*this);

	return true;
}

bool Float::toBinaryStream(sys::io::ObjectOutputStream* stream) {
	stream->writeFloat(BaseTypeVariable<float>::get());

	return true;
}

bool Float::parseFromBinaryStream(sys::io::ObjectInputStream* stream) {
	*this = stream->readFloat();

	return true;
}

float Float::valueOf(const String& str) {
	return atof(str.toCharArray());
}

uint32 Float::hashCode(float value) {
	return (uint32)std::hash<float>{}(value);
}

bool Float::areAlmostEqualRelative(float A, float B, float maxRelDiff) {
	float diff = fabs(A - B);

	A = fabs(A);
	B = fabs(B);

	float largest = (B > A) ? B : A;

	if (diff <= largest * maxRelDiff)
		return true;

	return false;
}
