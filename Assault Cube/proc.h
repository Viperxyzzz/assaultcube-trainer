#pragma once
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

class Proc {
public:
	static DWORD GetProcId(const wchar_t* proc_name);
	
	static HANDLE GetHandle(DWORD procId);

	uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName);

	uintptr_t FindDMAAddy(HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets);

	void GetProcInfo();

	HANDLE hProcess;
	DWORD ProcId;
};


