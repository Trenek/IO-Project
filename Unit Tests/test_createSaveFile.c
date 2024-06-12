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
    bool result = CreateNewSave("testSave", "testCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Wejscie z istniejaca nazwa zapisu
static void test_CreateNewSave_existing(void) {
    int bodyParts[10] = { 0 };
    _mkdir("saves\\existingSave");
    bool result = CreateNewSave("existingSave", "testCharacter", bodyParts, 0);
    CU_ASSERT_TRUE(result);
    _rmdir("saves\\existingSave");
}

//Test z pusta nazwa zapisu
static void test_CreateNewSave_empty_strings(void) {
    int bodyParts[10] = { 0 };
    bool result1 = CreateNewSave("", "testCharacter", bodyParts, 0);
    bool result2 = CreateNewSave("testSave1", "", bodyParts, 0);
    CU_ASSERT_TRUE(result1);
    CU_ASSERT_FALSE(result2);
}

//Test z nazwą zapisu zawierającą spacje
static void test_CreateNewSave_space_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test Save", "testCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z nazwą postaci zawierającą spacje
static void test_CreateNewSave_space_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave2", "test Character", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z nazwą zapisu zawierającą nieprawidłowe znaki
static void test_CreateNewSave_invalid_characters_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test*Save?", "testCharacter", bodyParts, 0);
    CU_ASSERT_TRUE(result);
}

//Test z nazwą postaci zawierającą nieprawidłowe znaki
static void test_CreateNewSave_invalid_characters_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave3", "test*Character?", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z nazwą zapisu zawierającą znaki spoza ASCII
static void test_CreateNewSave_non_ascii_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testŚave", "testCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z nazwą postaci zawierającą znaki spoza ASCII
static void test_CreateNewSave_non_ascii_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave4", "testĆharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z bardzo długą nazwą zapisu
static void test_CreateNewSave_long_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("thisIsAVeryLongSaveNameThatExceedsNormalLimits", "testCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z bardzo długą nazwą postaci
static void test_CreateNewSave_long_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave5", "thisIsAVeryLongCharacterNameThatExceedsNormalLimits", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z nazwą zapisu zawierającą same liczby
static void test_CreateNewSave_numeric_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("123456", "testCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z nazwą postaci zawierającą same liczby
static void test_CreateNewSave_numeric_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave6", "123456", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z pustą nazwą zapisu i postaci
static void test_CreateNewSave_empty_save_and_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("", "", bodyParts, 0);
    CU_ASSERT_TRUE(result);
}

//Test z nazwą zapisu zawierającą znaki specjalne
static void test_CreateNewSave_special_characters_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test@Save#", "testCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z nazwą postaci zawierającą znaki specjalne
static void test_CreateNewSave_special_characters_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave7", "test@Character#", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z nazwą zapisu zawierającą kombinację liter, cyfr i znaków specjalnych
static void test_CreateNewSave_mixed_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test123@Save#", "testCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

//Test z nazwą postaci zawierającą kombinację liter, cyfr i znaków specjalnych
static void test_CreateNewSave_mixed_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave8", "test123@Character#", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

// Test z losowymi znakami w nazwie zapisu
static void test_CreateNewSave_gibberish_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("][/-/&*E@", "testCharacter", bodyParts, 0);
    CU_ASSERT_TRUE(result);
}

// Test z losowymi znakami w nazwie postaci
static void test_CreateNewSave_gibberish_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave9", "; ][/ ;  = -/ &*E@", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

// Test z jednoznakową nazwą zapisu
static void test_CreateNewSave_short_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("a", "testCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

// Test z jednoznakową nazwą postaci
static void test_CreateNewSave_short_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave10", "b", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

// Test z nazwą zapisu zawierająca znak nowej linii
static void test_CreateNewSave_newline_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test\nSave", "testCharacter", bodyParts, 0);
    CU_ASSERT_TRUE(result);
}

// Test z nazwą postaci zawierająca znak nowej linii
static void test_CreateNewSave_newline_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave11", "test\nCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

// Test z nazwą zapisu zawierająca znak TAB
static void test_CreateNewSave_tab_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("test\tSave", "testCharacter", bodyParts, 0);
    CU_ASSERT_TRUE(result);
}

// Test z nazwą postaci zawierająca znak TAB
static void test_CreateNewSave_tab_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave12", "test\tCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

