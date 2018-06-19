#ifndef _TAX_H_
#define _TAX_H_
#include<iostream>
#include"human.h"
using namespace std;

class exTax
{
	int err;
public:
	exTax(int elem){err=elem;}
	int gterr(){return err;}
	void prmsg();
};

struct d_s
{
	int date;
	int sum;
};

struct _tax
{
	d_s* data;
	int csize, size;
	
	_tax();
	_tax(int );
	_tax(const _tax& );
	~_tax();
	
	d_s& operator [](int ) const;
	_tax& operator = (const _tax& );
	friend ostream& operator << (ostream& , const _tax& );
	friend istream& operator >> (istream& , _tax& );
};
#endif