#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stddef.h>

#include "renderer.h"

void Draw3DBillboardRec(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint) {
    rlPushMatrix();

    // get the camera view matrix
    Matrix mat = MatrixInvert(MatrixLookAt(camera.position, camera.target, camera.up));
    // peel off just the rotation
    Quaternion quat = QuaternionFromMatrix(mat);
    mat = QuaternionToMatrix(quat);

    // apply just the rotation
    rlMultMatrixf(MatrixToFloat(mat));

    // translate backwards in the inverse rotated matrix to put the item where it goes in world space
    position = Vector3Transform(position, MatrixInvert(mat));
    rlTranslatef(position.x, position.y, position.z);

    // draw the billboard
    float width = size.x / 2;
    float height = size.y / 2;

    Color color = WHITE;

    rlCheckRenderBatchLimit(6);

    rlSetTexture(texture.id);

    // draw quad
    rlBegin(RL_QUADS);
    rlColor4ub(tint.r, tint.g, tint.b, tint.a);
    // Front Face
    rlNormal3f(0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer

    rlTexCoord2f((float)source.x / texture.width, (float)(source.y + source.height) / texture.height);
    rlVertex3f(-width, -height, 0);  // Bottom Left Of The Texture and Quad

    rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)(source.y + source.height) / texture.height);
    rlVertex3f(+width, -height, 0);  // Bottom Right Of The Texture and Quad

    rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)source.y / texture.height);
    rlVertex3f(+width, +height, 0);  // Top Right Of The Texture and Quad

    rlTexCoord2f((float)source.x / texture.width, (float)source.y / texture.height);
    rlVertex3f(-width, +height, 0);  // Top Left Of The Texture and Quad

    rlEnd();
    rlSetTexture(0);
    rlPopMatrix();
}

void Draw3DBillboard(Camera camera, Texture2D texture, Vector3 position, float size, Color tint) {
    Draw3DBillboardRec(camera, texture, (Rectangle) { 0, 0, (float)texture.width, (float)texture.height }, position, (Vector2) { size, size }, tint);
}

#define _USE_MATH_DEFINES
#include <math.h>

int isCloser(struct Object2D* object1, struct Object2D* object2, Camera3D camera) {
    float deltaX = camera.target.x - camera.position.x;
    float deltaY = camera.target.z - camera.position.z;

    float a1 = deltaY / deltaX;
    float b1 = camera.target.z - (a1 * camera.target.x);

    float a23 = -1 / a1;
    float b2 = object1->position.z - (a23 * object1->position.x);
    float b3 = object2->position.z - (a23 * object2->position.x);

    float x3 = (b1 - b2) / (a23 - a1);
    float y3 = (a1 * x3) + b1;

    float x4 = (b1 - b3) / (a23 - a1);
    float y4 = (a1 * x3) + b1;

    x3 -= camera.position.x;
    y3 -= camera.position.z;
    x4 -= camera.position.x;
    y4 -= camera.position.z;

    return ((x3 * x3) + (y3 * y3)) > ((x4 * x4) + (y4 * y4));
}

void swapObj2D(struct Object2D* object1, struct Object2D* object2) {
    struct Object2D temp = *object1;
    *object1 = *object2;
    *object2 = temp;
}

void Mod_InsertionSort(struct ObjectsToRender* render, Camera3D camera) {
    int min = 0;
    int i = 0;
    struct Object2D tmp = { 0 };
    int j = 0;

    for (i = 1; i < render->size; i++) {
        if (isCloser(&render->objects[i], &render->objects[min], camera)) {
            min = i;
        }
    }
    swapObj2D(&render->objects[min], &render->objects[0]);

    for (i = 2; i < render->size; i++) {
        tmp = render->objects[i];
        j = i - 1;
        while (isCloser(&tmp, &render->objects[j], camera)) {
            render->objects[j + 1] = render->objects[j];
            j--;
        }
        render->objects[j + 1] = tmp;
    }
}
#include <stdlib.h>
#include <string.h>
void RenderTextures(struct ObjectsToRender* render, Camera3D camera) {
    int i = 0;
    struct ObjectsToRender temp = {
        .objects = malloc(sizeof(struct Object2D) * render->size),
        .size = render->size
    };
    memcpy(temp.objects, render->objects, sizeof(struct Object2D) * render->size);

    Mod_InsertionSort(&temp, camera);

    while (i < temp.size) {
        Draw3DBillboard(camera, *temp.objects[i].texture, temp.objects[i].position, temp.objects[i].size, WHITE);

        i += 1;
    }

    free(temp.objects);
}