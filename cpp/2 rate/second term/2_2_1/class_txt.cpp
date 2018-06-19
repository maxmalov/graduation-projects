#include "class_text.h"

_text::_text(_text& text1)
{
	char* buf=0;
	csize=text1.csize;
	msize=text1.msize;
	txt=new _string[msize];
	for(int i=0;i<csize;++i) 
	{
		buf=text1[i].GetS();
		txt[i].PutS(buf,0);
	}
}
istream& operator >> (istream& in, _text& text1)
{
	int elem=0;
	char* buf=new char[char_size];
	do	cout << "Enter maximum size (set needed size +1, for end text element):"; while( ((elem=ReadN())==-1) && (elem<1) );
	text1.SetMS( elem );
	do	cout << "Enter uses size (should be < maximal size):"; while( ((elem=ReadN())==-1) && (elem>=text1.GetMS()) );
	text1.SetCS(elem);
	
	cout<<"Go on:"<<endl;
	for(int i=0;i!=elem; ++i)
	{
		in.getline(buf,char_size);
		text1.txt[i]=buf;
		*buf=0;
	}

	delete []buf;
	return in;
}
ostream& operator << ( ostream& ot,  const _text& text1)
{
	ot<<" Current size: "; ot<< text1.csize <<endl;
	ot<<" Max size: "; ot<< text1.msize <<endl;
	ot<<" Text: "<<endl;
	for(int i=0; i<text1.csize; ++i) ot<<"   "<< text1.txt[i]<<endl;
	return ot ;
} 

_text& _text::operator = (_text& text1)
{
	if(!text1.txt)
	{
		msize=csize=0;
		delete[] txt; txt=0;
	}
	else
	{
		delete[] txt; txt=0;
		char* buf=0;
		csize=text1.csize;
		msize=text1.msize;
		txt=new _string[msize];
		for(int i=0;i<csize;++i) 
		{
			buf=text1[i].GetS();
			txt[i].PutS(buf,0);
		}
	}
	return *this;
}
