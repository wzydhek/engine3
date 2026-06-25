/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * Matrix3.h
 *
 *  Created on: 11/12/2010
 *      Author: victor
 */

#pragma once

#include "Vector3.h"

namespace engine {
 namespace util {
  namespace u3d {

 class Matrix3 {
	 Vector3 matrix[3];
 public:
	 Matrix3();

	 Matrix3(const Vector3& v1, const Vector3& v2, const Vector3& v3);

	 Matrix3(const Matrix3& mat);

	 Matrix3& operator=(const Matrix3& mat);

	 void scale(const Vector3& p);

	 void scale(float sx, float sy, float sz);

	 void transpose();

	 Vector3& operator[](uint32 index);

	 const Vector3& operator[](uint32 index) const;


 };

  } // u3d
 } // util
} // engine

using namespace engine::util::u3d;
