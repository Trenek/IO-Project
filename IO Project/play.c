#include <raylib.h>

#include "state.h"
#include "playState.h"

void play(enum state *state, struct menuInfo *info) {
    RenderTexture screenCamera = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    Rectangle rect = { 0.0f, 0.0f, (float)screenCamera.texture.width, (float)-screenCamera.texture.height };

    enum playState playState = EXPLORE;
    struct playInfo playInfo = {
        .fonts = info->fonts,
        .fontsQuantity = info->fontsQuantity,
        .screenCamera = &screenCamera,
        .screenRect = &rect
    };
    void (*function[])(enum playState *state, struct playInfo *info) = {
        [EXPLORE] = explore,
        [PAUSE] = pause
    };

    while (!WindowShouldClose() && (playState != RETURN) && (playState != DESKTOP)) {
        function[playState](&playState, &playInfo);
    }

    *state = (playState == RETURN) ? MENU : EXIT;
}