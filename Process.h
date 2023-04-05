#pragma once
#include <Windows.h>
#include <vector>

class Process {

public:
	Process(const wchar_t* procName, const wchar_t* modName);

	bool writeMemory(uintptr_t addr, void* buffer, unsigned int size);
	bool readMemory(uintptr_t addr, void* buffer, unsigned int size);
	uintptr_t FindDynamicAddr2(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets);
	uintptr_t FindDynamicAddr(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int>offsets);
	void PatchEx(HANDLE hProc, LPVOID Addr, LPCVOID buffer, SIZE_T size);
	void NopEx(HANDLE hProc, LPVOID Addr, SIZE_T size);
	uintptr_t getMainModuleAddr();
	void printhProc();
	
private:
	const wchar_t* _procName;
	const wchar_t* _modName;
	HANDLE _hProc;
	DWORD _procId;
	uintptr_t _mainModulePtr;
	
	
	void getProcessId();
	void getModuleBaseAddress();
	void openProcess();


	





};