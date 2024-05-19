#include <string.h>
#include <stdio.h>

#include "choiceBox.h"

void CalculateChoiceBoxPosition(struct choiceBox* element) {
    struct choiceBoxPositionParameters init = element->init;

    FilePathList pathList = LoadDirectoryFiles("../IO Project/saves");       // Load directory filepaths
    int j = -1;
    for (int i = 0; i < 1; i++) {
        if (pathList.paths[i] == NULL) {
            break;
        }

        char* saveName = strtok(pathList.paths[i], "/");
        saveName = strtok(NULL, "/");
        saveName = strtok(NULL, "\\");
        saveName = strtok(NULL, "\\");
        for (int k = 0; saveName[k] != 'm'; k++) {
            ++j;
            //printf("a");

            printf(" %c", saveName[k]);

            //element->saveNames[j] = saveName[k];
            //if (saveName[k + 1] == '\b') {
            //    ++j;
            //    element->saveNames[j] = '\b';
            //}
        }
    }

    element->LeftCorner = (Vector2){
         .x = init.x - 322.5f,
         .y = init.y  + 70.0f
    };

    for (int i = 0; i < 6; i++) {
        element->rowRectangle[MAIN][i] = (Rectangle){
            .x = element->LeftCorner.x,
            .y = element->LeftCorner.y + 50.0f * i,
            .width = 650.0f,
            .height = 50.0f
        };

        element->rowRectangle[NUM][i] = (Rectangle){
            .x = element->LeftCorner.x + 5,
            .y = element->LeftCorner.y + 50.0f * i + 5,
            .width = 40.0f,
            .height = 40.0f
        };

        element->rowRectangle[NAME][i] = (Rectangle){
            .x = element->LeftCorner.x + 50,
            .y = element->LeftCorner.y + 50.0f * i + 5,
            .width = 450.0f,
            .height = 40.0f
           
        };

        element->rowRectangle[DATE][i] = (Rectangle){
            .x = element->LeftCorner.x + 505,
            .y = element->LeftCorner.y + 50.0f * i + 5,
            .width = 140,
            .height = 40
        };
    }

}

void DrawChoiceBox(struct choiceBox element) {
    int i = 0;
    int j = 0;

    while (i < 6) {
        DrawRectangleRec(element.rowRectangle[MAIN][i], CheckCollisionPointRec(GetMousePosition(), element.rowRectangle[MAIN][i]) ? element.hoverColor : element.color);
        DrawRectangleLinesEx(element.rowRectangle[MAIN][i], 1, element.isActive ? element.borderActiveColor : element.borderColor);
        DrawTextEx(*(element.font), element.text, element.LeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);

        j = 1;
        while (j < 4) {
            DrawRectangleRec(element.rowRectangle[j][i], element.color);
            DrawRectangleLinesEx(element.rowRectangle[j][i], 1, element.isActive ? element.borderActiveColor : element.borderColor);
            DrawTextEx(*(element.font), element.text, element.LeftCorner, (float)element.fontSize, (float)element.spaceing, element.fontColor);
            j += 1;
        }

        i += 1;
    };
}


