#ifndef _MAN_H_
#define _MAN_H_

#include"elem.h"
class man: public elem
{
protected:
	char* name;
	char* sname;

	void print(ostream& out)	const
	{
		out<<name<<", "<<sname;
	}
	void fill(istream& in)
	{
		const int CHAR_L=32; //для ввода строки
		
		char* tmp=0; tmp=new char [CHAR_L];
		cout<<"Name: "; in.getline(tmp,CHAR_L);
		set_name(tmp); *tmp=0;
		cout<<"Second name: "; in.getline(tmp,CHAR_L);
		set_sname(tmp);
		delete[] tmp;
	}
public:
	man()
	{
		name=new char[1]; strcpy(name,"");
		sname=new char[1]; strcpy(sname,"");
	}
	
	man(const char* n,const char* s)
	{
		if(!n) n="";
		if(!s) s="";
		name=new char[strlen(n)+1]; 
		strcpy(name, n);
		sname=new char[strlen(s)+1]; 
		strcpy(sname, s);
	}

	man(const man& m)
	{
		name=new char [strlen(m.name)+1];
		strcpy(name, m.name);
		sname=new char [strlen(m.sname)+1];
		strcpy(sname, m.sname);
	}

	virtual ~man()
	{
		delete[] name; 
		delete[] sname;
	}

	man& operator = (const man& m)
	{
		if(this==&m) return *this;
		
		delete[] name; delete[] sname; 
		name=new char [strlen(m.name)+1];
		strcpy(name, m.name);
		sname=new char [strlen(m.sname)+1];
		strcpy(sname, m.sname);
		return *this;
	}
	
	virtual elem* getcopy() const
	{
		return new man(*this);
	}

	void set_name(const char* n)
	{
		if(name==n) return;
		delete[] name;
		name=new char [strlen(n)+1];
		strcpy(name, n);
	}
	void set_sname(const char* s)
	{
		if(sname==s) return;
		delete[] sname;
		sname=new char [strlen(s)+1];
		strcpy(sname, s);
	}
	
	const char* get_name() const
	{
		return name;
	}
	const char* get_sname() const
	{
		return sname;
	}
};
#endif