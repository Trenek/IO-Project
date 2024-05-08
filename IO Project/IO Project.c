#include <raylib.h>

#include "state.h"
#include "menuInfo.h"

#include "loadSettings.h"

int main(void) {
    enum state state = MENU;
    struct menuInfo info = { 0 };
    void (*function[])(enum state *state, struct menuInfo *info) = {
        [MENU] = menu,
        [NEW_GAME] = newGame,
        [LOAD_GAME] = loadGame,
        [SETTINGS] = settings,
        [ACHIEVEMENTS] = achievements,
        [PLAY] = play
    };

    do {
        state = MENU;

        loadSettings();
        SetFonts(&info);

        while (!WindowShouldClose() && (state != EXIT) && (state != RELOAD)) {
            function[state](&state, &info);
        }

        UnloadFonts(&info);

        CloseWindow();
    } while (state == RELOAD);

    return 0;
}
