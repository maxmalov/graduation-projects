#pragma once

#include "BlocksFacade.h"
#include "crc32.h"
#include <list>
#include <tchar.h>
using namespace std;

#define MOTIONLIST_ERROR_REDO		1
#define MOTIONLIST_ERROR_UNDO		2
#define MOTIONLIST_ERROR_SAVE		3
#define MOTIONLIST_ERROR_SAVEAS		4
#define MOTIONLIST_ERROR_LOAD		5


struct MotionListInfoFileHeader
{
	int cbSize;				//struct size
	int cbFileSize;			//file size
	int cbMoves;			//moves done
	unsigned long crc32;	//crc32 sum

	bool fIsFinished;
	char unused[3];
	int cbCurrentMove;
};

struct MotionListEx
{
	int errCode;
	MotionListEx(int n)
	{
		errCode = n; 
	}
};

struct CBlocksFactoryInfo
{
	CBlocksFactoryState cbfs;
	MOVE prevMove;

	CBlocksFactoryInfo(): cbfs(), prevMove()
	{
	}
};

class MotionList
{
	//list <CBlocksFactoryState> steps;
	//list <CBlocksFactoryState>::iterator current;
	list <CBlocksFactoryInfo> steps;
	list <CBlocksFactoryInfo>::iterator current;
	bool fIsFinished;

protected:
	
	MotionList (const MotionList& );
	int CurrentPosition()
	{
		int i = 0;
		for(list <CBlocksFactoryInfo>::iterator it = steps.begin(); it != current; it++)
			i++;
		return i;
	}

public:

	MotionList ()
	{
		steps.push_front(CBlocksFactoryInfo()); 
		current = steps.begin();
		fIsFinished = false;
	}

	~MotionList ()
	{
	}

	bool Save (LPCTSTR lpszSaveFileName)
	{
		int cFileSize = sizeof(MotionListInfoFileHeader) + steps.size() * sizeof(CBlocksFactoryInfo);

		HANDLE hFile = CreateFile(lpszSaveFileName, GENERIC_READ | GENERIC_WRITE, 0,
			0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		HANDLE hMapping = CreateFileMapping(hFile, 0, PAGE_READWRITE, 0, cFileSize, 0);

		BYTE *pbData = (BYTE*)MapViewOfFile(hMapping, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, cFileSize);

		MotionListInfoFileHeader* mlifh = (MotionListInfoFileHeader*)pbData;
		mlifh->cbSize = sizeof(MotionListInfoFileHeader);
		mlifh->cbFileSize = cFileSize;
		mlifh->cbMoves = steps.size();
		mlifh->fIsFinished = IsFinished();
		mlifh->cbCurrentMove = CurrentPosition();

		CBlocksFactoryInfo* cbfi = (CBlocksFactoryInfo*)(pbData + sizeof(MotionListInfoFileHeader));

		int i = 0;
		for(list <CBlocksFactoryInfo>::iterator it = steps.begin(); i < steps.size(); it++, i++)
		{
			*cbfi = *it;
			cbfi++;
		}
				
		mlifh->crc32 = Crc32((BYTE*)(pbData + sizeof(MotionListInfoFileHeader)), 
			mlifh->cbFileSize - mlifh->cbSize);
		
		UnmapViewOfFile(pbData);
		CloseHandle(hMapping);

		SetFilePointer(hFile, cFileSize, NULL, FILE_BEGIN); 
		SetEndOfFile(hFile);
		CloseHandle(hFile);
		return true;
	}

	bool Load (LPCTSTR lpszSaveFileName)
	{
		HANDLE hFile = CreateFile(lpszSaveFileName, GENERIC_READ | GENERIC_WRITE, 0, 
			0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		
		if(hFile == INVALID_HANDLE_VALUE)
			return false;
		
		DWORD dwFileSize= GetFileSize(hFile, 0);
		if(dwFileSize == 0)
			return false;

		HANDLE hMapping = CreateFileMapping(hFile, 0, PAGE_READWRITE, 0, dwFileSize, 0);
		
		BYTE *pbData = (BYTE*)MapViewOfFile(hMapping, FILE_MAP_WRITE | FILE_MAP_READ, 
			0, 0, dwFileSize);
		
		MotionListInfoFileHeader* mlifh = (MotionListInfoFileHeader*)pbData;
		if( (mlifh->cbSize != sizeof(MotionListInfoFileHeader)) || 
			(mlifh->cbFileSize != dwFileSize) ||
			(Crc32((BYTE*)(pbData + mlifh->cbSize), mlifh->cbFileSize - mlifh->cbSize) != mlifh->crc32) )
		{
			UnmapViewOfFile(pbData);
			CloseHandle(hMapping);
			CloseHandle(hFile);
			return false;
		}

		fIsFinished = mlifh->fIsFinished;

		CBlocksFactoryInfo* cbfi = (CBlocksFactoryInfo*)(pbData + sizeof(MotionListInfoFileHeader));

		steps.clear();
		for(int i = 0; i < mlifh->cbMoves; i++)
		{
			steps.push_back(*cbfi);
			cbfi++;
		}

		current = steps.begin();
		for(int i = 0; i < mlifh->cbCurrentMove; i++, current++ );
		
		UnmapViewOfFile(pbData);
		CloseHandle(hMapping);
		CloseHandle(hFile);
		return true;
	}

	CBlocksFactoryState Undo ()
	{
		list <CBlocksFactoryInfo>::iterator back = steps.end();
		back--;
		if(current == back) throw MotionListEx(MOTIONLIST_ERROR_UNDO);
		current++;
		if(fIsFinished) fIsFinished = false;
		return current->cbfs;
	}
	CBlocksFactoryState Redo ()
	{
		if(current == steps.begin()) throw MotionListEx(MOTIONLIST_ERROR_REDO);
		current--;
		if(current->cbfs.BlockPositions[1] == 13) fIsFinished = true;
		return current->cbfs;
	}

	
	void Run (const CBlocksFactoryState& cbfs, const MOVE* mv)
	{
		CBlocksFactoryInfo cbfi;
		cbfi.cbfs = cbfs;
		cbfi.prevMove = *mv;

		if(current == steps.begin())
		{
			steps.push_front(cbfi);
			current--;
			if(current->cbfs.BlockPositions[1] == 13) fIsFinished = true;
			else fIsFinished = false;
			return;
		}

		steps.erase( steps.begin(), current--);
		steps.push_front(cbfi);
		current = steps.begin();

		if(current->cbfs.BlockPositions[1] == 13) fIsFinished = true;
		fIsFinished = false;
	}

	CBlocksFactoryState CurrentState()
	{
		return current->cbfs;
	}

	void NewGame()
	{
		steps.clear();
		steps.push_front(CBlocksFactoryInfo());
		current = steps.begin();

		fIsFinished = false;
	}
	
	bool IsFinished()
	{
		return fIsFinished;
	}

	const CString GetMoveString(int ind)
	{
		list <CBlocksFactoryInfo>::iterator tmp = steps.end();
		for(int i = -1; i < ind; ++i)
			tmp--;
		return tmp->prevMove.ToString();
	}

	int MovesCount()
	{
		int i = 0;
		for(list <CBlocksFactoryInfo>::iterator it = steps.end(); it != current; it--)
			i++;
		return i;
	}
};