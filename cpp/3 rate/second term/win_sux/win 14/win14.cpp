#include <windows.h>
#include <iostream>

using namespace std;

int main()
{
	DWORD dwDrives = GetLogicalDrives();
	ULARGE_INTEGER dwFreeBytes, dwTotalBytes;
	DWORD dwSerialNumber;
	TCHAR _tVolumeName[100], _tFileSystem[100];
	MEMORYSTATUSEX ms;
	ms.dwLength = sizeof(MEMORYSTATUSEX);
	if(dwDrives & 1<<3)
	{
		GetDiskFreeSpaceEx("D:\\", NULL, &dwTotalBytes, &dwFreeBytes);
		GetVolumeInformation("D:\\", _tVolumeName, 100, &dwSerialNumber,
			NULL, NULL, _tFileSystem, 100);
		GlobalMemoryStatusEx(&ms);
		cout << "--------------- Disk D:" << " (" << _tFileSystem << ") ---------------\n";
		cout << "Total bytes: " << dwTotalBytes.QuadPart << endl;
		cout << "Free bytes: " << dwFreeBytes.QuadPart << endl;
		cout << "Volume label: " << _tVolumeName<< endl;
		cout << "Serial number: " << dwSerialNumber << endl;
		cout << "-------------------- Memory -------------------\n";
		cout << "Memory load: " << ms.dwMemoryLoad << " %\n";
		cout << "Total memory: " << ms.ullTotalPhys << endl;
		cout << "Free memory: " << ms.ullAvailPhys << endl;
		cout << "Total virtual: " << ms.ullTotalVirtual << endl;
		cout << "Free virtual: " << ms.ullAvailVirtual << endl;
		cout << "-----------------------------------------------\n";
	}
	 
	return 0;
}