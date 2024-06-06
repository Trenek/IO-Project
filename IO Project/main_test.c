//if you want to run tests simply uncomment below line and also uncomment the same line in file IO Project.c
//#define RUN_TESTS

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>



// Prototypes for the test registration functions
int add_tests_achievementElem(void);

#ifdef RUN_TESTS
int main(void) {
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
#endif