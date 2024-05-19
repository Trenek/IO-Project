#include <math.h>

#include "playState.h"

#include "character.h"

void hitbox(struct playInfo *info) {
	Vector3 *npcPosition = NULL;
	Vector3 *playerPosition = NULL;

	float size = 0;
	float distance = 0;

	int i = 0;

	while (i < info->npcQuantity) {
		playerPosition = &info->player.character.object.position;
		npcPosition = &info->npc[i].object.position;
		size = info->npc[i].object.sizeV.x / 2;

		distance = powf(playerPosition->x - npcPosition->x, 2.0) + powf(playerPosition->y - npcPosition->y, 2.0);

		if (sqrtf(distance) < size) {
			playerPosition->x = npcPosition->x + (size / sqrtf(distance)) * (playerPosition->x - npcPosition->x);
			playerPosition->z = npcPosition->z + (size / sqrtf(distance)) * (playerPosition->z - npcPosition->z);
		}

		i += 1;
	}
}
/*
	(size / sqrt(distance)) (p.x - n.x) + n.x = p'.x

*/