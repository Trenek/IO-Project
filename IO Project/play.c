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
        [FIGHT] = fight,
        [SHOP] = shop,
        [DIALOG] = dialog,
        [SAVE] = save,
        [DEATH_SCREEN] = deathScreen
    };

    while (!WindowShouldClose() && (playState != RETURN) && (playState != DESKTOP) && (playState != RELOAD_SAVE)) {
        function[playState](&playState, &playInfo);
    }

    freePlayInfo(&playInfo);

    *state = (playState == RETURN) ? MENU : (playState == RELOAD_SAVE) ? PLAY : EXIT;
}