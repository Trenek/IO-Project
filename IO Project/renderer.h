#include <raylib.h>

#include "object2D.h"

struct playInfo;

struct Object2D **createRenderer(struct playInfo *info);
void RenderTextures(struct Object2D *render[], int n, Camera3D camera);
void DrawFloor(Texture2D texture, Vector3 position, Vector2 size, Vector2 realSize, Color tint);