//B-14
//	Реализовать объект "Очередь в магазине"
//  Каждый человек имеет имя, фамилию, возможно льготы или детей 
//Автор: Малов Максим МП-703

#include<windows.h>
#include<process.h>
#include<iostream>
#include<time.h>
using namespace std;
#include"queue.h"

_queue g_queue;

DWORD WINAPI FirstThread(LPVOID lpV)
{
	srand(time(0));
	elem* _man = 0;
	for( char i = 'a'; i < 'e'; ++i )
	{
		_man = (elem*)new man("aaa","bbb");	
		Sleep(rand()%1000);
		g_queue.push(_man);
		//cout<<g_queue<<endl;
		delete _man;
	}
	return 0;
}
DWORD WINAPI SecondThread(LPVOID lpV)
{
	for(int i = 0; i < 5; ++i )
	{
		g_queue.pop();
		//cout<<g_queue<<endl;
	}
	return 0;
}
void main()
{
	HANDLE hThread[2];

	hThread[1] = (HANDLE)_beginthreadex(0,0, (unsigned int (__stdcall *)(void *)) SecondThread, 0, 0, 0);

	hThread[0] = (HANDLE)_beginthreadex(0,0, (unsigned int (__stdcall *)(void *)) FirstThread, 0, 0, 0);

	if( WaitForMultipleObjects(2,hThread,TRUE,INFINITE) == WAIT_OBJECT_0 )
	{
		CloseHandle(hThread[0]);
		CloseHandle(hThread[1]);
		cout<<g_queue;
	}

}