#include <iostream>
#include <windows.h>
#include <conio.h>
#include <tchar.h>
#include<process.h>
using namespace std;

DWORD WINAPI MyThreadFunc(LPVOID lpv)
{
	cout<< "Notepad is closed! " <<endl;
//	_endthreadex(0);

	return 0;
}

void main()
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi; 
	int e = CreateProcess(L"D:\\Windows\\System32\\notepad.exe", 0, 0, 0, FALSE, 0, 0, 0, &si, &pi);

	if(!e) return;

	cout<< "Notepad is opened!" <<endl;
	if( WaitForSingleObject(pi.hProcess, INFINITE ) == WAIT_OBJECT_0 )
	{
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);

		HANDLE hThread = (HANDLE)_beginthreadex(0,0, 
			(unsigned int (__stdcall *)(void *)) MyThreadFunc, 0,0, 0);

		if( WaitForSingleObject(hThread, INFINITE ) == WAIT_OBJECT_0 )
			CloseHandle(hThread);
	}

}