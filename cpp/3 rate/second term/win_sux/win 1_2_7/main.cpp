#include "StringPool.h"
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;

void main()
{
	//StringPool sp;
	StringPoolMMF sp(L"pool.txt", L"offsets.txt");

	//TCHAR _tStr [ MAX_STRINGSIZE / sizeof(TCHAR) - 16 ];
	bool b = true;

	//for( char j = 'a'; (j <= 'z') && b; ++j )
	//{
	//	for( int i = 0; i < MAX_STRINGSIZE / sizeof(TCHAR) - 17; ++i )
	//		_tStr[i] = j;
	//	_tStr[MAX_STRINGSIZE / sizeof(TCHAR) - 17] = 0;
	//	b = sp.Add(_tStr);
	//}

	TCHAR _tSmallStr[100];

	for( long int i = 0; i < 50000 && b; ++i )
	{
		for(int j = 0; j < 99; j++ )
			_tSmallStr[j] = '1';
		_tSmallStr[99] = 0;
		b = sp.Add(_tSmallStr);
	}

//	for( int i = 0; i < sp.Size(); ++i )
//		_tprintf(L"%s\n", sp[i]);
}