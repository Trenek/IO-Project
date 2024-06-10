#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <raylib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <direct.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "state.h"

static void CreateDate(const char* const saveName) {
    FILE* file = fopen(saveName, "w");
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

static void CreateCharacter(const char* const saveName, const char* const characterName, const int bodyParts[10]) {
    FILE* file = fopen(saveName, "w");
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

static void CreateEquipment(const char* const saveName) {
    FILE* file = fopen(saveName, "w");
    int i = 0;

    while (i < 25) {
        fprintf(file, "%i\n", 0);
        i += 1;
    }

    fclose(file);
}

static void RecreateFile(FILE* from, FILE* to) {
    int c = 0;

    while ((c = fgetc(from)) != EOF) {
        fputc(c, to);
    }

    fclose(from);
    fclose(to);
}

static void CreatePosition(const char* const saveName) {
    RecreateFile(fopen("dane\\mapy\\position.txt", "r"), fopen(TextFormat("saves\\%s\\mapy\\position.txt", saveName), "w"));
}

static void CreatePlayer(const char* const saveName, const char* const characterName, const int bodyParts[10]) {
    CreateCharacter(TextFormat("saves\\%s\\postaæ.txt", saveName), characterName, bodyParts);
    CreateEquipment(TextFormat("saves\\%s\\ekwipunek.txt", saveName));
    CreatePosition(saveName);
}

static void CopyShops(const char* const saveName) {
    FilePathList list = LoadDirectoryFiles("dane\\sklepy");
    unsigned int i = 0;

    while (i < list.capacity) {
        RecreateFile(fopen(TextFormat("dane\\sklepy\\%i.txt", i), "r"), fopen(TextFormat("saves\\%s\\sklepy\\%i.txt", saveName, i), "w"));

        i += 1;
    }

    UnloadDirectoryFiles(list);
}

static void CopyMaps(const char* const saveName) {
    FilePathList list = LoadDirectoryFiles("dane\\mapy");
    unsigned int i = 0;

    while (i < list.capacity - 1) {
        RecreateFile(fopen(TextFormat("dane\\mapy\\%i.txt", i), "r"), fopen(TextFormat("saves\\%s\\mapy\\%i.txt", saveName, i), "w"));

        i += 1;
    }

    UnloadDirectoryFiles(list);
}

static void CreateAchievements(const char* const saveName) {
    FILE* file = fopen(TextFormat("saves\\%s\\osi¹gniêcia\\0.txt", saveName), "w");

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

static int CreateNewSave(const char* const saveName, const char* const characterName, const int bodyParts[10]) {
    const char* saveDirectory = TextFormat("saves\\%s", saveName);
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


// Test cases

//Podstawowe wejscie
static void test_CreateNewSave_basic(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave", "testCharacter", bodyParts);
    CU_ASSERT_FALSE(result);
}

//Wejscie z istniejaca nazwa zapisu
static void test_CreateNewSave_existing(void) {
    int bodyParts[10] = { 0 };
    _mkdir("saves\\existingSave");
    bool result = CreateNewSave("existingSave", "testCharacter", bodyParts);
    CU_ASSERT_TRUE(result);
    _rmdir("saves\\existingSave");
}

//Test z pusta nazwa zapisu
static void test_CreateNewSave_empty_strings(void) {
    int bodyParts[10] = { 0 };
    bool result1 = CreateNewSave("", "testCharacter", bodyParts);
    bool result2 = CreateNewSave("testSave1", "", bodyParts);
    CU_ASSERT_TRUE(result1);
    CU_ASSERT_FALSE(result2);
}

//Test z nazw¹ zapisu zawieraj¹c¹ spacje
static void test_CreateNewSave_space_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test Save", "testCharacter", bodyParts);
    CU_ASSERT_FALSE(result);
}

//Test z nazw¹ postaci zawieraj¹c¹ spacje
static void test_CreateNewSave_space_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave2", "test Character", bodyParts);
    CU_ASSERT_FALSE(result);
}

//Test z nazw¹ zapisu zawieraj¹c¹ nieprawid³owe znaki
static void test_CreateNewSave_invalid_characters_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test*Save?", "testCharacter", bodyParts);
    CU_ASSERT_TRUE(result);
}

//Test z nazw¹ postaci zawieraj¹c¹ nieprawid³owe znaki
static void test_CreateNewSave_invalid_characters_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave3", "test*Character?", bodyParts);
    CU_ASSERT_FALSE(result);
}

