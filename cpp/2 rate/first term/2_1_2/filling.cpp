#include<fstream>
#include"all.h"
using namespace std;
bool ReadSize_t(size_t &value)
//Функция считывания натурального числа 
{
	value=0; 
	char* tmp=new char[10];
	cin.getline(tmp,10);
	for(int i=0;tmp[i];++i)
	{
		if((tmp[i]=='0')||(tmp[i]=='1')||(tmp[i]=='2')||(tmp[i]=='3')||(tmp[i]=='4')||(tmp[i]=='5')
			||(tmp[i]=='6')||(tmp[i]=='7')||(tmp[i]=='8')||(tmp[i]=='9')) continue;
		else return false;
	}
	value=atoi(tmp); 
	return true;
}
bool ReadInt(int &value)
//Функция считывания целого числа 
{
	value=0; 
	char* tmp=new char[10];
	cin.getline(tmp,10);
	for(int i=0;tmp[i];++i)
	{
		if((tmp[i]=='0')||(tmp[i]=='1')||(tmp[i]=='2')||(tmp[i]=='3')||(tmp[i]=='4')||(tmp[i]=='5')
			||(tmp[i]=='6')||(tmp[i]=='7')||(tmp[i]=='8')||(tmp[i]=='9')||(tmp[i]=='-')) continue;
		else return false;
	}
	value=atoi(tmp); 
	return true;
}
int** ReadF(char *Fname, size_t &size)
/*
   Функция чтения матрицы из файла.
   Входныой параметр: *Fname - указатель на строку с именем входного файла
                      size - размер матрицы (передается по ссылке), изначально равен 0
   Функция возвращает указатель на считанную матрицу при отсутствии ошибок считывания, в противном случае возвращает NULL
*/
{
	int** pArr;
	size_t i=0, j=0;
	
	ifstream inF(Fname); //создание входного файлового потока
	if(inF.fail()) 
	{
		cerr<<"File method: File not found!"<<endl; _getch();
		return NULL;
	}
	
	inF>>size;//Считывание размера
	if(inF.fail())
	{
		cerr<<"File method: Read file error(file is empty or incorrect size of matrix)!"<<endl; _getch();
		return NULL;
	}
	
	pArr=GetMem(size); //Выделение памяти
	
	if(pArr==NULL) return NULL;

	for(i=0;(i<size)&&(!inF.eof());++i)
	{
		for(j=0;(j<size)&&(!inF.eof());++j)
		{
			inF>>pArr[i][j];
	        if(inF.fail()) 
	        {  
				cerr<<"File method: Read file error (incorrect symbols)!"<<endl; _getch();
				DelMem(pArr,size);
				return NULL;	    	
			}
		}
	}
	if( (i*j)==(size*size) ) //проверка количества считанных символов 
	{
		cout<<"File method: Matrix was filled successfully!"<<endl; _getch();
		return pArr;
	}
	else
	{ 
	    	cerr<<"File method: Read file error(not enough symbols)!"<<endl; _getch();
	    	DelMem(pArr,size);
			return NULL;
	}
}
/*void CreateF(char* fname)
// Процедура создания входного файла.
// Входной параметр: *fname - указатель на строку с именем файла.
{
	size_t size, tmp;
	ofstream outF(fname);//создание выводного файлового потока

	do
	{
		cout<<"Enter size of future matrix: "; cin>>size;
	}while(size<=0);
	cout<<endl;
	outF<<size; outF<<'\n';	
	for(size_t i=0;i<size;++i)
	{
		for(size_t j=0;j<size;++j)
		{
			cout<<"Enter ["<<i<<"]["<<j<<"] element of matrix: "; cin>>tmp;
			outF<<tmp; outF<<" "; 
		}
		outF<<'\n';
	}
	cout<<"File was writed successfully! Press Enter to continue..."; _getch();
}*/
int** HandleFilling(size_t &size)
//Функция ручного заполнения матрицы. Выходной параметр указатель на 2мерный массив.
{
	bool flag; 
	int** pArr=NULL;
	do
	{
		cout<<"Enter matrix size: "; 
		flag=ReadSize_t(size);
	}while(!flag);
	
	pArr=GetMem(size);
	if(!pArr) return NULL;
	
	for(size_t i=0;i<size;++i)
        for(size_t j=0;j<size;++j)
		do
		{
			cout<<"Enter ["<<i<<"]["<<j<<"] element of matrix: ";
		    flag=ReadInt(pArr[i][j]);
		}while(!flag);		
	return pArr;
}