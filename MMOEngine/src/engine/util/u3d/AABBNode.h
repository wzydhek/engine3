/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * AABBNode.h
 *
 *  Created on: 12/12/2010
 *      Author: victor
 */

#pragma once

#include "AABB.h"

namespace sys {
 namespace io {
 	class ObjectOutputStream;
	class ObjectInputStream;
 }
}

namespace engine {
 namespace util {
	namespace u3d {

 	struct AABBTreeHeuristic;
	class Triangle;
	class Sphere;

 	class IntersectionResult {
 		float intersectionDistance;
 		Triangle* triangle;

 	public:
		IntersectionResult();

 		IntersectionResult(float intersectionDistance, Triangle* triangle);

 		IntersectionResult(const IntersectionResult& r);

 		IntersectionResult& operator=(const IntersectionResult& r);

 		bool toBinaryStream(sys::io::ObjectOutputStream* stream);

 		bool parseFromBinaryStream(sys::io::ObjectInputStream* stream);

 		int compareTo(const IntersectionResult& r) const;

 		float getIntersectionDistance() const;

 		Triangle* getTriangle();

		const Triangle* getTriangle() const;

 	};

	class AABBNode {
	protected:
		AABB mBox; // node's bounding box
		AABBNode* mChildren[2]; // child nodes of this node
		ArrayList<Triangle*> mTriangles; // triangles in this node

	public:
		// constructs this aabb tree node from a triangle list and creates its children recursively
		AABBNode(const ArrayList<Triangle*>& trilist, int depth, const AABBTreeHeuristic& heurdata);
		// destructs this node
		virtual ~AABBNode();
		// renders tris that collide with the sphere

		bool testCollide(const Sphere& testsphere) const;

		/**
		 * Checks for intersection against ray, stops on any intersection
		 * @return intersectionDistance, triangle which it intersects
		 */
		bool intersects(const Ray& ray, float distance, float& intersectionDistance, Triangle*& triangle, bool checkPrimitives = false) const;

		/**
		 * Checks for all intersections
		 */
		int intersects(const Ray& ray, float maxDistance, SortedVector<IntersectionResult>& result) const;

		//returns all the triangles from the mesh
		void getTriangles(ArrayList<Triangle*>& triangles) const;

		//returns all triangles from the mesh sorted
		void getTriangles(SortedVector<Triangle*>& triangles) const;

		AABB& getBoundingBox();

		const AABB& getBoundingBox() const;

		AABBNode* getLeftChild();

		const AABBNode* getLeftChild() const;

		AABBNode* getRightChild();

		const AABBNode* getRightChild() const;

	};

	} // u3d
  } // util
} // engine

using namespace engine::util::u3d;
