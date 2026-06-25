/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/
/*
 * AABTree.cpp
 *
 *  Created on: 05/12/2010
 *      Author: victor
 */

#include "system/lang/String.h"

#include "engine/log/Logger.h"

#include "AABBTree.h"

using namespace sys::lang;

AABBTree::AABBTree(const ArrayList<Triangle*>& trilist, int depth, const AABBTreeHeuristic& heurdata, bool triangleOwner) : AABBNode(trilist, depth, heurdata), trianglesOwner(triangleOwner) {

}

AABBTree::~AABBTree() {
	if (trianglesOwner) {
		SortedVector<Triangle*> uniqueTriangles;
		uniqueTriangles.setNoDuplicateInsertPlan();

		getTriangles(uniqueTriangles);

		for (int i = 0; i < uniqueTriangles.size(); ++i) {
			delete uniqueTriangles.getUnsafe(i);
		}
	}
}


