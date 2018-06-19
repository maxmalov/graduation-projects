#include"adress.h"
void exAdr::prmsg()
{
	switch(err)
	{
		case 1:cerr<<"adress.h: Initialization fail!"<<endl;break;
		case 2:cerr<<"adress.h: Copy fail!"<<endl;break;
		case 3:cerr<<"adress.h: Assign fail!"<<endl;break;
		case 4:cerr<<"adress.h: Incorrect index!"<<endl;break;
	}
	_getch();
}


_adress::_adress(){csize=size=0; data=0;}
_adress::_adress(int elem)
{
	try
	{
		data=new char*[elem];
		for(int i=0;i<elem;++i) data[i]=0;
		size=elem; csize=0;
	}
	catch(bad_alloc){throw exAdr(1);}
}
_adress::_adress(const _adress& adr)
{
	int i;
	try
	{
		data=new char*[adr.size];
		csize=adr.csize;
		size=adr.size;
		for(i=0;i<adr.csize;++i)
		{
			data[i]=new char[strlen(adr.data[i])+1];
			strcpy(data[i],adr.data[i]);
		}
		for(int i=csize;i<size;++i) data[i]=0;
	}
	catch(bad_alloc)
	{
		if(data)
		{
			for(int j=0;j<i;++j){ delete[] data[j]; data[j]=0; }
			delete[] data; data=0;
		}
		throw exAdr(2);
	}

}
_adress::~_adress() 
{ 
	if(data)
	{	
		for(int i=0;i<size;++i) if(data[i]){ delete[] data[i]; data[i]=0; }
		delete[] data; data=0;
	}
}


_adress& _adress::operator = (const _adress& adr)
{
	if(this==&adr) return *this;
	
	if(data)
	{	
		for(int i=0;i<size;++i) if(data[i]){ delete[] data[i]; data[i]=0; }
		delete[] data; data=0;
	}

	int i;
	try
	{
		data=new char*[adr.size];
		csize=adr.csize;
		size=adr.size;
		for(i=0;i<adr.csize;++i)
		{
			data[i]=new char[strlen(adr[i])+1];
			strcpy(data[i],adr[i]);
		}
		for(int i=csize;i<size;++i) data[i]=0;
	}
	catch(bad_alloc)
	{
		if(data)
		{
			for(int j=0;j<i;++j){ delete[] data[j]; data[j]=0; }
			delete[] data; data=0;
		}
		throw exAdr(3);
	}
	return *this;
}
inline const char* _adress::operator [](int elem) const 
{
	if(elem>=0 && elem<csize) return data[elem];
	throw exAdr(4);
}

ostream& operator << (ostream& ot, const _adress& adr)
{
	ot<<"Adresses: "<<endl;
	for(int i=0;i<adr.csize;++i) ot<<adr.data[i]<<endl;
	return ot;
}
istream& operator >> (istream& in, _adress& adr)
{
	if(adr.data)
	{
		for(int i=0;i<adr.size;++i) if(adr.data[i]){ delete[] adr.data[i]; adr.data[i]=0; }
		delete[] adr.data; adr.data=0;
	}
	
	int i;
	try
	{
		cout<<"\nSetting adress base: "<<endl;
		do cout<<"Set size: "; while((adr.size=ReadN(in))==-1);
		adr.data=new char*[adr.size];
		do cout<<"Set uses size: "; while((adr.csize=ReadN(in))==-1);
		for(i=0;i<adr.csize;++i)
		{
			cout<<"Set "<<i<<" adress: "; 
			adr.data[i]=new char[char_size]; in.getline(adr.data[i],char_size);
		}
		for(int i=adr.csize;i<adr.size;++i) adr.data[i]=0;
		return in;
	}
	catch(bad_alloc)
	{
		if(adr.data)
		{
			for(int j=0;j<i;++j){ delete[] adr.data[j]; adr.data[j]=0; }
			delete[] adr.data; adr.data=0;
		}
		throw exAdr(3);
	}
}