#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <conio.h>

using namespace std;
int ReadN();
const int char_size=256;
class Error
{
    int err;     
public:
	Error(int elem){ err=elem; }
    int GetErr(){ return err; }
	void PrtMsg()
	{
		switch (err)
		{
			case 1: cerr<<"Error:No memory to create text"; break;
			case 2: cout<<"Error:Bad str index"; break;
			case 3: cout<<"Error:Bad text index"; break;
			case 4: cout<<"Error:Cannot add string to the text"; break;
		}
	}
};

class _string 
{
	int lind, rind;													//левая и правая граница индексирования
	char* _str;														//строка
public:
	_string(){ lind=rind=0; _str=0;}								//конструктор по умолчанию
	_string (const char* );											//конструктор инициализации по строке
	_string (const _string& ) ;										//конструктор копирования
    ~_string(){	if(_str!=0) delete[] _str; lind=rind=0; _str=0;}	//деструктор

	void SetO(){lind=rind=0; _str=0;}								//обнуление содержимого
	void SetLR(int l,int r){ lind=l; rind=r; }						//установить границы индексирования
	int GetLI(){ return lind; }										//получить левую границу
	int GetRI(){ return rind; }										//получить правую границу
	int Size(){return rind-lind;}									//получить размер

    void PutS(const char* ,int );									//записать строку
	char GetCh(int elem)											//взять элемент
	{
		if(elem>=lind && elem<rind+1) return _str[elem-lind];
		else throw Error(2);
	}
	char* GetS()													//взять строку
	{
		if (_str) return _str;
		throw Error(2);
	}
		
	_string& operator = ( const char* );							//оператор присваивания строки
    _string& operator = ( const _string& );							//оператор присваивания класса
        
	char& operator [ ] (int elem)									//оператор взятия индекса
	{
		if(elem>=lind && elem<rind+1) return _str[elem];
		else throw Error(2);
	}
	
	friend ostream& operator << ( ostream& ot, _string& string1)	//оператор вывода в поток
	{
		for(int i=0;string1._str[i]; i++)	ot<<string1._str[i];
		return ot;
	}
	friend istream& operator >> ( istream& in, _string& string1)	//оператор ввода в поток
	{
		int l=0;
		char* buf=new char[char_size];
		cout<<"Input string: "; in.getline(buf,char_size);
		cout<<"Set left index range: "; do l=ReadN(); while(l==-1);
		string1.PutS(buf,l);
		return in; 
	}
}; 