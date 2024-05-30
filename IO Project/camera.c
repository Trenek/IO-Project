#include <math.h>

#include "player.h"
#include "playState.h"

#include <raymath.h>

static void check(Vector3 *cameraPosition, Vector3 *playerPosition, struct playInfo *info) {
	Vector2 cam = { cameraPosition->x, cameraPosition->z };
	Vector2 pos = { playerPosition->x, playerPosition->z };
	Vector2 result;

	int i = 0;

	while (i < info->wallQuantity) {
		Vector2 wall1 = { info->walls[i].object.position.x, info->walls[i].object.position.z };
		Vector2 wall2 = { info->walls[i].endPosition.x, info->walls[i].endPosition.z };

		if (CheckCollisionLines(pos, cam, wall1, wall2, &result)) {
			result = Vector2MoveTowards(result, pos, 0.05f);

			cameraPosition->x = result.x;
			cameraPosition->z = result.y;
		}
		
		i += 1;
	}
}

void updateCamera(struct playInfo *info) {
    Vector3 *x0 = &info->player.character.object.position;
    struct player *sp = &info->player;

    info->camera.position = (Vector3){
        .x = x0->x + sp->r * cosf(sp->a) * cosf(sp->b),
        .z = x0->z + sp->r * cosf(sp->a) * sinf(sp->b),
        .y = x0->y + sp->r * sinf(sp->a)
    };
	check(&info->camera.position, &info->player.character.object.position, info);
    info->camera.target = *x0;
    info->camera.target.y += info->player.character.object.sizeV.y / 2;
}