//Test z nazw¹ zapisu zawieraj¹c¹ znaki spoza ASCII
static void test_CreateNewSave_non_ascii_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testŒave", "testCharacter", bodyParts);
    CU_ASSERT_TRUE(result);
}

//Test z nazw¹ postaci zawieraj¹c¹ znaki spoza ASCII
static void test_CreateNewSave_non_ascii_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave4", "testÆharacter", bodyParts);
    CU_ASSERT_FALSE(result);
}

//Test z bardzo d³ug¹ nazw¹ zapisu
static void test_CreateNewSave_long_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("thisIsAVeryLongSaveNameThatExceedsNormalLimits", "testCharacter", bodyParts);
    CU_ASSERT_FALSE(result);
}

//Test z bardzo d³ug¹ nazw¹ postaci
static void test_CreateNewSave_long_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave5", "thisIsAVeryLongCharacterNameThatExceedsNormalLimits", bodyParts);
    CU_ASSERT_FALSE(result);
}

//Test z nazw¹ zapisu zawieraj¹c¹ same liczby
static void test_CreateNewSave_numeric_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("123456", "testCharacter", bodyParts);
    CU_ASSERT_FALSE(result);
}

//Test z nazw¹ postaci zawieraj¹c¹ same liczby
static void test_CreateNewSave_numeric_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave6", "123456", bodyParts);
    CU_ASSERT_FALSE(result);
}

//Test z pust¹ nazw¹ zapisu i postaci
static void test_CreateNewSave_empty_save_and_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("", "", bodyParts);
    CU_ASSERT_TRUE(result);
}

//Test z nazw¹ zapisu zawieraj¹c¹ znaki specjalne
static void test_CreateNewSave_special_characters_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test@Save#", "testCharacter", bodyParts);
    CU_ASSERT_TRUE(result);
}

//Test z nazw¹ postaci zawieraj¹c¹ znaki specjalne
static void test_CreateNewSave_special_characters_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave7", "test@Character#", bodyParts);
    CU_ASSERT_FALSE(result);
}

//Test z nazw¹ zapisu zawieraj¹c¹ kombinacjê liter, cyfr i znaków specjalnych
static void test_CreateNewSave_mixed_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test123@Save#", "testCharacter", bodyParts);
    CU_ASSERT_TRUE(result);
}

//Test z nazw¹ postaci zawieraj¹c¹ kombinacjê liter, cyfr i znaków specjalnych
static void test_CreateNewSave_mixed_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave8", "test123@Character#", bodyParts);
    CU_ASSERT_FALSE(result);
}

// Test z losowymi znakami w nazwie zapisu
static void test_CreateNewSave_gibberish_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("][/-/&*E@", "testCharacter", bodyParts);
    CU_ASSERT_TRUE(result);
}

// Test z losowymi znakami w nazwie postaci
static void test_CreateNewSave_gibberish_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave9", "; ][/ ;  = -/ &*E@", bodyParts);
    CU_ASSERT_FALSE(result);
}

// Test z jednoznakow¹ nazw¹ zapisu
static void test_CreateNewSave_short_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("a", "testCharacter", bodyParts);
    CU_ASSERT_FALSE(result);
}

// Test z jednoznakow¹ nazw¹ postaci
static void test_CreateNewSave_short_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave10", "b", bodyParts);
    CU_ASSERT_FALSE(result);
}

// Test z nazw¹ zapisu zawieraj¹ca znak nowej linii
static void test_CreateNewSave_newline_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test\nSave", "testCharacter", bodyParts);
    CU_ASSERT_TRUE(result);
}

