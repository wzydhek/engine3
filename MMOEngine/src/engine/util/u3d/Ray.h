/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * Ray.h
 *
 *  Created on: 11/12/2010
 *      Author: victor
 */

#pragma once

/*
 * Ray class, for use with the optimized ray-box intersection test
 * described in:
 *
 *      Amy Williams, Steve Barrus, R. Keith Morley, and Peter Shirley
 *      "An Efficient and Robust Ray-Box Intersection Algorithm"
 *      Journal of graphics tools, 10(1):49-54, 2005
 *
 */

#include "Vector3.h"

namespace engine {
namespace util {
namespace u3d {

class Ray {
protected:
	Vector3 origin;
	Vector3 direction;
	Vector3 invDirection;
	int sign[3];

public:
	Ray();

	Ray(const Vector3& o, const Vector3& d);

	Ray(const Ray& r);

	const Vector3& getOrigin() const;

	const Vector3& getDirection() const;

	Vector3& getOrigin();

	Vector3& getDirection();

	friend class AABB;
	friend class Triangle;
};

} // u3d
} // util
} // engine

using namespace engine::util::u3d;
