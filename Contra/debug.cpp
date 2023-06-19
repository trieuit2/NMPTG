#include <Windows.h>
#include "debug.h"

HWND _hwnd = NULL;

void MemCheckStart()
{
	if (MEMCHECK) _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void MemCheckRp()
{
	if (MEMCHECK) _CrtDumpMemoryLeaks();
}

void DebugOut(const wchar_t* fmt, ...)
{
	if (DEBUGOUT==false)
		return;
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}

void DebugOutTitle(const wchar_t* fmt, ...)
{
	wchar_t s[1024];
	VA_PRINTS(s);
	SetWindowText(_hwnd, s);
}

void SetDebugWindow(HWND hwnd)
{
	_hwnd = hwnd;
}