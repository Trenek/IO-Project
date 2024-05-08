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
    int letters[] = U"aąbcćdeęfghijklłmnoópqrsśtuvwxyzźżAĄBCĆDEĘFGHIJKLŁMNOÓPQRSŚTUVWXYZŹŻ";

    do {
        state = MENU;

        loadSettings();

        Font fonts[] = {
            LoadFontEx("resources/fonts/font2.ttf", 100, letters, sizeof(letters) / sizeof(int))
        };

        SetFontsFilter(fonts, sizeof(fonts) / sizeof(Font));

        info.fonts = fonts;

        while (!WindowShouldClose() && (state != EXIT) && (state != RELOAD)) {
            function[state](&state, &info);
        }

        UnloadFonts(fonts, sizeof(fonts) / sizeof(Font));

        CloseWindow();
    } while (state == RELOAD);

    return 0;
}
