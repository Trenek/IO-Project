#include <raylib.h>
#include <rlgl.h>

#include "playState.h"

void assemblePlayerTexture(struct playInfo *info, struct character *character) {
    RenderTexture2D render = LoadRenderTexture(info->width, info->height);
    RenderTexture2D render2 = LoadRenderTexture(info->width, info->height);
    int i = 0;

    BeginTextureMode(render);
    ClearBackground(BLANK);

    while (i < 10) {
        DrawTexture(
            info->texturePosition[i][character->bodyPart[i]].position[character->direction],
            info->bodyPosition[character->direction][i][0],
            info->bodyPosition[character->direction][i][1],
            WHITE);
        i += 1;
    }
    EndTextureMode();

    BeginTextureMode(render2);
    ClearBackground(BLANK);
    DrawTexture(render.texture, 0, 0, WHITE);
    EndTextureMode();

    UnloadTexture(*character->object.texture);

    *character->object.texture = render2.texture;

    rlUnloadFramebuffer(render2.id);
    UnloadRenderTexture(render);
}
