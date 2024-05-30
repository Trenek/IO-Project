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

static void DrawArmorPart(struct playInfo *info, struct character *character, int i) {
    if (character->armorPart[i] != -1)
    DrawTexture(
        info->armorPart[i][character->armorPart[i]][character->direction],
        info->armorPosition[character->direction][i][0],
        info->armorPosition[character->direction][i][1],
        WHITE);
}

static void DrawCharacter(struct playInfo *info, struct character *character) {
    DrawBodyPart(info, character, LEFT_LEG);
    DrawBodyPart(info, character, RIGHT_LEG);
    DrawArmorPart(info, character, PANTS);
    DrawBodyPart(info, character, LEFT_FOOT);
    DrawArmorPart(info, character, LEFT_BOOT);
    DrawBodyPart(info, character, RIGHT_FOOT);
    DrawArmorPart(info, character, RIGHT_BOOT);

    if (character->direction == BACK) {
        DrawBodyPart(info, character, LEFT_HAND);
        DrawArmorPart(info, character, LEFT_GLOVE);
        DrawBodyPart(info, character, RIGHT_HAND);
        DrawArmorPart(info, character, RIGHT_GLOVE);
        DrawBodyPart(info, character, LEFT_ARM);
        DrawArmorPart(info, character, LEFT_SLEEVE);
        DrawBodyPart(info, character, RIGHT_ARM);
        DrawArmorPart(info, character, RIGHT_SLEEVE);
        DrawBodyPart(info, character, HEAD);
        DrawArmorPart(info, character, HELMET);
        DrawBodyPart(info, character, TORSO);
        DrawArmorPart(info, character, BREASTPLATE);
    }
    else {
        DrawBodyPart(info, character, TORSO);
        DrawArmorPart(info, character, BREASTPLATE);
        DrawBodyPart(info, character, LEFT_ARM);
        DrawArmorPart(info, character, LEFT_SLEEVE);
        DrawBodyPart(info, character, RIGHT_ARM);
        DrawArmorPart(info, character, RIGHT_SLEEVE);
        DrawBodyPart(info, character, LEFT_HAND);
        DrawArmorPart(info, character, LEFT_GLOVE);
        DrawBodyPart(info, character, RIGHT_HAND);
        DrawArmorPart(info, character, RIGHT_GLOVE);
        DrawBodyPart(info, character, HEAD);
        DrawArmorPart(info, character, HELMET);
    }
}

void assemblePlayerTexture(struct playInfo *info, struct character *character) {
    RenderTexture2D render = LoadRenderTexture(info->width, info->height);
    RenderTexture2D render2 = LoadRenderTexture(info->width, info->height);

    BeginTextureMode(render);
        ClearBackground(BLANK);

        DrawCharacter(info, character);
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
