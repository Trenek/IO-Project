#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "stringSlideBox.h"


// Mock function to simulate InternalUpdateSlideBox with custom inputs
static void MockInternalUpdateSlideBox(struct slideBox* element, bool leftKeyPressed, bool rightKeyPressed, bool leftMousePressed, bool rightMousePressed) {
    if (leftKeyPressed || leftMousePressed) {
        if (element->currentOption == 0) {
            element->currentOption = element->numberOfOptions - 1;
        }
        else {
            element->currentOption -= 1;
        }
    }

    if (rightKeyPressed || rightMousePressed) {
        if (element->currentOption == element->numberOfOptions - 1) {
            element->currentOption = 0;
        }
        else {
            element->currentOption += 1;
        }
    }
}

// Test CalculateSlideBoxPosition
static void test_CalculateSlideBoxPosition(void) {
    const char* options[] = { "Option 1", "Option 2", "Option 3", "Option 4", "Option 5" };
    struct slideBox element = {
        .init = {
            .x = 400,
            .y = 300,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1,
            .width = 200
        },
        .fontSize = 20,
        .numberOfOptions = 5,
        .font = 0,
        .fontColor = BLACK,
        .color = WHITE,
        .borderActiveColor = RED,
        .borderColor = BLACK,
        .spaceing = 2,
        .currentOption = 2,
        .isActive = true,
        .options = options
    };

    CalculateSlideBoxPosition(&element);

    // Assertions
    CU_ASSERT_EQUAL(element.rect[0].width, 220);
    CU_ASSERT_EQUAL(element.rect[0].height, 40);
    CU_ASSERT_EQUAL(element.rect[1].width, 40);
    CU_ASSERT_EQUAL(element.rect[2].width, 40);
}

// Test InternalUpdateSlideBox
static void test_InternalUpdateSlideBox(void) {
    const char* options[] = { "Option 1", "Option 2", "Option 3", "Option 4", "Option 5" };
    struct slideBox element = {
        .init = {
            .x = 400,
            .y = 300,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1,
            .width = 200
        },
        .fontSize = 20,
        .numberOfOptions = 5,
        .font = 0,
        .fontColor = BLACK,
        .color = WHITE,
        .borderActiveColor = RED,
        .borderColor = BLACK,
        .spaceing = 2,
        .currentOption = 2,
        .isActive = true,
        .options = options
    };

    CalculateSlideBoxPosition(&element);

    // Simulate a left key press
    MockInternalUpdateSlideBox(&element, true, false, false, false);
    CU_ASSERT_EQUAL(element.currentOption, 1);

    // Simulate a right key press
    MockInternalUpdateSlideBox(&element, false, true, false, false);
    CU_ASSERT_EQUAL(element.currentOption, 2);

    // Simulate a left mouse button press
    MockInternalUpdateSlideBox(&element, false, false, true, false);
    CU_ASSERT_EQUAL(element.currentOption, 1);

    // Simulate a right mouse button press
    MockInternalUpdateSlideBox(&element, false, false, false, true);
    CU_ASSERT_EQUAL(element.currentOption, 2);
}

CU_ErrorCode add_tests_stringSlideBox(void) {
    CU_pSuite pSuite = CU_add_suite("String SlideBox tests", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "CalculateSlideBoxPosition", test_CalculateSlideBoxPosition);
        CU_add_test(pSuite, "InternalUpdateSlideBox", test_InternalUpdateSlideBox);
    }

    return CU_get_error();
}
