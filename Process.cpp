

#include <iostream>
#include "Process.h"
#include<tlhelp32.h>


Process::Process()
{
	_procName =  L"ac_client.exe";;
	_modName = L"ac_client.exe";


	getProcessId();
	getModuleBaseAddress();
	openProcess();
}


void Process::getProcessId()
{
	DWORD procId = NULL;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		if (Process32First(hSnap, &procEntry))
		{
			do
			{
				if (!_wcsicmp(_procName, procEntry.szExeFile))
				{
					procId = procEntry.th32ProcessID;
					break;
				}

			} while (Process32Next(hSnap, &procEntry));
		}
	}
	CloseHandle(hSnap);
	_procId = procId;
}

void Process::getModuleBaseAddress()
{
	
	uintptr_t modBaseAddr = NULL;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _procId);
	MODULEENTRY32 modEntry;
	modEntry.dwSize = sizeof(MODULEENTRY32);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!_wcsicmp(_modName, modEntry.szModule))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}

			} while (Module32Next(hSnap, &modEntry));
		}
	}
	
	CloseHandle(hSnap);
	_mainModulePtr = modBaseAddr;
}

void Process::openProcess()
{
	_hProc = OpenProcess(PROCESS_ALL_ACCESS, false, _procId);
		
}

void Process::printhProc()
{
	std::cout << "printing hProc:" <<std::hex<<_hProc << std::endl;
}



bool Process::writeMemory(uintptr_t addr, void* buffer, unsigned int size)
{

	return WriteProcessMemory(_hProc, (LPVOID)addr, (LPCVOID)buffer, size, NULL);
}


bool Process::readMemory(uintptr_t addr, void* buffer, unsigned int size)
{
	return ReadProcessMemory(_hProc, (LPCVOID)addr, (LPVOID)buffer, size, NULL);
}



uintptr_t Process::FindDynamicAddr2(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets)
{
	uintptr_t dynamicAddr = ptr;
	for (unsigned int i = 0; i < offsets.size(); i++)
	{

		ReadProcessMemory(hProc, (LPVOID)dynamicAddr, &dynamicAddr, sizeof(dynamicAddr), 0);

		dynamicAddr += offsets[i];


	}
	return dynamicAddr;

}


uintptr_t Process::FindDynamicAddr(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets)
{
	uintptr_t dynamicAddr = ptr;
	for (unsigned int i = 0; i < offsets.size() - 1; i++)
	{
		dynamicAddr += offsets[i];
		ReadProcessMemory(hProc, (LPVOID)dynamicAddr, &dynamicAddr, sizeof(dynamicAddr), 0);

	}
	dynamicAddr += offsets.back();
	return dynamicAddr;

}



void Process::PatchEx(HANDLE hProc, LPVOID Addr, LPCVOID buffer, SIZE_T size)
{
	DWORD dwOldProtect;
	VirtualProtectEx(hProc, Addr, size, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	WriteProcessMemory(hProc, Addr, buffer, size, 0);
	VirtualProtectEx(hProc, Addr, size, dwOldProtect, &dwOldProtect);
}


void Process::NopEx(HANDLE hProc, LPVOID Addr, SIZE_T size)
{
	BYTE* nopArray = new BYTE[size];
	memset(nopArray, 0x90, size);
	PatchEx(hProc, Addr, nopArray, size);
	delete[] nopArray;
}


uintptr_t Process::getMainModuleAddr()
{
	printhProc();
	return _mainModulePtr;
}
