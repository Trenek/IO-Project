#include <stdio.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "button.h"

void test_CalculateButtonPosition_Center(void) {
    struct button element = {
        .text = "Button",
        .isActive = true,
        .init = {
            .x = 100,
            .y = 100,
            .incX = 10,
            .incY = 10, 
            .posX = 1,
            .posY = 1
        },
        .font = &(Font) { 0 },
        .fontSize = 20,
        .fontColor = (Color) {255, 255, 255, 255},
        .spaceing = 1,
        .color = (Color) {200, 200, 200, 255},
        .hoverColor = (Color) {255, 255, 255, 255}
    };

    CalculateButtonPosition(&element);

    // Expected results based on the mock text size and button parameters
    CU_ASSERT_DOUBLE_EQUAL(element.boxRectangle.x, 90.0, 0.001); // 100 - (1 * (10 + 60 / 2.0))
    CU_ASSERT_DOUBLE_EQUAL(element.boxRectangle.y, 90.0, 0.001); // 100 - (1 * (10 + 20 / 2.0))
    CU_ASSERT_DOUBLE_EQUAL(element.boxRectangle.width, 20.0, 0.001); // 60 + 2 * 10
    CU_ASSERT_DOUBLE_EQUAL(element.boxRectangle.height, 20.0, 0.001); // 20 + 2 * 10
    CU_ASSERT_DOUBLE_EQUAL(element.textLeftCorner.x, 100.0, 0.001); // 60 + 10
    CU_ASSERT_DOUBLE_EQUAL(element.textLeftCorner.y, 100.0, 0.001); // 85 + 10
}

void test_CalculateButtonPosition_TopLeft(void) {
    struct button element = {
        .text = "Button",
        .isActive = true,
        .init = {
            .x = 100,
            .y = 100,
            .incX = 10,
            .incY = 10,
            .posX = 0,
            .posY = 0
        },
        .font = &(Font) { 0 },
        .fontSize = 20,
        .fontColor = (Color) {255, 255, 255, 255},
        .spaceing = 1,
        .color = (Color) {200, 200, 200, 255},
        .hoverColor = (Color) {255, 255, 255, 255}
    };

    CalculateButtonPosition(&element);

    // Expected results based on the mock text size and button parameters
    CU_ASSERT_EQUAL(element.boxRectangle.x, 100.0); // 100 - (0 * (10 + 60 / 2.0))
    CU_ASSERT_EQUAL(element.boxRectangle.y, 100.0); // 100 - (0 * (10 + 20 / 2.0))
    CU_ASSERT_EQUAL(element.boxRectangle.width, 20.0); // 60 + 2 * 10
    CU_ASSERT_EQUAL(element.boxRectangle.height, 20.0); // 20 + 2 * 10
    CU_ASSERT_EQUAL(element.textLeftCorner.x, 110.0); // 100 + 10
    CU_ASSERT_EQUAL(element.textLeftCorner.y, 110.0); // 100 + 10
}

void test_CalculateButtonPosition_TopRight(void) {
    struct button element = {
        .text = "Button",
        .isActive = true,
        .init = {
            .x = 100,
            .y = 100,
            .incX = 10,
            .incY = 10,
            .posX = 2,
            .posY = 0
        },
        .font = &(Font) { 0 },
        .fontSize = 20,
        .fontColor = (Color) {255, 255, 255, 255},
        .spaceing = 1,
        .color = (Color) {200, 200, 200, 255},
        .hoverColor = (Color) {255, 255, 255, 255}
    };

    CalculateButtonPosition(&element);

    // Expected results based on the mock text size and button parameters
    CU_ASSERT_EQUAL(element.boxRectangle.x, 80.0); // 100 - (2 * (10 + 60 / 2.0))
    CU_ASSERT_EQUAL(element.boxRectangle.y, 100.0); // 100 - (0 * (10 + 20 / 2.0))
    CU_ASSERT_EQUAL(element.boxRectangle.width, 20.0); // 60 + 2 * 10
    CU_ASSERT_EQUAL(element.boxRectangle.height, 20.0); // 20 + 2 * 10
    CU_ASSERT_EQUAL(element.textLeftCorner.x, 90.0); // 30 + 10
    CU_ASSERT_EQUAL(element.textLeftCorner.y, 110.0); // 100 + 10
}

