#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <raylib.h>

#include "saveData.h"

#define bitFscanf(a, b, c) (void)fscanf(a, b, &temp); c = temp

static void loadDate(struct saveData *const this, const char *const path) {
    FILE *saveFile = fopen(TextFormat("%s\\date.txt", path), "r");
    unsigned short temp = 0;

    bitFscanf(saveFile, "%hu", this->year);
    bitFscanf(saveFile, "%hu", this->month);
    bitFscanf(saveFile, "%hu", this->day);
    bitFscanf(saveFile, "%hu", this->hour);
    bitFscanf(saveFile, "%hu", this->minute);
    bitFscanf(saveFile, "%hu", this->second);

    fclose(saveFile);
}

static void extractSaveName(struct saveData *const this, const char *const savePath) {
    const char *saveName = strstr(savePath, "\\") + 1;

    this->text = malloc(sizeof(char) * (strlen(saveName) + 1));

    strcpy(this->text, saveName);
}

void initializeSaveData(struct saveData *const this, const char *const savePath) {
    extractSaveName(this, savePath);
    loadDate(this, savePath);
}

void freeSaveData(struct saveData *const this) {
    free(this->text);
}

int cmpSaveData(const struct saveData *const arg1, const struct saveData *const arg2) {
    int result = 0;

    if (result == 0 && arg1->year != arg2->year) {
        result = arg2->year - arg1->year;
    }

    if (result == 0 && arg1->month != arg2->month) {
        result = arg2->month - arg1->month;
    }

    if (result == 0 && arg1->day != arg2->day) {
        result = arg2->day - arg1->day;
    }

    if (result == 0 && arg1->hour != arg2->hour) {
        result = arg2->hour - arg1->hour;
    }

    if (result == 0 && arg1->minute != arg2->minute) {
        result = arg2->minute - arg1->minute;
    }

    if (result == 0 && arg1->second != arg2->second) {
        result = arg2->second - arg1->second;
    }

    return result;
}