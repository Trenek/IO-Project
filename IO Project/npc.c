#include <math.h>

#include "playState.h"

#include "character.h"

void detectFight(struct playInfo *info, enum playState *state) {
	Vector3 *npcPosition = NULL;
	Vector3 *playerPosition = NULL;

	float size = 0;
	float distance = 0;

	int i = 0;

	while (i < info->enemyQuantity) {
		playerPosition = &info->player.character.object.position;
		npcPosition = &info->enemies[i].object.position;
		size = info->enemies[i].object.sizeV.x * 2;

		distance = powf(playerPosition->x - npcPosition->x, 2.0) + powf(playerPosition->z - npcPosition->z, 2.0);

		if (sqrtf(distance) < size) {
			info->chosen = info->enemies[i];

			info->enemyQuantity -= 1;
			while (i < info->enemyQuantity) {
				info->enemies[i] = info->enemies[i + 1];

				i += 1;
			}

			*state = FIGHT;
		}

		i += 1;
	}
}

void hitbox(struct playInfo *info) {
	Vector3 *npcPosition = NULL;
	Vector3 *playerPosition = NULL;

	float newDistance = 0;
	float distance = 0;

	int i = 0;

	while (i < info->enemyQuantity) {
		playerPosition = &info->player.character.object.position;
		npcPosition = &info->enemies[i].object.position;
		newDistance = info->enemies[i].object.sizeV.x;

		distance = powf(playerPosition->x - npcPosition->x, 2.0) + powf(playerPosition->z - npcPosition->z, 2.0);

		if (sqrtf(distance) < newDistance) {
			playerPosition->x = npcPosition->x + (newDistance / sqrtf(distance)) * (playerPosition->x - npcPosition->x);
			playerPosition->z = npcPosition->z + (newDistance / sqrtf(distance)) * (playerPosition->z - npcPosition->z);
		}

		i += 1;
	}
}

void findShop(struct playInfo *info) {
	Vector3 *npcPosition = NULL;
	Vector3 *playerPosition = NULL;

	float newDistance = 0;
	float playerDistance = 0;

	int i = 0;

	while (i < info->shopsQuantity) {
		playerPosition = &info->player.character.object.position;
		npcPosition = &info->shops[i].object.position;
		newDistance = info->shops[i].object.sizeV.x;

		playerDistance = powf(playerPosition->x - npcPosition->x, 2.0) + powf(playerPosition->z - npcPosition->z, 2.0);

		if (sqrtf(playerDistance) < newDistance * 4) {
			info->chosen = info->shops[i];
		}

		i += 1;
	}
}

void hitboxShop(struct playInfo *info, int *shop) {
	Vector3 *npcPosition = NULL;
	Vector3 *playerPosition = NULL;

	float newDistance = 0;
	float playerDistance = 0;

	int i = 0;

	while (i < info->shopsQuantity) {
		playerPosition = &info->player.character.object.position;
		npcPosition = &info->shops[i].object.position;
		newDistance = info->shops[i].object.sizeV.x;

		playerDistance = powf(playerPosition->x - npcPosition->x, 2.0) + powf(playerPosition->z - npcPosition->z, 2.0);

		if (sqrtf(playerDistance) < newDistance * 4) {
			*shop = 1;
		}
		else {
			*shop = 0;
		}

		if (sqrtf(playerDistance) < newDistance) {
			playerPosition->x = npcPosition->x + (newDistance / sqrtf(playerDistance)) * (playerPosition->x - npcPosition->x);
			playerPosition->z = npcPosition->z + (newDistance / sqrtf(playerDistance)) * (playerPosition->z - npcPosition->z);
		}

		i += 1;
	}
}
/*
	(size / sqrt(distance)) (p.x - n.x) + n.x = p'.x

*/