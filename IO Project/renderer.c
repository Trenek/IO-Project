#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>

#include <stdlib.h>

#include "object2D.h"
#include "renderer.h"
#include "playState.h"

struct Object2D **createRenderer(struct playInfo *info) {
    struct Object2D **result = malloc(sizeof(struct Object2D *) * (info->enemyQuantity + info->sellersQuantity + 1));
    int i = 0;
    int j = 1;

    result[0] = &info->player.character.object;

    i = 0;
    while (i < info->enemyQuantity) {
        result[j] = &info->enemies[i].object;

        i += 1;
        j += 1;
    }

    i = 0;
    while (i < info->sellersQuantity) {
        result[j] = &info->shops[i].character.object;

        i += 1;
        j += 1;
    }

    return result;
}

static void Draw3DBillboard(Camera camera, Texture2D texture, Vector3 position, Vector2 size, Color tint) {
    const float width = size.x / 2;
    const float height = size.y / 2;

    // get the camera view matrix
    camera.position.y = height + position.y;
    camera.target.y = height + position.y;
    Matrix mat = MatrixLookAt(camera.position, camera.target, camera.up);

    rlPushMatrix();
        rlMultMatrixf(MatrixToFloat(MatrixInvert(mat)));

        // translate backwards in the inverse rotated matrix to put the item where it goes in world space
        position = Vector3Transform(position, mat);
        rlTranslatef(position.x, position.y, position.z);

        rlCheckRenderBatchLimit(6);
        rlSetTexture(texture.id);
            rlBegin(RL_QUADS);
                rlColor4ub(tint.r, tint.g, tint.b, tint.a);
                // Front Face
                rlNormal3f(0.0f, 0.0f, 1.0f); // Normal Pointing Towards Viewer

                rlTexCoord2f(0.0f, 1.0f); // Bottom Left Of The Texture and Quad
                rlVertex3f(-width, 0, 0);

                rlTexCoord2f(1.0f, 1.0f); // Bottom Right Of The Texture and Quad
                rlVertex3f(+width, 0, 0);

                rlTexCoord2f(1.0f, 0.0f); // Top Right Of The Texture and Quad
                rlVertex3f(+width, 2 * height, 0);

                rlTexCoord2f(0.0f, 0.0f); // Top Left Of The Texture and Quad
                rlVertex3f(-width, 2 * height, 0);
            rlEnd();
        rlSetTexture(0);
    rlPopMatrix();
}

void DrawFloor(Texture2D texture, Vector3 position, Vector2 size, Vector2 realSize, Color tint) {
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

static int isCloser(struct Object2D *object1, struct Object2D *object2, Camera3D camera) {
    int result = 0;

    float deltaX = camera.target.x - camera.position.x;
    float deltaZ = camera.target.z - camera.position.z;

    if (fabsf(deltaX) == 0.0f) {
        if (deltaZ > 0.0f) {
            result = object1->position.z - camera.position.z > object2->position.z - camera.position.z;
        }
        else {
            result = -(object1->position.z - camera.position.z) > -(object2->position.z - camera.position.z);
        }
    }
    else if (fabsf(deltaZ) == 0.0f) {
        if (deltaX > 0.0f) {
            result = object1->position.x - camera.position.x > object2->position.x - camera.position.x;
        }
        else {
            result = -(object1->position.x - camera.position.x) > -(object2->position.x - camera.position.x);
        }
    }
    else {
        float a1 = deltaZ / deltaX;
        float b1 = camera.target.z - (a1 * camera.target.x);

        // prostopad³e linie
        float a23 = -1 / a1;
        float b2 = object1->position.z - (a23 * object1->position.x);
        float b3 = object2->position.z - (a23 * object2->position.x);

        float x3 = (b1 - b2) / (a23 - a1);
        float z3 = (a1 * x3) + b1;

        float x4 = (b1 - b3) / (a23 - a1);
        float z4 = (a1 * x4) + b1;

        x3 -= camera.position.x;
        z3 -= camera.position.z;
        x4 -= camera.position.x;
        z4 -= camera.position.z;

        result = ((x3 * x3) + (z3 * z3)) > ((x4 * x4) + (z4 * z4));
    }

    return result;
}

static void Mod_InsertionSort(struct Object2D *render[], int n, Camera3D camera) {
    int min = 0;
    int i = 0;
    struct Object2D *tmp = 0;
    int j = 0;

    for (i = 1; i < n; i++) {
        if (isCloser(render[i], render[min], camera)) {
            min = i;
        }
    }

    tmp = render[min];
    render[min] = render[0];
    render[0] = tmp;

    for (i = 2; i < n; i++) {
        tmp = render[i];
        j = i - 1;
        while (isCloser(tmp, render[j], camera)) {
            render[j + 1] = render[j];
            j--;
        }
        render[j + 1] = tmp;
    }
}

void RenderTextures(struct Object2D *render[], int n, Camera3D camera) {
    int i = 0;

    Mod_InsertionSort(render, n, camera);
    while (i < n) {
        Draw3DBillboard(camera, *render[i]->texture, render[i]->position, render[i]->sizeV, WHITE);

        i += 1;
    }
}