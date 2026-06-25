#include "BasicQuadTreeNode.h"
#include "BasicQuadTree.h"
#include "engine/log/Logger.h"

namespace QTNode {
static Logger logger("BasicQuadTreeNode", Logger::WARNING);
}

using namespace QTNode;

BasicQuadTreeNode::BasicQuadTreeNode() {
	objects.setNoDuplicateInsertPlan();

	parentNode = nullptr;
	nwNode = neNode = swNode = seNode = nullptr;

	minX = 0;
	minY = 0;
	maxX = 0;
	maxY = 0;

	dividerX = 0;
	dividerY = 0;
}

BasicQuadTreeNode::BasicQuadTreeNode(float minx, float miny, float maxx, float maxy, BasicQuadTreeNode* parent) {
	objects.setNoDuplicateInsertPlan();

	parentNode = parent;
	nwNode = neNode = swNode = seNode = nullptr;

	minX = minx;
	minY = miny;
	maxX = maxx;
	maxY = maxy;

	if (!validateNode() || minX > maxX || minY > maxY) {
		logger.error() << "[BasicQuadTree] invalid node in create - " << *this;
	}

	dividerX = (minX + maxX) / 2;
	dividerY = (minY + maxY) / 2;
}

BasicQuadTreeNode::~BasicQuadTreeNode() {
	if (nwNode != nullptr)
		delete nwNode;

	if (neNode != nullptr)
		delete neNode;

	if (swNode != nullptr)
		delete swNode;

	if (seNode != nullptr)
		delete seNode;
}

void BasicQuadTreeNode::addObject(QuadTreeEntryInterface* obj) {
	if (BasicQuadTree::doLog())
		logger.info(true) << hex << "object [" << obj->getObjectID() << "] added to BasicQuadTree" << *this;

	if (!validateNode())
		logger.error() << "[BasicQuadTree] invalid node in addObject() - " << *this;

	objects.put(obj);

	E3_ASSERT(obj->getNode() == nullptr);

	obj->setNode(this);
}

void BasicQuadTreeNode::removeObject(QuadTreeEntryInterface* obj) {
	if (!objects.drop(obj)) {
		logger.error() << hex << "object [" << obj->getObjectID() << "] not found on BasicQuadTree" << *this;
	} else {
		obj->setNode(nullptr);

		if (BasicQuadTree::doLog())
			logger.info(true) << hex << "object [" << obj->getObjectID() << "] removed BasicQuadTree" << *this;
	}
}

void BasicQuadTreeNode::removeObject(int index) {
	QuadTreeEntryInterface* obj = objects.remove(index);
	obj->setNode(nullptr);
}

bool BasicQuadTreeNode::testInside(QuadTreeEntryInterface* obj) const {
	float x = obj->getPositionX();
	float y = obj->getPositionY();

	return x >= minX && x < maxX && y >= minY && y < maxY;
}

bool BasicQuadTreeNode::testInRange(float x, float y, float range) const {
	bool insideX = (minX <= x) && (x < maxX);
	bool insideY = (minY <= y) && (y < maxY);

	if (insideX && insideY)
		return true;

	bool closeenoughX = (fabs(minX - x) <= range || fabs(maxX - x) <= range);
	bool closeenoughY = (fabs(minY - y) <= range || fabs(maxY - y) <= range);

	if ((insideX || closeenoughX) && (insideY || closeenoughY))
		return true;
	else
		return false;
}

void BasicQuadTreeNode::check() {
	if (isEmpty() && !hasSubNodes() && parentNode != nullptr) {
		if (parentNode->nwNode == this)
			parentNode->nwNode = nullptr;
		else if (parentNode->neNode == this)
			parentNode->neNode = nullptr;
		else if (parentNode->swNode == this)
			parentNode->swNode = nullptr;
		else if (parentNode->seNode == this)
			parentNode->seNode = nullptr;

		if (BasicQuadTree::doLog())
			logger.info(true) << "deleteing node (" << *this << ")";

		delete this;
	}
}

String BasicQuadTreeNode::toStringData() const {
	StringBuffer s;
	s << "Node " << this << " (" << (int)minX << "," << (int)minY << "," << (int)maxX << "," << (int)maxY << ") [" << objects.size() << "]";

	return s.toString();
}

int BasicQuadTreeNode::_getSubNodeCount(const BasicQuadTreeNode* s) {
	int count = 1;

	if (s->neNode != nullptr) {
		count += _getSubNodeCount(s->neNode);
	}

	if (s->nwNode != nullptr) {
		count += _getSubNodeCount(s->nwNode);
	}

	if (s->seNode != nullptr) {
		count += _getSubNodeCount(s->seNode);
	}

	if (s->swNode != nullptr) {
		count += _getSubNodeCount(s->swNode);
	}

	return count;
}

int BasicQuadTreeNode::getNodeCount() const {
	return _getSubNodeCount(this);
}

QuadTreeEntryInterface* BasicQuadTreeNode::getObject(int index) const {
	return objects.get(index);
}

bool BasicQuadTreeNode::validateNode() const {
	if (minX > maxX || minY > maxY)
		return false;
	else
		return true;
}

// Check if this node has any associated objects
bool BasicQuadTreeNode::isEmpty() const {
	return objects.isEmpty();
}

// Check if this node has children nodes
bool BasicQuadTreeNode::hasSubNodes() const {
	return nwNode != nullptr || neNode != nullptr || swNode != nullptr || seNode != nullptr;
}

// Test if the point is inside this node
bool BasicQuadTreeNode::testInside(float x, float y) const {
	return x >= minX && x < maxX && y >= minY && y < maxY;
}