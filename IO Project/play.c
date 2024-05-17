#include <raylib.h>

#include "state.h"
#include "playState.h"

void play(enum state *state, struct menuInfo *info) {
    enum playState playState = EXPLORE;
    struct playInfo playInfo = initializePlayInfo(info);
    void (*function[])(enum playState *state, struct playInfo *info) = {
        [EXPLORE] = explore,
        [EQUIPEMENT] = equipement,
        [PAUSE] = pause,
        [FIGHT] = fight
    };

    while (!WindowShouldClose() && (playState != RETURN) && (playState != DESKTOP)) {
        function[playState](&playState, &playInfo);
    }

    freePlayInfo(&playInfo);

    *state = (playState == RETURN) ? MENU : EXIT;
}