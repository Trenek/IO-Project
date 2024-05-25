#include <stdio.h>
#include <stdbool.h>

#include <sys/stat.h>
#include <direct.h>

#include <time.h>

#include <raylib.h>

static void createDate(const char *const saveName) {
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

static void createCharacter(const char *const saveName, const char *const characterName, const int bodyParts[10], const int armorParts[9]) {
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
        fprintf(file, "%i\n", armorParts[i]);
        i += 1;
    }

    fprintf(file, "\n%i", 0);

    fclose(file);
}

static void createEquipment(const char *const saveName) {
    FILE *file = fopen(saveName, "w");
    int i = 0;

    while (i < 25) {
        fprintf(file, "%i\n", 0);
        i += 1;
    }

    fclose(file);
}

static void copyMaps(const char *const saveName) {
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

bool createNewSave(const char *const saveName, const char *const characterName, const int bodyParts[10], const int armorParts[9]) {
    const char *saveDirectory = TextFormat("saves\\%s", saveName);
    struct stat st = { 0 };
    bool result = 1;

    if (stat(saveDirectory, &st) != 0) {
        result = 0;

        _mkdir(saveDirectory);

        createCharacter(TextFormat("saves\\%s\\posta\u0107.txt", saveName), characterName, bodyParts, armorParts);
        createEquipment(TextFormat("saves\\%s\\ekwipunek.txt", saveName));
        createDate(TextFormat("saves\\%s\\date.txt", saveName));

        _mkdir(TextFormat("saves\\%s\\mapy", saveName));
        copyMaps(saveName);
    }

    return result;
}
