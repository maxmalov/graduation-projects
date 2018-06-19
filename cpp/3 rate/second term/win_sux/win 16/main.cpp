#include<windows.h>
#include<iostream>
#include<tchar.h>
#include<list>
using namespace std;

int dir_s(LPCTSTR szDirName)
{
	TCHAR szBuf[MAX_PATH + 1], szCurDirName[MAX_PATH + 1];
	HANDLE hFindFile;
	WIN32_FIND_DATA wfd;
	SYSTEMTIME st;
	list<LPCTSTR> lDirList;
	DWORD nFiles = 0, nBytes = 0;

	_tcscpy(szBuf, szDirName);
	_tcscat(szBuf, TEXT("\\*.*"));
	
	hFindFile = FindFirstFile(szBuf, &wfd);
	if(hFindFile == INVALID_HANDLE_VALUE)
		return 0;

	_tcscpy(szCurDirName, szDirName);
	_tprintf(TEXT("%s:\n"), szCurDirName);

	BOOL b = TRUE;
	while(b)
	{
		FileTimeToSystemTime(&wfd.ftLastWriteTime, &st);
		_tprintf(TEXT("%d.%d.%d\t%d:%d\t\t"), st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute);
		if(wfd.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
		{
			if(_tcscmp(wfd.cFileName, TEXT(".")) && _tcscmp(wfd.cFileName, TEXT("..")))
			{
				_tcscpy(szBuf, wfd.cFileName);
				lDirList.push_back(szBuf);
			}
			_tprintf(TEXT("<DIR>\t\t"));
		}
		else
		{
			_tprintf(TEXT("\t%d\t"), wfd.nFileSizeLow);
			nFiles ++;
			nBytes += wfd.nFileSizeLow;
		}
		_tprintf(TEXT("%s\n"), wfd.cFileName);
		b = FindNextFile(hFindFile, &wfd);
	}
	_tprintf(TEXT("\t%d files\t\t%d bytes\n"), nFiles, nBytes);
	_tprintf(TEXT("\n\n"));

	for(list<LPCTSTR>::iterator it = lDirList.begin(); it != lDirList.end(); it++)	
	{
		_tprintf(*it);
		_tprintf(TEXT("\n"));
		_tcscpy(szCurDirName, szDirName);
		_tcscat(szCurDirName, TEXT("\\"));
		_tcscat(szCurDirName, *it);
		dir_s(szCurDirName);
	}
	return 0;
}

int main()
{
	int i = 1;
	++i++;
	//cout<<1,2,3,4,5;
	cout<< i;
	dir_s(TEXT("D:\\test"));
	return 0;
}

