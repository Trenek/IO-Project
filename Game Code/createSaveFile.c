#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#include <sys/stat.h>
#include <direct.h>

#include <time.h>

#include <raylib.h>

static void CreateDate(const char *const saveName) {
    FILE *file = fopen(saveName, "w");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    fprintf(file, "%i ", tm.tm_year + 1900);
    fprintf(file, "%i ", tm.tm_mon + 1);
    fprintf(file, "%i ", tm.tm_mday);
    fprintf(file, "%i ", tm.tm_hour);
    fprintf(file, "%i ", tm.tm_min);
    fprintf(file, "%i", tm.tm_sec);

    fclose(file);
}

static void CreateCharacter(const char *const saveName, const char *const characterName, const int bodyParts[10]) {
    FILE *file = fopen(saveName, "w");
    int i = 0;

    fprintf(file, "%s\n", characterName);
    fprintf(file, "%f %f\n\n", 0.91666, 2.0);

    while (i < 10) {
        fprintf(file, "%i\n", bodyParts[i]);
        i += 1;
    }

    fprintf(file, "\n");

    i = 0;
    while (i < 9) {
        fprintf(file, "%i\n", 0);
        i += 1;
    }

    fprintf(file, "\n%i", 0);

    fclose(file);
}

static void CreateEquipment(const char *const saveName) {
    FILE *file = fopen(saveName, "w");
    int i = 0;

    while (i < 25) {
        fprintf(file, "%i\n", 0);
        i += 1;
    }

    fclose(file);
}

static void RecreateFile(FILE *from, FILE *to) {
    int c = 0;

    while ((c = fgetc(from)) != EOF) {
        fputc(c, to);
    }

    fclose(from);
    fclose(to);
}

static void CreatePosition(const char *const saveName) {
    RecreateFile(fopen("dane\\mapy\\position.txt", "r"), fopen(TextFormat("saves\\%s\\mapy\\position.txt", saveName), "w"));
}

static void CreatePlayer(const char *const saveName, const char *const characterName, const int bodyParts[10]) {
    CreateCharacter(TextFormat("saves\\%s\\postaæ.txt", saveName), characterName, bodyParts);
    CreateEquipment(TextFormat("saves\\%s\\ekwipunek.txt", saveName));
    CreatePosition(saveName);
}

static void CopyShops(const char *const saveName) {
    FilePathList list = LoadDirectoryFiles("dane\\sklepy");
    unsigned int i = 0;

    while (i < list.capacity) {
        RecreateFile(fopen(TextFormat("dane\\sklepy\\%i.txt", i), "r"), fopen(TextFormat("saves\\%s\\sklepy\\%i.txt", saveName, i), "w"));

        i += 1;
    }

    UnloadDirectoryFiles(list);
}

static void CopyMaps(const char *const saveName) {
    FilePathList list = LoadDirectoryFiles("dane\\mapy");
    unsigned int i = 0;

    while (i < list.capacity - 1) {
        RecreateFile(fopen(TextFormat("dane\\mapy\\%i.txt", i), "r"), fopen(TextFormat("saves\\%s\\mapy\\%i.txt", saveName, i), "w"));

        i += 1;
    }

    UnloadDirectoryFiles(list);
}

static void CreateAchievements(const char *const saveName) {
    FILE *file = fopen(TextFormat("saves\\%s\\osi¹gniêcia\\0.txt", saveName), "w");

    fprintf(file, "Osi¹gniêcie pierwsze\n");
    fprintf(file, "Osi¹gniêcie pierwsze - opis\n");
    fprintf(file, "%i\n", 2);
    fprintf(file, "Pierwsze wymaganie\n");
    fprintf(file, "Drugie wymaganie\n");
    fprintf(file, "%i", 0);

    fclose(file);

    file = fopen(TextFormat("saves\\%s\\osi¹gniêcia\\1.txt", saveName), "w");

    fprintf(file, "Osi¹gniêcie drugie\n");
    fprintf(file, "Osi¹gniêcie drugie - opis\n");
    fprintf(file, "%i\n", 2);
    fprintf(file, "Pierwsze wymaganie 2\n");
    fprintf(file, "Drugie wymaganie 2\n");
    fprintf(file, "%i", 0);

    fclose(file);
}

static bool isValidSaveName(const char* saveName) {
    while (*saveName) {
        if (!isalnum((unsigned char)*saveName) && *saveName != ' ') {
            return false;
        }
        saveName++;
    }
    return true;
}

int CreateNewSave(const char *const saveName, const char *const characterName, const int bodyParts[10]) {
    const char *saveDirectory = TextFormat("saves\\%s", saveName);
    struct stat st = { 0 };

    if (stat(saveDirectory, &st) == 0)
        return 1;
    
    if (!isValidSaveName(saveName)) 
        return 2;

    _mkdir(saveDirectory);

    _mkdir(TextFormat("saves\\%s\\mapy", saveName));
    _mkdir(TextFormat("saves\\%s\\sklepy", saveName));
    _mkdir(TextFormat("saves\\%s\\osi¹gniêcia", saveName));

    CreateDate(TextFormat("saves\\%s\\date.txt", saveName));

    CreatePlayer(saveName, characterName, bodyParts);
    CopyShops(saveName);
    CopyMaps(saveName);
    CreateAchievements(saveName);

    return 0;
}
