#include <raylib.h>

#include "playState.h"

#include "menuElements.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void achievements(enum playState* state, struct playInfo* info) {
    int currentAchievementIndex = 0;
    const int height = (GetScreenHeight() >> 1) + 80;
    const int space = FONT_SIZE + INC_Y * 2 + 10;

    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };
    Color color2 = { .r = 0, .g = 0, .b = 0, .a = 60 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button title = {
        .text = "Osiągnięcia",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = GetScreenHeight() >> 3,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct button goBack = {
        .text = "Powrót",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = height + 3 * space,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = color2,
        .spaceing = 0
    };

    struct button turnLeft = {
        .text = "<",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 2,
            .y = GetScreenHeight() >> 1,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = 40,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    struct button turnRight = {
        .text = ">",
        .isActive = 1,
        .init = {
            .x = 3 * (GetScreenWidth() >> 2),
            .y = GetScreenHeight() >> 1,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = 40,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    struct achievementElem achievement = {
        .font = &info->resources->fonts[0],
        .space = space >> 1,
        .x = GetScreenWidth() >> 1,
        .y = (GetScreenHeight() >> 2) + space,
    };

    UpdateAchievementElem(&achievement, info->save.achievements[currentAchievementIndex]);

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&goBack);
    CalculateButtonPosition(&turnLeft);
    CalculateButtonPosition(&turnRight);

    while (!WindowShouldClose() && *state == ACHIEVEMENTS) {
        BeginDrawing();
        ClearBackground(color1);
        if (info->screenCamera != NULL) {
            DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
        }
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);
        DrawRectangle(GetScreenWidth() >> 2, GetScreenHeight() >> 2, GetScreenWidth() >> 1, GetScreenHeight() >> 1, GRAY);
        
        DrawAchievementElem(achievement);

        DrawButton(title);
        DrawButton(goBack);
        DrawButton(turnLeft);
        DrawButton(turnRight);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(goBack)) *state = PAUSE;
            else if (isMouseOver(turnLeft)) {
                if (currentAchievementIndex == 0) {
                    currentAchievementIndex = info->save.achievementsQuantity - 1;
                }
                else {
                    currentAchievementIndex -= 1;
                }
                free(achievement.requirements);
                UpdateAchievementElem(&achievement, info->save.achievements[currentAchievementIndex]);
            }
            else if (isMouseOver(turnRight)) {
                if (currentAchievementIndex == info->save.achievementsQuantity - 1) {
                    currentAchievementIndex = 0;
                }
                else {
                    currentAchievementIndex += 1;
                }
                free(achievement.requirements);
                UpdateAchievementElem(&achievement, info->save.achievements[currentAchievementIndex]);
            }
        }
    }
    free(achievement.requirements);
}