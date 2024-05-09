#ifndef STATE_H
#define STATE_H

struct menuInfo {
    Font *fonts;
    int fontsQuantity;
    const char *saveName;
};

void SetFonts(struct menuInfo *info);
void UnloadFonts(struct menuInfo *info);

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

void menu(enum state *state, struct menuInfo fonts[]);
void newGame(enum state *state, struct menuInfo fonts[]);
void loadGame(enum state *state, struct menuInfo fonts[]);
void settings(enum state *state, struct menuInfo fonts[]);
void achievements(enum state *state, struct menuInfo fonts[]);
void play(enum state *state, struct menuInfo *info);

#endif