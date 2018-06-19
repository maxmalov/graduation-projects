#include"all.h"
using namespace std;
int** GetMem(size_t size)
/*
   Функция выделения памяти.
   Входной параметр size - размер таблицы.
   Функция возвращает NULL в случае проблемы с выделением памяти, в противном случае 
   возвращает указатель с выделенной памятью
*/
{
	size_t i;
	int** matrix=NULL;
	if(size<0)
	{
		cerr<<"Memory method: Incorrect size!"; _getch();
		return NULL;
	}
	try
	{
		matrix=new int* [size];
	}
	catch(bad_alloc)
	{
		cerr<<"Memory method: Out of memory!"; _getch();
		return NULL;
	}
	if(matrix!=NULL)
	{
		for(i=0;i<size;++i) 
	    try
		{
			matrix[i]=new int[size];
		}
		catch(bad_alloc)
		{
			cerr<<"Memory modul: Out of memory! Press Enter to continue..."<<endl; _getch();
			for(size_t j=0; j<i;++j) delete []matrix[i];
			delete []matrix;
		}
		return matrix;
	}
	else 
	{
		cerr<<"Memory modul: Out of memory!"<<endl; _getch();
		return NULL;
	}
}
void DelMem(int** pArr, size_t size)
/*
  Процедура освобождения памяти.
  Входные параметры: ** pArr - указатель на двумерный динамический массив
                     size - размер двумерного динамического массива с указателем pArr.
*/
{
	if (pArr)
	{ 
		for(size_t i=0;i<size;++i) delete []pArr[i];
		delete []pArr;
		cout<<"Memory was clear out successfully"<<endl; 
	}
}