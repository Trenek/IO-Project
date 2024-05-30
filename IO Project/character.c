#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>
#include <rlgl.h>

#include "playState.h"
#include "state.h"

static void DrawBodyPart(struct Resources *info, struct character *character, int i) {
    DrawTexture(
        info->bodyParts[i][character->bodyPart[i]][character->direction],
        info->bodyPosition[character->direction][i][0],
        info->bodyPosition[character->direction][i][1],
        WHITE);
}

static void DrawArmorPart(struct Resources *info, struct character *character, int i) {
    if (character->armorPart[i] != -1)
    DrawTexture(
        info->armorPart[i][character->armorPart[i]][character->direction],
        info->armorPosition[character->direction][i][0],
        info->armorPosition[character->direction][i][1],
        WHITE);
}

static void DrawCharacter(struct Resources *info, struct character *character) {
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

void assemblePlayerTexture(struct Resources *info, struct character *character) {
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