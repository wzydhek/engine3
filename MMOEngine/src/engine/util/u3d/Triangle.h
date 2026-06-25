/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * Triangle.h
 *
 *  Created on: 05/12/2010
 *      Author: victor
 */

#pragma once

//#define TRIANGLE_INHERITS_VARIABLE

#include "Vector3.h"
#include "Matrix4.h"

namespace engine {
 namespace util {
  	namespace u3d {

	class AABB;
	class Ray;

#ifdef TRIANGLE_INHERITS_VARIABLE
	class Triangle : public Variable {
#else
	class Triangle {
#endif
	protected:
		Vector3 verts[3];

	public:
		Triangle() noexcept;

#ifdef TRIANGLE_INHERITS_VARIABLE
		Triangle(const Triangle& tri) noexcept;
#else
		Triangle(const Triangle& tri)  = default;
#endif
		Triangle(const Vector3 vert[3]) noexcept;

#ifdef TRIANGLE_INHERITS_VARIABLE
		Triangle& operator=(const Triangle& tri) noexcept;
#else
		Triangle& operator=(const Triangle& tri) = default;
#endif

		void transform(const Matrix4& worldMatrix);

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		int compareTo(const Triangle* triangle) const;

		// calculate the midpoint
		Vector3 midPoint() const;

		AABB triAABB() const;

		//    Input:  a ray Ray
		//    Output: intersectionPoint = intersection point (when it exists)
		//    Return: -1 = triangle is degenerate (a segment or point)
		//             0 = disjoint (no intersect)
		//             1 = intersect in unique point I1
		//             2 = are in the same plane
		//int intersects(const Ray& ray, Vector3& intersectionPoint);

		bool intersects(const Ray& ray, float maxDistance, float& intersectionDistance) const;

		Vector3 getNormal() const;

		/**
		 * returns 0 on success
		 */
		int getSharedVertices(const Triangle& tri, const Vector3*& vertexA, const Vector3*& vertexB) const;

		const Vector3& getLeftSharedVertex(const Triangle& tri) const;
		const Vector3& getRightSharedVertex(const Triangle& tri) const;

		Vector3 getBarycenter() const;

		float area() const;

		//uses vertices x and z
		float area2D() const;

		static float area2D(const Vector3& a, const Vector3& b, const Vector3& c);

		void set(const Vector3 vert[3]);

		Vector3& getVertex(uint32 i);

		const Vector3& getVertex(uint32 i) const;
	};

  	} // u3d
  } // util
} // engine

using namespace engine::util::u3d;
