#include <iostream>
#include <conio.h>
#include <windows.h>
#include "MyDll.h"
using namespace std;

int main()
{
	//static int x,y;
	int action = '0';
	do
	{
		system("cls");
		cout<<"\t 1 - Set value"<<endl;
		cout<<"\t 2 - Get value"<<endl;
		cout<<"\t 3 - Exit"<<endl;
		action = _getch();
		switch(action)
		{
			case '1':
				cout<<"Write value : ";
				cin>>g_n;
				break;
			case '2':
				cout<<"Value: "<<g_n;
				_getch();
				break;
			case '3':
				break;
		}
	}while(action != '3');
	return 0;
}