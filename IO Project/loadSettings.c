#include <raylib.h>
#include <rlgl.h>

#include <stdio.h>
#include <stdbool.h>

#include "state.h"

void loadSettings(struct menuInfo *info) {
    FILE *file = fopen("config.cfg", "r");

    (void)fscanf(file, "%i", &info->framesPerSecond);
    (void)fscanf(file, "%i", &info->textureQuality);
    (void)fscanf(file, "%i %i", &info->windowWidth, &info->windowHeight);
    (void)fscanf(file, "%i", &info->fullScreenMode);

    //SetTraceLogLevel(LOG_ERROR); // For final version
    SetConfigFlags(
//      FLAG_WINDOW_UNDECORATED |
        FLAG_MSAA_4X_HINT | 
        FLAG_VSYNC_HINT
    );


    InitWindow(info->windowWidth, info->windowHeight, "Project");
    if ((info->fullScreenMode == 1 && IsWindowFullscreen() == false) || (info->fullScreenMode == 0 && IsWindowFullscreen() == true)) ToggleFullscreen();
    SetTargetFPS(info->framesPerSecond);

    rlEnableDepthTest();

    fclose(file);
}