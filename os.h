#ifdef _WIN32
#include <windows.h>
TCHAR *getcwd()
{
    static TCHAR path[MAX_PATH] = {0};
    GetCurrentDirectory(MAX_PATH, path);
    return path;
}

#endif