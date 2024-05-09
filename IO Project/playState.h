#include <raylib.h>

#ifndef PLAYSTATE_H
#define PLAYSTATE_H

struct playInfo;

enum playState {
    EXPLORE,
    EQUIPEMENT,
    MAP,
    SAVE,
    PAUSE,
    FIGHT,
    DIALOG,
    SHOP,
    TRAINING,

    RETURN,
    DESKTOP
};

struct playInfo {
    Font *fonts;
    int fontsQuantity;
    RenderTexture *screenCamera;
    Rectangle *screenRect;
};

void explore(enum playState *playState, struct playInfo *info);
void pause(enum playState *state, struct playInfo *info);

#endif