#include <Cunit/CUnit.h>
#include <Cunit/Basic.h>

// Prototypes for the test registration functions
int add_tests_achievementElem(void);

int main(void) {
    printf("RUNNING TESTS:\n");

    if (CUE_SUCCESS == CU_initialize_registry())
    if (CUE_SUCCESS == add_tests_achievementElem()) {
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
    }

    CU_cleanup_registry();

    return CU_get_error();
}
