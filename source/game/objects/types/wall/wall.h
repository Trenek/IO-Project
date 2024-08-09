#ifndef WALL_H
#define WALL_H

#include "object2D.h"

struct wall {
	int ID;
	struct Object2D object;
	Vector3 endPosition;
};

void DrawWalls(struct playInfo *info);

#endif