#include"travel.h"
void exTrv::prmsg()
{
	switch(err)
	{
		case 1:cerr<<"travel.h: Initialization fail!"<<endl;break;
		case 2:cerr<<"travel.h: Copy fail!"<<endl;break;
		case 3:cerr<<"travel.h: Assign fail!"<<endl;break;
		case 4:cerr<<"travel.h: Incorrect index!"<<endl;break;
		case 5:cerr<<"travel.h: Incorrect size!"<<endl;break;
		case 6:cerr<<"travel.h: Incorrect uses size!"<<endl;break;
	}
	_getch();
}


_travel::_travel(){csize=size=0; data=0;}
_travel::_travel(int elem)
{
	try
	{
		data=new d_c[elem];
		size=elem;
		for(int i=0;i<elem;++i) 
		{	
			data[i].date=0;
			data[i].country=0;
		}
	}
	catch(bad_alloc){ throw exTrv(1);}
}
_travel::_travel(const _travel& tr)
{
	try
	{
		data=new d_c[tr.size];
		csize=tr.csize;
		size=tr.size;
		for(int i=0;i<tr.csize;++i)
		{
			data[i].date=tr[i].date;
			if(data[i].country) delete[] data[i].country; data[i].country=0;
			data[i].country=new char[strlen(tr[i].country)+1];
			strcpy(data[i].country,tr[i].country);
		}
		for(int i=csize;i<size;++i) {data[i].country=0; data[i].date=0;}
	}
	catch(bad_alloc){throw exTrv(2);}

}
_travel::~_travel() { if(data) delete[] data; data=0; }

inline d_c& _travel::operator [](int elem) const 
{
	if(elem>=0 && elem<csize) return data[elem];
	else throw exTrv(4);
}
_travel& _travel::operator = (const _travel& tr)
{
	if(this==&tr) return *this;
	if(data){delete[] data; data=0;}
	try
	{
		data=new d_c[tr.size]; 
		for(int i=0;i<tr.size;++i)
		{
			data[i].country=0;
			data[i].date=0;
		}
		csize=tr.csize;
		size=tr.size;
		for(int i=0;i<tr.csize;++i)
		{
			data[i].date=tr[i].date;
			if(data[i].country) delete[] data[i].country; data[i].country=0;
			data[i].country=new char[strlen(tr[i].country)+1];
			strcpy(data[i].country,tr[i].country);
		}
	}
	catch(bad_alloc){throw exTrv(3);}
	return *this;
}

ostream& operator << (ostream& ot, const _travel& tr)
{
	ot<<"travels: "<<endl;
	for(int i=0;i<tr.csize;++i)
		ot<<i<<": Date: "<<tr[i].date<<", Country: "<<tr[i].country<<endl;
	return ot;
}
istream& operator >> (istream& in, _travel& tr)
{
	if(tr.data){delete[] tr.data; tr.data=0;}
	cout<<"\nSetting travel base: "<<endl;
	do cout<<"Set size: "; while( (tr.size=ReadN(in))==-1 );
	tr.data=new d_c[tr.size];
	do cout<<"Set uses size: "; while( (tr.csize=ReadN(in))==-1 && tr.csize<=tr.size);
	char* buf=0; buf=new char[char_size];
	for(int i=0;i<tr.csize;++i)
	{
		do cout<<i<<": Set date: "; while( (tr.data[i].date=ReadN(in))==-1 );
		cout<<i<<": Set country: "; in.getline(buf,char_size); 
		tr.data[i].country=new char[strlen(buf)+1]; strcpy(tr.data[i].country,buf); *buf=0;
	}
	return in;
	delete[] buf;
}