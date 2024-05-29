#include <raylib.h>

#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "player.h"
#include "seller.h"
#include "load.h"
#include "floor.h"

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

    struct floor *floors;
    int floorsQuantity;

    int (*shopEquipment)[10][3];
    int shopQuantity;

    struct seller *shops;
    int sellersQuantity;

    struct character chosen;
    int chosenShop;
    int shouldDestroy;

    int dialog;

    Texture2D (*(*bodyParts)[10])[4];
    int height;
    int width;
    int (*bodyPosition)[4][10][2];

    Texture2D(*armorPart[9])[4];
    int (*armorPrice[9])[3];
    int armorPosition[4][9][2];

    Texture2D *weapons;
    int (*weaponPrice)[3];
    int weaponsQuantity;

    Texture2D *items;
    int (*itemsPrice)[3];
    int itemsQuantity;
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