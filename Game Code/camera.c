#include <math.h>

#include "player.h"
#include "playState.h"

#include <raymath.h>

#define IN_BETWEEN(key, b, c) ((key >= b && key <= c) || (key >= c && key <= b))

static void detectCeilingHitbox(Vector3 *object, struct ceiling *obsticle) {
	Vector3 *B = &obsticle->object.position;
	Vector3 rA = {
		.x = B->x + obsticle->actualSize.x,
		.y = B->y,
		.z = B->z + obsticle->actualSize.y
	};
	Vector3 *A = &rA;
	Vector3 *C = object;

	if (C->y > B->y) {
		if (IN_BETWEEN(C->x, A->x, B->x) && IN_BETWEEN(C->z, A->z, B->z)) {
			C->y = B->y;
		}
	}
}

static void check(Vector3 *cameraPosition, Vector3 *playerPosition, struct playInfo *info) {
	Vector2 cam = { cameraPosition->x, cameraPosition->z };
	Vector2 pos = { playerPosition->x, playerPosition->z };
	Vector2 result;

	int i = 0;

	while (i < info->save.wallQuantity) {
		Vector2 wall1 = { info->save.walls[i].object.position.x, info->save.walls[i].object.position.z };
		Vector2 wall2 = { info->save.walls[i].endPosition.x, info->save.walls[i].endPosition.z };

		if (CheckCollisionLines(pos, cam, wall1, wall2, &result)) {
			result = Vector2MoveTowards(result, pos, 0.05f);

			cameraPosition->x = result.x;
			cameraPosition->z = result.y;
		}
		
		i += 1;
	}

	i = 0;
	while (i < info->save.ceilingQuantity) {
		detectCeilingHitbox(cameraPosition, &info->save.ceiling[i]);

		i += 1;
	}
}

void updateCamera(struct playInfo *info) {
    Vector3 *x0 = &info->save.player.character.object.position;
    struct player *sp = &info->save.player;

    info->camera.position = (Vector3){
        .x = x0->x + sp->r * cosf(sp->a) * cosf(sp->b),
        .z = x0->z + sp->r * cosf(sp->a) * sinf(sp->b),
        .y = x0->y + sp->r * sinf(sp->a)
    };
	check(&info->camera.position, &info->save.player.character.object.position, info);
    info->camera.target = *x0;
    info->camera.target.y += info->save.player.character.object.sizeV.y / 2;
}