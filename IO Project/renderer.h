#include <raylib.h>

#include "object2D.h"

struct playInfo;

struct Object2D **createRenderer(struct playInfo *info);
void RenderTextures(struct Object2D *render[], int n, Camera3D camera);