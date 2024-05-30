#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <raylib.h>

#include "player.h"
#include "seller.h"
#include "floor.h"
#include "wall.h"

#include "resources.h"

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
    ACHIEVEMENTS,
    DEATH_SCREEN,

    RELOAD_SAVE,
    RETURN,
    DESKTOP
};

enum position {
    FRONT,
    RIGHT,
    BACK,
    LEFT
};

struct playInfo {
    char *const saveName;

    int mapID;

    struct Resources *resources;

    int(*shopEquipment)[10][3];
    int shopQuantity;

    struct Objects {
        struct character *enemies;
        int enemyQuantity;

        struct seller *shops;
        int sellersQuantity;

        struct floor *floors;
        int floorsQuantity;

        struct wall *walls;
        int wallQuantity;
    };

    struct CommonInfo {
        RenderTexture *screenCamera;
        Rectangle *screenRect;
        Camera camera;

        struct player player;

        enum playState resumeState;

        struct character chosen;
        int chosenShop;
        int shouldDestroy;

        int dialog;
    };
};

struct playInfo initializePlayInfo(struct menuInfo *info);
void freePlayInfo(struct playInfo *info);

void explore(enum playState *playState, struct playInfo *info);
void equipement(enum playState* playState, struct playInfo* info);
void pause(enum playState *state, struct playInfo *info);
void fight(enum playState *playState, struct playInfo *info);
void shop(enum playState *state, struct playInfo *info);
void dialog(enum playState *playState, struct playInfo *info);
void save(enum playState *state, struct playInfo *info);
void deathScreen(enum playState *state, struct playInfo *info);

#endif