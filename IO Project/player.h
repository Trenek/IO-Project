#include "renderer.h"

struct player {
    struct Object2D* object;
    float speedY;
};

void gravity(struct player* player, Camera* cam);
void movePlayer(struct player* player, Camera* cam);