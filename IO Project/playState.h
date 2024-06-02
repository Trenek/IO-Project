#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <raylib.h>

#include "resources.h"
#include "savefile.h"

struct menuInfo;

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

struct playInfo {
    struct Resources *resources;

    struct SaveFile save;

    struct CommonInfo {
        RenderTexture *screenCamera;
        Rectangle *screenRect;
        Camera camera;

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
void achievements(enum playState* state, struct playInfo* info);
void deathScreen(enum playState *state, struct playInfo *info);

#endif