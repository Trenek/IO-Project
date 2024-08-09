#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <raylib.h>
#include "equipementBox.h"
#include "itemBox.h"
#include "button.h"
#include "playState.h"


// Test InitializeEquipementBox
static void test_InitializeEquipementBox(void) {
    struct equipementBox box = {
        .init = {
            .x = 100,
            .y = 100,
            .posX = 1,
            .posY = 1,
            .gapSize = 10,
            .itemBoxSize = 20,
            .buttonFont = &(Font) { 0 },
            .buttonIncX = 2,
            .buttonIncY = 2
        },
        .playerItemsID = malloc(sizeof(int[25][3])),
        .armorPart = malloc(sizeof(int[9])),
        .weapon = malloc(sizeof(int))
    };

    InitializeEquipementBox(&box);

    // Assertions
    CU_ASSERT_EQUAL(box.activeItemType, -1);
    CU_ASSERT_PTR_NOT_NULL(box.playerItemsID);
    CU_ASSERT_PTR_NOT_NULL(box.armorPart);
    CU_ASSERT_PTR_NOT_NULL(box.weapon);
    CU_ASSERT_EQUAL(box.equip.isActive, 0);
    CU_ASSERT_EQUAL(box.unequip.isActive, 0);
    CU_ASSERT_EQUAL(box.destroy.isActive, 0);
    CU_ASSERT_EQUAL(box.goBack.isActive, 1);

    // Free allocated memory
    free(box.playerItemsID);
    free(box.armorPart);
    free(box.weapon);
}

// Test UpdateEquipementBox
static void test_UpdateEquipementBox(void) {
    struct equipementBox box = {
        .init = {
            .x = 100,
            .y = 100,
            .posX = 1,
            .posY = 1,
            .gapSize = 10,
            .itemBoxSize = 20,
            .buttonFont = &(Font) { 0 },
            .buttonIncX = 2,
            .buttonIncY = 2
        },
        .playerItemsID = malloc(sizeof(int[25][3])),
        .armorPart = malloc(sizeof(int[9])),
        .weapon = malloc(sizeof(int))
    };

    InitializeEquipementBox(&box);

    struct playInfo info = {
        .resources = NULL,
        .save = {0},
    };


    // Assertions
    CU_ASSERT_FALSE(UpdateEquipementBox(&box, &info));

    // Free allocated memory
    free(box.playerItemsID);
    free(box.armorPart);
    free(box.weapon);
}

CU_ErrorCode add_tests_equipementBox(void) {
    CU_pSuite pSuite = CU_add_suite("Equipement Box tests", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "InitializeEquipementBox", test_InitializeEquipementBox);
        CU_add_test(pSuite, "UpdateEquipementBox", test_UpdateEquipementBox);
    }

    return CU_get_error();
}
