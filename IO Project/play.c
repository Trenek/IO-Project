#include <raylib.h>

#include "state.h"

#include "menuElement.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

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