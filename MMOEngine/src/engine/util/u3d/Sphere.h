/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * Sphere.h
 *
 *  Created on: 05/12/2010
 *      Author: victor
 */

#pragma once

#include "Vector3.h"
#include "Triangle.h"

namespace engine {
 namespace util {
   	namespace u3d {

	class AABB;

	class Sphere : public Object {
		Vector3 origin;
		float radius;
		float radiusSquared;

	public:
		Sphere();

		Sphere(const Vector3& orig, float rad);

		bool containsPoint(const Vector3 point) const;

		bool intersects(const Triangle& tri) const;/* {
			return (tri.distSqrd(origin) <= radiusSquared);
		}*/
		// does this intersect an aabb?
		bool intersects(const AABB& aabb) const;
		// renders a sphere

		float getRadius() const;

		float getRadiusSquared() const;

		Vector3& getCenter();

		const Vector3& getCenter() const;
	};

   	} // u3d
  } // util
} // engine

using namespace engine::util::u3d;
