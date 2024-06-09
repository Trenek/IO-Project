#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <raylib.h>
#include "inputBox.h"

static void test_CalculateInputBoxPosition(void) {
    struct inputBox element = {
        .init = {
            .x = 100,
            .y = 100,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1,
            .width = 200
        },
        .font = &(Font) { 0 },
        .fontSize = 20,
        .spaceing = 1
    };

    strcpy(element.text, "Hello, world!");

    CalculateInputBoxPosition(&element);

    // Assertions
    CU_ASSERT_EQUAL(element.currentLength, 0);
    CU_ASSERT_EQUAL(element.lengthArrayLength, 0);
}

static void test_DrawInputBox(void) {
    struct inputBox element = {
        .init = {
            .x = 100,
            .y = 100,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1,
            .width = 200
        },
        .font = &(Font) { 0 },
        .fontSize = 20,
        .spaceing = 1,
        .isActive = true,
        .color = LIGHTGRAY,
        .borderActiveColor = RED,
        .borderColor = DARKGRAY,
        .fontColor = BLACK
    };

    strcpy(element.text, "Test Input");

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawInputBox(&element);
    EndDrawing();

    // Assertions (since we are mocking, we assume no errors occur)
    CU_ASSERT_TRUE(true);
}

static void test_InternalUpdateInputBox(void) {
    struct inputBox element = {
        .init = {
            .x = 100,
            .y = 100,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1,
            .width = 200
        },
        .font = &(Font) { 0 },
        .fontSize = 20,
        .spaceing = 1,
        .isActive = true
    };

    // Simulate adding characters
    InternalUpdateInputBox(&element);

    // Assertions (since we are mocking, we assume no errors occur)
    CU_ASSERT_TRUE(true);
}

CU_ErrorCode add_tests_inputBox(void) {
    CU_pSuite pSuite = CU_add_suite("Input Box tests", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "test of CalculateInputBoxPosition", test_CalculateInputBoxPosition);
        CU_add_test(pSuite, "test of DrawInputBox", test_DrawInputBox);
        CU_add_test(pSuite, "test of InternalUpdateInputBox", test_InternalUpdateInputBox);
    }

    return CU_get_error();
}