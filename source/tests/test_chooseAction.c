#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <raylib.h>
#include "chooseAction.h"
#include "animateAttack.h"

#define MAIN 2


void mock_freeRows(struct chooseAction* const this) {
    free(this->row);
}

// Mock fighterLabel structure
struct fighter {
    int attackQuantity;
};

struct fighterLabel {
    struct fighter fighter;
};

// Test initializeChooseAction
static void test_initializeChooseAction(void) {
    struct chooseAction action = {
        .rowQuantity = 3,
        .font = &(Font) { 0 },
        .fontColor = (Color){ 255, 255, 255, 255 },
        .fontSize = 20,
        .spaceing = 1,
        .color = (Color){ 200, 200, 200, 255 },
        .activeBorderColor = (Color){ 255, 0, 0, 255 },
        .inactiveBorderColor = (Color){ 0, 0, 0, 255 },
        .hoverColor = (Color){ 100, 100, 100, 255 },
        .init = {
            .x = 100,
            .y = 100,
            .width = 200,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1
        }
    };

    // Initialize rows
    initializeChooseAction(&action);

    // Assertions
    CU_ASSERT_PTR_NOT_NULL(action.row);
    CU_ASSERT_EQUAL(action.rowQuantity, 3);

    // Free allocated memory
    mock_freeRows(&action);
}

// Test AttackPlayer
static void test_AttackPlayer(void) {
    struct fighterLabel fighter1 = {
        .fighter = {
            .attackQuantity = 3
        }
    };
    struct fighterLabel fighter2 = {
        .fighter = {
            .attackQuantity = 2
        }
    };

    struct fighterLabel fighter1Copy = fighter1;
    struct fighterLabel fighter2Copy = fighter2;
    struct chooseAction action = {
        .active = &fighter1Copy,
        .target = &fighter2Copy
    };
    struct animateAttack attack = { 0 };

    action.active = &fighter1;
    action.target = &fighter2;

    AttackPlayer(&action, &attack);

    // Assertions
    CU_ASSERT_EQUAL(attack.isAttacked, 1);
    CU_ASSERT_EQUAL(attack.attacker, &fighter1);
    CU_ASSERT_EQUAL(attack.attacked, &fighter2);
    CU_ASSERT_EQUAL(attack.attackID, 41);
}

// Test UpdateChooseAction
static void test_UpdateChooseAction(void) {
    struct chooseAction action = {
        .active = &(struct fighterLabel) { .fighter = {.attackQuantity = 3 } },
        .isActive = 1,
        .rowQuantity = 3,
        .row = malloc(sizeof(struct celle[4]) * 3)
    };
    struct animateAttack attack = { 0 };
    struct fighterLabel fighter1 = { .fighter = {.attackQuantity = 3 } };

    action.active = &fighter1;
    action.isActive = 1;
    action.rowQuantity = 3;
    action.row = malloc(sizeof(struct celle[4]) * action.rowQuantity);

    for (int i = 0; i < action.rowQuantity; i++) {
        action.row[i][MAIN].rec = (Rectangle){ 0, 0, 100, 20 };
    }

    // Simulate a click
    int result = UpdateChooseAction(&action, &attack);

    CU_ASSERT_EQUAL(result, 0);

    // Free allocated memory
    free(action.row);
}

CU_ErrorCode add_tests_chooseAction(void) {
    CU_pSuite pSuite = CU_add_suite("Choose Action tests", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "initializeChooseAction", test_initializeChooseAction);
        //CU_add_test(pSuite, "AttackPlayer", test_AttackPlayer);
        CU_add_test(pSuite, "UpdateChooseAction", test_UpdateChooseAction);
    }

    return CU_get_error();
}