// Test z nazw¹ postaci zawieraj¹ca znak nowej linii
static void test_CreateNewSave_newline_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave11", "test\nCharacter", bodyParts);
    CU_ASSERT_FALSE(result);
}

// Test z nazw¹ zapisu zawieraj¹ca znak TAB
static void test_CreateNewSave_tab_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test\tSave", "testCharacter", bodyParts);
    CU_ASSERT_TRUE(result);
}

// Test z nazw¹ postaci zawieraj¹ca znak TAB
static void test_CreateNewSave_tab_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave12", "test\tCharacter", bodyParts);
    CU_ASSERT_FALSE(result);
}

// Test z nazw¹ zapisu zawieraj¹ca spacje na pocz¹tku
static void test_CreateNewSave_leading_spaces_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("   testSave", "testCharacter", bodyParts);
    CU_ASSERT_FALSE(result);
}

// Test z nazw¹ postaci zawieraj¹ca spacje na pocz¹tku
static void test_CreateNewSave_leading_spaces_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave13", "   testCharacter", bodyParts);
    CU_ASSERT_FALSE(result);
}

// Test z nazw¹ zapisu zawieraj¹c¹ wy³¹cznie spacje
static void test_CreateNewSave_only_spaces_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("     ", "testCharacter", bodyParts);
    CU_ASSERT_TRUE(result);
}

// Test z nazw¹ postaci zawieraj¹c¹ wy³¹cznie spacje
static void test_CreateNewSave_only_spaces_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave15", "     ", bodyParts);
    CU_ASSERT_FALSE(result);
}

CU_ErrorCode add_tests_CreateNewSave(void) {
    CU_pSuite pSuite = CU_add_suite("CreateNewSave_TestSuite", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "test of CreateNewSave - basic", test_CreateNewSave_basic);
        CU_add_test(pSuite, "test of CreateNewSave - existing save", test_CreateNewSave_existing);
        CU_add_test(pSuite, "test of CreateNewSave - empty strings", test_CreateNewSave_empty_strings);
        CU_add_test(pSuite, "test of CreateNewSave - space in save name", test_CreateNewSave_space_in_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - space in character name", test_CreateNewSave_space_in_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - invalid characters in save name", test_CreateNewSave_invalid_characters_in_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - invalid characters in character name", test_CreateNewSave_invalid_characters_in_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - non ASCII save name", test_CreateNewSave_non_ascii_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - non ASCII character name", test_CreateNewSave_non_ascii_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - long save name", test_CreateNewSave_long_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - long character name", test_CreateNewSave_long_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - numeric save name", test_CreateNewSave_numeric_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - numeric character name", test_CreateNewSave_numeric_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - empty save and character name", test_CreateNewSave_empty_save_and_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - special characters in save name", test_CreateNewSave_special_characters_in_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - special characters in character name", test_CreateNewSave_special_characters_in_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - mixed save name", test_CreateNewSave_mixed_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - mixed character name", test_CreateNewSave_mixed_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - gibberish save name", test_CreateNewSave_gibberish_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - gibberish character name", test_CreateNewSave_gibberish_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - short save name", test_CreateNewSave_short_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - short character name", test_CreateNewSave_short_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - newline in save name", test_CreateNewSave_newline_in_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - newline in character name", test_CreateNewSave_newline_in_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - tab in save name", test_CreateNewSave_tab_in_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - tab in character name", test_CreateNewSave_tab_in_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - leading spaces in save name", test_CreateNewSave_leading_spaces_in_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - leading spaces in character name", test_CreateNewSave_leading_spaces_in_character_name);
        CU_add_test(pSuite, "test of CreateNewSave - only spaces in save name", test_CreateNewSave_only_spaces_in_save_name);
        CU_add_test(pSuite, "test of CreateNewSave - only spaces in character name", test_CreateNewSave_only_spaces_in_character_name);
    }

    return CU_get_error();
}