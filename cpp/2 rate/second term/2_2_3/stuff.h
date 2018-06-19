#ifndef _STUFF_H_
#define _STUFF_H_
#include<iostream>
#include<conio.h>
using namespace std;

class bad_cases
{
protected:
	int err;
public:
	bad_cases(int elem){err=elem;}
	int get_err() { return err; }
	virtual void prmsg()=0;
};

class exArray: public bad_cases
{
public:
	exArray(int elem):bad_cases(elem){};
	void prmsg()
	{
		switch(err)
		{
			case 1:cerr<<"elements.h (class _array): Memory allocation (size initialization)!"<<endl; break; 
			case 2:cerr<<"elements.h (class _array): Memory allocation (copy constructor)!"<<endl; break;
			case 3:cerr<<"elements.h (class _array): Memory allocation (assignation)!"<<endl; break;
			case 4:cerr<<"elements.h (class _array): Bad index!"<<endl; break;
			case 5:cerr<<"elements.h (class _array): Memory allocation (steam initialization)!"<<endl; break;
		}
		_getch();
	}
};
class exTree: public bad_cases
{
public:
	exTree(int elem):bad_cases(elem){};
	void prmsg()
	{
		switch(err)
		{
			case 1:cerr<<"tree.h: Out of memory (bad copying)!"<<endl; break; 
			case 2:cerr<<"tree.h: Out of memory (bad assignation)!"<<endl; break;
			case 3:cerr<<"tree.h: Empty tree!"<<endl; break;
		}
		_getch();
	}
};

bool read(istream& in, int& elem)
{
	in>>elem;
	if(!in)
	{
		in.clear();
		while(in.peek()=='\n') in.ignore(); in.ignore();
		return false;
	}
	return true;
}

char mmenu()
{
	char ans;
	do
	{
		system("cls");
		cout<<"1.Create/edit char tree"<<endl;
		cout<<"2.Create/edit complex tree"<<endl;
		cout<<"3.Create/edit array tree"<<endl;
		cout<<"0.Back"<<endl;
		ans=_getch();
	}while(ans!='1' && ans!='2' && ans!='3' && ans!='0');
	return ans;
}
char trmenu()
{
	char ans;
	do
	{
		system("cls");
		cout<<"1.Insert element"<<endl;
		cout<<"2.Delete element"<<endl;
		cout<<"3.Find subtree"<<endl;
		cout<<"4.Print tree"<<endl;
		cout<<"0.Back"<<endl;
		ans=_getch();
	}while(ans!='1' && ans!='2' && ans!='3' && ans!='4' && ans!='5' && ans!='0');
	return ans;
}
#endif