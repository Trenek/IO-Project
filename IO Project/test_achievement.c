#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "achievementElem.h"
#include "savefile.h"

// Function prototypes for the drawing functions assumed to exist
void DrawButton(struct button button);
void CalculateButtonPosition(struct button* button);

int init_suite(void) {
    return 0;
}
int clean_suite(void) {
    return 0;
}
void compareColors(Color color1, Color color2) {
    CU_ASSERT_EQUAL(color1.r, color2.r);
    CU_ASSERT_EQUAL(color1.g, color2.g);
    CU_ASSERT_EQUAL(color1.b, color2.b);
    CU_ASSERT_EQUAL(color1.a, color2.a);
}

void test_UpdateAchievementElem(void) {
    struct achievementElem element;
    struct Achievement achievement;

    // Initialize element
    element.x = 10;
    element.y = 20;
    element.space = 5;
    Font font = { 0 }; // Assume an empty font for simplicity
    element.font = &font;

    // Initialize achievement
    achievement.requirementsCount = 2;
    strcpy(achievement.name, "Achievement 1");
    strcpy(achievement.description, "This is the first achievement.");
    achievement.status = 1;
    char* reqs[] = { "Requirement 1", "Requirement 2" };
    achievement.requirements = reqs;

    // Call the function to test
    UpdateAchievementElem(&element, achievement);

    // Debug print statement
    printf("element.status.text: '%s'\n", element.status.text);

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

void test_UpdateAchievementElem_Status0(void) {
    struct achievementElem element;
    struct Achievement achievement;

    // Initialize element
    element.x = 10;
    element.y = 20;
    element.space = 5;
    Font font = { 0 }; // Assume an empty font for simplicity
    element.font = &font;

    // Initialize achievement
    achievement.requirementsCount = 1;
    strcpy(achievement.name, "Achievement 2");
    strcpy(achievement.description, "This is the second achievement.");
    achievement.status = 0;
    char* reqs[] = { "Requirement 1" };
    achievement.requirements = reqs;

    // Call the function to test
    UpdateAchievementElem(&element, achievement);

    // Debug print statement
    printf("element.status.text: '%s'\n", element.status.text);

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

void test_UpdateAchievementElem_MultipleRequirements(void) {
    struct achievementElem element;
    struct Achievement achievement;

    // Initialize element
    element.x = 10;
    element.y = 20;
    element.space = 5;
    Font font = { 0 }; // Assume an empty font for simplicity
    element.font = &font;

    // Initialize achievement
    achievement.requirementsCount = 3;
    strcpy(achievement.name, "Achievement 3");
    strcpy(achievement.description, "This is the third achievement.");
    achievement.status = 1;
    char* reqs[] = { "Requirement 1", "Requirement 2", "Requirement 3" };
    achievement.requirements = reqs;

    // Call the function to test
    UpdateAchievementElem(&element, achievement);

    // Debug print statement
    printf("element.status.text: '%s'\n", element.status.text);

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

void test_UpdateAchievementElem_NoRequirements(void) {
    struct achievementElem element;
    struct Achievement achievement;

    // Initialize element
    element.x = 10;
    element.y = 20;
    element.space = 5;
    Font font = { 0 }; // Assume an empty font for simplicity
    element.font = &font;

    // Initialize achievement
    achievement.requirementsCount = 0;
    strcpy(achievement.name, "Achievement 4");
    strcpy(achievement.description, "This is the fourth achievement.");
    achievement.status = 1;
    achievement.requirements = NULL;

    // Call the function to test
    UpdateAchievementElem(&element, achievement);

    // Debug print statement
    printf("element.status.text: '%s'\n", element.status.text);

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

int add_tests_achievementElem(void) {
    CU_pSuite pSuite = CU_add_suite("Achievement tests", NULL, NULL);
    if (NULL == pSuite) {
        return CU_get_error();
    }

    if (NULL == CU_add_test(pSuite, "test of UpdateAchievementElem", test_UpdateAchievementElem) ||
        NULL == CU_add_test(pSuite, "test of UpdateAchievementElem with Status0", test_UpdateAchievementElem_Status0) ||
        NULL == CU_add_test(pSuite, "test of UpdateAchievementElem with MultipleRequirements", test_UpdateAchievementElem_MultipleRequirements) ||
        NULL == CU_add_test(pSuite, "test of UpdateAchievementElem with NoRequirements", test_UpdateAchievementElem_NoRequirements)) {
        return CU_get_error();
    }

    return CUE_SUCCESS;
}