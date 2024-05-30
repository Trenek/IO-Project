#include "playState.h"

#include <rlgl.h>

static void DrawFloor(Texture2D texture, Vector3 position, Vector2 size, Vector2 realSize, Color tint) {
    const float countY = realSize.y / size.y;
    const float countX = realSize.x / size.x;

    rlPushMatrix();
        rlTranslatef(position.x, position.y, position.z);

        rlCheckRenderBatchLimit(6);
        rlSetTexture(texture.id);
            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);
                // Front Face
                rlNormal3f(0.0f, 1.0f, 0.0f); // Normal Pointing Towards Viewer

                rlTexCoord2f(0.0f, countY); // Bottom Left Of The Texture and Quad
                rlVertex3f(0, 0, realSize.y);

                rlTexCoord2f(countX, countY); // Bottom Right Of The Texture and Quad
                rlVertex3f(realSize.x, 0, realSize.y);

                rlTexCoord2f(countX, 0.0f); // Top Right Of The Texture and Quad
                rlVertex3f(realSize.x, 0, 0);

                rlTexCoord2f(0.0f, 0.0f); // Top Left Of The Texture and Quad
                rlVertex3f(0, 0, 0);
            rlEnd();
        rlSetTexture(0);
    rlPopMatrix();
}

void DrawFloors(struct playInfo *info) {
	int i = 0;

	while (i < info->floorsQuantity) {
		DrawFloor(*info->floors[i].object.texture, info->floors[i].object.position, info->floors[i].object.sizeV, info->floors[i].actualSize, WHITE);

		i += 1;
	}
}