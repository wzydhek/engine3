/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * AABB.h
 *
 *  Created on: 11/12/2010
 *      Author: victor
 */

#pragma once

#include "Vector3.h"
#include "Triangle.h"
#include "Ray.h"

namespace engine {
  namespace util {
	namespace u3d {

 class AABB {
	 Vector3 mBounds[2]; // box bounds - min followed by max
 public:
	 AABB();

	 AABB(const Vector3& boxmin, const Vector3& boxmax);

	 // calc aabb from trilist
	 AABB(const ArrayList<Triangle*>& triangles);

	 AABB(const AABB& aab);

	 AABB& operator=(const AABB& aabb);

	 bool toBinaryStream(ObjectOutputStream* stream);

	 bool parseFromBinaryStream(ObjectInputStream* stream);

	 // returns a sub box of the octant specified, with the partition as the new corner.
	 float distSqrd(const Vector3& point) const;

	 // calculate the floating point error metric
	 float errorMetric() const;

	 // intersection scalar (used for weighting in building aabb)
	 uint32 longestAxis() const;
	 // mid-point

	 Vector3 midPoint() const;

	 Vector3 center() const;

	 Vector3 extents() const;
	 // copy
	 void copy(const AABB& box);

	 // make this box encompass the current box as well as this one - returns * this
	 void encompass(const AABB& encbox);


	 /*
	  * Ray-box intersection using IEEE numerical properties to ensure that the
	  * test is both robust and efficient, as described in:
	  *
	  *      Amy Williams, Steve Barrus, R. Keith Morley, and Peter Shirley
	  *      "An Efficient and Robust Ray-Box Intersection Algorithm"
	  *      Journal of graphics tools, 10(1):49-54, 2005
	  *
	  */

	 bool intersects(const Ray &r, float t0, float t1) const;

	 const Vector3* getMinBound() const;

	 Vector3* getMinBound();

	 float getXMin() const;

	 float getYMin() const;

	 float getZMin() const;

	 float getXMax() const;

	 float getYMax() const;

	 float getZMax() const;

	 Vector3* getMaxBound();

	 const Vector3* getMaxBound() const;

 };

	} // u3d
  } // util
} // engine

using namespace engine::util::u3d;
