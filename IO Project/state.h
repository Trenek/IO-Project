#ifndef STATE_H
#define STATE_H

enum state {
    MENU,
    NEW_GAME,
    LOAD_GAME,
    SETTINGS,
    ACHIEVEMENTS,
    PLAY,
    TUTORIAL,

    RELOAD,
    EXIT
};

struct menuInfo {
    Font *fonts;
    int fontsQuantity;
    Music *music;
    int musicQuantity;
    const char *saveName;
};

void initializeState(struct menuInfo *info);
void freeState(struct menuInfo *info);

void menu(enum state *state, struct menuInfo *info);
void newGame(enum state *state, struct menuInfo *info);
void loadGame(enum state *state, struct menuInfo *info);
void settings(enum state *state, struct menuInfo *info);
void achievements(enum state *state, struct menuInfo *info);
void play(enum state *state, struct menuInfo *info);
void tutorial(enum state* state, struct menuInfo* info);

#endif