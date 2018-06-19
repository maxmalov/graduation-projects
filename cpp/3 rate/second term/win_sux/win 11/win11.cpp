#include <windows.h>
#include <iostream>
#include <process.h>

HANDLE hEvent;
int g_buf;

UINT WINAPI Thread1(PVOID pParams)
{
	WaitForSingleObject(hEvent, INFINITE);
	for(int i = 0; i < 10; i++)
		g_buf++;
	SetEvent(hEvent);
	return 0;
}

UINT WINAPI Thread2(PVOID pParams)
{
	WaitForSingleObject(hEvent, INFINITE);
	for(int i = 0; i < 4; i++)
		g_buf--;;
	SetEvent(hEvent);
	return 0;
}

int main()
{
	HANDLE hThread[2];
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	hThread[0] = (HANDLE) _beginthreadex(NULL, 0, Thread1, NULL, CREATE_SUSPENDED, NULL);
	hThread[1] = (HANDLE) _beginthreadex(NULL, 0, Thread2, NULL, CREATE_SUSPENDED, NULL);
	
	SetThreadPriority(hThread[0], THREAD_PRIORITY_TIME_CRITICAL);
	SetThreadPriority(hThread[1], THREAD_PRIORITY_IDLE);
	
	ResumeThread(hThread[0]);
	ResumeThread(hThread[1]);
	
	SetEvent(hEvent);

	if( WaitForMultipleObjects(2, hThread, TRUE, INFINITE) == WAIT_OBJECT_0 )
	{
		CloseHandle(hThread[0]);
		CloseHandle(hThread[1]);
	}
	return 0;
}