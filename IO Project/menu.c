#include <stdio.h>

#include <raylib.h>

#include "state.h"

#include "menuElement.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void menu(enum state *state) {
    const int height = GetScreenHeight() >> 1;
    const int space = INC_Y + INC_Y + FONT_SIZE + 10;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    Font title = LoadFontEx("resources/fonts/font2.ttf", 100, NULL, 512);
    Font element = LoadFontEx("resources/fonts/font2.ttf", 100, NULL, 512);

    GenTextureMipmaps(&title.texture);
    GenTextureMipmaps(&element.texture);
    SetTextureFilter(title.texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(element.texture, TEXTURE_FILTER_POINT);

    struct menuElement menuTitle = {
        .text = u8"Menu Startowe",
        .x = GetScreenWidth() >> 1,
        .y = 100,
        .incX = 0,
        .incY = 0,
        .font = &title,
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct menuElement newGame = {
        .text = u8"Nowa Gra",
        .x = GetScreenWidth() >> 1,
        .y = height,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &element,
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct menuElement loadGame = {
        .text = u8"Wczytaj Grê",
        .x = GetScreenWidth() >> 1,
        .y = height + space,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &element,
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct menuElement settings = {
        .text = u8"Ustawienia",
        .x = GetScreenWidth() >> 1,
        .y = height + 2 * space,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &element,
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct menuElement achivements = {
        .text = u8"Osi¹gniêcia",
        .x = GetScreenWidth() >> 1,
        .y = height + 3 * space,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &element,
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct menuElement exit = {
        .text = u8"WyjdŸ do Pulpitu",
        .x = GetScreenWidth() >> 1,
        .y = height + 4 * space,
        .incX = INC_X,
        .incY = INC_Y,
        .font = &element,
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    while (!WindowShouldClose() && *state == MENU) {
        BeginDrawing();
            ClearBackground(color);

            DrawMenuElement(menuTitle);
            DrawMenuElement(newGame);
            DrawMenuElement(loadGame);
            DrawMenuElement(settings);
            DrawMenuElement(achivements);
            DrawMenuElement(exit);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(newGame)) *state = NEW_GAME;
            else if (isMouseOver(loadGame)) *state = LOAD_GAME;
            else if (isMouseOver(settings)) *state = SETTINGS;
            else if (isMouseOver(achivements)) *state = ACHIVEMENTS;
            else if (isMouseOver(exit)) *state = EXIT;
        }
    }

    UnloadFont(title);
    UnloadFont(element);
}