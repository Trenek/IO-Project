#ifndef CEILING_H
#define CEILING_H

#include "object2D.h"

struct ceiling {
	int ID;
	struct Object2D object;
	Vector2 actualSize;
};

struct playInfo;
void DrawCeilings(struct playInfo *info);

#endif