#include <raylib.h>

#include "state.h"
#include "playState.h"

void play(enum state *state, struct menuInfo *info) {
    enum playState playState = EXPLORE;
    void (*function[])(enum playState *state, struct playInfo *info) = {
        [EXPLORE] = explore,
        [EQUIPEMENT] = equipement,
        [PAUSE] = pause,
        [FIGHT] = fight,
        [SHOP] = shop,
        [DIALOG] = dialog,
        [SAVE] = save,
        [DEATH_SCREEN] = deathScreen
    };

    do {
        playState = EXPLORE;
        struct playInfo playInfo = initializePlayInfo(info);

        while (!WindowShouldClose() && (playState != RETURN) && (playState != DESKTOP) && (playState != RELOAD_SAVE)) {
            function[playState](&playState, &playInfo);
        }

        freePlayInfo(&playInfo);
    } while (playState == RELOAD_SAVE);

    *state = (playState == RETURN) ? MENU : EXIT;
}