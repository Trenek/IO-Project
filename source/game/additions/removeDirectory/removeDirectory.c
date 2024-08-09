#include <Windows.h>

#include <string.h>
#include <tchar.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

BOOL IsDots(const TCHAR *str) {
    if (_tcscmp(str, ".") && _tcscmp(str, "..")) return FALSE;
    return TRUE;
}

BOOL removeDirectory(const TCHAR *sPath) {
    HANDLE hFind;  // file handle
    WIN32_FIND_DATA FindFileData;

    TCHAR DirPath[MAX_PATH];
    TCHAR FileName[MAX_PATH];

    _tcscpy(DirPath, sPath);
    _tcscat(DirPath, "\\*");    // searching all files
    _tcscpy(FileName, sPath);
    _tcscat(FileName, "\\");

    hFind = FindFirstFile(DirPath, &FindFileData); // find the first file
    if (hFind == INVALID_HANDLE_VALUE) return FALSE;
    _tcscpy(DirPath, FileName);

    bool bSearch = true;
    while (bSearch) { // until we finds an entry
        if (FindNextFile(hFind, &FindFileData)) {
            if (IsDots(FindFileData.cFileName)) continue;
            _tcscat(FileName, FindFileData.cFileName);
            if ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {

                // we have found a directory, recurse
                if (!removeDirectory(FileName)) {
                    FindClose(hFind);
                    return FALSE; // directory couldn't be deleted
                }
                RemoveDirectory(FileName); // remove the empty directory
                _tcscpy(FileName, DirPath);
            }
            else {
                if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_READONLY)
                    _chmod(FileName, _S_IWRITE); // change read-only file mode
                if (!DeleteFile(FileName)) {  // delete the file
                    FindClose(hFind);
                    return FALSE;
                }
                _tcscpy(FileName, DirPath);
            }
        }
        else {
            if (GetLastError() == ERROR_NO_MORE_FILES) // no more files there
                bSearch = false;
            else {
                // some error occured, close the handle and return FALSE
                FindClose(hFind);
                return FALSE;
            }

        }

    }
    FindClose(hFind);  // closing file handle

    return RemoveDirectory(sPath); // remove the empty directory
}
