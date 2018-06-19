#include"all.h"
using namespace std;
/*
  Вариант 25. Начиная с верхнего левого элемента обойти по спирали квадратную матрицу, распечатывая элементы 
  в порядке обхода.
  Автор: Малов Максим.
  Версия: beta 1.000
*/
void main(int argc, char *argv[])
{
	char ans, ans1;
	size_t size=0; 
	int** Array=NULL;
	system("cls");
	if(argc>1) 
	{	
		Array=ReadF(argv[1],size);
		if(Array)
		{ 
			GoSpiral(Array,size); _getch(); 
		}
	}
	
	do
	{
		ans=menu();
		switch(ans)
		{
		    /*case '1':
			{
				fname=new char[40];
				cout<<"Enter file directory: "; cin.getline(fname,40);
				CreateF(fname);
				delete []fname;
				break;
			}*/
			case '1':
			{
				if(Array==NULL) Array=HandleFilling(size); //проверка на пустоту
			    else //если матрица уже задана, то освобождаем память, а потом записываем другую
				{
					cout<<"Next operation will delete current matrix! Are you sure to continue? (Y/any key)";
					ans1=_getch();
					if((ans1=='Y')||(ans1=='y'))
					{
						DelMem(Array,size);
						Array=HandleFilling(size);					
					}
					else continue;
				}
				break;
			}
			case '2':
			{
				if(Array==NULL) 
				{
					cerr<<"You should fill the table previously! Press any key to continue..."; _getch();
				}
				else 
				{
					Print(Array,size); _getch();
				}
				break;			
			}
			case '3':
			{
				if(Array==NULL) 
				{
					cerr<<"You should fill the table previously! Press any key to continue..."; _getch();
				}
				else 
				{ 
					GoSpiral(Array,size); _getch(); 
				}
				break;
			}
			case '4': 
			{ 
				if(Array!=NULL) DelMem(Array,size); 
				break;
			}
			/*default:
			{
				cout<<"You should choose only 1-5 actions! Press any key to continue...";	_getch(); 
				break;
			}*/
		}
	}while(ans!='4');
}