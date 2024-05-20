#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

struct player {
    struct character character;
    int equipment[25][3];
    float speedY;
};

void loadPlayer(struct playInfo *info, const char *saveName);
void unloadPlayer(struct playInfo *info);
void gravity(struct player* player);
void movePlayer(struct playInfo *info, struct player *player, Camera *cam);

#endif