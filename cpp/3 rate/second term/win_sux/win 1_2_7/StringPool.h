#pragma once
#include <windows.h>
#include<conio.h>
#include<tchar.h>

#define MAX_POOLSIZE	0x10000000  // 256 mb
#define MAX_STRINGSIZE	0x00004000	// 16kb
#define MAX_STRINGQUAN	0x08000000	// in a bad case when all strings are about 2 bytes
#define BYTE_PORTION	0x00010000	// 64kb

class StringPool
{
	TCHAR* _tpStrData;
	TCHAR** _tpDataArray;

	int nByteCommited, nByteArrayCommited,
		nCurSize;

	struct exBadIndex{};

public:
	
	StringPool (): nCurSize(0), nByteCommited(0), nByteArrayCommited(0)
	{
		_tpStrData = (TCHAR*)VirtualAlloc(0, MAX_POOLSIZE, MEM_RESERVE, PAGE_READWRITE );
		if( !_tpStrData) throw;
	    
		_tpDataArray = (TCHAR**)VirtualAlloc(0, sizeof(TCHAR*)*MAX_STRINGQUAN, 
			MEM_RESERVE, PAGE_READWRITE ); 
		
		if( !_tpDataArray )
		{
			VirtualFree ( _tpStrData, 0, MEM_RELEASE );
			throw;
		}
									
		VirtualAlloc(_tpDataArray, BYTE_PORTION, MEM_COMMIT, PAGE_READWRITE);
		nByteArrayCommited = BYTE_PORTION;
		_tpDataArray[0] = _tpStrData;
		
	}

	~StringPool()
	{
		VirtualFree ( _tpStrData, 0, MEM_RELEASE );
		VirtualFree ( _tpDataArray, 0, MEM_RELEASE );
	}

	bool Add ( TCHAR* _tpStr )
	{
		int nSize = (_tcslen(_tpStr) + 1) * sizeof(TCHAR);
		 
		if ( nSize > MAX_STRINGSIZE || nCurSize == MAX_STRINGQUAN-1 )
			return false;
		 
		//Data commit
		if( (int)_tpStrData + (int)nByteCommited - (int)_tpDataArray[nCurSize] - 2 < nSize)
		{
			if(nByteCommited + BYTE_PORTION > MAX_POOLSIZE)
			   return false;
			nByteCommited += BYTE_PORTION;
			VirtualAlloc(_tpStrData, nByteCommited, MEM_COMMIT, PAGE_READWRITE);
		}

		//Array commit
		if((nCurSize + 1)%(BYTE_PORTION/sizeof(TCHAR*)) == 0)
		{
			nByteArrayCommited += BYTE_PORTION;
			VirtualAlloc(_tpDataArray, nByteArrayCommited, MEM_COMMIT, PAGE_READWRITE);
		}

		_tcscpy(_tpDataArray[nCurSize], _tpStr);
		nCurSize++;
		_tpDataArray[nCurSize] = (TCHAR*)((int)(_tpDataArray[nCurSize - 1]) + nSize);
		_tpDataArray[nCurSize][0] = 0;
		return true;
	}

	const TCHAR* operator [] (int n)	const
	{
		if( -1 < n < nCurSize ) return _tpDataArray[ n ];
		throw exBadIndex();
	}

