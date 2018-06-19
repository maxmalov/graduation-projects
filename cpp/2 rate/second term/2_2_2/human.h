#ifndef _HUMAN_H_
#define _HUMAN_H_
#include<iostream>
#include<conio.h>
using namespace std;

const int char_size=256;
int ReadN(istream& );
bool ReadI(int );

class exHuman
{
	int err;
public:
	exHuman(int elem){err=elem;}
	int get_err(){return err;}
	void prmsg();
};

struct _name
{
	char* fname;
	char* sname;
	char* pname;
};

class human
{
protected:
	_name name;																			//‘»ќ
	int bdate;																			//год рождени€
public:
	human(){name.fname=0; name.pname=0; name.sname=0; bdate=0;}							//конструктор по умолчанию
	human(const char* ,const char* ,const char* ,int );									//инициализаци€
	human(const human& );																//конструктор копировани€
	virtual ~human();																	//деструктор
	
	virtual void destroy()
	{
		if(name.fname) delete[] name.fname; name.fname=0;
		if(name.sname) delete[] name.sname; name.sname=0;
		if(name.pname) delete[] name.pname; name.pname=0;
	}
	
	human& operator = (const human& );													//оператор присваивани€

	friend ostream& operator << (ostream& , const human& ); 
	friend istream& operator >> (istream& , human& );
	
	const char* get_fname() const
	{
		if(name.fname)return name.fname;
		throw exHuman(8);
	}
	const char* get_sname() const
	{
		if(name.sname) return name.sname;
		throw exHuman(9);
	}
	const char* get_pname()const
	{
		if(name.pname)return name.pname; 
		throw exHuman(10);
	}
	const int get_bdate()const{return bdate;}

	void set_fname(const char* );
	void set_sname(const char* );
	void set_pname(const char* );
	void set_bdate(int );
};
char hmenu();
void hwork(human& );
#endif