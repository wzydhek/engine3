/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/io/Serializable.h"
#include "system/lang/String.h"
#include "Vector3.h"
#include "Matrix3.h"

namespace engine {
namespace util {
namespace u3d {

class Quaternion : public Variable {
protected:
	float w, x, y, z;

public:
	static const Quaternion ZERO;
	static const Quaternion IDENTITY;

public:
	/**
	 * Creates a quaternion initialized to the quaternion identity.
	 */
	Quaternion();

	Quaternion(const Quaternion& qt);

	/**
	 * Create a quaternion based on four scalar values.
	 * float fx = vector x
	 * float fy = vector y
	 * float fz = vector z
	 * float fw = scalar
	 */
	Quaternion(float fw, float fx, float fy, float fz);

	/**
	 * Create a quaternion based on a vector and an angle of direction.
	 * \param v The vector to base rotation off of. Should be a UNIT vector.
	 * \param angle The angle in radians.
	 */
	Quaternion(const Vector3& axis, float angle);

	// inline explicit Quaternion(const Matrix4& matrix) {
	// }

	virtual ~Quaternion() {
	}

	/**
	 * Returns the string representation of the vector in (x, y, z) format.
	 */
	/*
		void addSerializableVariables() {
			addSerializableVariable("w", &w);
			addSerializableVariable("x", &x);
			addSerializableVariable("y", &y);
			addSerializableVariable("z", &z);
		}
	 */

	bool readObjectMember(ObjectInputStream* stream, const String& name);

	int writeObjectMembers(ObjectOutputStream* stream);

	bool toBinaryStream(ObjectOutputStream* stream);

	bool parseFromBinaryStream(ObjectInputStream* stream);

	Quaternion& operator=(const Quaternion& q);

	Quaternion operator+(const Quaternion& q) const;

	Quaternion operator-(const Quaternion& q) const;

	Quaternion operator*(const Quaternion& q) const;

	Quaternion operator*(const float scalar) const;

	bool operator==(const Quaternion& q) const;

	bool operator!=(const Quaternion& q) const;

	float dotProduct(const Quaternion& q) const;

	float lengthSquared() const;

	float length() const;

	float normalize();

	/**
	* Computes the inverse of this quaternion.
	* @return The inverse quaternion.
	*/
	Quaternion inverse() const;

	/**
	 * Rotates the quaternion on an axis of rotation n degrees.
	 * \param axis The unit axis of rotation.
	 * \param degrees How many degrees to rotate the quaternion.
	 * \return Returns this quaternion, rotated.
	 */
	Quaternion& rotate(const Vector3& axis, float degrees);

	/**
	 * Converts this quaternion to a matrix4.
	 * \return Matrix4 The matrix4 equivalent of this quaternion.
	 */
	// inline Matrix4 toMatrix() { }

	Matrix3 toMatrix3() const;

	float getX() const;

	float getY() const;

	float getZ() const;

	float getW() const;

	float getRadians() const;

	Quaternion getConjugate() const;

	float getSpecialDegrees() const;

	float getDegrees() const;

	bool isIdentity() const;

	void set(float fw, float fx, float fy, float fz);

	void setHeadingDirection(float radians);
};

} // namespace u3d
} // namespace util
} // namespace engine

using namespace engine::util::u3d;
