#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <Cunit/CUnit.h>
#include <Cunit/Basic.h>

#include "achievementElem.h" 
#include "savefile.h"
#include "button.h"

static void compareColors(Color color1, Color color2) {
    CU_ASSERT_EQUAL(color1.r, color2.r);
    CU_ASSERT_EQUAL(color1.g, color2.g);
    CU_ASSERT_EQUAL(color1.b, color2.b);
    CU_ASSERT_EQUAL(color1.a, color2.a);
}

static void test_UpdateAchievementElem(void) {
    struct achievementElem element = {
        .x = 10,
        .y = 20,
        .space = 5,
        .font = &(Font) { 0 }
    };
    struct Achievement achievement = {
        .requirementsCount = 2,
        .name = "Achievement 1",
        .description = "This is the first achievement.",
        .status = 1,
        .requirements = (char *[]) {
            "Requirement 1",
            "Requirement 2"
        }
    };

    // Call the function to test
    UpdateAchievementElem(&element, achievement);

    // Assertions
    CU_ASSERT_EQUAL(element.numberOfRequirements, achievement.requirementsCount);
    CU_ASSERT_STRING_EQUAL(element.name.text, achievement.name);
    CU_ASSERT_STRING_EQUAL(element.description.text, achievement.description);
    CU_ASSERT_STRING_EQUAL(element.status.text, "Zakonczone");

    Color expectedColor = (achievement.status == 1) ? GREEN : RED;
    compareColors(element.status.fontColor, expectedColor);

    for (int i = 0; i < element.numberOfRequirements; i++) {
        CU_ASSERT_STRING_EQUAL(element.requirements[i].text, achievement.requirements[i]);
    }

    // Clean up
    free(element.requirements);
}

static void test_UpdateAchievementElem_Status0(void) {
    struct achievementElem element = {
        .x = 10,
        .y = 20,
        .space = 5,
        .font = &(Font) { 0 }
    };
    struct Achievement achievement = {
        .requirementsCount = 1,
        .name = "Achievement 2",
        .description = "This is the second achievement.",
        .status = 0,
        .requirements = (char *[]) {
            "Requirement 1"
        }
    };

    // Call the function to test
    UpdateAchievementElem(&element, achievement);

    // Assertions
    CU_ASSERT_EQUAL(element.numberOfRequirements, achievement.requirementsCount);
    CU_ASSERT_STRING_EQUAL(element.name.text, achievement.name);
    CU_ASSERT_STRING_EQUAL(element.description.text, achievement.description);
    CU_ASSERT_STRING_EQUAL(element.status.text, "Niezakonczone");

    Color expectedColor = (achievement.status == 1) ? GREEN : RED;
    compareColors(element.status.fontColor, expectedColor);

    for (int i = 0; i < element.numberOfRequirements; i++) {
        CU_ASSERT_STRING_EQUAL(element.requirements[i].text, achievement.requirements[i]);
    }

    // Clean up
    free(element.requirements);
}

static void test_UpdateAchievementElem_MultipleRequirements(void) {
    struct achievementElem element = {
        .x = 10,
        .y = 20,
        .space = 5,
        .font = &(Font) { 0 }
    };
    struct Achievement achievement = {
        .requirementsCount = 3,
        .name = "Achievement 3",
        .description = "This is the third achievement.",
        .status = 1,
        .requirements = (char *[]){
            "Requirement 1",
            "Requirement 2",
            "Requirement 3"
        }
    };

    // Call the function to test
    UpdateAchievementElem(&element, achievement);

    // Assertions
    CU_ASSERT_EQUAL(element.numberOfRequirements, achievement.requirementsCount);
    CU_ASSERT_STRING_EQUAL(element.name.text, achievement.name);
    CU_ASSERT_STRING_EQUAL(element.description.text, achievement.description);
    CU_ASSERT_STRING_EQUAL(element.status.text, "Zakonczone");

    Color expectedColor = (achievement.status == 1) ? GREEN : RED;
    compareColors(element.status.fontColor, expectedColor);

    for (int i = 0; i < element.numberOfRequirements; i++) {
        CU_ASSERT_STRING_EQUAL(element.requirements[i].text, achievement.requirements[i]);
    }

    // Clean up
    free(element.requirements);
}

static void test_UpdateAchievementElem_NoRequirements(void) {
    struct achievementElem element = {
        .x = 10,
        .y = 20,
        .space = 5,
        .font = &(Font) { 0 }
    };
    struct Achievement achievement = {
        .requirementsCount = 0,
        .name = "Achievement 4",
        .description = "This is the fourth achievement.",
        .status = 1,
        .requirements = NULL,
    };

    // Call the function to test
    UpdateAchievementElem(&element, achievement);

    // Assertions
    CU_ASSERT_EQUAL(element.numberOfRequirements, achievement.requirementsCount);
    CU_ASSERT_STRING_EQUAL(element.name.text, achievement.name);
    CU_ASSERT_STRING_EQUAL(element.description.text, achievement.description);
    CU_ASSERT_STRING_EQUAL(element.status.text, "Zakonczone");

    Color expectedColor = (achievement.status == 1) ? GREEN : RED;
    compareColors(element.status.fontColor, expectedColor);

    // Clean up
    free(element.requirements);
}

CU_ErrorCode add_tests_achievementElem(void) {
    CU_pSuite pSuite = CU_add_suite("Achievement tests", NULL, NULL);

    if (NULL != pSuite) {
        CU_add_test(pSuite, "UpdateAchievementElem", test_UpdateAchievementElem);
        CU_add_test(pSuite, "UpdateAchievementElem with Status0", test_UpdateAchievementElem_Status0);
        CU_add_test(pSuite, "UpdateAchievementElem with MultipleRequirements", test_UpdateAchievementElem_MultipleRequirements);
        CU_add_test(pSuite, "UpdateAchievementElem with NoRequirements", test_UpdateAchievementElem_NoRequirements);
    }

    return CU_get_error();
}