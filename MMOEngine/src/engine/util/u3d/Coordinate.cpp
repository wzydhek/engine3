#include "Coordinate.h"

Coordinate::Coordinate() {
}

Coordinate::Coordinate(const Coordinate& ct) {
	position = ct.position;

	previousPosition = ct.previousPosition;
}

Coordinate::Coordinate(float x, float z, float y) {
	position.set(x, z, y);

	updatePreviousPosition();
}

Coordinate& Coordinate::operator=(const Coordinate& ct) {
	if (this == &ct)
		return *this;

	position = ct.position;
	previousPosition = ct.previousPosition;

	return *this;
}

void Coordinate::initializePosition(float x, float z, float y) {
	position.set(x, z, y);

	updatePreviousPosition();
}

void Coordinate::initializePosition(const Vector3& pos) {
	position = pos;

	updatePreviousPosition();
}

bool Coordinate::toBinaryStream(ObjectOutputStream* stream) {
	position.toBinaryStream(stream);
	previousPosition.toBinaryStream(stream);

	return true;
}

bool Coordinate::parseFromBinaryStream(ObjectInputStream* stream) {
	position.parseFromBinaryStream(stream);
	previousPosition.parseFromBinaryStream(stream);

	return true;
}

void Coordinate::randomizePosition(float maxRadius, float minRadius) {
	updatePreviousPosition();

	float angle = (45 + System::random(200)) / 3.14;
	float distance = System::random((int)(maxRadius - minRadius)) + minRadius;

	position.setX(position.getX() + cos(angle) * distance);
	position.setY(position.getY() + sin(angle) * distance);
}

void Coordinate::setPosition(float x, float z, float y) {
	updatePreviousPosition();

	position.set(x, z, y);
}

void Coordinate::setPosition(const Vector3& pos) {
	updatePreviousPosition();

	position = pos;
}

void Coordinate::setPositionX(float x) {
	previousPosition.setX(x);

	position.setX(x);
}

void Coordinate::setPositionZ(float z) {
	previousPosition.setZ(z);

	position.setZ(z);
}

void Coordinate::setPositionY(float y) {
	previousPosition.setY(y);

	position.setY(y);
}

void Coordinate::updatePreviousPosition() {
	previousPosition = position;
}

// getters
float Coordinate::getPositionX() const {
	return position.getX();
}

float Coordinate::getPositionZ() const {
	return position.getZ();
}

float Coordinate::getPositionY() const {
	return position.getY();
}

float Coordinate::getPreviousPositionX() const {
	return previousPosition.getX();
}

float Coordinate::getPreviousPositionZ() const {
	return previousPosition.getZ();
}

float Coordinate::getPreviousPositionY() const {
	return previousPosition.getY();
}

const Vector3& Coordinate::getPosition() const {
	return position;
}

const Vector3& Coordinate::getPreviousPosition() const {
	return previousPosition;
}

Vector3& Coordinate::getPosition() {
	return position;
}

Vector3& Coordinate::getPreviousPosition() {
	return previousPosition;
}