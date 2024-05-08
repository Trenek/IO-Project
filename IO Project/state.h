#ifndef STATE_H
#define STATE_H

struct menuInfo;

enum state {
    MENU,
    NEW_GAME,
    LOAD_GAME,
    SETTINGS,
    ACHIEVEMENTS,
    PLAY,

    RELOAD,
    EXIT
};

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

void menu(enum state *state, struct menuInfo fonts[]);
void newGame(enum state *state, struct menuInfo fonts[]);
void loadGame(enum state *state, struct menuInfo fonts[]);
void settings(enum state *state, struct menuInfo fonts[]);
void achievements(enum state *state, struct menuInfo fonts[]);
void play(enum state *state, struct menuInfo fonts[]);

void explore(enum playState *playState, struct menuInfo fonts[]);

int example2(void);

#endif