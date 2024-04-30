#ifndef STATE_H
#define STATE_H

enum state {
    MENU,
    NEW_GAME,
    LOAD_GAME,
    SETTINGS,
    ACHIVEMENTS,
    EXPLORE,
    EQUIPEMENT,
    MAP,
    SAVE,
    PAUSE,
    FIGHT,
    DIALOG,
    SHOP,
    TRAINING,

    RELOAD,
    EXIT
};

void menu(enum state *state);
void newGame(enum state *state);
void loadGame(enum state *state);
void settings(enum state *state);
void achivements(enum state *state);
void explore(enum state *state);

#endif