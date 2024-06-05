#include <sys/stat.h>
#include <direct.h>

#include <raylib.h>

#include "playState.h"

#include "menuElements.h"

#include "savefile.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void save(enum playState *state, struct playInfo *info) {
    const int height = (GetScreenHeight() >> 1) + 80;
    const int space = FONT_SIZE + INC_Y * 2 + 10;

    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 200 };
    Color color2 = { .r = 0, .g = 0, .b = 0, .a = 60 };

    struct button title = {
        .text = "Zapisz Rozgrywkę",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = GetScreenHeight() >> 2,
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

    struct button saveNameInfo = {
        .text = "Nazwa Zapisu",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 3),
            .y = height,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color2,
        .spaceing = 0
    };

    struct button overwrite = {
        .text = "Nadpisz",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = height + 2 * space,
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
    struct button create = {
        .text = "Stwórz",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = height + 2 * space,
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

    struct inputBox saveName = {
        .text = "Wpisz Nazwę Postaci",
        .currentLength = 0,
        .isActive = false,
        .init = {
            .x = (GetScreenWidth() >> 1) + (GetScreenWidth() >> 3),
            .y = height,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1,
            .width = 300
        },
        .font = &info->resources->fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .borderActiveColor = BLACK,
        .borderColor = BLACK,
        .spaceing = 0
    };

    struct button resume = {
        .text = u8"Wróć",
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

    struct stat st = { 0 };

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&saveNameInfo);
    CalculateButtonPosition(&overwrite);
    CalculateButtonPosition(&create);
    CalculateButtonPosition(&resume);

    CalculateInputBoxPosition(&saveName);
    strcpy(saveName.text, info->save.saveName);

    while (*state == SAVE && !WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(color1);
            if (info->screenCamera != NULL) {
                DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
            }
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);

            DrawButton(title);
            DrawButton(saveNameInfo);
            DrawButton((stat(TextFormat("saves\\%s", saveName.text), &st) != 0) ? create : overwrite);
            DrawButton(resume);

            DrawInputBox(&saveName);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(resume)) *state = EXPLORE;
            else {
                if (stat(TextFormat("saves\\%s", saveName.text), &st) == 0) {
                    if (isMouseOver(overwrite)) {
                        strcpy(info->save.saveName, saveName.text);
                        SaveSaveFile(&info->save);
                    }
                }
                else {
                    if (isMouseOver(create)) {
                        strcpy(info->save.saveName, saveName.text);
                        SaveSaveFile(&info->save);
                    }
                }
            }
        }

        UpdateInputBox(&saveName);
    }
}