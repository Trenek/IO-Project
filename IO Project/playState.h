#include <raylib.h>

#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "player.h"

struct menuInfo;
struct Object2D;
struct player;

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
    MISSIONS,

    RETURN,
    DESKTOP
};

enum position {
    FRONT,
    RIGHT,
    BACK,
    LEFT
};

enum BodyPartTexture {
    HEAD,
    TORSO,
    LEFT_ARM,
    RIGHT_ARM,
    LEFT_LEG,
    RIGHT_LEG,
    LEFT_HAND,
    RIGHT_HAND,
    LEFT_FOOT,
    RIGHT_FOOT
};

struct playInfo {
    RenderTexture *screenCamera;
    Rectangle *screenRect;
    Camera camera;

    Font *fonts;
    int fontsQuantity;

    Music *music;
    int musicQuantity;

    enum playState resumeState;

    struct player player;

    struct character *enemies;
    int enemyQuantity;

    struct character *shops;
    int shopsQuantity;

    struct character chosen;

    int dialog;

    Texture2D (*bodyParts[10])[4];
    int height;
    int width;
    int bodyPosition[4][10][2];
};

struct playInfo initializePlayInfo(struct menuInfo *info);
void freePlayInfo(struct playInfo *info);

void explore(enum playState *playState, struct playInfo *info);
void equipement(enum playState* playState, struct playInfo* info);
void pause(enum playState *state, struct playInfo *info);
void fight(enum playState *playState, struct playInfo *info);
void shop(enum playState *state, struct playInfo *info);
void dialog(enum playState *playState, struct playInfo *info);

#endif