	int Size()
	{
		return nCurSize;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class StringPoolMMF
{			
	TCHAR* _tpStrData;
	int* pDataOffsets;

	int nCount;
	
	HANDLE hMutex;

	HANDLE hFilePool, hMappingPool,
		hFileOffsets, hMappingOffsets;

	int nPoolBytesFlush, nOffsetsBytesFlush;
	
	struct exBadIndex {};
	struct exMissingFile {};

	void SyncPool(int nSize)
	{
		UnmapViewOfFile(_tpStrData);
		UnmapViewOfFile(pDataOffsets);

		DWORD dwFileSizeOffsets = (nCount + 2) * 4, dwFileSizePool; 

		nOffsetsBytesFlush = min (dwFileSizeOffsets + BYTE_PORTION, MAX_STRINGQUAN * 4);
		
		pDataOffsets = (int*)MapViewOfFile(hMappingOffsets, FILE_MAP_ALL_ACCESS, 0, 0,
			nOffsetsBytesFlush);
		if(!pDataOffsets) throw exMissingFile();
		
		nCount = pDataOffsets[0];

		dwFileSizePool = pDataOffsets[nCount + 1] + sizeof(TCHAR);
		nPoolBytesFlush = min (dwFileSizePool + BYTE_PORTION, MAX_POOLSIZE);
		
		if(nSize)
		{
			if (nPoolBytesFlush - pDataOffsets[pDataOffsets[0]+1] - 1 < nSize)
			{
				if(nPoolBytesFlush + BYTE_PORTION <= MAX_POOLSIZE)
					nPoolBytesFlush += BYTE_PORTION;
				else throw exMissingFile();
			}
		}
		
		_tpStrData = (TCHAR*)MapViewOfFile(hMappingPool, FILE_MAP_ALL_ACCESS, 0, 0,
				nPoolBytesFlush);
	}

public:

	StringPoolMMF(TCHAR* lpszPoolName, TCHAR* lpszOffsetsName)
	{
		hFilePool = CreateFile(lpszPoolName, GENERIC_READ | GENERIC_WRITE, 0, 
						 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	
		hFileOffsets = CreateFile(lpszOffsetsName, GENERIC_READ | GENERIC_WRITE, 0, 
							 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		
		DWORD dwFileSizePool = GetFileSize(hFilePool, 0), dwFileSizeOffsets = GetFileSize(hFileOffsets, 0);
		
		if((dwFileSizeOffsets > MAX_STRINGQUAN * sizeof(int)) || (dwFileSizePool > MAX_POOLSIZE))
		{
			CloseHandle(hFileOffsets);
			CloseHandle(hFilePool);
			throw exMissingFile();
		}

		hMappingPool = CreateFileMapping(hFilePool, 0, PAGE_READWRITE, 0, MAX_POOLSIZE, 0);
		hMappingOffsets = CreateFileMapping(hFileOffsets, 0, PAGE_READWRITE, 0, 
			MAX_STRINGQUAN * sizeof(int), 0);

		hMutex = CreateMutex(0,true,L"{904240D4-44B8-42b8-9177-FD7688485D87}");
		if( GetLastError() == ERROR_ALREADY_EXISTS )
		{
			WaitForSingleObject(hMutex,INFINITE);
			pDataOffsets = (int*)MapViewOfFile(hMappingOffsets, FILE_MAP_ALL_ACCESS, 
										0, 0, MAX_STRINGQUAN * 4);
			nCount = pDataOffsets[0];
			dwFileSizeOffsets = (nCount + 2) * 4;
			dwFileSizePool = pDataOffsets[nCount + 1] + sizeof(TCHAR);
			UnmapViewOfFile(pDataOffsets);
		}
		else nCount = 0;
		
		if( !dwFileSizePool || !dwFileSizeOffsets )
			nPoolBytesFlush = nOffsetsBytesFlush = BYTE_PORTION;
		else
		{
			nPoolBytesFlush = min( dwFileSizePool + BYTE_PORTION, MAX_POOLSIZE);
			nOffsetsBytesFlush = min( dwFileSizeOffsets + BYTE_PORTION, MAX_STRINGQUAN * sizeof(int));
		}

		_tpStrData = (TCHAR*)MapViewOfFile(hMappingPool, FILE_MAP_ALL_ACCESS, 
										0, 0, nPoolBytesFlush);

		pDataOffsets = (int*)MapViewOfFile(hMappingOffsets, FILE_MAP_ALL_ACCESS, 
										0, 0, nOffsetsBytesFlush);

		if( !_tpStrData || !pDataOffsets )
			throw exMissingFile();

		if( !dwFileSizePool || !dwFileSizeOffsets )
			pDataOffsets[0] = pDataOffsets[1] = 0; 

		ReleaseMutex(hMutex);
	}

	~StringPoolMMF()
	{
		WaitForSingleObject(hMutex,INFINITE);		
		
		DWORD dwFileSizePool = pDataOffsets[pDataOffsets[0] + 1] + 2,
			dwFileSizeOffsets = (pDataOffsets[0] + 2) * sizeof(int);
		
		UnmapViewOfFile(_tpStrData);
		UnmapViewOfFile(pDataOffsets);
		
		CloseHandle(hMappingOffsets);
		CloseHandle(hMappingPool);
		
		SetFilePointer(hFileOffsets, dwFileSizeOffsets, 0, FILE_BEGIN); 
		SetFilePointer(hFilePool, dwFileSizePool, 0, FILE_BEGIN); 
		
		SetEndOfFile(hFileOffsets);
		SetEndOfFile(hFilePool);
		
		CloseHandle(hFileOffsets);
		CloseHandle(hFilePool);

		ReleaseMutex(hMutex);
		CloseHandle(hMutex);
	}
	
	bool Add(TCHAR* _tpStr)
	{
		int nSize = ( _tcslen(_tpStr) + 1) * sizeof(TCHAR);
		if( nSize > MAX_STRINGSIZE ) return false;

		WaitForSingleObject(hMutex,INFINITE);
		if(nCount != pDataOffsets[0])
		{
			try{
				SyncPool(nSize);
				if( pDataOffsets[0] == MAX_STRINGQUAN-2 )
					return false;
			}
			catch( exMissingFile ){
				return false;
			}
		}

		//if( nPoolBytesFlush - pDataOffsets[pDataOffsets[0]+1] - 1 < nSize )
		//{
		//	if(nPoolBytesFlush + BYTE_PORTION > MAX_POOLSIZE)
		//		return false;
		//	nPoolBytesFlush += BYTE_PORTION;
		//	
		//	UnmapViewOfFile(_tpStrData);
		//	_tpStrData = (TCHAR*)MapViewOfFile(hMappingPool, FILE_MAP_ALL_ACCESS, 
		//									0, 0, nPoolBytesFlush);
		//}

		if( (pDataOffsets[0] + 2) % (BYTE_PORTION / 4) == 0)
		{
			nOffsetsBytesFlush += BYTE_PORTION;
			UnmapViewOfFile(pDataOffsets);
			pDataOffsets = (int*)MapViewOfFile(hMappingOffsets, FILE_MAP_ALL_ACCESS, 
											0, 0, nOffsetsBytesFlush);
		}

		_tcscpy((TCHAR*)((int)_tpStrData + pDataOffsets[pDataOffsets[0] + 1]), _tpStr);
		pDataOffsets[0]++;
		pDataOffsets[pDataOffsets[0] + 1] = pDataOffsets[pDataOffsets[0]] + nSize;
		_tpStrData[pDataOffsets[pDataOffsets[0] + 1] / 2] = 0;

		ReleaseMutex(hMutex);
		return true;
	}
	
	TCHAR* operator[](int i)
	{
		WaitForSingleObject(hMutex,INFINITE);
		
		if (nCount != pDataOffsets[0])
			SyncPool(0);
		
		if( -1 < i && i < pDataOffsets[0] )
		{
			ReleaseMutex(hMutex);
			return (TCHAR*)((int)_tpStrData + pDataOffsets[i+1]);
		}
		ReleaseMutex(hMutex);
		throw exBadIndex();
	}
	
	int Size()
	{
		return pDataOffsets[0];
	}
};


