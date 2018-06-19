#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <conio.h>

using namespace std;
int ReadN();
const int char_size=256;
class Error
{
    int err;     
public:
	Error(int elem){ err=elem; }
    int GetErr(){ return err; }
	void PrtMsg()
	{
		switch (err)
		{
			case 1: cerr<<"Error:No memory to create text"; break;
			case 2: cout<<"Error:Bad str index"; break;
			case 3: cout<<"Error:Bad text index"; break;
			case 4: cout<<"Error:Cannot add string to the text"; break;
		}
	}
};

class _string 
{
	int lind, rind;													//����� � ������ ������� ��������������
	char* _str;														//������
public:
	_string(){ lind=rind=0; _str=0;}								//����������� �� ���������
	_string (const char* );											//����������� ������������� �� ������
	_string (const _string& ) ;										//����������� �����������
    ~_string(){	if(_str!=0) delete[] _str; lind=rind=0; _str=0;}	//����������

	void SetO(){lind=rind=0; _str=0;}								//��������� �����������
	void SetLR(int l,int r){ lind=l; rind=r; }						//���������� ������� ��������������
	int GetLI(){ return lind; }										//�������� ����� �������
	int GetRI(){ return rind; }										//�������� ������ �������
	int Size(){return rind-lind;}									//�������� ������

    void PutS(const char* ,int );									//�������� ������
	char GetCh(int elem)											//����� �������
	{
		if(elem>=lind && elem<rind+1) return _str[elem-lind];
		else throw Error(2);
	}
	char* GetS()													//����� ������
	{
		if (_str) return _str;
		throw Error(2);
	}
		
	_string& operator = ( const char* );							//�������� ������������ ������
    _string& operator = ( const _string& );							//�������� ������������ ������
        
	char& operator [ ] (int elem)									//�������� ������ �������
	{
		if(elem>=lind && elem<rind+1) return _str[elem];
		else throw Error(2);
	}
	
	friend ostream& operator << ( ostream& ot, _string& string1)	//�������� ������ � �����
	{
		for(int i=0;string1._str[i]; i++)	ot<<string1._str[i];
		return ot;
	}
	friend istream& operator >> ( istream& in, _string& string1)	//�������� ����� � �����
	{
		int l=0;
		char* buf=new char[char_size];
		cout<<"Input string: "; in.getline(buf,char_size);
		cout<<"Set left index range: "; do l=ReadN(); while(l==-1);
		string1.PutS(buf,l);
		return in; 
	}
}; 