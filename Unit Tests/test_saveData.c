#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <raylib.h>
#include "saveData.h"


static void extractSaveName(struct saveData *const this, const char *const savePath) {
    const char *saveName = strstr(savePath, "\\") + 1;

    this->text = malloc(sizeof(char) * (strlen(saveName) + 1));

    strcpy(this->text, saveName);
}

// Mock function to simulate reading from a file
static void mock_loadDate(struct saveData* const this) {
    this->year = 2024;
    this->month = 6;
    this->day = 8;
    this->hour = 10;
    this->minute = 30;
    this->second = 45;
}

//function version for testing purposes
static void initializeSaveDataForTest(struct saveData* const this, const char* const savePath) {
    extractSaveName(this, savePath);
    mock_loadDate(this);
}

static void test_initializeSaveData(void) {
    struct saveData data;
    const char* savePath = "C:\\save\\game1";

    initializeSaveDataForTest(&data, savePath);

    // Assertions
    CU_ASSERT_STRING_EQUAL(data.text, "save\\game1");
    CU_ASSERT_EQUAL(data.year, 2024);
    CU_ASSERT_EQUAL(data.month, 6);
    CU_ASSERT_EQUAL(data.day, 8);
    CU_ASSERT_EQUAL(data.hour, 10);
    CU_ASSERT_EQUAL(data.minute, 30);
    CU_ASSERT_EQUAL(data.second, 45);

    freeSaveData(&data);
}

static void test_cmpSaveData(void) {
    struct saveData data1 = { .year = 2024, .month = 6, .day = 7, .hour = 10, .minute = 30, .second = 45 };
    struct saveData data2 = { .year = 2024, .month = 6, .day = 7, .hour = 10, .minute = 30, .second = 30 };
    struct saveData data3 = { .year = 2023, .month = 6, .day = 7, .hour = 10, .minute = 30, .second = 45 };
    struct saveData data4 = { .year = 2024, .month = 6, .day = 7, .hour = 10, .minute = 30, .second = 45 };

    // Assertions
    CU_ASSERT_EQUAL(cmpSaveData(&data1, &data2), -15);
    CU_ASSERT_EQUAL(cmpSaveData(&data1, &data3), -1);
    CU_ASSERT_EQUAL(cmpSaveData(&data2, &data3), -1);
    CU_ASSERT_EQUAL(cmpSaveData(&data3, &data1), 1);
    CU_ASSERT_EQUAL(cmpSaveData(&data1, &data4), 0);
}


CU_ErrorCode add_tests_saveData(void) {
    CU_pSuite pSuite = CU_add_suite("Save Data tests", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "test of initializeSaveData", test_initializeSaveData);
        CU_add_test(pSuite, "test of cmpSaveData", test_cmpSaveData);
    }

    return CU_get_error();
}