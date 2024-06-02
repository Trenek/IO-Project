#include <math.h>

#include "playState.h"

#include "character.h"

void detectFight(struct playInfo *info, enum playState *state) {
	Vector3 *npcPosition = NULL;
	Vector3 *playerPosition = NULL;

	float size = 0;
	float distance = 0;

	int i = 0;

	while (i < info->save.enemyQuantity) {
		playerPosition = &info->save.player.character.object.position;
		npcPosition = &info->save.enemies[i].object.position;
		size = info->save.enemies[i].object.sizeV.x * 2;

		distance = powf(playerPosition->x - npcPosition->x, 2.0) + powf(playerPosition->z - npcPosition->z, 2.0);

		if (sqrtf(distance) < size) {
			info->chosen = info->save.enemies[i];
			info->dialog = info->save.enemies[i].dialog;

			info->save.enemyQuantity -= 1;
			while (i < info->save.enemyQuantity) {
				info->save.enemies[i] = info->save.enemies[i + 1];
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

	while (i < info->save.enemyQuantity) {
		playerPosition = &info->save.player.character.object.position;
		npcPosition = &info->save.enemies[i].object.position;
		newDistance = info->save.enemies[i].object.sizeV.x;

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

void detectHitbox2(struct Object2D *object, Vector3 obsticle, const float minDistance) {
	const float distance = sqrtf(powf(object->position.x - obsticle.x, 2.0) + powf(object->position.z - obsticle.z, 2.0));

	if (distance < minDistance) {
		object->position.x = obsticle.x + (minDistance / distance) * (object->position.x - obsticle.x);
		object->position.z = obsticle.z + (minDistance / distance) * (object->position.z - obsticle.z);
	}
}

#define IN_BETWEEN(key, b, c) ((key >= b && key <= c) || (key >= c && key <= b))

void detectWallHitbox(struct Object2D *object, struct wall *obsticle) {
	Vector3 *A = &obsticle->endPosition;
	Vector3 *B = &obsticle->object.position;
	Vector3 *C = &object->position;

	const float expectedDistance = object->sizeV.x;

	if (A->x == B->x) {
		if (IN_BETWEEN(C->z, A->z, B->z)) {
			if (fabsf(C->x - A->x) < expectedDistance) {
				C->x = (C->x - A->x >= 0) ?
					A->x + expectedDistance :
					A->x - expectedDistance;
			}
		}
		else {
			detectHitbox2(object, *A, expectedDistance);
			detectHitbox2(object, *B, expectedDistance);
		}
	}
	if (A->z == B->z) {
		if (IN_BETWEEN(C->x, A->x, B->x)) {
			if (fabsf(C->z - A->z) < expectedDistance) {
				C->z = (C->z - A->z >= 0) ?
					A->z + expectedDistance :
					A->z - expectedDistance;
			}
		}
		else {
			detectHitbox2(object, *A, expectedDistance);
			detectHitbox2(object, *B, expectedDistance);
		}
	}
}

void checkHitbox(struct Object2D *object, struct playInfo *info) {
	int i = 0;

	while (i < info->save.enemyQuantity) {
		if (object != &info->save.enemies[i].object)
			detectHitbox(object, info->save.enemies[i].object.position);

		i += 1;
	}

	i = 0;
	while (i < info->save.sellersQuantity) {
		detectHitbox(object, info->save.sellers[i].character.object.position);

		i += 1;
	}

	i = 0;
	while (i < info->save.wallQuantity) {
		detectWallHitbox(object, &info->save.walls[i]);

		i += 1;
	}
}

void hitbox(struct playInfo *info) {
	int i = 0;

	checkHitbox(&info->save.player.character.object, info);
	while (i < info->save.enemyQuantity) {
		checkHitbox(&info->save.enemies[i].object, info);

		i += 1;
	}
}

void findShop(struct playInfo *info) {
	Vector3 *npcPosition = NULL;
	Vector3 *playerPosition = NULL;

	float newDistance = 0;
	float playerDistance = 0;

	int i = 0;

	while (i < info->save.sellersQuantity) {
		playerPosition = &info->save.player.character.object.position;
		npcPosition = &info->save.sellers[i].character.object.position;
		newDistance = info->save.sellers[i].character.object.sizeV.x;

		playerDistance = powf(playerPosition->x - npcPosition->x, 2.0) + powf(playerPosition->z - npcPosition->z, 2.0);

		if (sqrtf(playerDistance) < newDistance * 4) {
			info->chosen = info->save.sellers[i].character;
			info->chosenShop = info->save.sellers[i].shopID;
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

	while (i < info->save.sellersQuantity) {
		playerPosition = &info->save.player.character.object.position;
		npcPosition = &info->save.sellers[i].character.object.position;
		newDistance = info->save.sellers[i].character.object.sizeV.x;

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