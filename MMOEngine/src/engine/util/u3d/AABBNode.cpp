#include "AABBNode.h"
#include "Sphere.h"
#include "AABBTree.h"

IntersectionResult::IntersectionResult() {
	intersectionDistance = 0;
	triangle = nullptr;
}

IntersectionResult::IntersectionResult(float intersectionDistance, Triangle* triangle) {
	this->intersectionDistance = intersectionDistance;
	this->triangle = triangle;
}

IntersectionResult::IntersectionResult(const IntersectionResult& r) {
	intersectionDistance = r.intersectionDistance;
	triangle = r.triangle;
}

IntersectionResult& IntersectionResult::operator=(const IntersectionResult& r) {
	if (this == &r)
		return *this;

	intersectionDistance = r.intersectionDistance;
	triangle = r.triangle;

	return *this;
}

bool IntersectionResult::toBinaryStream(sys::io::ObjectOutputStream* stream) {
	return false;
}

bool IntersectionResult::parseFromBinaryStream(sys::io::ObjectInputStream* stream) {
	return false;
}

int IntersectionResult::compareTo(const IntersectionResult& r) const {
	if (intersectionDistance < r.intersectionDistance)
		return 1;
	else if (intersectionDistance > r.intersectionDistance)
		return -1;
	else
		return 0;
}

float IntersectionResult::getIntersectionDistance() const {
	return intersectionDistance;
}

Triangle* IntersectionResult::getTriangle() {
	return triangle;
}

const Triangle* IntersectionResult::getTriangle() const {
	return triangle;
}

// constructs this aabb tree node from a triangle list and creates its children recursively
// note node box is initialised to the first triangle's box
AABBNode::AABBNode(const ArrayList<Triangle*>& trilist, int depth, const AABBTreeHeuristic& heurdata) : mBox(trilist) {
	// test our build heuristic - if passes, make children
	if (depth < (int)heurdata.maxdepth && trilist.size() > (int)heurdata.mintricnt && (trilist.size() > (int)heurdata.tartricnt || mBox.errorMetric() > heurdata.minerror)) {
		// list<CTriangle>::const_iterator triitr; // iterator for looping through trilist
		ArrayList<Triangle*> tribuckets[2] = {ArrayList<Triangle*>(1, 1), ArrayList<Triangle*>(1, 1)}; // buckets of triangles
		uint32 longaxis = mBox.longestAxis();														   // longest axis
		Vector3 geoavg(0.f);																		   // geometric average - midpoint of ALL the triangles

		// go through all tris and calculate the average of the midpoints
		// for (triitr=trilist.begin(); triitr!=trilist.end(); triitr++)
		for (int i = 0; i < trilist.size(); ++i) {
			geoavg = geoavg + trilist.getUnsafe(i)->midPoint() * (1.0f / trilist.size());
		}

		// bucket tris based on their midpoint's side of the geo average in the longest axis
		// for (triitr=trilist.begin(); triitr!=trilist.end(); triitr++)
		for (int i = 0; i < trilist.size(); ++i) {
			tribuckets[geoavg[longaxis] > trilist.getUnsafe(i)->midPoint()[longaxis]].add(trilist.getUnsafe(i));
		}

		// create new children using the buckets
		mChildren[0] = new AABBNode(tribuckets[0], depth + 1, heurdata);
		mChildren[1] = new AABBNode(tribuckets[1], depth + 1, heurdata);

	} else { // otherwise the build heuristic failed, this is

		// set the first child to null (identifies a leaf)
		mChildren[0] = nullptr;
		mChildren[1] = nullptr;

		// copy triangle list
		if (heurdata.storePrimitives) {
			mTriangles = trilist;
		} else {
			mTriangles.removeAll(0, 1);
		}
	}
}

// destructor
AABBNode::~AABBNode() {
	// if a note a leaf node, delete the children.
	if (mChildren[0]) {
		delete mChildren[0];
		delete mChildren[1];
	}
}

int AABBNode::intersects(const Ray& ray, float maxDistance, SortedVector<IntersectionResult>& result) const {
	float intersectionDistance;

	if (mBox.intersects(ray, 0.f, maxDistance)) {
		if (mChildren[0]) {
			// recurse to children
			mChildren[0]->intersects(ray, maxDistance, result);
			mChildren[1]->intersects(ray, maxDistance, result);

		} else { // is a leaf
			for (int i = 0; i < mTriangles.size(); ++i) {
				// Vector3 intersectionPoint;

				if (mTriangles.getUnsafe(i)->intersects(ray, maxDistance, intersectionDistance)) {
					result.put(IntersectionResult(intersectionDistance, mTriangles.getUnsafe(i)));
				}
			}
		}
	}

	return result.size();
}

// bool intersects(const Ray& ray, float distance, float& intersectionDistance, Triangle*& triangle, bool checkPrimitives = false);
bool AABBNode::intersects(const Ray& ray, float distance, float& intersectionDistance, Triangle*& triangle, bool checkPrimitives) const {
	if (mBox.intersects(ray, 0.f, distance)) {
		if (mChildren[0]) {
			// recurse to children
			if (!mChildren[0]->intersects(ray, distance, intersectionDistance, triangle, checkPrimitives))
				return mChildren[1]->intersects(ray, distance, intersectionDistance, triangle, checkPrimitives);
			else
				return true;

		} else { // is a leaf
			if (checkPrimitives) {
				for (int i = 0; i < mTriangles.size(); ++i) {
					// Vector3 intersectionPoint;

					if (mTriangles.getUnsafe(i)->intersects(ray, distance, intersectionDistance)) {
						triangle = mTriangles.getUnsafe(i);
						return true;
					}
				}
			} else
				return true;
		}
	}

	return false;
}

bool AABBNode::testCollide(const Sphere& testsphere) const {
	// if no intersection with the node box, don't continue
	if (testsphere.intersects(mBox)) {
		// m_box.Render();

		// is not a leaf
		if (mChildren[0]) {
			// recurse to children
			if (!mChildren[0]->testCollide(testsphere))
				return mChildren[1]->testCollide(testsphere);
			else
				return true;

		} else { // is a leaf

			for (int i = 0; i < mTriangles.size(); ++i) {
				if (testsphere.intersects(*mTriangles.getUnsafe(i)))
					return true;
			}
		}
	}

	return false;
}

void AABBNode::getTriangles(ArrayList<Triangle*>& triangles) const {
	triangles.addAll(mTriangles);

	if (mChildren[0] != nullptr) {
		mChildren[0]->getTriangles(triangles);
		mChildren[1]->getTriangles(triangles);
	}
}

// returns all triangles from the mesh sorted
void AABBNode::getTriangles(SortedVector<Triangle*>& triangles) const {
	for (int i = 0; i < mTriangles.size(); ++i) {
		triangles.put(mTriangles.getUnsafe(i));
	}

	if (mChildren[0] != nullptr) {
		mChildren[0]->getTriangles(triangles);
		mChildren[1]->getTriangles(triangles);
	}
}

AABB& AABBNode::getBoundingBox() {
	return mBox;
}

const AABB& AABBNode::getBoundingBox() const {
	return mBox;
}

AABBNode* AABBNode::getLeftChild() {
	return mChildren[0];
}

const AABBNode* AABBNode::getLeftChild() const {
	return mChildren[0];
}

AABBNode* AABBNode::getRightChild() {
	return mChildren[1];
}

const AABBNode* AABBNode::getRightChild() const {
	return mChildren[1];
}