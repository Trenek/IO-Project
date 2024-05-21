#include <sys/stat.h>
#include <direct.h>

#include <time.h>

#include <raylib.h>

#include "state.h"

#include "menuElements.h"

#define INC_Y (10)
#define INC_X (10)
#define FONT_SIZE (25)

void createCharacter(const char *const saveName, const char *const characterName) {
    FILE *file = fopen(saveName, "w");
    int i = 0;

    fprintf(file, "%s\n", characterName);
    fprintf(file, "%f %f\n\n", 0.91666, 2.0);
   
    while (i < 10) {
        fprintf(file, "%i\n", 0);
        i += 1;
    }

    fprintf(file, "\n");

    i = 0;
    while (i < 10) {
        fprintf(file, "%i\n", 0);
        i += 1;
    }

    fprintf(file, "\n%i", 0);

    fclose(file);
}

void createEquipment(const char *const saveName) {
    FILE *file = fopen(saveName, "w");
    int i = 0;

    while (i < 25) {
        fprintf(file, "%i\n", 0);
        i += 1;
    }

    fclose(file);
}

void createDate(const char *const saveName) {
    FILE *file = fopen(saveName, "w");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    
    fprintf(file, "%i ", tm.tm_year + 1900);
    fprintf(file, "%i ", tm.tm_mon + 1);
    fprintf(file, "%i ", tm.tm_mday);
    fprintf(file, "%i ", tm.tm_hour);
    fprintf(file, "%i", tm.tm_min);

    fclose(file);
}

void copyMaps(const char *const saveName) {
    FilePathList list = LoadDirectoryFiles("dane\\mapy");
    FILE *from = NULL;
    FILE *to = NULL;
    unsigned int i = 0;
    int c = 0;

    while (i < list.capacity) {
        from = fopen(TextFormat("dane\\mapy\\%i.txt", i), "r");
        to = fopen(TextFormat("saves\\%s\\mapy\\%i.txt", saveName, i), "w");

        while ((c = fgetc(from)) != EOF) {
            fputc(c, to);
        }

        fclose(from);
        fclose(to);
        i += 1;
    }

    UnloadDirectoryFiles(list);
}

static bool createNewSave(const char *const saveName, const char *const characterName) {
    const char *saveDirectory = TextFormat("saves\\%s", saveName);
    struct stat st = { 0 };
    bool result = 1;

    if (stat(saveDirectory, &st) != 0) {
        result = 0;

        _mkdir(saveDirectory);

        createCharacter(TextFormat("saves\\%s\\posta\u0107.txt", saveName), characterName);
        createEquipment(TextFormat("saves\\%s\\ekwipunek.txt", saveName));
        createDate(TextFormat("saves\\%s\\date.txt", saveName));

        _mkdir(TextFormat("saves\\%s\\mapy", saveName));
        copyMaps(saveName);
    }

    return result;
}

