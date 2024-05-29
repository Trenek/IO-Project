#include "playState.h"
#include "renderer.h"

void DrawWalls(struct playInfo *info) {
	int i = 0;

	while (i < info->wallQuantity) {
		DrawWall(*info->walls[i].object.texture, info->walls[i].object.position, info->walls[i].object.sizeV, info->walls[i].endPosition, WHITE);

		i += 1;
	}
}