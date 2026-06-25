/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * Matrix4.h
 *
 *  Created on: 11/12/2010
 *      Author: victor
 */

#pragma once

#include "Vector4.h"
#include "system/lang/Object.h"

namespace engine {
 namespace util {
  namespace u3d {

 class Matrix3;
 class Vector3;

 class Matrix4 : public Object {
	 Vector4 matrix[4];

 public:
	 Matrix4();

	 Matrix4(const Vector4& a, const Vector4& b, const Vector4& c, const Vector4& d);

	 Matrix4(const Matrix4& mat);

	 Matrix4& operator=(const Matrix4& op);

	 void identity();

	 Vector4& operator[](uint32 index);

	 const Vector4& operator[](uint32 index) const;

	 void setTranslation(float x, float y, float z);

	 void swapLtoR();

	 void transpose();

	 Matrix4 inverse() const;

	 void setRotationMatrix(const Matrix3& rot);

	 Matrix4 operator*(const Matrix4& mat) const;
	 Vector3 operator*(const Vector3& mat) const;

 };

  } // u3d
 } // util
} // engine

using namespace engine::util::u3d;
