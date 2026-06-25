/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "system/io/Serializable.h"
#include "system/lang/Math.h"
#include "system/lang/DivisionByZeroException.h"

#include "Matrix4.h"

namespace engine {
  namespace util {
  	namespace u3d {

	class Vector3 {
	protected:
		float values[3];

	public:
		static const Vector3 ZERO;

		//Axis Representations
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;

	public:
		Vector3() noexcept;

		Vector3(const Vector3& vec) = default;

		Vector3(const float fx, const float fy, const float fz) noexcept;

		/**
		 * Converts a 3 dimensional float array into a Vector3.
		 */
		inline explicit Vector3(const float coord[3]) noexcept {
			values[0] = coord[0];
			values[1] = coord[1];
			values[2] = coord[2];
		}

		/**
		 * Converts a 3 dimensional int array into a Vector3.
		 */
		inline explicit Vector3(const int coord[3]) noexcept {
			values[0] = (float) coord[0];
			values[1] = (float) coord[1];
			values[2] = (float) coord[2];
		}

		/**
		 * Converts a float scalar to a Vector3.
		 */
		inline explicit Vector3(const float scalar) noexcept {
			values[0] = scalar;
			values[1] = scalar;
			values[2] = scalar;
		}

	public:

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		/**
		 * Returns the exact length of the vector. Should be used sparingly as it
		 * uses much CPU power. Use squaredLength for comparing lengths.
		 */
		float length() const;

		float length2d() const;

		/**
		 * Returns the length before being squared. Good for comparing lengths.
		 */
		float squaredLength() const;

		float squaredLength2d() const;

		/**
		 * Returns the real distance to another vector. Should not be used for comparisons.
		 * See squaredDistanceTo(.
		 * \param v The vector to get the distance to.
		 * \return Returns the float representation of the distance between the two vectors.
		 */
		float distanceTo(const Vector3& v) const;

		float distanceTo2d(const Vector3& v) const;

		/**
		 * Good for comparisons of distance. Saves the cpu usage needed for sqrt.
		 * \param v The vector to get the distance to.
		 * \return Returns the float representation of the distance between two points prior to application of a square root.
		 */
		float squaredDistanceTo(const Vector3& v) const;

		float squaredDistanceTo2d(const Vector3& v) const;

		/**
		 * This method returns the midpoint between this vector and another vector.
		 * \param v The vector to find a midpoint in conjunction with.
		 * \return Returns a vector half way in between this vector and the passed in vector.
		 */
		Vector3 midPoint(const Vector3& v) const;

		/**
		 * This method is used to calculate the angle between two vectors. If both
		 * are unit vectors then the product is the cosine of the angle; otherwise,
		 * the dot product must be divided by the product of the length
		 */
		float dotProduct(const Vector3& v) const;

		float product() const;

		/**
		 * The cross product returns the vector which is perpendicular to this vector
		 * and the vector passed in. For example, if you have two vectors in the same
		 * geometric plane, then the vector would be on the plane perpendicular to that
		 * plane, and the vector perpendicular to the two vectors. Imagine a 3D o
		 */
		Vector3 crossProduct(const Vector3& v) const;

		/**
		 * Returns the string representation of the vector in (x, y, z) format.
		 */
		String toString() const;

		String toStringData() const;

		float operator[](uint32 index) const;

		float& operator[](uint32 index);

		float* toFloatArray();

		const float* toFloatArray() const;

		Vector3& operator = (const Vector3& v)  = default;

		Vector3& operator=(const float scalar);

		Vector3 operator+(const Vector3& v) const;

		Vector3 operator-(const Vector3& v) const;

		Vector3 operator*(const Vector3& v) const;

		Vector3 operator*(const Matrix4& mat) const;

		Vector3 operator/(const Vector3& v) const;

		Vector3& operator+=(const Vector3& v);

		Vector3& operator-=(const Vector3& v);

		Vector3& operator*=(const Vector3& v);

		Vector3& operator/=(const Vector3& v);

		inline friend Vector3 operator + (const Vector3& v, const float scalar) {
			return Vector3(v.values[0] + scalar, v.values[1] + scalar, v.values[2] + scalar);
		}

		inline friend Vector3 operator + (const float scalar, const Vector3& v) {
			return Vector3(scalar + v.values[0], scalar + v.values[1], scalar + v.values[2]);
		}

		inline friend Vector3 operator - (const Vector3& v, const float scalar) {
			return Vector3(v.values[0] - scalar, v.values[1] - scalar, v.values[2] - scalar);
		}

		inline friend Vector3 operator - (const float scalar, const Vector3& v) {
			return Vector3(scalar - v.values[0], scalar - v.values[1], scalar - v.values[2]);
		}

		inline friend Vector3 operator * (const Vector3& v, const float scalar) {
			return Vector3(v.values[0] * scalar, v.values[1] * scalar, v.values[2] * scalar);
		}

		inline friend Vector3 operator * (const float scalar, const Vector3& v) {
			return Vector3(scalar * v.values[0], scalar * v.values[1], scalar * v.values[2]);
		}

		inline friend Vector3 operator / (const Vector3& v, const float scalar) {
			if (scalar == 0.0f)
				throw DivisionByZeroException();

			return Vector3(v.values[0] / scalar, v.values[1] / scalar, v.values[2] / scalar);
		}

		inline friend Vector3 operator / (const float scalar, const Vector3& v) {
			return Vector3(scalar / v.values[0], scalar / v.values[1], scalar / v.values[2]);
		}

		//Boolean operators
		bool operator==(const Vector3& v) const;

		bool operator!=(const Vector3& v) const;

		bool operator<(const Vector3& v) const;

		bool operator>(const Vector3& v) const;

		Vector3 getMin(const Vector3& vec) const;

		Vector3 getMax(const Vector3& vec) const;

		float normalize();

		//Getters
		float getX() const;

		float getY() const;

		float getZ() const;

		//Setters
		void setX(float xv);

		void setY(float yv);

		void setZ(float zv);

		void set(float x, float z, float y);

		friend class Quaternion;
	};

	class SerializableVector3 : public Vector3, public Variable {
	public:
		SerializableVector3();

		SerializableVector3(const SerializableVector3& v);

		SerializableVector3(const Vector3& vec);

		SerializableVector3& operator=(const SerializableVector3& v);

		SerializableVector3& operator=(const Vector3& v);

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);
	};

  	} // u3d
  } // util
} // engine

using namespace engine::util::u3d;
