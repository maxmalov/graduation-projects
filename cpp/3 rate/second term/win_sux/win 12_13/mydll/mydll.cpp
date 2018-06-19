#include "mydll.h"

extern "C" __declspec(dllexport) int GetGI ( )
{
	return g_int;
}
extern "C" __declspec(dllexport) void SetGI ( int a )
{
	g_int = a;
}
