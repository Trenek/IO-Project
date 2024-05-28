#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <rlgl.h>

#include "playState.h"
#include "state.h"

static void DrawBodyPart(struct playInfo *info, struct character *character, int i) {
    DrawTexture(
        (*info->bodyParts)[i][character->bodyPart[i]][character->direction],
        (*info->bodyPosition)[character->direction][i][0],
        (*info->bodyPosition)[character->direction][i][1],
        WHITE);
}

static void DrawBody(struct playInfo *info, struct character *character) {
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

static void DrawArmorPart(struct playInfo *info, struct character *character, int i) {
    if (character->armorPart[i] != -1)
    DrawTexture(
        info->armorPart[i][character->armorPart[i]][character->direction],
        info->armorPosition[character->direction][i][0],
        info->armorPosition[character->direction][i][1],
        WHITE);
}

static void DrawArmor(struct playInfo *info, struct character *character) {
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

static void mainDrawBodyPart(struct menuInfo *info, struct character *character, int i) {
    DrawTexture(
        info->bodyParts[i][character->bodyPart[i]][character->direction],
        info->bodyPosition[character->direction][i][0],
        info->bodyPosition[character->direction][i][1],
        WHITE);
}

static void mainDrawBody(struct menuInfo *info, struct character *character) {
    mainDrawBodyPart(info, character, LEFT_FOOT);
    mainDrawBodyPart(info, character, RIGHT_FOOT);
    mainDrawBodyPart(info, character, LEFT_LEG);
    mainDrawBodyPart(info, character, RIGHT_LEG);

    if (character->direction == BACK) {
        mainDrawBodyPart(info, character, LEFT_HAND);
        mainDrawBodyPart(info, character, RIGHT_HAND);
        mainDrawBodyPart(info, character, LEFT_ARM);
        mainDrawBodyPart(info, character, RIGHT_ARM);
        mainDrawBodyPart(info, character, HEAD);
        mainDrawBodyPart(info, character, TORSO);
    }
    else {
        mainDrawBodyPart(info, character, TORSO);
        mainDrawBodyPart(info, character, LEFT_ARM);
        mainDrawBodyPart(info, character, RIGHT_ARM);
        mainDrawBodyPart(info, character, LEFT_HAND);
        mainDrawBodyPart(info, character, RIGHT_HAND);
        mainDrawBodyPart(info, character, HEAD);
    }
}

void mainAssemblePlayerTexture(struct menuInfo *info, struct character *character) {
    RenderTexture2D render = LoadRenderTexture(info->width, info->height);
    RenderTexture2D render2 = LoadRenderTexture(info->width, info->height);

    BeginTextureMode(render);
        ClearBackground(BLANK);

        mainDrawBody(info, character);
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
