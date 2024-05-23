#include <raylib.h>
#include <stdio.h>

#include "state.h"

#include "loadSettings.h"

union index {
    struct {
        unsigned char rank : 4;
        unsigned char file : 4;
    };
    unsigned char index;
};

int main(void) {
    union index index = {
        .rank = 0x8,
        .file = 0x8
    };

    if (index.index && 0x88) {
        // bad index
    }

    enum state state = MENU;
    struct menuInfo info = { 0 };
    void (*function[])(enum state *state, struct menuInfo *info) = {
        [MENU] = menu,
        [NEW_GAME] = newGame,
        [LOAD_GAME] = loadGame,
        [SETTINGS] = settings,
        [TUTORIAL] = tutorial,
        [PLAY] = play
    };

    do {
        state = MENU;

        loadSettings(&info);
        initializeState(&info);

        while (!WindowShouldClose() && (state != EXIT) && (state != RELOAD)) {
            function[state](&state, &info);
        }

        freeState(&info);

        CloseWindow();
    } while (state == RELOAD);

    return 0;
}
