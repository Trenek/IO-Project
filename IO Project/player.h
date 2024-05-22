#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

struct player {
    struct character character;
    int equipment[25][3];
    float speedY;
};

void gravity(struct player* player);
void movePlayer(struct playInfo *info, struct player *player, Camera *cam);

#endif