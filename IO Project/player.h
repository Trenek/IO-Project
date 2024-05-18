#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

struct player {
    struct character character;
    float speedY;
};

void gravity(struct player* player);
void movePlayer(struct playInfo *info, struct player *player, Camera *cam);

#endif