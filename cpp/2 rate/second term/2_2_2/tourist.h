#ifndef _TOURIST_H_
#define _TOURIST_H_
#include"travel.h"
const int pass_size=12;

class exTourist
{
	int err;
public:
	exTourist(int elem){err=elem;}
	int get_err(){return err;}
	void prmsg();
};

class tourist : virtual public human
{
protected:
	char* passport;
	 _travel travel;
public:
	tourist():human() {passport=0; travel.csize=travel.size=0; travel.data=0; }
	tourist(const char* , const char* , const char* , int , const char* ,const _travel& );
	tourist(const tourist& );
	virtual ~tourist();

	virtual void destroy()
	{
		human::destroy();
		if(passport) delete[] passport; passport=0;
		if(travel.data) delete[] travel.data; travel.data=0;
		travel.csize=travel.size=0;
	}

	const char* get_passport()const
	{
		if(passport) return passport;
		throw exTourist(7);
	}

	const _travel& get_travel()const
	{
		if(travel.data) return travel;
		throw exTourist(8);
	}
	const d_c& operator[](int elem)const
	{
		if(elem>=0 && elem<travel.csize) return travel[elem];
		throw exTourist(9);
	}
		
	void set_passport(const char* pass)
	{
		if(pass)
		{
			try
			{
				if(passport) delete[] passport; passport=0;
				passport=new char[strlen(pass)+1];
				strcpy(passport,pass);
			}
			catch(bad_alloc){throw exTourist(1);}
		}
		else throw exTourist(6);
	}
	void set_travel(const _travel& tr)
	{
		if(tr.data) travel=tr;
		else throw exTourist(4);
	}
	void set_traveli(const d_c& elem, int ind)
	{
		if(ind>=0 && ind<travel.csize)
		{
			travel[ind].date=elem.date;
			if(travel[ind].country) delete[] travel[ind].country; travel[ind].country=0;
			travel[ind].country=new char[strlen(elem.country)+1]; 
			strcpy(travel[ind].country,elem.country);
		}
		else throw exTourist(5);
	}

	tourist& operator = (const tourist& );
		
	friend ostream& operator << (ostream& ,const tourist& );
	friend istream& operator >> (istream& ,tourist& );
	
};
int tmenu();
void twork(tourist& );
#endif