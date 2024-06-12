#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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

static void CreateAttacks(FILE *toWrite) {
    FILE *file = fopen("dane\\walka\\basic attackSet.txt", "r");
    int c = 0;

    fprintf(toWrite, "\n");
  
    while ((c = fgetc(file)) != EOF) {
        fputc(c, toWrite);
    }

    fclose(file);
}

static void CreateCharacter(const char *const saveName, const char *const characterName, const int bodyParts[10], const int difficultyLevel) {
    FILE *file = fopen(saveName, "w");
    int armorParts[10] = { 0 };
    int i = 0;

    memset(armorParts, -1, sizeof(int) * ((difficultyLevel * 10) / 2));
    
    fprintf(file, "%s\n", characterName);
    fprintf(file, "%f %f\n\n", 0.91666, 2.0);

    while (i < 10) {
        fprintf(file, "%i\n", bodyParts[i]);
        i += 1;
    }

    fprintf(file, "\n");

    i = 0;
    while (i < 9) {
        fprintf(file, "%i\n", armorParts[i]);
        i += 1;
    }

    fprintf(file, "\n%i", armorParts[9]);

    CreateAttacks(file);

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

static void CreatePlayer(const char *const saveName, const char *const characterName, const int bodyParts[10], const int difficultyLevel) {
    CreateCharacter(TextFormat("saves\\%s\\postaæ.txt", saveName), characterName, bodyParts, difficultyLevel);
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

// difficultyLevel - 0, 1, 2
int CreateNewSave(const char *const saveName, const char *const characterName, const int bodyParts[10], int difficultyLevel) {
    const char *saveDirectory = TextFormat("saves\\%s", saveName);
    struct stat st = { 0 };
    bool result = 1;

    if (stat("saves", &st) != 0) {
        _mkdir("saves");
    }

    if (stat(saveDirectory, &st) != 0) {
        result = 0;

        _mkdir(saveDirectory);

        _mkdir(TextFormat("saves\\%s\\mapy", saveName));
        _mkdir(TextFormat("saves\\%s\\sklepy", saveName));
        _mkdir(TextFormat("saves\\%s\\osi¹gniêcia", saveName));

        CreateDate(TextFormat("saves\\%s\\date.txt", saveName));

        CreatePlayer(saveName, characterName, bodyParts, difficultyLevel);
        CopyShops(saveName);
        CopyMaps(saveName);
        CreateAchievements(saveName);
    }

    return result;
}
