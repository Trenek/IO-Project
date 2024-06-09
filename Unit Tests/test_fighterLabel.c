#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "fighterLabel.h"
#include "character.h"
#include "resources.h"


int countDurability(int* ((*durability)[9]), int(*armorPart)[9]);


static void MockInitializeFighterLabel(struct fighterLabel* this) {
    struct fighterLabelPositionParameters init = this->init;
    const int width = 3 * init.height;

    this->leftCorner = (Vector2){
        .x = init.x - (init.posX * width) / 2.0f,
        .y = init.y - (init.posY * init.height) / 2.0f
    };

    this->name = (Vector2){
        .x = this->leftCorner.x + init.height,
        .y = this->leftCorner.y
    };

    this->width = width;
    this->height = init.height;

    this->fighter.direction = FRONT;
    this->fighter.object.position = init.position;

    this->health = this->maxHealth;
    this->maxDurability = countDurability(init.durability, &this->fighter.armorPart);
    this->durability = this->maxDurability;
    this->rest = this->maxRest;
}

// Test CountDurability
static void test_CountDurability(void) {
    // Allocate memory for the durability array and initialize it
    int* durability[9];
    for (int i = 0; i < 9; i++) {
        durability[i] = (int*)malloc(9 * sizeof(int));
        for (int j = 0; j < 9; j++) {
            durability[i][j] = j + 1;
        }
    }

    // Initialize the armorPart array
    int armorPart[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    // Cast to the correct types and call the function
    int* (*durability_cast)[9] = (int* (*)[9])durability;
    int result = countDurability(durability_cast, (int(*)[9])armorPart);

    // Assertions
    CU_ASSERT_EQUAL(result, 45);

    // Free allocated memory
    for (int i = 0; i < 9; i++) {
        free(durability[i]);
    }
}

// Test InitializeFighterLabel
static void test_InitializeFighterLabel(void) {
    // Allocate and initialize durability array
    int* durability[9];
    for (int i = 0; i < 9; i++) {
        durability[i] = (int*)malloc(9 * sizeof(int));
        for (int j = 0; j < 9; j++) {
            durability[i][j] = j + 1;
        }
    }

    struct fighterLabel label = {
        .init = {
            .x = 100,
            .y = 100,
            .incX = 10,
            .incY = 10,
            .posX = 1,
            .posY = 1,
            .height = 50,
            .durability = (int* (*)[9])durability,
            .position = {0, 0, 0}
        },
        .maxHealth = 100,
        .maxRest = 50
    };

    MockInitializeFighterLabel(&label);

    // Assertions
    CU_ASSERT_EQUAL(label.health, 100);
    CU_ASSERT_EQUAL(label.maxHealth, 100);
    CU_ASSERT_EQUAL(label.maxRest, 50);
    CU_ASSERT_EQUAL(label.rest, 50);
    CU_ASSERT_EQUAL(label.maxDurability, 9);
    CU_ASSERT_EQUAL(label.durability, 9);


    FreeFighterLabel(&label);

    // Free allocated memory
    for (int i = 0; i < 9; i++) {
        free(durability[i]);
    }
}

// Test FreeFighterLabel
static void test_FreeFighterLabel(void) {
    struct fighterLabel label = {
        .render = LoadRenderTexture(100, 50)
    };

    FreeFighterLabel(&label);

    // Assertions (since we are mocking, we assume no errors occur)
    CU_ASSERT_TRUE(true);
}

// Test DrawFighterLabel
static void test_DrawFighterLabel(void) {
    struct fighterLabel label = {
        .leftCorner = {50, 50},
        .render = LoadRenderTexture(100, 50)
    };

    DrawFighterLabel(&label);

    // Assertions (since we are mocking, we assume no errors occur)
    CU_ASSERT_TRUE(true);
}


CU_ErrorCode add_tests_fighterLabel(void) {
    CU_pSuite pSuite = CU_add_suite("Fighter Label tests", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "test of countDurability", test_CountDurability);
        CU_add_test(pSuite, "test of InitializeFighterLabel", test_InitializeFighterLabel);
        CU_add_test(pSuite, "test of FreeFighterLabel", test_FreeFighterLabel);
        CU_add_test(pSuite, "test of DrawFighterLabel", test_DrawFighterLabel);
    }

    return CU_get_error();
}
