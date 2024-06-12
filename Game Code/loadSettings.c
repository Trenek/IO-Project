#include <raylib.h>
#include <rlgl.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "state.h"

void loadSettings(struct menuInfo *info) {
    FILE *file = fopen("config.cfg", "r");

    (void)fscanf(file, "%i", &info->framesPerSecond);
    (void)fscanf(file, "%i", &info->textureQuality);
    (void)fscanf(file, "%i %i", &info->windowWidth, &info->windowHeight);
    (void)fscanf(file, "%i", &info->fullScreenMode);

    SetTraceLogLevel(LOG_ERROR);
    SetConfigFlags(
        FLAG_MSAA_4X_HINT | 
        FLAG_VSYNC_HINT
    );

    InitWindow(info->windowWidth, info->windowHeight, "Project");
    if ((info->fullScreenMode == 1 && IsWindowFullscreen() == false) || (info->fullScreenMode == 0 && IsWindowFullscreen() == true)) ToggleFullscreen();
    SetTargetFPS(info->framesPerSecond);

    SetExitKey(KEY_END);
    
    srand((unsigned int)time(NULL));
    rlEnableDepthTest();

    fclose(file);
}