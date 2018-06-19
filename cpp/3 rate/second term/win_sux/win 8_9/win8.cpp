#include <windows.h>
#include <process.h>
#include <iostream>
#include <fstream>
using namespace std;

HANDLE hSemWritten, hSemRead, hEvent;
int g_book = 0;

ofstream out("test.txt");

CRITICAL_SECTION g_cs;

UINT WINAPI Writer(LPVOID lpv )
{
	int wbook = 0;
	for(;;)
	{
		wbook++;

		WaitForSingleObject(hSemRead, INFINITE);

		if( WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0 )
			return 0;

		g_book = wbook;
		
		EnterCriticalSection(&g_cs);
		out<<wbook<<" writer ";
		LeaveCriticalSection(&g_cs);
		
		ReleaseSemaphore(hSemWritten, 1, NULL);

	}
	return 0;
}
UINT WINAPI Reader(LPVOID lpv )
{
	int rbook;
	for(;;)
	{
		WaitForSingleObject(hSemWritten, INFINITE);
		
		rbook = g_book;
		
		if(rbook == 25)
		{
			SetEvent(hEvent);
			
			EnterCriticalSection(&g_cs);
			out << rbook << "reader " <<endl;
			LeaveCriticalSection(&g_cs);
			
			ReleaseSemaphore(hSemRead, 1, 0);
			return 0;
		}

		EnterCriticalSection(&g_cs);
		out << rbook << "reader " <<endl;
		LeaveCriticalSection(&g_cs);		

		ReleaseSemaphore(hSemRead, 1, 0);
	}
	return 0;
}

void main()
{
	HANDLE hMutex = CreateMutex(0, FALSE, "{3437E360-33A3-4338-B045-A84C02802DA5}" );
	if(hMutex == 0) return;

	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		return;
	}

	hSemWritten = CreateSemaphore(0, 0, 1, 0);
	hSemRead = CreateSemaphore(0, 1, 1, 0);
	hEvent = CreateEvent(0, false, false, 0);
	
	HANDLE hThread[2];

	InitializeCriticalSection(&g_cs);

	hThread[0] = (HANDLE)_beginthreadex(0, 0, Writer, 0, 0, 0);
	hThread[1] = (HANDLE)_beginthreadex(0, 0, Reader, 0, 0, 0);

	if( WaitForMultipleObjects( 2, hThread, true, INFINITE) == WAIT_OBJECT_0 )
	{
		CloseHandle(hSemWritten);
		CloseHandle(hSemRead);
		CloseHandle(hThread[0]);
		CloseHandle(hThread[1]);
		CloseHandle(hEvent);
	}
	
	DeleteCriticalSection(&g_cs);

	CloseHandle(hMutex);
}