// raylib.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <raylib.h>

#include "state.h"

//#define FULLSCREEN

int main(void) {
    enum state state = MENU;
    void (*function[])(enum state *state) = {
        [MENU] = menu,
        [NEW_GAME] = newGame,
        [LOAD_GAME] = loadGame,
        [SETTINGS] = settings,
        [ACHIVEMENTS] = achivements,
        [EXPLORE] = explore
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

        while (!WindowShouldClose() && (state != EXIT)) {
            function[state](&state);
        }

        CloseWindow();
    } while (state == RELOAD);

    return 0;
}