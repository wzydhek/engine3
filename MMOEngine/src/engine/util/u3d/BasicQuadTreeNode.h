/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * LightweightQuadTreeNode.h
 *
 *  Created on: 15 de ago. de 2015
 *      Author: victor
 */

#pragma once

#include "system/util/SortedVector.h"

namespace engine {
namespace util {
namespace u3d {

class QuadTreeEntryInterface;

class BasicQuadTreeNode {
protected:
	SortedVector<engine::util::u3d::QuadTreeEntryInterface*> objects;

	BasicQuadTreeNode* parentNode;
	BasicQuadTreeNode* nwNode;
	BasicQuadTreeNode* neNode;
	BasicQuadTreeNode* swNode;
	BasicQuadTreeNode* seNode;

	float minX, minY;
	float maxX, maxY;

	float dividerX, dividerY;

public:
	BasicQuadTreeNode();
	BasicQuadTreeNode(float minx, float miny, float maxx, float maxy,
			BasicQuadTreeNode *parent);

	~BasicQuadTreeNode();

	// Add a object to this node
	void addObject(QuadTreeEntryInterface *obj);

	QuadTreeEntryInterface* getObject(int index) const;

	// Remove a object by GUID
	void removeObject(QuadTreeEntryInterface *obj);

	void removeObject(int index);

	// Approximative test if a circle with center in x,y and
	// given radius crosses this node.
	bool testInRange(float x, float y, float range) const;

	// Check if this node makes any sense to exist
	void check();

	bool validateNode() const;

	// Check if this node has any associated objects
	bool isEmpty() const;

	// Check if this node has children nodes
	bool hasSubNodes() const;

	// Test if the point is inside this node
	bool testInside(float x, float y) const;

	// Test if the object is inside this node
	bool testInside(QuadTreeEntryInterface* obj) const;

	/**
	 * gets the node count including this one
	 */
	int getNodeCount() const;

	String toStringData() const;

private:
	static int _getSubNodeCount(const BasicQuadTreeNode* s);

	friend class BasicQuadTree;
	friend class QuadTreeEntryInterface;
	template<class Node>
	friend class QuadTreeEntryInterfaceBase;
};

} // u3d
} // namespace util
} // namespace engine

using namespace engine::util::u3d;
