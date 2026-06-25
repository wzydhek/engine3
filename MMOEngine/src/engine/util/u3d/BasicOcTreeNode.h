/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * LightweightTreeNode.h
 *
 *  Created on: 15 de ago. de 2015
 *      Author: victor
 */

#pragma once

#include "system/util/SortedVector.h"

namespace engine {
namespace util {
namespace u3d {

class OcTreeEntryInterface;

class BasicOcTreeNode {
protected:
	SortedVector<engine::util::u3d::OcTreeEntryInterface*> objects;

	BasicOcTreeNode* parentNode;
	BasicOcTreeNode* nwNode;
	BasicOcTreeNode* neNode;
	BasicOcTreeNode* swNode;
	BasicOcTreeNode* seNode;
	BasicOcTreeNode* nwNode2;
	BasicOcTreeNode* neNode2;
	BasicOcTreeNode* swNode2;
	BasicOcTreeNode* seNode2;

	float minX, minY, minZ;
	float maxX, maxY, maxZ;

	float dividerX, dividerY, dividerZ;

public:
	BasicOcTreeNode();
	BasicOcTreeNode(float minx, float miny, float minz, float maxx, float maxy, float maxz, BasicOcTreeNode *parent);
	BasicOcTreeNode(float minx, float miny, float maxx, float maxy, BasicOcTreeNode *parent);

	~BasicOcTreeNode();

	// Add a object to this node
	void addObject(OcTreeEntryInterface *obj);

	OcTreeEntryInterface* getObject(int index) const;

	// Remove a object by GUID
	void removeObject(OcTreeEntryInterface *obj);

	void removeObject(int index);

	// Approximative test if a circle with center in x,y and
	// given radius crosses this node.
	bool testInRange(float x, float y, float range) const;
	bool testInRange(float x, float y, float z, float range) const;

	// Check if this node makes any sense to exist
	void check();

	bool validateNode() const;

	// Check if this node has any associated objects
	bool isEmpty() const;

	// Check if this node has children nodes
	bool hasSubNodes() const;


	// Test if the point is inside this node
	bool testInside(float x, float y, float z) const;

	bool testInside(float x, float y) const;

	// Test if the object is inside this node
	bool testInside(OcTreeEntryInterface* obj) const;

	/**
	 * gets the node count including this one
	 */
	int getNodeCount() const;

	String toStringData() const;

private:
	static int _getSubNodeCount(const BasicOcTreeNode* s);

	friend class BasicQuadTree;
	friend class BasicOcTree;
	friend class OcTreeEntryInterface;
	template<class Node>
	friend class OcTreeEntryInterfaceBase;
};

} // u3d
} // namespace util
} // namespace engine

using namespace engine::util::u3d;
