#include "Vector3.h"

Vector3::Vector3() noexcept {
	values[0] = 0;
	values[1] = 0;
	values[2] = 0;
}

Vector3::Vector3(const float fx, const float fy, const float fz) noexcept {
	values[0] = fx;
	values[1] = fy;
	values[2] = fz;
}

bool Vector3::toBinaryStream(ObjectOutputStream* stream) {
	stream->writeFloat(values[0]);
	stream->writeFloat(values[2]);
	stream->writeFloat(values[1]);

	return true;
}

bool Vector3::parseFromBinaryStream(ObjectInputStream* stream) {
	values[0] = stream->readFloat();
	values[2] = stream->readFloat();
	values[1] = stream->readFloat();

	return true;
}

/**
 * Returns the exact length of the vector. Should be used sparingly as it
 * uses much CPU power. Use squaredLength for comparing lengths.
 */
float Vector3::length() const {
	return Math::sqrt(values[0] * values[0] + values[1] * values[1] + values[2] * values[2]);
}

float Vector3::length2d() const {
	return Math::sqrt(values[0] * values[0] + values[1] * values[1]);
}

/**
 * Returns the length before being squared. Good for comparing lengths.
 */
float Vector3::squaredLength() const {
	return (values[0] * values[0] + values[1] * values[1] + values[2] * values[2]);
}

float Vector3::squaredLength2d() const {
	return (values[0] * values[0] + values[1] * values[1]);
}

/**
 * Returns the real distance to another vector. Should not be used for comparisons.
 * See squaredDistanceTo(.
 * \param v The vector to get the distance to.
 * \return Returns the float representation of the distance between the two vectors.
 */
float Vector3::distanceTo(const Vector3& v) const {
	return (*this - v).length();
}

float Vector3::distanceTo2d(const Vector3& v) const {
	return (*this - v).length2d();
}

/**
 * Good for comparisons of distance. Saves the cpu usage needed for sqrt.
 * \param v The vector to get the distance to.
 * \return Returns the float representation of the distance between two points prior to application of a square root.
 */
float Vector3::squaredDistanceTo(const Vector3& v) const {
	return (*this - v).squaredLength();
}

float Vector3::squaredDistanceTo2d(const Vector3& v) const {
	return (*this - v).squaredLength2d();
}

/**
 * This method returns the midpoint between this vector and another vector.
 * \param v The vector to find a midpoint in conjunction with.
 * \return Returns a vector half way in between this vector and the passed in vector.
 */
Vector3 Vector3::midPoint(const Vector3& v) const {
	return Vector3((values[0] + v.values[0]) * 0.5f, (values[1] + v.values[1]) * 0.5f, (values[2] + v.values[2]) * 0.5f);
}

/**
 * This method is used to calculate the angle between two vectors. If both
 * are unit vectors then the product is the cosine of the angle; otherwise,
 * the dot product must be divided by the product of the length
 */
float Vector3::dotProduct(const Vector3& v) const {
	return (values[0] * v.values[0] + values[1] * v.values[1] + values[2] * v.values[2]);
}

float Vector3::product() const {
	return dotProduct(*this);
}

/**
 * The cross product returns the vector which is perpendicular to this vector
 * and the vector passed in. For example, if you have two vectors in the same
 * geometric plane, then the vector would be on the plane perpendicular to that
 * plane, and the vector perpendicular to the two vectors. Imagine a 3D o
 */
Vector3 Vector3::crossProduct(const Vector3& v) const {
	return Vector3(values[1] * v.values[2] - values[2] * v.values[1], values[2] * v.values[0] - values[0] * v.values[2], values[0] * v.values[1] - values[1] * v.values[0]);
}

/**
 * Returns the string representation of the vector in (x, y, z) format.
 */
String Vector3::toString() const {
	StringBuffer sb;
	sb << "(x:" << values[0] << ", y:" << values[1] << ", z:" << values[2] << ")";
	return sb.toString();
}

String Vector3::toStringData() const {
	return toString();
}

float Vector3::operator[](uint32 index) const {
#ifdef VECTORS_OUT_OF_BOUNDS_CHECK
	if (index > 2)
		throw ArrayIndexOutOfBoundsException(index);
#endif
	return values[index];
}

float& Vector3::operator[](uint32 index) {
#ifdef VECTORS_OUT_OF_BOUNDS_CHECK
	if (index > 2)
		throw ArrayIndexOutOfBoundsException(index);
#endif
	return values[index];
}

float* Vector3::toFloatArray() {
	return values;
}

const float* Vector3::toFloatArray() const {
	return values;
}