void newGame(enum state *state, struct menuInfo *info) {
    const int height = GetScreenHeight() >> 1;
    const int spaceY = INC_Y + INC_Y + FONT_SIZE + 10;
    const int spaceX = 90;

    Color backgroundColor = { .r = 100, .g = 100, .b = 100, .a = 255 };
    Color buttonBackgroundColor = { .r = 78, .g = 215, .b = 50, .a = 255 };
    Color buttonBackgroundHoverColor = { .r = 78, .g = 215, .b = 50, .a = 105 };
    Color borderColor = { .r = 78, .g = 78, .b = 78, .a = 255 };
    Color inputColor = { .r = 78, .g = 78, .b = 78, .a = 255 };

    struct button title = {
        .text = "Nowa gra",
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = 100,
            .incX = INC_X,
            .incY = INC_Y,
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

    struct button gameSaveName = {
        .text = "Nazwa zapisu",
        .init = {
            .x = (GetScreenWidth() >> 3),
            .y = height - spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct button characterName = {
        .text = "Nazwa postaci",
        .init = {
            .x = (GetScreenWidth() >> 3),
            .y = height,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };
    struct button difficultyLevel = {
        .text = "Poziom trudności",
        .init = {
            .x = (GetScreenWidth() >> 3),
            .y = height + spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 0,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = BLANK,
        .hoverColor = BLANK,
        .spaceing = 0
    };

    struct button startGame = {
        .text = "Rozpocznij grę",
        .init = {
            .x = (GetScreenWidth() >> 1) - spaceX,
            .y = height + 4 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = buttonBackgroundColor,
        .hoverColor = buttonBackgroundHoverColor,
        .spaceing = 0
    };
    struct button goBack = {
        .text = "Powrót",
        .init = {
            .x = (GetScreenWidth() >> 1) + spaceX,
            .y = height + 4 * spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = buttonBackgroundColor,
        .hoverColor = buttonBackgroundHoverColor,
        .spaceing = 0
    };

    struct button errorButton = {
        .text = "Zapis o takiej nazwie już istnieje!",
        .init = {
            .x = GetScreenWidth() >> 1,
            .y = height + (int)(2.5 * spaceY),
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1
        },
        .font = &info->fonts[0],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = RED,
        .hoverColor = RED,
        .spaceing = 0
    };

    struct inputBox inputGameSaveName = {
        .text = "Wpisz Nazwę Zapisu",
        .currentLength = 0,
        .isActive = false,
        .init = {
            .x = (GetScreenWidth() >> 1) + (GetScreenWidth() >> 3),
            .y = height - spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1,
            .width = 300
        },
        .font = &info->fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = inputColor,
        .borderActiveColor = BLACK,
        .borderColor = borderColor,
        .spaceing = 0
    };
    struct inputBox inputCharacterName = {
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
        .font = &info->fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = inputColor,
        .borderActiveColor = BLACK,
        .borderColor = borderColor,
        .spaceing = 0
    };

    struct slideBox setDifficultyLevel = {
        .numberOfOptions = 3,
        .isActive = false,
        .currentOption = 0,
        .options = {
            "Easy",
            "Medium",
            "Hard"
        },
        .init = {
            .x = (GetScreenWidth() >> 1) + (GetScreenWidth() >> 3),
            .y = height + spaceY,
            .incX = INC_X,
            .incY = INC_Y,
            .posX = 1,
            .posY = 1,
            .width = 300
        },
        .font = &info->fonts[1],
        .fontSize = FONT_SIZE,
        .fontColor = BLACK,
        .color = inputColor,
        .borderActiveColor = RED,
        .borderColor = BLACK,
        .spaceing = 0
    };

    int error = 0;

    CalculateButtonPosition(&title);
    CalculateButtonPosition(&startGame);
    CalculateButtonPosition(&goBack);
    CalculateButtonPosition(&gameSaveName);
    CalculateButtonPosition(&characterName);
    CalculateButtonPosition(&difficultyLevel);
    CalculateButtonPosition(&errorButton);

    CalculateInputBoxPosition(&inputGameSaveName);
    CalculateInputBoxPosition(&inputCharacterName);
    CalculateSlideBoxPosition(&setDifficultyLevel);

    while (!WindowShouldClose() && *state == NEW_GAME) {
        BeginDrawing();
            ClearBackground(backgroundColor);

            DrawButton(gameSaveName);
            DrawButton(characterName);
            DrawButton(difficultyLevel);
            DrawButton(title);
            DrawButton(startGame);
            DrawButton(goBack);

            if (error) DrawButton(errorButton);

            DrawInputBox(&inputGameSaveName);
            DrawInputBox(&inputCharacterName);
            DrawSlideBox(&setDifficultyLevel);

            if (inputGameSaveName.currentLength < 1 || inputCharacterName.currentLength < 1) {
                DrawRectangleRec(startGame.boxRectangle, (Color) { 100, 100, 100, 100 });
            }
        EndDrawing();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if (isMouseOver(startGame)) {
                if (inputGameSaveName.currentLength > 0 && inputCharacterName.currentLength > 0) {
                    error = createNewSave(inputGameSaveName.text, inputCharacterName.text);
                    if (error == 0) {
                        *state = PLAY;
                        strcpy(info->saveName, inputGameSaveName.text);
                    }
                }
            }
            else if (isMouseOver(goBack)) *state = MENU;
        }

        UpdateInputBox(&inputGameSaveName);
        UpdateInputBox(&inputCharacterName);
        UpdateSlideBox(&setDifficultyLevel);
    }
}