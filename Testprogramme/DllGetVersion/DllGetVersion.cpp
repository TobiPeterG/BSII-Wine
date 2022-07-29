#include <windows.h>
#include <stdio.h>

typedef struct _CABINETDLLVERSIONINFO{
  DWORD cbStruct;
  DWORD dwReserved1;
  DWORD dwReserved2;
  DWORD dwFileVersionMS;
  DWORD dwFileVersionLS;
} CABINETDLLVERSIONINFO, *PCABINETDLLVERSIONINFO;
typedef LPCSTR (__stdcall *f_funct)(PCABINETDLLVERSIONINFO);

int main(int argc, char * argv[])
{
    HMODULE libHandle;
    libHandle = LoadLibrary(TEXT("Cabinet.dll"));

    if (libHandle == NULL)
    {
        printf("Loading DLL failed. Are you sure about the name?\n");
        return 1;
    }

    f_funct DllGetVersion = (f_funct)GetProcAddress(libHandle, "DllGetVersion");
    if (libHandle == NULL)
    {
        printf("Function in DLL not found. Are you sure about the name?\n");
        return 1;
    }
    PCABINETDLLVERSIONINFO VerInfo;
    char                *version;

    VerInfo = (PCABINETDLLVERSIONINFO)malloc(sizeof(CABINETDLLVERSIONINFO));
    DllGetVersion(VerInfo);
    // Doesn't matter if you are on 32 bit or 64 bit,
    // DWORD is always 32 bits, so first two revision numbers
    // come from dwFileVersionMS, last two come from dwFileVersionLS
    version = (char*)malloc(sizeof((int)( VerInfo->dwFileVersionMS >> 16 ) & 0xffff)+sizeof((int)( VerInfo->dwFileVersionMS >>  0 ) & 0xffff)+sizeof((int)( VerInfo->dwFileVersionLS >> 16 ) & 0xffff)+sizeof((int)( VerInfo->dwFileVersionLS >>  0 ) & 0xffff));
    sprintf(version, "%d.%d.%d.%d\n",
    (int)( VerInfo->dwFileVersionMS >> 16 ) & 0xffff,
    (int)( VerInfo->dwFileVersionMS >>  0 ) & 0xffff,
    (int)( VerInfo->dwFileVersionLS >> 16 ) & 0xffff,
    (int)( VerInfo->dwFileVersionLS >>  0 ) & 0xffff);
    printf("%s\n",version);
    
    FreeLibrary(libHandle);
    return 0;
}