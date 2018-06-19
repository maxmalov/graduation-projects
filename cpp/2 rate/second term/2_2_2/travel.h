#ifndef _TRAVEL_H_
#define _TRAVEL_H_
#include<iostream>
#include"human.h"
using namespace std;
class exTrv
{
	int err;
public:
	exTrv(int elem){err=elem;}
	int gterr(){return err;}
	void prmsg();
};

struct d_c
{
	int date;
	char* country;
};

struct _travel
{
	d_c* data;
	int csize, size;
	
	_travel();
	_travel(int );
	_travel(const _travel& );
	~_travel();
	
	d_c& operator [](int )const;
	_travel& operator = (const _travel& );
	friend ostream& operator << (ostream& , const _travel& );
	friend istream& operator >> (istream& , _travel& );
};
#endif