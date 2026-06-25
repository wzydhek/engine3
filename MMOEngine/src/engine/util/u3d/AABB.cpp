#include "AABB.h"

AABB::AABB() {
}

AABB::AABB(const Vector3& boxmin, const Vector3& boxmax) {
	mBounds[0] = boxmin;
	mBounds[1] = boxmax;
}

AABB::AABB(const AABB& aab) {
	mBounds[0] = aab.mBounds[0];
	mBounds[1] = aab.mBounds[1];
}

AABB& AABB::operator=(const AABB& aabb) {
	if (this == &aabb) {
		return *this;
	}

	mBounds[0] = aabb.mBounds[0];
	mBounds[1] = aabb.mBounds[1];

	return *this;
}

bool AABB::toBinaryStream(ObjectOutputStream* stream) {
	mBounds[0].toBinaryStream(stream);
	mBounds[1].toBinaryStream(stream);

	return true;
}

bool AABB::parseFromBinaryStream(ObjectInputStream* stream) {
	mBounds[0].parseFromBinaryStream(stream);
	mBounds[1].parseFromBinaryStream(stream);

	return true;
}

Vector3 AABB::midPoint() const {
	return (mBounds[0] + mBounds[1]) * .5f;
}

Vector3 AABB::center() const {
	return midPoint();
}

Vector3 AABB::extents() const {
	return (mBounds[1] - mBounds[0]) * .5f;
}
// copy
void AABB::copy(const AABB& box) {
	mBounds[0] = box.mBounds[0];
	mBounds[1] = box.mBounds[1];
}

const Vector3* AABB::getMinBound() const {
	return &mBounds[0];
}

Vector3* AABB::getMinBound() {
	return &mBounds[0];
}

float AABB::errorMetric() const {
	return (Vector3(1.0f) + (mBounds[1] - mBounds[0])).product();
}

float AABB::getXMin() const {
	return mBounds[0].getX();
}

float AABB::getYMin() const {
	return mBounds[0].getY();
}

float AABB::getZMin() const {
	return mBounds[0].getZ();
}

float AABB::getXMax() const {
	return mBounds[1].getX();
}

float AABB::getYMax() const {
	return mBounds[1].getY();
}

float AABB::getZMax() const {
	return mBounds[1].getZ();
}

Vector3* AABB::getMaxBound() {
	return &mBounds[1];
}

const Vector3* AABB::getMaxBound() const {
	return &mBounds[1];
}

// construct an AABB from a list of triangles.
AABB::AABB(const ArrayList<Triangle*>& triangles) {
	// do nothing if no triangles in the list
	if (triangles.size() == 0)
		return;

	mBounds[0] = Vector3(0.f);
	mBounds[1] = Vector3(0.f);

	// copy aabb of first triangle
	copy(triangles.getUnsafe(0)->triAABB());

	// encompass all other triangles in the list
	for (int i = 0; i < triangles.size(); ++i) {
		encompass(triangles.getUnsafe(i)->triAABB());
	}
}

// distance squared to a point from the box (arvos algorithm)
float AABB::distSqrd(const Vector3& point) const {
	/*StringBuffer msg;
	msg << "checking against mBounds box:";
	msg << "mbounds[0] x:" << mBounds[0][0] << " y:" << mBounds[0][1] << " z:" << mBounds[0][2] << endl;
	msg << "mbounds[1] x:" << mBounds[1][0] << " y:" << mBounds[1][1] << " z:" << mBounds[1][2];

	Logger::console.info(msg.toString(), true);*/

	float dst = 0;

	// for each component, find the point's relative position and the distance contribution
	for (uint32 ii = 0; ii < 3; ++ii)
		dst += (point[ii] < mBounds[0][ii]) ? Math::sqr(point[ii] - mBounds[0][ii]) : (point[ii] > mBounds[1][ii]) ? Math::sqr(point[ii] - mBounds[1][ii]) : 0.0f;

	return dst;
}

// longest axii of the bounding box
uint32 AABB::longestAxis() const {
	Vector3 boxdim(mBounds[1] - mBounds[0]);

	uint32 la = 0;	  // longest axis
	float lav = 0.0f; // longest axis length

	// for each dimension
	for (uint32 ii = 0; ii < 3; ++ii) {
		// check if its longer
		if (boxdim[ii] > lav) {
			// store it if it is
			la = ii;
			lav = boxdim[ii];
		}
	}

	return la;
}

// make this box encompass the current box as well as this one
void AABB::encompass(const AABB& encbox) {
	mBounds[0] = mBounds[0].getMin(encbox.mBounds[0]);
	mBounds[1] = mBounds[1].getMax(encbox.mBounds[1]);
}

bool AABB::intersects(const Ray& r, float t0, float t1) const {
	/*StringBuffer msg;
	msg << "checking ray intersect against mBounds box:";
	msg << "mbounds[0] x:" << mBounds[0][0] << " y:" << mBounds[0][1] << " z:" << mBounds[0][2] << endl;
	msg << "mbounds[1] x:" << mBounds[1][0] << " y:" << mBounds[1][1] << " z:" << mBounds[1][2];

	Logger::console.info(msg.toString(), true);*/

	float tmin, tmax, tymin, tymax, tzmin, tzmax;

	tmin = (mBounds[r.sign[0]].getX() - r.origin.getX()) * r.invDirection.getX();
	tymax = (mBounds[1 - r.sign[1]].getY() - r.origin.getY()) * r.invDirection.getY();

	if (tmin > tymax) {
		return false;
	}

	tymin = (mBounds[r.sign[1]].getY() - r.origin.getY()) * r.invDirection.getY();
	tmax = (mBounds[1 - r.sign[0]].getX() - r.origin.getX()) * r.invDirection.getX();

	if (tymin > tmax) {
		return false;
	}

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	tzmin = (mBounds[r.sign[2]].getZ() - r.origin.getZ()) * r.invDirection.getZ();
	tzmax = (mBounds[1 - r.sign[2]].getZ() - r.origin.getZ()) * r.invDirection.getZ();

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	return ((tmin < t1) && (tmax > t0));
}
