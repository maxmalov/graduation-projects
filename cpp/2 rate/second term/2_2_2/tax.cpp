#include"tax.h"
void exTax::prmsg()
{
	switch(err)
	{
		case 1:cerr<<"Tax.h: Initialization fail!"<<endl;break;
		case 2:cerr<<"Tax.h: Copy fail!"<<endl;break;
		case 3:cerr<<"Tax.h: Assign fail!"<<endl;break;
		case 4:cerr<<"Tax.h: Incorrect index!"<<endl;break;
		case 5:cerr<<"Tax.h: Incorrect size!"<<endl;break;
		case 6:cerr<<"Tax.h: Incorrect uses size!"<<endl;break;
	}
	_getch();
}


_tax::_tax(){csize=size=0; data=0;}
_tax::_tax(int elem)
{
	try
	{
		data=new d_s[elem];
		size=elem;
		for(int i=0;i<elem;++i) 
		{	
			data[i].date=0;
			data[i].sum=0;
		}
	}
	catch(bad_alloc){ throw exTax(1);}
}
_tax::_tax(const _tax& tx)
{
	try
	{
		data=new d_s[tx.size];
		csize=tx.csize;
		size=tx.size;
		for(int i=0;i<tx.csize;++i) data[i]=tx[i];
	}
	catch(bad_alloc){throw exTax(2);}

}
_tax::~_tax() { if(data) delete[] data; data=0; }

inline d_s& _tax::operator [](int elem) const 
{
	if(elem>=0 && elem<csize) return data[elem];
	else throw exTax(4);
}
_tax& _tax::operator = (const _tax& tx)
{
	if(this==&tx) return *this;
	if(data){delete[] data; data=0;}
	try
	{
		data=new d_s[tx.size];
		csize=tx.csize;
		size=tx.size;
		for(int i=0;i<tx.csize;++i) data[i]=tx[i];
		for(int i=csize;i<size;++i) data[i].date=data[i].sum=0;
	}
	catch(bad_alloc){throw exTax(3);}
	return *this;
}

ostream& operator << (ostream& ot, const _tax& tx)
{
	ot<<"Taxes: "<<endl;
	for(int i=0;i<tx.csize;++i)
		ot<<i<<": Date: "<<tx[i].date<<", Sum: "<<tx[i].sum<<endl;
	return ot;
}
istream& operator >> (istream& in, _tax& tx)
{
	if(tx.data){delete[] tx.data; tx.data=0;}
	cout<<"\nSetting tax base: "<<endl;
	do cout<<"Set size: "; while( (tx.size=ReadN(in))==-1 );
	tx.data=new d_s[tx.size];
	do cout<<"Set uses size: "; while( (tx.csize=ReadN(in))==-1 && tx.csize<=tx.size);
	for(int i=0;i<tx.csize;++i)
	{
		do cout<<i<<": Set date: "; while( (tx.data[i].date=ReadN(in))==-1 );
		do cout<<i<<": Set sum: "; while( (tx.data[i].sum=ReadN(in))==-1 );
	}
	return in;
}