Vector3& Vector3::operator=(const float scalar) {
	values[0] = scalar;
	values[1] = scalar;
	values[2] = scalar;

	return *this;
}

Vector3 Vector3::operator+(const Vector3& v) const {
	return Vector3(values[0] + v.values[0], values[1] + v.values[1], values[2] + v.values[2]);
}

Vector3 Vector3::operator-(const Vector3& v) const {
	return Vector3(values[0] - v.values[0], values[1] - v.values[1], values[2] - v.values[2]);
}

Vector3 Vector3::operator*(const Vector3& v) const {
	return Vector3(values[0] * v.values[0], values[1] * v.values[1], values[2] * v.values[2]);
}

Vector3 Vector3::operator*(const Matrix4& mat) const {
	return Vector3(values[0] * mat[0][0] + values[1] * mat[1][0] + values[2] * mat[2][0] + mat[3][0], values[0] * mat[0][1] + values[1] * mat[1][1] + values[2] * mat[2][1] + mat[3][1], values[0] * mat[0][2] + values[1] * mat[1][2] + values[2] * mat[2][2] + mat[3][2]);
}

Vector3 Vector3::operator/(const Vector3& v) const {
	return Vector3(values[0] / v.values[0], values[1] / v.values[1], values[2] / v.values[2]);
}

Vector3& Vector3::operator+=(const Vector3& v) {
	values[0] += v.values[0];
	values[1] += v.values[1];
	values[2] += v.values[2];

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& v) {
	values[0] -= v.values[0];
	values[1] -= v.values[1];
	values[2] -= v.values[2];

	return *this;
}

Vector3& Vector3::operator*=(const Vector3& v) {
	values[0] *= v.values[0];
	values[1] *= v.values[1];
	values[2] *= v.values[2];

	return *this;
}

Vector3& Vector3::operator/=(const Vector3& v) {
	values[0] /= v.values[0];
	values[1] /= v.values[1];
	values[2] /= v.values[2];

	return *this;
}


// Boolean operators
bool Vector3::operator==(const Vector3& v) const {
	return values[0] == v.values[0] && values[1] == v.values[1] && values[2] == v.values[2];
}

bool Vector3::operator!=(const Vector3& v) const {
	return values[0] != v.values[0] || values[1] != v.values[1] || values[2] != v.values[2];
}

bool Vector3::operator<(const Vector3& v) const {
	if (values[0] < v.values[0] && values[1] < v.values[1] && values[2] < v.values[2])
		return true;

	return false;
}

bool Vector3::operator>(const Vector3& v) const {
	if (values[0] > v.values[0] && values[1] > v.values[1] && values[2] > v.values[2])
		return true;

	return false;
}

Vector3 Vector3::getMin(const Vector3& vec) const {
	return Vector3(Math::min(values[0], vec.values[0]), Math::min(values[1], vec.values[1]), Math::min(values[2], vec.values[2]));
}

Vector3 Vector3::getMax(const Vector3& vec) const {
	return Vector3(Math::max(values[0], vec.values[0]), Math::max(values[1], vec.values[1]), Math::max(values[2], vec.values[2]));
}

float Vector3::normalize() {
	float magnitude = length();

	values[0] /= magnitude;
	values[1] /= magnitude;
	values[2] /= magnitude;

	return magnitude;
}

// Getters
float Vector3::getX() const {
	return values[0];
}

float Vector3::getY() const {
	return values[1];
}

float Vector3::getZ() const {
	return values[2];
}

// Setters
void Vector3::setX(float xv) {
	values[0] = xv;
}

void Vector3::setY(float yv) {
	values[1] = yv;
}

void Vector3::setZ(float zv) {
	values[2] = zv;
}

void Vector3::set(float x, float z, float y) {
	this->values[0] = x;
	this->values[1] = y;
	this->values[2] = z;
}

SerializableVector3::SerializableVector3() {
}

SerializableVector3::SerializableVector3(const SerializableVector3& v) : Vector3(v), Variable() {
}

SerializableVector3::SerializableVector3(const Vector3& vec) : Vector3(vec) {
}

SerializableVector3& SerializableVector3::operator=(const SerializableVector3& v) {
	if (this == &v) {
		return *this;
	}

	Vector3::operator=(v);

	return *this;
}

SerializableVector3& SerializableVector3::operator=(const Vector3& v) {
	Vector3::operator=(v);

	return *this;
}

bool SerializableVector3::toBinaryStream(ObjectOutputStream* stream) {
	return Vector3::toBinaryStream(stream);
}

bool SerializableVector3::parseFromBinaryStream(ObjectInputStream* stream) {
	return Vector3::parseFromBinaryStream(stream);
}