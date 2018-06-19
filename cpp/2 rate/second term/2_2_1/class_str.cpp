#include "class_str.h"
int ReadN()
{
	int num=0;
	cin>>num;
	if((!cin)||(num<0))
	{
		cin.clear();
		while(cin.peek()!='\n') cin.ignore();
		cin.ignore();
		return -1;
	}
	while(cin.peek()!='\n') cin.ignore();
	cin.ignore();
	return num;
}
_string::_string(const char* buf)
{
	_str=0; _str=new char[strlen(buf)+1];
	strcpy(_str,buf);
	lind=0; rind=strlen(buf);
}
_string::_string( const _string &string1 )
{
	try
	{
		_str=new char[string1.rind-string1.lind + 1];
		lind=string1.lind; rind=string1.rind;
		strcpy(_str,string1._str); 
	}
	catch(bad_alloc){ throw Error(1); } 
}
void _string::PutS (const char *str1, int l)
{
	if(!str1){ delete[]_str; _str=0; }
	else
	{
		try
		{
			if(_str!=0){ delete[] _str; _str=0; }
			_str=new char[strlen(str1)+ 1] ;
			lind=l; rind=l+strlen(str1)-1;
			strcpy(_str,str1);
		}
		catch(bad_alloc) { throw Error(1); } 
	}
}    
_string& _string::operator = (const char* str1)
{
	if(!str1)
	{
		lind=rind=0 ;
		delete[] _str; _str=0;
	}
	else 
	{
		try
		{
			if(_str) delete[] _str;
			_str=new char[strlen(str1)+1];
			strcpy(_str,str1);
			lind=0; rind=strlen(str1)+1;
		}
		catch(bad_alloc){ throw Error(1); }
	}
	return *this;
}
_string& _string::operator = ( const _string& string1)
{
	if(this==&string1) return *this;
	try
	{
		if(_str){ delete[]_str; _str=0; }
		_str=new char[string1.rind-string1.lind + 1];
		lind=string1.lind; rind=string1.rind;
		strcpy(_str,string1._str); 
	}
	catch(bad_alloc){ throw Error(1); } 
	return *this;
}
