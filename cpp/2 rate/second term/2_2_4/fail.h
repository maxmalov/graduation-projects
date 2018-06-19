#ifndef _FAIL_
#define _FAIL_
#include <iostream>
#include<conio.h>
using namespace std;

class bad_cases
{
protected:
	int err;
public:
	bad_cases(int elem){err=elem;}
	int get_err(){return err;}
	virtual void prtmsg()=0;
};

class exSet : public bad_cases
{
public:
	exSet(int err):bad_cases(err){}
	void prtmsg()
	{
		switch(err)
		{
			case 1:cerr<<"set_of.h: different sets!"; break;
		}
		_getch();
	}
};
class exIter : public bad_cases
{
public:
	exIter(int err):bad_cases(err){}
	void prtmsg()
	{
		switch(err)
		{
			case 1:cerr<<"iterator.h: empty set!"; break;
		}
		_getch();
	}
};
class exHT : public bad_cases
{
public:
	exHT(int err):bad_cases(err){}
	void prtmsg()
	{
		switch(err)
		{
			case 1:cerr<<"hash_table.h: bad index!"; break;
		}
		_getch();
	}
};

bool read(istream& in, int& elem)
{
	in>>elem;
	if(!in)
	{
		in.clear();
		while(in.peek()!='\n') in.ignore(); in.ignore();
		return false;
	}
	return true;
}
#endif