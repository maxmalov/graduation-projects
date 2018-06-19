#include "class_str.h"

class _text
{
	_string* txt;													//������ �������
	int msize, csize;												//������������ � ������� ������
public:
	_text(){ msize=csize=0; txt=0;}									//����������� �� ���������
	_text(int m)													//����������� �������������
	{
		try
		{
			csize=0; msize=m; txt=0;
			txt=new _string[msize];
			for(int i=0;i<msize;i++) txt[i].SetO();
		}
		catch(bad_alloc){throw Error(1);}
	} 
	_text(_text& );													//����������� �����������
	~_text()														//����������
	{
		if (txt!=0) delete []txt; 
		txt=0;	csize=msize=0; 
	}


	void SetMS(int size)											//���������� ������������ ������
	{
		try
		{
			if (txt!=0)	delete []txt;
			csize=0; msize=size;
			txt=new _string [msize];
		}
		catch(bad_alloc){ throw Error(1); }
	}
	void SetCS(int elem)											//���������� ������� ������
	{
		if (0<=elem && elem<msize )	csize=elem;
		else throw Error(3);
	}

	int GetMS(){return msize;}										//�������� ������������ ������
	int GetCS(){return csize;}										//�������� ������� ������
	
	_string* GetTxt(){return txt;}									//�������� �����
	_string* GetS(int elem)											//�������� ������
	{
		if(0<=elem && elem<csize )return &txt[elem];
		else throw Error(3);
	} 

	void adds(const char* buf)										//�������� ������ � �����
	{
		if(csize<msize-1)
		{
			txt[csize]=buf;
			csize++;
		}
		else throw Error(4);
	}
	void chgs(int elem,int ind,char* buf)							//�������� ������ � �������� ��������
	{
		if(0<=elem && elem<csize) txt[elem].PutS(buf,ind);
		else throw Error(3);
	}
	void dels(int elem)												//������� ������ � �������� ��������
	{
		if(0<=elem && elem<csize)
		{
			for(int i=elem;i<csize-1; ++i) txt[i] = txt[i+1];
			csize--;
		}
		else throw Error(3);
	}
	
	_string& operator[ ](int elem)									//�������� ������ �������
	{
		if(0<=elem && elem<csize && elem<msize)	return txt[elem];
		else throw Error(3);
	}
	_text& operator = (_text& );									//�������� ������������ ������
	
	friend istream& operator >> ( istream& ,  _text& ) ;			//�������� ������ � �����
	friend ostream& operator << ( ostream& ,  const _text& ) ;		//�������� ����� � �����
};

