@ stdcall GetDllVersion()
@ stdcall -private DllGetVersion (ptr)
@ stdcall Extract(ptr str)
@ stub DeleteExtractedFiles
@ cdecl FCICreate(ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr ptr)
@ cdecl FCIAddFile(long ptr ptr long ptr ptr ptr long)
@ cdecl FCIFlushFolder(long ptr ptr)
@ cdecl FCIFlushCabinet(long long ptr ptr)
@ cdecl FCIDestroy(long)
@ cdecl FDICreate(ptr ptr ptr ptr ptr ptr ptr long ptr)
@ cdecl FDIIsCabinet(long long ptr)
@ cdecl FDICopy(long ptr ptr long ptr ptr ptr)
@ cdecl FDIDestroy(long)
@ cdecl FDITruncateCabinet(long ptr long)
@ stdcall -import GetFileVersionInfoA(str long long ptr)
@ stdcall -import GetFileVersionInfoSizeA(str ptr)
@ stdcall -import VerQueryValueA(ptr str ptr ptr)
