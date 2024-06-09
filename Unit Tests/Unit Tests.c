#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <raylib.h>
#include "tests.h"

int setup(void) {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(800, 600, "Test Window");
    SetTargetFPS(60);
    return 0;
}


int main(void) {
    setup();
    CU_basic_set_mode(CU_BRM_VERBOSE);

    if (CUE_SUCCESS == CU_initialize_registry())
    if (CUE_SUCCESS == add_tests_achievementElem())
    if (CUE_SUCCESS == add_tests_button())
    if (CUE_SUCCESS == add_tests_saveData())
    if (CUE_SUCCESS == add_tests_chooseAction())
    if (CUE_SUCCESS == add_tests_equipementBox())
    if (CUE_SUCCESS == add_tests_fighterLabel())
    if (CUE_SUCCESS == add_tests_inputBox())
    if (CUE_SUCCESS == add_tests_itemBox())
    if (CUE_SUCCESS == add_tests_numberSlideBox())
    if (CUE_SUCCESS == add_tests_stringSlideBox()) {
        CU_basic_run_tests();
    }

    CU_cleanup_registry();
    CloseWindow();

    return CU_get_error();
}