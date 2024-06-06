#ifndef STATE_H
#define STATE_H

#include <raylib.h>

#include "resources.h"
#include "settings.h"

enum state {
    MENU,
    NEW_GAME,
    LOAD_GAME,
    SETTINGS,
    PLAY,
    TUTORIAL,
    CHARACTER_CREATOR,

    RELOAD,
    EXIT
};

struct menuInfo {
    char saveName[125];

    int body[10];

    struct Resources resources;
    struct Settings;
};

void initializeState(struct menuInfo *info);
void freeState(struct menuInfo *info);

void menu(enum state *state, struct menuInfo *info);
void newGame(enum state *state, struct menuInfo *info);
void loadGame(enum state *state, struct menuInfo *info);
void settings(enum state *state, struct menuInfo *info);
void play(enum state *state, struct menuInfo *info);
void tutorial(enum state* state, struct menuInfo* info);
void characterCreator(enum state* state, struct menuInfo* info);

#endif