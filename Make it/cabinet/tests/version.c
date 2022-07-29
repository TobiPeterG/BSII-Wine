#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winbase.h>
#include <wine/test.h>


#include "windef.h"
#define NO_SHLWAPI_REG
#include "shlwapi.h"
#undef NO_SHLWAPI_REG
#include "winbase.h"


typedef VOID (__stdcall *f_dllget)(PCABINETDLLVERSIONINFO);
typedef LPCSTR (__stdcall *f_getdll)(void);


static void test_dllget(HMODULE libHandle)
{
    PCABINETDLLVERSIONINFO verInfo;
    char                   *version;
    int                    sizeVerInfo;
    DWORD                  FileVersionMS;
    DWORD                  FileVersionLS;
    int                    majorV;
    int                    minorV;
    int                    buildV;
    int                    revisV;

    f_dllget DllGetVersion = (f_dllget)GetProcAddress(libHandle, "DllGetVersion");
    ok(libHandle != NULL, "Function DllGetVersion in DLL not found: Error = %ld.\n", GetLastError());


    verInfo = malloc(sizeof(CABINETDLLVERSIONINFO));
    ok(verInfo != NULL, "Couldn't allocate memory to run tests properly!\n");
    DllGetVersion(verInfo);

    FileVersionMS = verInfo->dwFileVersionMS;
    FileVersionLS = verInfo->dwFileVersionLS;

    sizeVerInfo =  2 * sizeof((FileVersionMS));
    sizeVerInfo += 2 * sizeof((FileVersionLS));

    version = malloc(sizeVerInfo);
    ok(version != NULL, "Couldn't allocate memory to run tests properly!\n");

    majorV = (int)( FileVersionMS >> 16 ) & 0xffff;
    minorV = (int)( FileVersionMS >>  0 ) & 0xffff;
    buildV = (int)( FileVersionLS >> 16 ) & 0xffff;
    revisV = (int)( FileVersionLS >>  0 ) & 0xffff;

    sprintf(version, "%d.%d.%d.%d\n",majorV,minorV,buildV,revisV);

    ok(verInfo->cbStruct == sizeof(CABINETDLLVERSIONINFO), "Size of cabinet version structure incorrect: Error = %ld.\n", GetLastError());
    ok(strcmp(version,"") != 0, "Cabinet struct doesn't contain correct version: Error = %ld.\n", GetLastError());
}


static void test_getdll(HMODULE libHandle)
{
    f_getdll GetDllVersion = (f_getdll)GetProcAddress(libHandle, "GetDllVersion");
    ok(libHandle != NULL, "Function GetDllVersion in DLL not found: Error = %ld.\n", GetLastError());
    ok(strcmp(GetDllVersion(),"") != 0, "GetDllVersion doesn't return correct version: Error = %ld.\n", GetLastError());
}

START_TEST(version)
{
    HMODULE libHandle;
    libHandle = LoadLibraryA("Cabinet.dll");
    ok(libHandle != NULL, "Cabinet.dll not found: Error = %ld.\n", GetLastError());
    test_dllget(libHandle);
    test_getdll(libHandle);
}
