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

    RETURN,
    DESKTOP
};

struct TexturePosition {
    Texture2D front;
    Texture2D back;
};

enum BodyPartTexture {
    HEAD,
    TORSO,
    LEFT_ARM,
    RIGHT_ARM,
    LEFT_HAND,
    RIGHT_HAND,
    LEFT_LEG,
    RIGHT_LEG,
    LEFT_FOOT,
    RIGHT_FOOT
};

struct playInfo {
    Font *fonts;
    int fontsQuantity;
    RenderTexture *screenCamera;
    Rectangle *screenRect;
    Music *music;
    int musicQuantity;
    Camera camera;
    struct Object2D *objects;
    int objectsQuantity;
    Texture2D *textures;
    int texturesQuantity;
    struct player player;
    enum playState resumeState;

    struct character *npc;
    struct character enemy;

    struct TexturePosition *texturePosition[10];
};

struct playInfo initializePlayInfo(struct menuInfo *info);
void freePlayInfo(struct playInfo *info);

void explore(enum playState *playState, struct playInfo *info);
void equipement(enum playState* playState, struct playInfo* info);
void pause(enum playState *state, struct playInfo *info);
void fight(enum playState *playState, struct playInfo *info);

#endif