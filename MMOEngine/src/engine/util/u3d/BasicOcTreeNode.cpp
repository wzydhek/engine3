#include "BasicOcTreeNode.h"
#include "OcTreeEntryInterface.h"

OcTreeEntryInterface* BasicOcTreeNode::getObject(int index) const {
	return objects.get(index);
}

bool BasicOcTreeNode::validateNode() const {
	if (dividerZ != -1) {
		if (minX > maxX || minY > maxY || minZ > maxZ) {
			return false;
		}
	} else if (minX > maxX || minY > maxY) {
		return false;
	}

	return true;
}

// Check if this node has any associated objects
bool BasicOcTreeNode::isEmpty() const {
	return objects.isEmpty();
}

// Check if this node has children nodes
bool BasicOcTreeNode::hasSubNodes() const {
	return nwNode != nullptr || neNode != nullptr || swNode != nullptr || seNode != nullptr || nwNode2 != nullptr || neNode2 != nullptr || swNode2 != nullptr || seNode2 != nullptr;
}

// Test if the point is inside this node
bool BasicOcTreeNode::testInside(float x, float y, float z) const {
	return x >= minX && x < maxX && y >= minY && y < maxY && z >= minZ && z < maxZ;
}

bool BasicOcTreeNode::testInside(float x, float y) const {
	return x >= minX && x < maxX && y >= minY && y < maxY;
}