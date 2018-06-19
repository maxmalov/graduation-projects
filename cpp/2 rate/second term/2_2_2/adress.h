#ifndef _ADRESS_H_
#define _ADRESS_H_
#include"human.h"

class exAdr
{
	int err;
public:
	exAdr(int elem){err=elem;}
	int gterr(){return err;}
	void prmsg();
};

struct _adress
{
	char** data;
	int csize, size;

	_adress();
	_adress(int );
	_adress(const _adress& );
	~_adress();
	
	const char* operator [](int )const;
	_adress& operator = (const _adress& );
	friend ostream& operator << (ostream& , const _adress& );
	friend istream& operator >> (istream& , _adress& );
};
#endif