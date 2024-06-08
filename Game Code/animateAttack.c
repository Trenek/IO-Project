#include <raylib.h>

#include "playState.h"

#include "fighterLabel.h"
#include "animateAttack.h"
#include "button.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void animateAttack(struct playInfo *info, struct animateAttack *attack) {
    float time = 1.0f;

    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };

    struct button attacker = {
        .text = attack->attacker->fighter.name,
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = (GetScreenHeight() >> 1) - FONT_SIZE * 2,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color2,
        .spaceing = 0
    };
    struct button button = {
        .text = info->resources->attack[attack->attacker->fighter.attacks[attack->attackID]].name,
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = GetScreenHeight() >> 1,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color2,
        .spaceing = 0
    };

    CalculateButtonPosition(&attacker);
    CalculateButtonPosition(&button);

    while (time > 0) {
        UpdateMusicStream(info->resources->music[0]);

        BeginDrawing();
        DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
        DrawButton(button);
        DrawButton(attacker);
        EndDrawing();

        time -= GetFrameTime();
    }

    attack->attacked->durability -= info->resources->attack[attack->attacker->fighter.attacks[attack->attackID]].force;

    if (attack->attacked->durability < 0) {
        attack->attacked->health += attack->attacked->durability;
        attack->attacked->durability = 0;
    }

    if (attack->attacked->health < 0) {
        attack->attacked->health = 0;
    }

    attack->attacker->rest -= info->resources->attack[attack->attacker->fighter.attacks[attack->attackID]].cost;

    attack->isAttacked = 0;
}