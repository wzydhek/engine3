/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#pragma once

#include "Vector3.h"

namespace engine {
  namespace util {
  	namespace u3d {

	class Coordinate {
	protected:
		Vector3 position;
		Vector3 previousPosition;

	public:
		Coordinate();

		Coordinate(const Coordinate& ct);

		Coordinate(float x, float z, float y);

		Coordinate& operator=(const Coordinate& ct);

		void initializePosition(float x, float z, float y);

		void initializePosition(const Vector3& pos);

		bool toBinaryStream(ObjectOutputStream* stream);

		bool parseFromBinaryStream(ObjectInputStream* stream);

		void randomizePosition(float maxRadius, float minRadius = 1.f);

		void setPosition(float x, float z, float y);

		void setPosition(const Vector3& pos);

		void setPositionX(float x);

		void setPositionZ(float z);

		void setPositionY(float y);

		void updatePreviousPosition();

		// getters
		float getPositionX() const;

		float getPositionZ() const;

		float getPositionY() const;

		float getPreviousPositionX() const;

		float getPreviousPositionZ() const;

		float getPreviousPositionY() const;

		const Vector3& getPosition() const;

		const Vector3& getPreviousPosition() const;

		Vector3& getPosition();

		Vector3& getPreviousPosition();

	};

  	} // u3d
  } // namespace util
} // namespace engine

using namespace engine::util::u3d;
