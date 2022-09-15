#include "../includes.h"

void getprocId(const char* wndName, DWORD &procId)
{
	GetWindowThreadProcessId(FindWindow(NULL, wndName), &procId);
}