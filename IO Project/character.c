#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <rlgl.h>

#include "playState.h"

void loadCharacter(struct character *character, const char *characterSave, float x, float z) {
    FILE *playerFile = fopen(characterSave, "r");
    struct Object2D *object = &character->object;
    int i = 0;

    *object = (struct Object2D){
        .position = (Vector3) {
            .x = x,
            .y = 0.0f,
            .z = z
        },
        .texture = malloc(sizeof(Texture2D))
    };

    character->direction = 0;

    fscanf(playerFile, "%[^\n]", character->name);
    fscanf(playerFile, "%f %f", &object->sizeV.x, &object->sizeV.y);

    while (i < 10) {
        fscanf(playerFile, "%i", &character->bodyPart[i]);

        i += 1;
    }

    fclose(playerFile);
}

void unloadCharacter(struct character *character) {
    if (character->object.texture != NULL) {
        UnloadTexture(*character->object.texture);

        free(character->object.texture);
    }
}

inline void DrawBodyPart(struct playInfo *info, struct character *character, int i) {
    DrawTexture(
        info->bodyParts[i][character->bodyPart[i]][character->direction],
        info->bodyPosition[character->direction][i][0],
        info->bodyPosition[character->direction][i][1],
        WHITE);
}

void assemblePlayerTexture(struct playInfo *info, struct character *character) {
    RenderTexture2D render = LoadRenderTexture(info->width, info->height);
    RenderTexture2D render2 = LoadRenderTexture(info->width, info->height);
    int i = 0;

    BeginTextureMode(render);
        ClearBackground(BLANK);

        DrawBodyPart(info, character, LEFT_FOOT);
        DrawBodyPart(info, character, RIGHT_FOOT);
        DrawBodyPart(info, character, LEFT_LEG);
        DrawBodyPart(info, character, RIGHT_LEG);

        if (character->direction == BACK) {
            DrawBodyPart(info, character, LEFT_HAND);
            DrawBodyPart(info, character, RIGHT_HAND);
            DrawBodyPart(info, character, LEFT_ARM);
            DrawBodyPart(info, character, RIGHT_ARM);
            DrawBodyPart(info, character, HEAD);
            DrawBodyPart(info, character, TORSO);
        }
        else {
            DrawBodyPart(info, character, TORSO);
            DrawBodyPart(info, character, LEFT_ARM);
            DrawBodyPart(info, character, RIGHT_ARM);
            DrawBodyPart(info, character, LEFT_HAND);
            DrawBodyPart(info, character, RIGHT_HAND);
            DrawBodyPart(info, character, HEAD);
        }

        while (i < 10) {
            DrawBodyPart(info, character, i);
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
