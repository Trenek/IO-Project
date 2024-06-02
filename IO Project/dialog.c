#include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>

#include "playState.h"

#include "menuElements.h"

#include "renderer.h"
#include "player.h"

#include "fscanfWithAllocation.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

struct DialogData {
    int id;
    char *statement;
    int numberOfPossibleResponses;
    struct a {
        char *statement;
        int consequence;
        int state;
        int next;
    } *responses;
    int statementID;
};

static void loadFile(const char* fileName, struct DialogData *saveData, struct button **options, struct playInfo *info, RenderTexture *screenCamera) {
    FILE *file = fopen(TextFormat("%s\\%i.txt", fileName, saveData->statementID), "r");
    int i = 0;

    fscanf(file, "%i %i ", &saveData->id, &saveData->numberOfPossibleResponses);
    fscanfUnlimited(file, &saveData->statement, '\n');
    
    saveData->responses = malloc(sizeof(struct a) * saveData->numberOfPossibleResponses);
    *options = malloc(sizeof(struct button) * saveData->numberOfPossibleResponses);
    while (i < saveData->numberOfPossibleResponses) {
        fscanf(file, "%i ", &saveData->responses[i].consequence);
        if (saveData->responses[i].consequence == 0) {
            fscanf(file, "%i ", &saveData->responses[i].state);
        }
        fscanf(file, "%i ", &saveData->responses[i].next);

        fscanfUnlimited(file, &saveData->responses[i].statement, '\n');
        (*options)[i] = (struct button) {
            .text = saveData->responses[i].statement,
            .isActive = 1,
            .init = {
                .x = (int)(screenCamera->texture.width / 5.0f + i * 0.8f * screenCamera->texture.width / (saveData->numberOfPossibleResponses)),
                .y = (GetScreenHeight() - (GetScreenHeight() >> 2)) + screenCamera->texture.height - 40,
                .incX = 10,
                .incY = 10,
                .posX = 0,
                .posY = 1
            },
            .font = &info->resources->fonts[0],
            .fontSize = 30,
            .fontColor = BLACK,
            .color = RED,
            .hoverColor = GREEN,
            .spaceing = 0
        };
        CalculateButtonPosition(&(*options)[i]);

        i += 1;
    }


    fclose(file);
}

static void unloadFile(struct DialogData *saveData) {
    int i = 0;

    free(saveData->statement);

    while (i < saveData->numberOfPossibleResponses) {
        free(saveData->responses[i].statement);

        i += 1;
    }

    free(saveData->responses);
}

void dialog(enum playState *state, struct playInfo *info) {
    RenderTexture screenCamera = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() >> 2);
    Rectangle screenRect = (Rectangle){ 0.0f, 0.0f, (float)screenCamera.texture.width, (float)-screenCamera.texture.height };

    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 50 };

    struct button title = {
        .text = "Dialog",
        .isActive = 1,
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 50,
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
    struct button *options;

    struct DialogData saveData = {
        .statementID = 0
    };

    int i = 0;

    EnableCursor();
    CalculateButtonPosition(&title);

    loadFile(TextFormat("dane\\dialogi\\%i", info->dialog), &saveData, &options, info, &screenCamera);

    while (*state == DIALOG && !WindowShouldClose()) {
        BeginTextureMode(screenCamera);
            ClearBackground(VIOLET);

            DrawTextureEx(*info->chosen.object.texture, (Vector2) { 0.0f, 0.0f }, 0.0f, 2.5f * (float)screenCamera.texture.height / info->chosen.object.texture->height, WHITE);
            DrawTextEx(info->resources->fonts[0], info->chosen.name, (Vector2) { screenCamera.texture.width / 5.0f, 0.0f}, 40.0f, 0.0f, BLACK);
            DrawTextEx(info->resources->fonts[0], saveData.statement, (Vector2) { screenCamera.texture.width / 5.0f, 40.0f }, 30.0f, 0.0f, BLACK);
        EndTextureMode();

        BeginDrawing();
            ClearBackground(color1);
            if (info->screenCamera != NULL) {
                DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
            }
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);
            DrawTextureRec(screenCamera.texture, screenRect, (Vector2) { 0, (float)((GetScreenHeight() >> 1) + (GetScreenHeight() >> 2))}, WHITE);

            i = 0;
            while (i < saveData.numberOfPossibleResponses) {
                DrawButton(options[i]);

                i += 1;
            }

            DrawButton(title);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            i = 0;
            while (i < saveData.numberOfPossibleResponses) {
                if (isMouseOver(options[i])) {
                    if (saveData.responses[i].consequence == 0) {
                        *state = saveData.responses[i].state;
                        info->dialog = saveData.responses[i].next;
                    }
                    else {
                        saveData.statementID = saveData.responses[i].next;

                        unloadFile(&saveData);
                        loadFile(TextFormat("dane\\dialogi\\%i", info->dialog), &saveData, &options, info, &screenCamera);
                    }
                }

                i += 1;
            }
        }
    }

    unloadFile(&saveData);
    UnloadRenderTexture(screenCamera);
}