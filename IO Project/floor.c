#include "playState.h"
#include "renderer.h"

void DrawFloors(struct playInfo *info) {
	int i = 0;

	while (i < info->floorsQuantity) {
		DrawFloor(*info->floors[i].object.texture, info->floors[i].object.position, info->floors[i].object.sizeV, info->floors[i].actualSize, WHITE);

		i += 1;
	}
}