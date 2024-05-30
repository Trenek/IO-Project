#include <math.h>

#include "playState.h"

#include <rlgl.h>

void DrawWall(Texture2D texture, Vector3 position, Vector2 size, Vector3 realSize, Color tint) {
    const float countY = realSize.y / size.y;
    const float countX = sqrtf(powf(realSize.x - position.x, 2) + powf(realSize.z - position.z, 2)) / size.x;

    rlPushMatrix();
        rlTranslatef(position.x, position.y, position.z);

        rlCheckRenderBatchLimit(6);
        rlSetTexture(texture.id);
            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);
                // Front Face
                rlNormal3f(0.0f, 1.0f, 0.0f); // Normal Pointing Towards Viewer

                rlTexCoord2f(0.0f, countY); // Bottom Left Of The Texture and Quad
                rlVertex3f(0, realSize.y - position.y, 0);

                rlTexCoord2f(countX, countY); // Bottom Right Of The Texture and Quad
                rlVertex3f(realSize.x - position.x, realSize.y - position.y, realSize.z - position.z);

                rlTexCoord2f(countX, 0.0f); // Top Right Of The Texture and Quad
                rlVertex3f(realSize.x - position.x, 0, realSize.z - position.z);

                rlTexCoord2f(0.0f, 0.0f); // Top Left Of The Texture and Quad
                rlVertex3f(0, 0, 0);
            rlEnd();
        rlSetTexture(0);
    rlPopMatrix();
}

void DrawWalls(struct playInfo *info) {
	int i = 0;

	while (i < info->wallQuantity) {
		DrawWall(*info->walls[i].object.texture, info->walls[i].object.position, info->walls[i].object.sizeV, info->walls[i].endPosition, WHITE);

		i += 1;
	}
}