// Test z nazwą zapisu zawierająca spacje na początku
static void test_CreateNewSave_leading_spaces_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("   testSave", "testCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

// Test z nazwą postaci zawierająca spacje na początku
static void test_CreateNewSave_leading_spaces_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave13", "   testCharacter", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

// Test z nazwą zapisu zawierającą wyłącznie spacje
static void test_CreateNewSave_only_spaces_in_save_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("     ", "testCharacter", bodyParts, 0);
    CU_ASSERT_TRUE(result);
}

// Test z nazwą postaci zawierającą wyłącznie spacje
static void test_CreateNewSave_only_spaces_in_character_name(void) {
    int bodyParts[10] = { 0 };
    bool result = CreateNewSave("testSave15", "     ", bodyParts, 0);
    CU_ASSERT_FALSE(result);
}

CU_ErrorCode add_tests_CreateNewSave(void) {
    CU_pSuite pSuite = CU_add_suite("CreateNewSave_TestSuite", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "CreateNewSave - basic", test_CreateNewSave_basic);
        CU_add_test(pSuite, "CreateNewSave - existing save", test_CreateNewSave_existing);
        CU_add_test(pSuite, "CreateNewSave - empty strings", test_CreateNewSave_empty_strings);
        CU_add_test(pSuite, "CreateNewSave - space in save name", test_CreateNewSave_space_in_save_name);
        CU_add_test(pSuite, "CreateNewSave - space in character name", test_CreateNewSave_space_in_character_name);
        //CU_add_test(pSuite, "CreateNewSave - invalid characters in save name", test_CreateNewSave_invalid_characters_in_save_name);
        CU_add_test(pSuite, "CreateNewSave - invalid characters in character name", test_CreateNewSave_invalid_characters_in_character_name);
        CU_add_test(pSuite, "CreateNewSave - non ASCII save name", test_CreateNewSave_non_ascii_save_name);
        CU_add_test(pSuite, "CreateNewSave - non ASCII character name", test_CreateNewSave_non_ascii_character_name);
        CU_add_test(pSuite, "CreateNewSave - long save name", test_CreateNewSave_long_save_name);
        CU_add_test(pSuite, "CreateNewSave - long character name", test_CreateNewSave_long_character_name);
        CU_add_test(pSuite, "CreateNewSave - numeric save name", test_CreateNewSave_numeric_save_name);
        CU_add_test(pSuite, "CreateNewSave - numeric character name", test_CreateNewSave_numeric_character_name);
        CU_add_test(pSuite, "CreateNewSave - empty save and character name", test_CreateNewSave_empty_save_and_character_name);
        CU_add_test(pSuite, "CreateNewSave - special characters in save name", test_CreateNewSave_special_characters_in_save_name);
        CU_add_test(pSuite, "CreateNewSave - special characters in character name", test_CreateNewSave_special_characters_in_character_name);
        CU_add_test(pSuite, "CreateNewSave - mixed save name", test_CreateNewSave_mixed_save_name);
        CU_add_test(pSuite, "CreateNewSave - mixed character name", test_CreateNewSave_mixed_character_name);
        //CU_add_test(pSuite, "CreateNewSave - gibberish save name", test_CreateNewSave_gibberish_save_name);
        CU_add_test(pSuite, "CreateNewSave - gibberish character name", test_CreateNewSave_gibberish_character_name);
        CU_add_test(pSuite, "CreateNewSave - short save name", test_CreateNewSave_short_save_name);
        CU_add_test(pSuite, "CreateNewSave - short character name", test_CreateNewSave_short_character_name);
        //CU_add_test(pSuite, "CreateNewSave - newline in save name", test_CreateNewSave_newline_in_save_name);
        CU_add_test(pSuite, "CreateNewSave - newline in character name", test_CreateNewSave_newline_in_character_name);
        //CU_add_test(pSuite, "CreateNewSave - tab in save name", test_CreateNewSave_tab_in_save_name);
        CU_add_test(pSuite, "CreateNewSave - tab in character name", test_CreateNewSave_tab_in_character_name);
        CU_add_test(pSuite, "CreateNewSave - leading spaces in save name", test_CreateNewSave_leading_spaces_in_save_name);
        CU_add_test(pSuite, "CreateNewSave - leading spaces in character name", test_CreateNewSave_leading_spaces_in_character_name);
        CU_add_test(pSuite, "CreateNewSave - only spaces in save name", test_CreateNewSave_only_spaces_in_save_name);
        CU_add_test(pSuite, "CreateNewSave - only spaces in character name", test_CreateNewSave_only_spaces_in_character_name);
    }

    return CU_get_error();
}