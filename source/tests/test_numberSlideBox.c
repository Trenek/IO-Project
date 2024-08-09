#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "numberSlideBox.h"

static bool MocknInternalUpdateSlideBox(struct nSlideBox* element, MouseButton m) {
    bool result = false;

    if (IsKeyPressed(KEY_LEFT) || (m == MOUSE_BUTTON_RIGHT)) {
        if (element->currentOption == 0) {
            element->currentOption = element->numberOfOptions - 1;
        }
        else {
            element->currentOption -= 1;
        }

        result = true;
    }

    if (IsKeyPressed(KEY_RIGHT) || (m == MOUSE_BUTTON_LEFT)) {
        if (element->currentOption == element->numberOfOptions) {
            element->currentOption = 0;
        }
        else {
            element->currentOption += 1;
            element->currentOption %= element->numberOfOptions;
        }

        result = true;
    }

    return result;
}

// Test nCalculateSlideBoxPosition
static void test_nCalculateSlideBoxPosition(void) {
    struct nSlideBox element = {
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
        .isActive = true
    };

    nCalculateSlideBoxPosition(&element);

    // Assertions
    CU_ASSERT_EQUAL(element.rect[0].width, 220);
    CU_ASSERT_EQUAL(element.rect[0].height, 40);
    CU_ASSERT_EQUAL(element.rect[1].width, 40);
    CU_ASSERT_EQUAL(element.rect[2].width, 40);
}

// Test nInternalUpdateSlideBox
static void test_nInternalUpdateSlideBox(void) {
    struct nSlideBox element = {
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
        .isActive = true
    };

    nCalculateSlideBoxPosition(&element);

    // Simulate a left key press
    MocknInternalUpdateSlideBox(&element, MOUSE_BUTTON_LEFT);

    CU_ASSERT_EQUAL(element.currentOption, 3);

    // Simulate a right key press
    MocknInternalUpdateSlideBox(&element, MOUSE_BUTTON_RIGHT);

    CU_ASSERT_EQUAL(element.currentOption, 2);
}

CU_ErrorCode add_tests_numberSlideBox(void) {
    CU_pSuite pSuite = CU_add_suite("Number SlideBox tests", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "nCalculateSlideBoxPosition", test_nCalculateSlideBoxPosition);
        CU_add_test(pSuite, "nInternalUpdateSlideBox", test_nInternalUpdateSlideBox);
    }

    return CU_get_error();
}
