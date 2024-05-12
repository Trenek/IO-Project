#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <raylib.h>

struct Object2D {
    Vector3 position;
    Texture2D* texture;
    Vector2 sizeV;
    Texture (*Animation)[4][4];
    int animFrame;
    int state;
};

void RenderTextures(struct Object2D *render[], int n, Camera3D camera);

#endif