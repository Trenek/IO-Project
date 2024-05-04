#include <raylib.h>

#include "state.h"

void play(enum state *state, Font fonts[]) {
    enum playState playState = EXPLORE;
    void (*function[])(enum playState *state, Font fonts[]) = {
        //[EXPLORE] = explore,
    };

    while (!WindowShouldClose() && (playState != RETURN) && (playState != DESKTOP)) {
        function[playState](&playState, fonts);
    }

    *state = (playState == RETURN) ? MENU : EXIT;
}