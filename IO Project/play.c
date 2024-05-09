#include <raylib.h>

#include "state.h"
#include "menuInfo.h"

void play(enum state *state, struct menuInfo *info) {
    enum playState playState = EXPLORE;
    void (*function[])(enum playState *state, struct menuInfo *info) = {
        [EXPLORE] = explore,
    };

    while (!WindowShouldClose() && (playState != RETURN) && (playState != DESKTOP)) {
        function[playState](&playState, info);
    }

    *state = (playState == RETURN) ? MENU : EXIT;
}