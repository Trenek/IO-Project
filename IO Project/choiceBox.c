#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "choiceBox.h"

void CalculateChoiceBoxPosition(struct choiceBox* element) {
    struct choiceBoxPositionParameters init = element->init;

    element->clicked = 7;

    element->LeftCorner[MAIN] = (Vector2){
         .x = init.x - 322.5f,
         .y = init.y  + 70.0f
    };

    element->LeftCorner[NUM] = (Vector2){
         .x = init.x - 322.5f,
         .y = init.y + 70.0f
    };

    element->LeftCorner[NAME] = (Vector2){
         .x = init.x - 265.0f,
         .y = init.y + 70.0f
    };

    element->LeftCorner[DATE] = (Vector2){
         .x = init.x - 322.5f,
         .y = init.y + 70.0f
    };

    for (int i = 0; i < 6; i++) {
        element->rowRectangle[MAIN][i] = (Rectangle){
            .x = element->LeftCorner[MAIN].x,
            .y = element->LeftCorner[MAIN].y + 50.0f * i,
            .width = 650.0f,
            .height = 50.0f
        };

        element->rowRectangle[NUM][i] = (Rectangle){
            .x = element->LeftCorner[MAIN].x + 5,
            .y = element->LeftCorner[MAIN].y + 50.0f * i + 5,
            .width = 40.0f,
            .height = 40.0f
        };

        element->rowRectangle[NAME][i] = (Rectangle){
            .x = element->LeftCorner[MAIN].x + 50,
            .y = element->LeftCorner[MAIN].y + 50.0f * i + 5,
            .width = 450.0f,
            .height = 40.0f
           
        };

        element->rowRectangle[DATE][i] = (Rectangle){
            .x = element->LeftCorner[MAIN].x + 505,
            .y = element->LeftCorner[MAIN].y + 50.0f * i + 5,
            .width = 140,
            .height = 40
        };
    }

}

void DrawChoiceBox(struct choiceBox element, unsigned int *clicked) {
    FilePathList pathList = LoadDirectoryFiles("../IO Project/saves");       // Load directory filepaths
    for (unsigned int i = 0; i < pathList.count; i++) {
        if (pathList.paths[i] == NULL) {
            break;
        }
        element.saveNames[i] = strstr(pathList.paths[i], "\\") + 1;
    }

    unsigned int i = 0;
    int j = 0;

    while (i < 6) {
        if ((CheckCollisionPointRec(GetMousePosition(), element.rowRectangle[MAIN][i]) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) || *clicked == i) {
            DrawRectangleRec(element.rowRectangle[MAIN][i], RED);
            *clicked = i;
        }
        else DrawRectangleRec(element.rowRectangle[MAIN][i], CheckCollisionPointRec(GetMousePosition(), element.rowRectangle[MAIN][i]) ? element.hoverColor : element.color);

        DrawRectangleLinesEx(element.rowRectangle[MAIN][i], 1, element.isActive ? element.borderActiveColor : element.borderColor);


        j = 1;
        while (j < 4) {
            DrawRectangleRec(element.rowRectangle[j][i], element.color);
            DrawRectangleLinesEx(element.rowRectangle[j][i], 1, element.isActive ? element.borderActiveColor : element.borderColor);
            j += 1;
        }
        if (i < pathList.count) {
            DrawTextEx(*(element.font), element.saveNames[i], element.LeftCorner[NAME], (float)element.fontSize, (float)element.spaceing, element.fontColor);
            DrawTextEx(*element.font, TextFormat("%i.", i + 1), (Vector2) { .x = element.rowRectangle[NUM][i].x + 5, .y = element.rowRectangle[NUM][i].y }, (float)element.fontSize, (float)element.spaceing, BLACK);
        }

        else DrawTextEx(*(element.font), element.text, element.LeftCorner[NAME], (float)element.fontSize, (float)element.spaceing, element.fontColor);
        element.LeftCorner[NAME].y += 50;


        i += 1;
    };
    UnloadDirectoryFiles(pathList);

}


