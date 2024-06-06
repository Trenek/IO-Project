#ifndef FLOORS_H
#define FLOORS_H

#include "object2D.h"

struct floors {
	int ID;
	struct Object2D object;
	Vector2 actualSize;
};

void DrawFloors(struct playInfo *info);

#endif