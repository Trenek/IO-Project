#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <rlgl.h>

#include "playState.h"

static void loadBody(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 10) {
        fscanf(playerFile, "%i", &character->bodyPart[i]);

        i += 1;
    }
}

static void loadArmor(FILE *playerFile, struct character *character) {
    int i = 0;

    while (i < 9) {
        fscanf(playerFile, "%i", &character->armorPart[i]);

        i += 1;
    }
}

void loadCharacter(struct character *character, const char *characterSave, float x, float z) {
    FILE *playerFile = fopen(characterSave, "r");
    struct Object2D *object = &character->object;

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

    loadBody(playerFile, character);
    loadArmor(playerFile, character);

    fscanf(playerFile, "%i", &character->weapon);

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

void DrawBody(struct playInfo *info, struct character *character) {
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
}

inline void DrawArmorPart(struct playInfo *info, struct character *character, int i) {
    if (character->armorPart[i] != -1)
    DrawTexture(
        info->armorPart[i][character->armorPart[i]][character->direction],
        info->armorPosition[character->direction][i][0],
        info->armorPosition[character->direction][i][1],
        WHITE);
}

void DrawArmor(struct playInfo *info, struct character *character) {
    int i = 0;

    while (i < 9) {
        DrawArmorPart(info, character, i);

        i += 1;
    }
}

void assemblePlayerTexture(struct playInfo *info, struct character *character) {
    RenderTexture2D render = LoadRenderTexture(info->width, info->height);
    RenderTexture2D render2 = LoadRenderTexture(info->width, info->height);

    BeginTextureMode(render);
        ClearBackground(BLANK);

        DrawBody(info, character);
        DrawArmor(info, character);
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
