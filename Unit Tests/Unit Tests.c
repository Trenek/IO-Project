#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <raylib.h>
#include <stdio.h>
#include <direct.h>
#include <io.h>
#include <sys/stat.h>
#include <string.h>
#include "tests.h"

// Function to remove a directory and its contents recursively
void RemoveDirectoryRecursively(const char* directory) {
    struct _finddata_t fileInfo;
    intptr_t hFile;
    char path[260];
    snprintf(path, sizeof(path), "%s\\*.*", directory);

    if ((hFile = _findfirst(path, &fileInfo)) != -1L) {
        do {
            if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0) {
                snprintf(path, sizeof(path), "%s\\%s", directory, fileInfo.name);

                if (fileInfo.attrib & _A_SUBDIR) {
                    RemoveDirectoryRecursively(path);
                }
                else {
                    remove(path);
                }
            }
        } while (_findnext(hFile, &fileInfo) == 0);

        _findclose(hFile);
    }
    _rmdir(directory);
    _mkdir(directory);
}

// Setup function for raylib
void raylibSetup(void) {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(800, 600, "Test Window");
    SetTargetFPS(60);
}

int main(void) {
    RemoveDirectoryRecursively("saves");
    raylibSetup();
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
    if (CUE_SUCCESS == add_tests_stringSlideBox())
    if (CUE_SUCCESS == add_tests_CreateNewSave()) {
        CU_basic_run_tests();
    }

    CU_cleanup_registry();
    CloseWindow();

    return CU_get_error();
}