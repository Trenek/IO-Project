#include <raylib.h>

//#define FULLSCREEN

void loadSettings(void) {
    SetConfigFlags(
//      FLAG_WINDOW_UNDECORATED |
        FLAG_WINDOW_HIGHDPI | 
        FLAG_MSAA_4X_HINT | 
        FLAG_VSYNC_HINT
    );
#ifdef FULLSCREEN
    int display = GetCurrentMonitor();
    InitWindow(GetMonitorWidth(display), GetMonitorHeight(display), "Project");
    ToggleFullscreen();
#else
    InitWindow(800, 600, "Project");
#endif

    SetTargetFPS(240);
}