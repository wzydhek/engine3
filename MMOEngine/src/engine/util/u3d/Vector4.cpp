#include "Vector4.h"

Vector4::Vector4() {
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	v[3] = 0;
}

Vector4::Vector4(float px, float py, float pz, float pw) {
	v[0] = px;
	v[1] = py;
	v[2] = pz;
	v[3] = pw;
}

Vector4::Vector4(const float values[4]) {
	memcpy(v, values, sizeof(v));
}

Vector4::Vector4(const Vector4& vector) {
	v[0] = vector.v[0];
	v[1] = vector.v[1];
	v[2] = vector.v[2];
	v[3] = vector.v[3];
}

Vector4& Vector4::operator=(const Vector4& vector) {
	if (this == &vector)
		return *this;

	v[0] = vector.v[0];
	v[1] = vector.v[1];
	v[2] = vector.v[2];
	v[3] = vector.v[3];

	return *this;
}

// Boolean operators
bool Vector4::operator==(const Vector4& vec) const {
	return memcmp(v, vec.v, sizeof(v));
}

void Vector4::setZero() {
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	v[3] = 0;
}

bool Vector4::isZero() const {
	return v[0] == 0 && v[1] == 0 && v[2] == 0 && v[3] == 0;
}

float& Vector4::operator[](uint32 index) {
#ifdef VECTORS_OUT_OF_BOUNDS_CHECK
	if (index > 3)
		throw ArrayIndexOutOfBoundsException(index);
#endif
	return v[index];
}

float Vector4::operator[](uint32 index) const {
#ifdef VECTORS_OUT_OF_BOUNDS_CHECK
	if (index > 3)
		throw ArrayIndexOutOfBoundsException(index);
#endif
	return v[index];
}

float* Vector4::toFloatArray() {
	return v;
}

const float* Vector4::toFloatArray() const {
	return v;
}