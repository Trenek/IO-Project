#include <raylib.h>

#include "playState.h"

#include "menuElements.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void deathScreen(enum playState *state, struct playInfo *info) {
    const int height = GetScreenHeight() >> 1;
    const int space = INC_Y + INC_Y + FONT_SIZE + 10;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button title = {
        .text = "Umarłeś",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 100,
            .incX = 0,
            .incY = 0,
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
    struct button tryAgain = {
        .text = "Spróbuj ponownie",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = height - space,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button reloadLastSave = {
        .text = "Wczytaj ostatni zapis gry",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = height,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button exitToMenu = {
        .text = "Wyjdź do Menu",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = height + space,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button exit = {
        .text = "Wyjdź do Pulpitu",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = height + 4 * space,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&tryAgain);
    CalculateButtonPosition(&reloadLastSave);
    CalculateButtonPosition(&exitToMenu);
    CalculateButtonPosition(&exit);

    while (!WindowShouldClose() && *state == DEATH_SCREEN) {
        BeginDrawing();
            ClearBackground(color);

            DrawButton(title);
            DrawButton(tryAgain);
            DrawButton(reloadLastSave);
            DrawButton(exitToMenu);
            DrawButton(exit);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(tryAgain)) *state = FIGHT;
            if (isMouseOver(reloadLastSave)) *state = RELOAD_SAVE;
            else if (isMouseOver(exitToMenu)) *state = RETURN;
            else if (isMouseOver(exit)) *state = DESKTOP;
        }
    }

    if (*state != FIGHT && info->shouldDestroy == 1) {
        unloadCharacter(&info->chosen);
        info->shouldDestroy = 0;
    }
}