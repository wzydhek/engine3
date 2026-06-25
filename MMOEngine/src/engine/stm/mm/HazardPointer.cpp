#include "HazardPointer.h"

void HazardPointer::retireObject(Object* object) {
	retireList.add(object);

	if (retireList.size() > RETIRED_TRESHOLD)
		scan();
}