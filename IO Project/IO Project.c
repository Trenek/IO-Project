//if you want to run tests simply uncomment below line and also uncomment the same line in file main_test.c
#define RUN_TESTS

#include <raylib.h>

#include "state.h"

#ifndef RUN_TESTS
int main(void) {
    enum state state = MENU;
    struct menuInfo info = { 0 };
    void (*function[])(enum state *state, struct menuInfo *info) = {
        [MENU] = menu,
        [NEW_GAME] = newGame,
        [LOAD_GAME] = loadGame,
        [SETTINGS] = settings,
        [TUTORIAL] = tutorial,
        [CHARACTER_CREATOR] = characterCreator,
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
#endif
