#include "includes.h"

int main()
{
	DWORD proc_id = NULL;
	char dll_path[MAX_PATH];
	const char* dll_name = "Dll1.dll";
	const char* wndName = "osu!";

	if (!fileexists(dll_name))
	{
		error("fileexists", "File doesnt exist");
	}

	if (!GetFullPathName(dll_name, MAX_PATH, dll_path, nullptr))
	{
		error("GetFullPathName", "Cant get the full path");
	}

	getprocId(wndName, proc_id);
	if (proc_id == NULL)
	{
		error("getprocId", "Cant get process ID");
	}

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, proc_id);
	if (!hProc)
	{
		error("OpenProcess", "Cant open process");
	}

	void* alloc_mem = VirtualAllocEx(hProc, nullptr, MAX_PATH, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	if (!alloc_mem)
	{
		error("VirtualAllocEx", "Cant allocate memory");
	}

	if (!WriteProcessMemory(hProc, nullptr, dll_path, MAX_PATH, nullptr))
	{
		error("WriteProcessMemory", "Cant write memory");
	}

	HANDLE hThread = CreateRemoteThread(hProc, nullptr, NULL, LPTHREAD_START_ROUTINE(LoadLibraryA), alloc_mem, NULL, nullptr);
	if (!hThread)
	{
		error("CreateRemoteThread", "Cant create remote thread");
	}

	CloseHandle(hProc);
	VirtualFreeEx(hProc, alloc_mem, NULL, MEM_RELEASE);
	MessageBox(NULL, "Successfully injected DLL", "Success", NULL);
}