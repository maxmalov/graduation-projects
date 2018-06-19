// DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

__declspec(dllexport) int Mult(int x, int y)
{
	return x*y;
}

#pragma data_seg("SharedSection")

__declspec(dllexport) int g_n = 0;

#pragma data_seg()