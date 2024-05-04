#ifndef STATE_H
#define STATE_H

enum state {
    MENU,
    NEW_GAME,
    LOAD_GAME,
    SETTINGS,
    ACHIVEMENTS,
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

void menu(enum state *state, Font fonts[]);
void newGame(enum state *state, Font fonts[]);
void loadGame(enum state *state, Font fonts[]);
void settings(enum state *state, Font fonts[]);
void achivements(enum state *state, Font fonts[]);
void play(enum state *state, Font fonts[]);

void explore(enum state *state, Font fonts[]);

int example2(void);

#endif