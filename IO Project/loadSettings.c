#include <raylib.h>
#include <rlgl.h>

//#define FULLSCREEN

void loadSettings(void) {
    //SetTraceLogLevel(LOG_ERROR); // For final version
    SetConfigFlags(
//      FLAG_WINDOW_UNDECORATED |
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
    rlEnableDepthTest();
}