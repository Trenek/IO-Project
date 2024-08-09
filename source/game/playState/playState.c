#include <stdlib.h>

#include <raylib.h>

#include "state.h"
#include "playState.h"

struct playInfo initializePlayInfo(struct menuInfo *info) {
    struct playInfo result = {
        .save.saveName = info->saveName,

        .resources = &info->resources,

        .screenCamera = malloc(sizeof(RenderTexture)),
        .screenRect = malloc(sizeof(Rectangle)),
        .camera = {
            .position = {
                .x = 10,
                .y = 2,
                .z = 0
            },
            .up.y = 1,
            .fovy = 45
        }
    };

    *result.screenCamera = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() + 20);
    *result.screenRect = (Rectangle){ 0.0f, 0.0f, (float)result.screenCamera->texture.width, (float)-result.screenCamera->texture.height };

    LoadSaveFile(&result.save, result.resources);

    return result;
}

void freePlayInfo(struct playInfo *info) {
    UnloadSaveFile(&info->save);

    UnloadRenderTexture(*info->screenCamera);

    free(info->screenCamera);
    free(info->screenRect);
}