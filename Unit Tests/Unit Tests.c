#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "tests.h"

int main(void) {
    printf("RUNNING TESTS:\n");

    if (CUE_SUCCESS == CU_initialize_registry()) {
        if (CUE_SUCCESS == add_tests_achievementElem()
            && CUE_SUCCESS == add_tests_button()
            ) {
            CU_basic_set_mode(CU_BRM_VERBOSE);
            CU_basic_run_tests();
        }
    }

    CU_cleanup_registry();

    return CU_get_error();
}