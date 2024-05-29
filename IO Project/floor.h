#include "object2D.h"

struct floor {
	int ID;
	struct Object2D object;
	Vector2 actualSize;
};

void DrawFloors(struct playInfo *info);