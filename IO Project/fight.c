#include <raylib.h>
#include <raymath.h>

#include "playState.h"

#include "menuElements.h"

#include "renderer.h"
#include "player.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void fight(enum playState *state, struct playInfo *info) {
    const int height = (GetScreenHeight() >> 2) + (GetScreenHeight() >> 1);
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;

    Color color = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color color2 = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color color3 = { .r = 78, .g = 215, .b = 50, .a = 105 };

    struct button action = {
        .text = "Akcja",
        .isActive = 1,
        .init = {
            .x = - (GetScreenWidth() >> 3) + (GetScreenWidth() >> 1),
            .y = height + 0 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 2,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button items = {
        .text = "Przedmioty",
        .isActive = 1,
        .init = {
            .x = - (GetScreenWidth() >> 3) + (GetScreenWidth() >> 1),
            .y = height + 1 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 2,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button runAway = {
        .text = "Ucieknij",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 3) + (GetScreenWidth() >> 1),
            .y = height + 0 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };
    struct button giveUp = {
        .text = "Poddaj się",
        .isActive = 1,
        .init = {
            .x = (GetScreenWidth() >> 3) + (GetScreenWidth() >> 1),
            .y = height + 1 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = color2,
        .hoverColor = color3,
        .spaceing = 0
    };

    struct fighterLabel me = {
        .maxHealth = 100,
        .maxDurability = 100,
        .maxRest = 100,
        .barWidth = (GetScreenHeight() >> 6) + (GetScreenHeight() >> 7),
        .barGap = (GetScreenHeight() >> 7),
        .fighter = info->save.player.character,
        .init = {
            .x = 0,
            .y = 0,
            .posX = 0,
            .posY = 0,
            .height = GetScreenHeight() >> 3,
            .durability = &info->resources->armorDurability,
            .position = (Vector3){.x = 1, .y = 0, .z = 4 }
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = VIOLET,
        .spaceing = 0
    };

    struct fighterLabel enemy = {
        .maxHealth = 100,
        .maxDurability = 100,
        .maxRest = 100,
        .barWidth = (GetScreenHeight() >> 6) + (GetScreenHeight() >> 7),
        .barGap = (GetScreenHeight() >> 7),
        .fighter = info->chosen,
        .init = {
            .x = GetScreenWidth(),
            .y = 0,
            .posX = 2,
            .posY = 0,
            .height = GetScreenHeight() >> 3,
            .durability = &info->resources->armorDurability,
            .position = (Vector3){.x = 1, .y = 0, .z = -4 }
        },
        .font = &info->resources->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = VIOLET,
        .spaceing = 0
    };

    struct chooseAction saves = {
        .isActive = 0,
        .rowQuantity = 5,
        .wideness = 5,
        .attacks = &info->resources->attack,
        .attacksQuantity = info->resources->attackQuantity,
        .active = &me,
        .target = &enemy,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = GetScreenHeight() >> 1,
            .width = GetScreenWidth() >> 2,
            .incX = 15,
            .incY = 15,
            .posX = 0,
            .posY = 0
        },
        .font = &info->resources->fonts[0],
        .fontColor = BLACK,
        .fontSize = 20,
        .spaceing = 0,
        .color = GREEN,
        .activeBorderColor = RED,
        .inactiveBorderColor = BLACK,
        .hoverColor = PINK
    };

    ShowCursor();

    struct Object2D *render[] = {
        &me.fighter.object,
        &enemy.fighter.object
    };

    Camera3D fightCamera = {
        .position = {
            .x = 10,
            .y = 3,
            .z = 0
        },
        .up.y = 1,
        .fovy = 45
    };

    CalculateButtonPosition(&action);
    CalculateButtonPosition(&items);
    CalculateButtonPosition(&runAway);
    CalculateButtonPosition(&giveUp);

    initializeChooseAction(&saves);
    
    InitializeFighterLabel(&me, info->resources);
    InitializeFighterLabel(&enemy, info->resources);

    info->resumeState = FIGHT;
    while (!WindowShouldClose() && *state == FIGHT) {
        UpdateMusicStream(info->resources->music[0]);

        BeginDrawing();
            BeginTextureMode(*info->screenCamera);
                ClearBackground(color);

                BeginMode3D(fightCamera);
                    DrawGrid(100, 1);

                    RenderTextures(render, sizeof(render) / sizeof(struct Object2D *), fightCamera);
                EndMode3D();
            EndTextureMode();

            DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);


            DrawButton(action);
            DrawButton(items);
            DrawButton(runAway);
            DrawButton(giveUp);

            DrawChooseAction(&saves);

            DrawFighterLabel(&me);
            DrawFighterLabel(&enemy);
        EndDrawing();

        UpdateChooseAction(&saves);

        if (saves.isActive == 0) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                if (isMouseOver(giveUp)) *state = DEATH_SCREEN;
                else if (isMouseOver(runAway)) { 
                    if (rand() % 2) {
                        *state = DEATH_SCREEN;
                    }
                    else {
                        *state = DIALOG;
                        info->dialog = 4;
                    }
                }
                else if (isMouseOver(action)) saves.isActive = 1;
            }
            else if (IsKeyPressed(KEY_P)) {
                *state = PAUSE;
            }
        }
        UpdateFighterLabel(&me);
        UpdateFighterLabel(&enemy);

        if (me.health == 0) {
            *state = DEATH_SCREEN;
        }
        else if (enemy.health == 0) {
            *state = DIALOG;
        }
    }

    FreeFighterLabel(&me);
    FreeFighterLabel(&enemy);
    FreeChooseAction(&saves);
}