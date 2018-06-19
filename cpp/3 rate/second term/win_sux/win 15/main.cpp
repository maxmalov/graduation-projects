#include <windows.h>
#include <iostream>
using namespace std;
int main()
{
    HANDLE hEvents[2];
    hEvents[0] = CreateEvent(NULL, TRUE, FALSE, 0);               
    hEvents[1] = CreateEvent(NULL, TRUE, FALSE, 0);              

    const int nSize = 1024;
	char buf1[nSize], buf2[nSize];
	for(int i = 0; i < nSize - 1; i++)
	{
		buf1[i] = '1';
		buf2[i] = '2';
	}
    buf1[nSize - 1] = 0;
    buf2[nSize - 1] = 0;

	HANDLE hFileOut = CreateFile(L"out.txt", GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, 0);

    OVERLAPPED ov1, ov2;
    ov1.hEvent = hEvents[0];
    ov2.hEvent = hEvents[1];
    ov1.OffsetHigh = ov1.Offset = 0;
    ov2.OffsetHigh =0;
    ov2.Offset = nSize;
    
    WriteFile(hFileOut, buf1, nSize, 0, &ov1);
    WriteFile(hFileOut, buf2, nSize, 0, &ov2);

    while(WaitForMultipleObjects(2, hEvents, TRUE, INFINITE) != WAIT_OBJECT_0)
         cout<<".";
    
	SetFilePointer(hFileOut, nSize*2, 0, FILE_BEGIN);
    SetEndOfFile(hFileOut);
    
    ov1.OffsetHigh = ov1.Offset = 0;
    ov2.OffsetHigh = 0;
    ov2.Offset = nSize;
    
	ResetEvent(hEvents[0]);
    ResetEvent(hEvents[1]);

    ReadFile(hFileOut, buf2, nSize, 0, &ov1);
    ReadFile(hFileOut, buf1, nSize, 0, &ov2);
    while(WaitForMultipleObjects(2, hEvents, TRUE, 0) != WAIT_OBJECT_0)
         cout<<".";
    
	CloseHandle(hEvents[0]);
    CloseHandle(hEvents[1]);
    CloseHandle(hFileOut);
    
	return 0;
}