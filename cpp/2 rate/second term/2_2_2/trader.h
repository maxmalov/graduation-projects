#ifndef _TRADER_H_
#define _TRADER_H_
#include"employer.h"
#include"tourist.h"
#include"adress.h"

class exTrader
{
	int err;
public:
	exTrader(int elem){err=elem;}
	int get_err(){return err;}
	void prmsg();
};

class trader: virtual public employer, virtual public tourist
{
protected:
	_adress adress;
public:
	trader():human(),employer(),tourist(){adress.csize=adress.size=0; adress.data=0; }
	trader(const trader& );
	~trader();

	virtual void destroy()
	{
		employer::destroy();
		tourist::destroy();
		if(adress.data)
		{
			for(int i=0;i<adress.csize;++i)
				if(adress.data[i]){ delete[] adress.data[i]; adress.data[i]=0; } 
			delete[] adress.data; adress.data=0;
			adress.csize=adress.size=0;
		}
	}

	const _adress& get_adr()const{return adress;}
	void set_adr(const _adress& adr){adress=adr;}
	void set_adri(const char* tmp, int elem)
	{
		if(elem>=0 && elem<adress.csize)
		{
			if(adress.data[elem]) delete[] adress.data[elem]; 
			adress.data[elem]=0; adress.data[elem]=new char[char_size];
			strcpy(adress.data[elem],tmp);
		}
		throw exTrader(3);
	}
	const char* operator [](int elem) const
	{
		if(elem>=0 && elem<adress.csize) return adress[elem];
		throw exTrader(3);
	}
	
	trader& operator =(const trader& );	
	friend ostream& operator <<(ostream& ,const trader& );
	friend istream& operator >>(istream& ,trader& );
	
};
int trmenu();
void trwork(trader& );
#endif