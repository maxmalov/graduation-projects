#include <windows.h>
#include <iostream>
#include <conio.h>
using namespace std;

typedef int (__cdecl*FUNC_GET)();
typedef void (__cdecl*FUNC_SET)(int);

void main()
{
	HMODULE hLib = LoadLibrary(L"mydll");

	if(!hLib) return;

	FUNC_GET GetGInt = (FUNC_GET)GetProcAddress( hLib, "GetGI" );
	FUNC_SET SetGInt = (FUNC_SET)GetProcAddress( hLib, "SetGI" );

	char ans;
	do{
		cout<< " 1. See param. " << endl; 
		cout<< " 2. Set param. " << endl;
		cout<< " 0. Exit. " << endl; 

		switch(ans = _getch())
		{
		case '1':
			{
				__declspec(dllimport) int c = GetGInt();
				cout<< c << endl;
				break;
			}
		case '2':
			{
				int tmp;
				cout << "Input: "; cin>>tmp;
				SetGInt(tmp);
				break;
			}
		}
	}while(ans!='0');

	FreeLibrary(hLib);

}