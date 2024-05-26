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
			info->dialog = info->enemies[i].dialog;

			info->enemyQuantity -= 1;
			while (i < info->enemyQuantity) {
				info->enemies[i] = info->enemies[i + 1];
				info->shouldDestroy = 1;

				i += 1;
			}

			*state = DIALOG;
		}

		i += 1;
	}
}

void followPlayer(struct playInfo *info) {
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

		npcPosition->x = playerPosition->x + ((sqrtf(distance) - GetFrameTime()) / sqrtf(distance)) * (npcPosition->x - playerPosition->x);
		npcPosition->z = playerPosition->z + ((sqrtf(distance) - GetFrameTime()) / sqrtf(distance)) * (npcPosition->z - playerPosition->z);

		i += 1;
	}
}

void detectHitbox(struct Object2D *object, Vector3 obsticle) {
	const float distance = sqrtf(powf(object->position.x - obsticle.x, 2.0) + powf(object->position.z - obsticle.z, 2.0));
	const float minDistance = object->sizeV.x;

	if (distance < object->sizeV.x) {
		object->position.x = obsticle.x + (minDistance / distance) * (object->position.x - obsticle.x);
		object->position.z = obsticle.z + (minDistance / distance) * (object->position.z - obsticle.z);
	}
}

void hitbox(struct playInfo *info) {
	int i = 0;
	int j = 0;

	while (i < info->enemyQuantity) {
		detectHitbox(&info->player.character.object, info->enemies[i].object.position);

		j = 0;
		while (j < info->enemyQuantity) {
			if (i != j) {
				detectHitbox(&info->enemies[i].object, info->enemies[j].object.position);
			}

			j += 1;
		}

		j = 0;
		while (j < info->enemyQuantity) {
			if (i == j) {
				detectHitbox(&info->enemies[i].object, info->shops[j].character.object.position);
			}

			j += 1;
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

	while (i < info->sellersQuantity) {
		playerPosition = &info->player.character.object.position;
		npcPosition = &info->shops[i].character.object.position;
		newDistance = info->shops[i].character.object.sizeV.x;

		playerDistance = powf(playerPosition->x - npcPosition->x, 2.0) + powf(playerPosition->z - npcPosition->z, 2.0);

		if (sqrtf(playerDistance) < newDistance * 4) {
			info->chosen = info->shops[i].character;
			info->chosenShop = info->shops[i].shopID;
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

	while (i < info->sellersQuantity) {
		playerPosition = &info->player.character.object.position;
		npcPosition = &info->shops[i].character.object.position;
		newDistance = info->shops[i].character.object.sizeV.x;

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