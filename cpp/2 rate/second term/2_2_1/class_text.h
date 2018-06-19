#include "class_str.h"

class _text
{
	_string* txt;													//массив классов
	int msize, csize;												//максимальный и текущий размер
public:
	_text(){ msize=csize=0; txt=0;}									//конструктор по умолчанию
	_text(int m)													//конструктор инициализации
	{
		try
		{
			csize=0; msize=m; txt=0;
			txt=new _string[msize];
			for(int i=0;i<msize;i++) txt[i].SetO();
		}
		catch(bad_alloc){throw Error(1);}
	} 
	_text(_text& );													//конструктор копирования
	~_text()														//деструктор
	{
		if (txt!=0) delete []txt; 
		txt=0;	csize=msize=0; 
	}


	void SetMS(int size)											//установить максимальный размер
	{
		try
		{
			if (txt!=0)	delete []txt;
			csize=0; msize=size;
			txt=new _string [msize];
		}
		catch(bad_alloc){ throw Error(1); }
	}
	void SetCS(int elem)											//установить текущий размер
	{
		if (0<=elem && elem<msize )	csize=elem;
		else throw Error(3);
	}

	int GetMS(){return msize;}										//получить максимальный размер
	int GetCS(){return csize;}										//получить текущий размер
	
	_string* GetTxt(){return txt;}									//получить текст
	_string* GetS(int elem)											//получить строку
	{
		if(0<=elem && elem<csize )return &txt[elem];
		else throw Error(3);
	} 

	void adds(const char* buf)										//добавить строку в конец
	{
		if(csize<msize-1)
		{
			txt[csize]=buf;
			csize++;
		}
		else throw Error(4);
	}
	void chgs(int elem,int ind,char* buf)							//изменить строку с заданным индексом
	{
		if(0<=elem && elem<csize) txt[elem].PutS(buf,ind);
		else throw Error(3);
	}
	void dels(int elem)												//удалить строку с заданным индексом
	{
		if(0<=elem && elem<csize)
		{
			for(int i=elem;i<csize-1; ++i) txt[i] = txt[i+1];
			csize--;
		}
		else throw Error(3);
	}
	
	_string& operator[ ](int elem)									//оператор взятия индекса
	{
		if(0<=elem && elem<csize && elem<msize)	return txt[elem];
		else throw Error(3);
	}
	_text& operator = (_text& );									//оператор присваивания класса
	
	friend istream& operator >> ( istream& ,  _text& ) ;			//оператор вывода в поток
	friend ostream& operator << ( ostream& ,  const _text& ) ;		//оператор ввода в поток
};

