// haki.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "memproc.h"
#include <Windows.h>

enum returnValues
{
    RET_OK,
    RET_NOT_OK,
};

bool writeMemory(HANDLE handle, uintptr_t addr, void* buffer, unsigned int size)
{
    return WriteProcessMemory(handle, (LPVOID)addr, (LPCVOID)buffer, size, NULL);
}


bool readMemory(HANDLE handle, uintptr_t addr, void* buffer, unsigned int size)
{
    return ReadProcessMemory(handle, (LPCVOID)addr, (LPVOID)buffer, size, NULL);
}

int main()
{
    DWORD ProcId = NULL;
    uintptr_t moduleAddr = NULL;
    const wchar_t* procName = L"ac_client.exe";
    HANDLE hProc = NULL;
    int health = 2000;
    uintptr_t healthAddr = NULL;
    uintptr_t playerBasePtrAddr = 0x17E0A8;
    std::vector<unsigned int> healthOffsets{ 0xEC };
    uintptr_t temp = NULL;


    ProcId = GetProcessId(procName);
    if (NULL != ProcId)
    {
        std::cout << "Process ID retrieved: " << ProcId << std::endl;
        hProc = OpenProcess(PROCESS_ALL_ACCESS, false, ProcId);
        moduleAddr = GetModuleBaseAddress(ProcId, procName);
    }
    if (NULL != moduleAddr && NULL != hProc)
    {
        
        healthAddr = FindDynamicAddr2(hProc, moduleAddr + playerBasePtrAddr, healthOffsets);
        writeMemory(hProc, healthAddr, &health, sizeof(health));
    }

  


    

    std::cout << "Hello World!\n";
}

