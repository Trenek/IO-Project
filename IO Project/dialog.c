#include <raylib.h>
#include <raymath.h>

#include <stdio.h>
#include <stdlib.h>

#include "playState.h"

#include "menuElements.h"

#include "renderer.h"
#include "player.h"

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

void fscanfUnlimited(FILE *file, char **buffor, char terminate) {
    char c = 0;
    int size = 128;
    int currentSize = 0;

    *buffor = malloc(sizeof(char) * size);
    while ((c = (char)fgetc(file)) != terminate) {
        (*buffor)[currentSize] = c;
        currentSize += 1;
        if (currentSize == size) {
            size *= 2;
            realloc(*buffor, size);
        }
    }
    (*buffor)[currentSize] = '\0';
}

static void loadFile(const char* fileName, struct DialogData *data, struct button **options, struct playInfo *info, RenderTexture *screenCamera) {
    FILE *file = fopen(TextFormat("%s\\%i.txt", fileName, data->statementID), "r");
    int i = 0;

    fscanf(file, "%i %i ", &data->id, &data->numberOfPossibleResponses);
    fscanfUnlimited(file, &data->statement, '\n');
    
    data->responses = malloc(sizeof(struct a) * data->numberOfPossibleResponses);
    *options = malloc(sizeof(struct button) * data->numberOfPossibleResponses);
    while (i < data->numberOfPossibleResponses) {
        fscanf(file, "%i ", &data->responses[i].consequence);
        if (data->responses[i].consequence == 0) {
            fscanf(file, "%i ", &data->responses[i].state);
        }
        fscanf(file, "%i ", &data->responses[i].next);

        fscanfUnlimited(file, &data->responses[i].statement, '\n');
        (*options)[i] = (struct button) {
            .text = data->responses[i].statement,
            .init = {
                .x = (int)(screenCamera->texture.width / 5.0f + i * 0.8f * screenCamera->texture.width / (data->numberOfPossibleResponses)),
                .y = (GetScreenHeight() - (GetScreenHeight() >> 2)) + screenCamera->texture.height - 40,
                .incX = 10,
                .incY = 10,
                .posX = 0,
                .posY = 1
            },
            .font = &info->fonts[0],
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

static void unloadFile(struct DialogData *data) {
    int i = 0;

    free(data->statement);

    while (i < data->numberOfPossibleResponses) {
        free(data->responses[i].statement);

        i += 1;
    }

    free(data->responses);
}

void dialog(enum playState *playState, struct playInfo *info) {
    RenderTexture screenCamera = LoadRenderTexture(GetScreenWidth(), GetScreenHeight() >> 2);
    Rectangle screenRect = (Rectangle){ 0.0f, 0.0f, (float)screenCamera.texture.width, (float)-screenCamera.texture.height };

    Color color1 = { .r = 100, .g = 100, .b = 100, .a = 50 };

    struct button title = {
        .text = "Dialog",
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 50,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = 100,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct button *options;

    struct DialogData data = {
        .statementID = 0
    };

    int i = 0;

    EnableCursor();
    CalculateButtonPosition(&title);

    loadFile(TextFormat("dane\\dialogi\\%i", info->dialog), &data, &options, info, &screenCamera);

    while (*playState == DIALOG && !WindowShouldClose()) {
        BeginTextureMode(screenCamera);
            ClearBackground(VIOLET);

            DrawTextureEx(*info->chosen.object.texture, (Vector2) { 0.0f, 0.0f }, 0.0f, 2.5f * (float)screenCamera.texture.height / info->chosen.object.texture->height, WHITE);
            DrawTextEx(info->fonts[0], info->chosen.name, (Vector2) { screenCamera.texture.width / 5.0f, 0.0f}, 40.0f, 0.0f, BLACK);
            DrawTextEx(info->fonts[0], data.statement, (Vector2) { screenCamera.texture.width / 5.0f, 40.0f }, 30.0f, 0.0f, BLACK);
        EndTextureMode();

        BeginDrawing();
            ClearBackground(color1);
            if (info->screenCamera != NULL) {
                DrawTextureRec(info->screenCamera->texture, *info->screenRect, (Vector2) { 0, 0 }, WHITE);
            }
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight() + 100, color1);
            DrawTextureRec(screenCamera.texture, screenRect, (Vector2) { 0, (float)((GetScreenHeight() >> 1) + (GetScreenHeight() >> 2))}, WHITE);

            i = 0;
            while (i < data.numberOfPossibleResponses) {
                DrawButton(options[i]);

                i += 1;
            }

            DrawButton(title);
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            i = 0;
            while (i < data.numberOfPossibleResponses) {
                if (isMouseOver(options[i])) {
                    if (data.responses[i].consequence == 0) {
                        *playState = data.responses[i].state;
                        info->dialog = data.responses[i].next;
                    }
                    else {
                        data.statementID = data.responses[i].next;

                        unloadFile(&data);
                        loadFile(TextFormat("dane\\dialogi\\%i", info->dialog), &data, &options, info, &screenCamera);
                    }
                }

                i += 1;
            }
        }
    }

    unloadFile(&data);
    UnloadRenderTexture(screenCamera);
}