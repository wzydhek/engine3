#include "Ray.h"

Ray::Ray() {
}

Ray::Ray(const Vector3& o, const Vector3& d) : origin(o), direction(d), invDirection(1 / d.getX(), 1 / d.getY(), 1 / d.getZ()) {
	sign[0] = (invDirection.getX() < 0);
	sign[1] = (invDirection.getY() < 0);
	sign[2] = (invDirection.getZ() < 0);
}

Ray::Ray(const Ray& r) : origin(r.origin), direction(r.direction), invDirection(r.invDirection) {
	sign[0] = r.sign[0];
	sign[1] = r.sign[1];
	sign[2] = r.sign[2];
}

const Vector3& Ray::getOrigin() const {
	return origin;
}

const Vector3& Ray::getDirection() const {
	return direction;
}

Vector3& Ray::getOrigin() {
	return origin;
}

Vector3& Ray::getDirection() {
	return direction;
}