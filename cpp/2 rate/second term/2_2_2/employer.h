#ifndef _EMPLOYER_H_
#define _EMPLOYER_H_
#include"human.h"
#include"tax.h"
const int TIN_size=12;

class exEmployer
{
	int err;
public:
	exEmployer(int elem){err=elem;}
	int get_err(){return err;}
	void prmsg();
};

class employer : virtual public human
{
protected:
	int license;
	char* registration;
	char* TIN;
	_tax tax;
public:
	employer():human(){license=0; registration=TIN=0; tax.csize=tax.size=0;}
	employer(const char* , const char* , const char* , int , int ,const char* ,const char* ,const _tax& );
	employer(const employer& );
	virtual ~employer();
	
	virtual void destroy()
	{
		human::destroy();
		license=0;
		if(registration) delete[] registration; registration=0;
		if(TIN) delete[] TIN; TIN=0;
		if(tax.data) delete[] tax.data; tax.data=0;
		tax.csize=tax.size=0;
	}
	int get_lic()const{return license;}
	const char* get_reg()const
	{ 
		if(registration) return registration;
		throw exEmployer(9);
	}
	const char* get_TIN()const
	{
		if(TIN) return TIN;
		throw exEmployer(10);
	}
	const _tax& get_tax() const{return tax;}
	const d_s& operator[](int elem) const
	{
		if(elem>=0 && elem<tax.csize) return tax[elem];
		throw exEmployer(11);
	}
		
	void set_lic(int lic)
	{
		if(lic>=0) license=lic;
		else throw exEmployer(4);
	}
	void set_reg(const char* reg)
	{
		if(reg)
		{
			try
			{
				if(registration) delete[] registration; registration=0;
				registration=new char[strlen(reg)+1];
				strcpy(registration,reg);
			}
			catch(bad_alloc){throw exEmployer(1);}
		}
		else throw exEmployer(5);
	}
	void set_TIN(const char* tin)
	{
		if(tin)
		{
			try
			{
				if(TIN)delete[] TIN; TIN=0;
				TIN=new char[strlen(tin)+1];
				strcpy(TIN,tin);
			}
			catch(bad_alloc){throw exEmployer(1);}
		}
		else throw exEmployer(6);
	}
	void set_tax(const _tax& tx)
	{
		if(tx.data)
		{
			try{ tax=tx; }
			catch(exTax){throw exEmployer(7);}
		}
		else throw exEmployer(7);
	}
	void set_taxi(d_s elem, int ind)
	{
		if(ind>=0 && ind<tax.csize)
		{
			try{ tax[ind]=elem; }
			catch(exTax){throw exEmployer(8);}
		}
		else throw exEmployer(8);
	}

	employer& operator = (const employer& );
	
	friend ostream& operator << (ostream& ,const employer& );
	friend istream& operator >> (istream& ,employer& );
};
int emenu();
void ework(employer& );
#endif