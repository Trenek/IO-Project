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

#include "savefile.h"

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