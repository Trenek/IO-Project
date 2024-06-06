#include <Cunit/CUnit.h>
#include <Cunit/Basic.h>

// Prototypes for the test registration functions
int add_tests_achievementElem(void);

int test(void) {
    printf("RUNNING TESTS:\n");
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add test suites
    if (CUE_SUCCESS != add_tests_achievementElem()) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    // Add calls to other test registration functions here

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}