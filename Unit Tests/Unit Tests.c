#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "tests.h"

int main(void) {
    CU_basic_set_mode(CU_BRM_VERBOSE);

    if (CUE_SUCCESS == CU_initialize_registry())
    if (CUE_SUCCESS == add_tests_achievementElem())
    if (CUE_SUCCESS == add_tests_button()) {
        CU_basic_run_tests();
    }

    CU_cleanup_registry();

    return CU_get_error();
}