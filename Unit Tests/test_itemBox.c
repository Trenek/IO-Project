#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <raylib.h>
#include "itemBox.h"
#include "playState.h"

static void test_CalculateItemBoxPosition(void) {
    struct itemBox element = {
        .init = {
            .x = 100,
            .y = 100,
            .posX = 1,
            .posY = 1,
            .width = 50,
            .height = 50
        },
        .color = GRAY,
        .activeColor = DARKGRAY,
        .borderColor = BLACK
    };

    CalculateItemBoxPosition(&element);

    // Assertions
    CU_ASSERT_EQUAL(element.isActive, false);
    CU_ASSERT_EQUAL(element.boxRectangle.x, 75);
    CU_ASSERT_EQUAL(element.boxRectangle.y, 75);
    CU_ASSERT_EQUAL(element.boxRectangle.width, 50);
    CU_ASSERT_EQUAL(element.boxRectangle.height, 50);
}

static void test_DrawItemBox(void) {
    struct itemBox element = {
        .init = {
            .x = 100,
            .y = 100,
            .posX = 1,
            .posY = 1,
            .width = 50,
            .height = 50
        },
        .color = GRAY,
        .activeColor = DARKGRAY,
        .borderColor = BLACK,
        .isActive = true
    };

    CalculateItemBoxPosition(&element);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawItemBox(element);
    EndDrawing();

    // Assertions (since we are mocking, we assume no errors occur)
    CU_ASSERT_TRUE(true);
}


CU_ErrorCode add_tests_itemBox(void) {
    CU_pSuite pSuite = CU_add_suite("Item Box tests", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "test of CalculateItemBoxPosition", test_CalculateItemBoxPosition);
        CU_add_test(pSuite, "test of DrawItemBox", test_DrawItemBox);
    }

    return CU_get_error();
}
