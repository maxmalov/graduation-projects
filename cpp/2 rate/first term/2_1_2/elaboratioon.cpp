#include"all.h"
using namespace std;
void Print(int** pArr, size_t size)
//Функция выводит на экран массив с указателем pArr и размером size
{
	system("cls");
	cout<<"Your current matrix: "<<endl;
	for(size_t i=0;i<size;++i)
	{
		for(size_t j=0;j<size;++j) 
		{
			cout<<pArr[i][j]<<"\t";
		}
		cout<<'\n';
	}
}
void GoSpiral(int** pArr, size_t size)
/*
  Функция, начиная с вернего левого элемента заданного массива, обходит таблицу по спирали и распечатывает 
  элементы в порядке обхода. 
  Входные параметры: ** pArr - указатель на заданный массив,
                     size - размер массива.
*/   
{
	int d=1;
	int y=-1;
	int x=0;
	
	Print(pArr,size);
	cout<<"Result: ";
	for(size_t j=size*size;j>=1;) //цикл пока элементы не закончатся
	{
		for(size_t i=0;i<size;++i) //цикл прохода по горизонтали
		{
			y+=d;
			cout<<pArr[x][y]<<" "; --j;
		}
		for(size_t i=0;i<size-1;++i) //цикл прохода по вертикали
		{
			x+=d;
			cout<<pArr[x][y]<<" "; --j;		
		}
		d*=-1;
		--size;
	}
}
char menu()
//Процедура вывода на экран меню. Возвращает выбранный пункт меню.
{
	char ans;
	
	system("cls");
	cout<<"   Main menu"<<endl;
	//cout<<"1. Create the config file."<<endl;
	cout<<"1. Infill a table."<<endl; 
	cout<<"2. Print the table. "<<endl;
	cout<<"3. Work with table. "<<endl;
	cout<<"4. Exit. "<<endl;
	cout<<'\n';
	ans=_getch();
	
	return ans;
}
