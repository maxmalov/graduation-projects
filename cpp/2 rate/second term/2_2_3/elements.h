#ifndef _ELEM_H_
#define _ELEM_H_
#include"stuff.h"

//-----------------------------------------------------------------------------------------------------
class _complex
{
	int re, im;
public:
	_complex(){ re=im=0; }												//����������� �� ���������
	_complex(int r,int i){ re=r; im=i; }								//����������� �� ��������
	_complex(const _complex& c){ re=c.re; im=c.im; }					//����������� �����������
	~_complex(){};														//����������

	_complex& operator = (const _complex& c)							//�������� ������������
	{
		if(this==&c) return *this;
		re=c.re; im=c.im; return *this;
	}

	bool operator > (const _complex& c) const							//�������� ���������
	{
		if(re>c.re) return true;
		else
		{
			if(re==c.re && im>c.im) return true;
			return false;
		}
	}
	
	bool operator < (const _complex& c) const							//�������� ���������
	{
		if(re<c.re) return true;
		else
		{
			if(re==c.re && im<c.im) return true;
			return false;
		}
	}
	
	bool operator == (const _complex& c) const
	{
		return (re==c.re && im==c.im)?true:false;
	}
	
	int get_re(){return re;} const										//����� ������������ �����
	int get_im(){return im;} const										//����� ������ �����

	void set_re(int elem){re=elem;}										//���������� ������������ �����
	void set_im(int elem){im=elem;}										//���������� ������������ �����

	friend ostream& operator << (ostream& out, const _complex& c){ out<<c.re<<"+"<<c.im<<"*i"; return out;}
	friend istream& operator >> (istream& in, _complex& c)
	{
		do cout<<"Set real: "; while(!read(in,c.re)); 
		do cout<<"Set image: "; while(!read(in,c.im));
		return in;
	}
};

//-----------------------------------------------------------------------------------------------------
class _array
{
	int* data;
	int len;
public:
	_array(){data=0; len=0;}											//����������� �� ���������
	_array(int size)													//����������� �� �������		
	{
		try
		{
			data=new int[size]; len=size;
			for(int i=0;i<len;++i) data[i]=0;
		}
		catch(bad_alloc) { throw exArray(1); }
	}
	_array(const _array& arr)											//����������� �����������
	{
		try
		{
			data=new int[arr.len]; len=arr.len;
			for(int i=0;i<len;++i) data[i]=arr.data[i];
		}
		catch(bad_alloc){ throw exArray(2); }
	}
	~_array(){if(data) delete[] data;}									//����������	

	_array& operator = (const _array& arr)								//�������� ������������
	{
		if(this==&arr) return *this;
		if(data) delete[] data; data=0;

		try
		{
			data=new int[arr.len]; len=arr.len;
			for(int i=0;i<len;++i) data[i]=arr.data[i];
			return *this;
		}
		catch(bad_alloc){ throw exArray(3); }
	}

	bool operator == (const _array& arr) const
	{
		if(len!=arr.len) return false;
		for(int i=0;i<len;++i) if(data[i]!=arr[i]) return false;
		return true;
	}
	
	int& operator [](int ind)											//�������� ������ �������
	{
		if(ind>=0 && ind<len) return data[ind];
		throw exArray(4);
	}

	const int& operator [] (int ind) const								//�������� ������ �������
	{
		if(ind>=0 && ind<len) return data[ind];
		throw exArray(4);
	}
	
	int get_len() const {return len;}									//����� �����
	const int* get_data() const {return data;}							//����� ������

	bool operator > (const _array& arr) const							//�������� ���������
	{
		if(arr==(*this)) return false;
		if( !((*this)<arr) ) return true;
		return false;
	}

	bool operator < (const _array& arr) const							//�������� ���������
	{
		if(arr==(*this)) return false;
		int elem = (arr.len<=len)?arr.len:len;
		for(int i=0;i<elem;++i)
		{
			if(data[i]<arr[i]) return true;
			else if(data[i]>arr[i]) return false;  
		}
		return (elem==len);
	}

	friend ostream& operator << (ostream& out, const _array& arr)
	{ 
		out<<"[";
		for(int i=0;i<arr.len;++i) 
			if(i!=arr.len-1) out<<arr.data[i]<<",";
			else out<<arr.data[i]<<"]";
		return out;
	}
	friend istream& operator >> (istream& in, _array& arr)
	{
		try
		{
			do cout<<"\nSet size: "; while(!read(in,arr.len) || arr.len<=0); 
			if(arr.data) delete[] arr.data; arr.data=0; arr.data=new int[arr.len];
			for(int i=0;i<arr.len;++i) do cout<<"Set "<<i<<" element: "; while(!read(in,arr[i])); 
			return in;
		}
		catch(bad_alloc) { throw exArray(5); }
	}
};
#endif