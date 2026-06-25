/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * Vector4.h
 *
 *  Created on: 11/12/2010
 *      Author: victor
 */

#pragma once

#include "system/platform.h"
#include "system/lang/ArrayIndexOutOfBoundsException.h"

namespace engine {
namespace util {
namespace u3d {

class Vector4 {
protected:
	float v[4];

public:
	Vector4();

	Vector4(float px, float py, float pz, float pw);

	Vector4(const float values[4]);

	Vector4(const Vector4& vector);

	Vector4& operator=(const Vector4& vector);

	//Boolean operators
	bool operator==(const Vector4& vec) const;

	void setZero();

	bool isZero() const;

	float& operator[](uint32 index);

	float operator[](uint32 index) const;

	float* toFloatArray();

	const float* toFloatArray() const;

};

} // u3d
} // util
} // engine

using namespace engine::util::u3d;
