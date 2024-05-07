#include <raylib.h>

#include "state.h"
#include "menuInfo.h"

//#define FULLSCREEN

int main(void) {
    enum state state = MENU;
    void (*function[])(enum state *state, Font fonts[]) = {
        [MENU] = menu,
        [NEW_GAME] = newGame,
        [LOAD_GAME] = loadGame,
        [SETTINGS] = settings,
        [ACHIEVEMENTS] = achievements,
        [PLAY] = play
    };

    do {
        state = MENU;

        SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
#ifdef FULLSCREEN
        int display = GetCurrentMonitor();
        InitWindow(GetMonitorWidth(display), GetMonitorHeight(display), "Project");
        ToggleFullscreen();
#else
        InitWindow(800, 600, "Project");
#endif

        SetTargetFPS(240);

        Font fonts[] = {
            LoadFontEx("resources/fonts/font2.ttf", 100, NULL, 512)
        };

        SetFontsFilter(fonts, sizeof(fonts) / sizeof(Font));

        while (!WindowShouldClose() && (state != EXIT) && (state != RELOAD)) {
            function[state](&state, fonts);
        }

        UnloadFonts(fonts, sizeof(fonts) / sizeof(Font));

        CloseWindow();
    } while (state == RELOAD);

    return 0;
}
