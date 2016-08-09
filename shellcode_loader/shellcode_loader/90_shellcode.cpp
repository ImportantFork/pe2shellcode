// 90_shellcode.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "90_shellcode.h"

void import_table()
{
	HMODULE hMod = LoadLibraryA("User32.dll");
	hMod = LoadLibraryA("ADVAPI32.dll");

}

int  main()
{
    LoadLibraryA("User32.dll");
	LoadLibraryA("ADVAPI32.dll");
	LoadLibraryA("WS2_32.dll");

	
    HANDLE hHeap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 1024, 0);
    PVOID pMem = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, 1024 * 1024 * 20);
	ZeroMemory(pMem,  1024 * 1024 * 20);
    pMem = (PVOID)((int)pMem + 16);

	HANDLE hFile = CreateFile(L"shellcode.bin",
		GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	LARGE_INTEGER ll_shellcode_size; 
    GetFileSizeEx(hFile, &ll_shellcode_size);
	DWORD dwRead = 0;
	ReadFile(hFile, (PVOID)((int)pMem+1), ll_shellcode_size.LowPart, &dwRead, NULL);
	memset(pMem, 0xcc, 1);
	CloseHandle(hFile);
	if (dwRead != ll_shellcode_size.LowPart)
		return 0;
    HANDLE hThread0 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pMem, NULL, 0, NULL);
    Sleep(INFINITE);
    return 0;
}