void test_CalculateButtonPosition_BottomLeft(void) {
    struct button element = {
        .text = "Button",
        .isActive = true,
        .init = {
            .x = 100,
            .y = 100,
            .incX = 10,
            .incY = 10,
            .posX = 0,
            .posY = 2
        },
        .font = &(Font) { 0 },
        .fontSize = 20,
        .fontColor = (Color) {255, 255, 255, 255},
        .spaceing = 1,
        .color = (Color) {200, 200, 200, 255},
        .hoverColor = (Color) {255, 255, 255, 255}
    };

    CalculateButtonPosition(&element);

    // Expected results based on the mock text size and button parameters
    CU_ASSERT_EQUAL(element.boxRectangle.x, 100.0); // 100 - (0 * (10 + 60 / 2.0))
    CU_ASSERT_EQUAL(element.boxRectangle.y, 80.0); // 100 - (2 * (10 + 20 / 2.0))
    CU_ASSERT_EQUAL(element.boxRectangle.width, 20.0); // 60 + 2 * 10
    CU_ASSERT_EQUAL(element.boxRectangle.height, 20.0); // 20 + 2 * 10
    CU_ASSERT_EQUAL(element.textLeftCorner.x, 110.0); // 100 + 10
    CU_ASSERT_EQUAL(element.textLeftCorner.y, 90.0); // 55 + 10
}

void test_CalculateButtonPosition_BottomRight(void) {
    struct button element = {
        .text = "Button",
        .isActive = true,
        .init = {
            .x = 100,
            .y = 100,
            .incX = 10,
            .incY = 10,
            .posX = 2,
            .posY = 2
        },
        .font = &(Font) { 0 },
        .fontSize = 20,
        .fontColor = (Color) {255, 255, 255, 255},
        .spaceing = 1,
        .color = (Color) {200, 200, 200, 255},
        .hoverColor = (Color) {255, 255, 255, 255}
    };

    CalculateButtonPosition(&element);

    // Expected results based on the mock text size and button parameters
    CU_ASSERT_EQUAL(element.boxRectangle.x, 80.0); // 100 - (2 * (10 + 60 / 2.0))
    CU_ASSERT_EQUAL(element.boxRectangle.y, 80.0); // 100 - (2 * (10 + 20 / 2.0))
    CU_ASSERT_EQUAL(element.boxRectangle.width, 20.0); // 60 + 2 * 10
    CU_ASSERT_EQUAL(element.boxRectangle.height, 20.0); // 20 + 2 * 10
    CU_ASSERT_EQUAL(element.textLeftCorner.x, 90.0); // -20 + 10
    CU_ASSERT_EQUAL(element.textLeftCorner.y, 90.0); // 55 + 10
}

int add_tests_button(void) {
    CU_pSuite pSuite = CU_add_suite("Button tests", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "test of CalculateButtonPosition_Center", test_CalculateButtonPosition_Center);
        CU_add_test(pSuite, "test of CalculateButtonPosition_TopLeft", test_CalculateButtonPosition_TopLeft);
        CU_add_test(pSuite, "test of CalculateButtonPosition_TopRight", test_CalculateButtonPosition_TopRight);
        CU_add_test(pSuite, "test of CalculateButtonPosition_BottomLeft", test_CalculateButtonPosition_BottomLeft);
        CU_add_test(pSuite, "test of CalculateButtonPosition_BottomRight", test_CalculateButtonPosition_BottomRight);
    }

    return CU_get_error();
}
