#include <raylib.h>

struct Object2D {
    Vector3 position;
    Texture2D* texture;
    int size;
};

struct ObjectsToRender {
    struct Object2D* objects;
    int size;
};

void RenderTextures(struct ObjectsToRender* render, Camera3D camera);