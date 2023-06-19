#pragma once

#include <windows.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>
#include"STL_storage.h"
#include <fstream>
#define DEBUGOUT true
#define MEMCHECK false
#define RENDER_HITBOX true
#define _W(x)  __W(x)
#define __W(x)  L##x

#define VA_PRINTS(s) {				\
		va_list argp;				\
		va_start(argp, fmt);		\
		vswprintf_s(s, fmt, argp);	\
		va_end(argp);				\
}
void MemCheckStart();
void MemCheckRp();
void DebugOut(const wchar_t* fmt, ...);
void DebugOutTitle(const wchar_t* fmt, ...);
void SetDebugWindow(HWND hwnd);