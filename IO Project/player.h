#include "renderer.h"

#ifndef PLAYER_H
#define PLAYER_H

struct player {
    struct Object2D* object;
    float speedY;
};

void gravity(struct player* player);
void movePlayer(struct player* player, Camera* cam);

#endif