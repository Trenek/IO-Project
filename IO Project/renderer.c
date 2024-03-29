#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"
#include <stddef.h>

#include "renderer.h"

void Draw3DBillboard(Camera camera, Texture2D texture, Vector3 position, Vector2 size, Color tint) {
    Rectangle source = { .x = 0, .y = 0, .width = (float)texture.width, .height = (float)texture.height };

    float width = size.x / 2;
    float height = size.y / 2;
    static float a = 0.0f;

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

    rlCheckRenderBatchLimit(6);
    rlSetTexture(texture.id);
    rlBegin(RL_QUADS);
        rlColor4ub(tint.r, tint.g, tint.b, tint.a);
        // Front Face
        rlNormal3f(0.0f, 0.0f, 1.0f);                  // Normal Pointing Towards Viewer
        /**/
        rlTexCoord2f((float)source.x / texture.width, (float)(source.y + source.height) / texture.height);
        rlVertex3f(-width, -height, -sin(a) / 16);  // Bottom Left Of The Texture and Quad
        /**/
        rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)(source.y + source.height) / texture.height);
        rlVertex3f(+width, -height, -sin(a) / 16);  // Bottom Right Of The Texture and Quad

        rlTexCoord2f((float)(source.x + source.width) / texture.width, (float)source.y / texture.height);
        rlVertex3f(+width, +height, sin(a) / 16);  // Top Right Of The Texture and Quad

        rlTexCoord2f((float)source.x / texture.width, (float)source.y / texture.height);
        rlVertex3f(-width, +height, sin(a) / 16);  // Top Left Of The Texture and Quad
    rlEnd();
    rlSetTexture(0);
    rlPopMatrix();

    //a += 0.004f;
    a += 0.01;
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

void Mod_InsertionSort(struct ObjectsToRender* render, int n, Camera3D camera) {
    int min = 0;
    int i = 0;
    struct Object2D *tmp = 0;
    int j = 0;

    for (i = 1; i < n; i++) {
        if (isCloser(render[i].objects, render[min].objects, camera)) {
            min = i;
        }
    }

    tmp = render[min].objects;
    render[min].objects = render[0].objects;
    render[0].objects = tmp;
    
    for (i = 2; i < n; i++) {
        tmp = render[i].objects;
        j = i - 1;
        while (isCloser(tmp, render[j].objects, camera)) {
            render[j + 1].objects = render[j].objects;
            j--;
        }
        render[j + 1].objects = tmp;
    }
}
#include <stdlib.h>
#include <string.h>
void RenderTextures(struct ObjectsToRender* render, int n, Camera3D camera) {
    int i = 0;

    Mod_InsertionSort(render, n, camera);
    while (i < n) {
        if (render[i].objects->state != 0) {
            Draw3DBillboard(camera, render[i].objects->Animation[render[i].objects->state - 1][(render[i].objects->animFrame >> 6) % 4], render[i].objects->position, render[i].objects->sizeV, WHITE);
            render[i].objects->animFrame += 1;
        }
        else {
            Draw3DBillboard(camera, *render[i].objects->texture, render[i].objects->position, render[i].objects->sizeV, WHITE);
            render[i].objects->animFrame = 0;
        }

        i += 1;
    }
}