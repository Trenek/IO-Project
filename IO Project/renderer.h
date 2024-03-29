#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <raylib.h>

struct Object2D {
    Vector3 position;
    Texture2D* texture;
    Vector2 sizeV;
    Texture2D Animation[4][4];
    int animFrame;
    int state;
};

struct ObjectsToRender {
    struct Object2D* objects;
    int size;
};

void RenderTextures(struct ObjectsToRender* render, int n, Camera3D camera);

#endif