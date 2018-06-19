#pragma once

#include <windows.h>

extern "C" __declspec(dllexport) int GetGI ( );
extern "C" __declspec(dllexport) void SetGI ( int );

#pragma data_seg ("MySharedSect")
__declspec(dllexport) int g_int = 10;
#pragma data_seg
