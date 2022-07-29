#include <windows.h>
#include <stdio.h>
typedef LPCSTR (__stdcall *f_funct)(void);

int main(int argc, char * argv[])
{
    HMODULE libHandle;
    libHandle = LoadLibrary(TEXT("Cabinet.dll"));

    if (libHandle == NULL)
    {
        printf("Loading DLL failed. Are you sure about the name?\n");
        return 1;
    }

    f_funct GetDllVersion = (f_funct)GetProcAddress(libHandle, "GetDllVersion");
    if (libHandle == NULL)
    {
        printf("Function in DLL not found. Are you sure about the name?\n");
        return 1;
    }

    LPCSTR CabinetDllVersion = GetDllVersion();
    char str[42];

    //printf("%d\n", sprintf(str, "%d", CabinetDllVersion));
    //printf("%d\n", itoa(CabinetDllVersion, str,16));
    printf("%s\n", CabinetDllVersion);
    FreeLibrary(libHandle);
    return 0;
}
