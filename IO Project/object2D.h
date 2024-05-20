#ifndef OBJECT2D_H
#define OBJECT2D_H

#include <raylib.h>

struct Object2D {
    Vector3 position;
    Texture2D *texture;
    Vector2 sizeV;
};

#endif