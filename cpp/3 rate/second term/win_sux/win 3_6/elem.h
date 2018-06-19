#ifndef _ELEM_H_
#define _ELEM_H_
#include <windows.h>
class elem
{
	static HANDLE hHeap;
	static int examples;
protected:
	virtual void print(ostream&)const=0;
	virtual void fill(istream&)=0;
public:
	virtual elem* getcopy() const=0;
	virtual ~elem(){};

	void* operator new(size_t size)
	{
		if(!hHeap)
			hHeap = HeapCreate(0,0,0);
		
		elem* p = (elem*) HeapAlloc(hHeap,0,size);
		
		if(p) examples++;

		return p;
	}

	void* operator new[] (size_t size)
	{
		if(!hHeap)
			hHeap = HeapCreate(0,0,0);
		
		elem* p = (elem*) HeapAlloc(hHeap,0,size);
		
		if(p) examples += size/sizeof(elem);

		return p;
	}
	
	void operator delete (void* p)
	{
		if( HeapFree(hHeap,0,p) )
			examples--;

		if(!examples)
			if(HeapDestroy(hHeap))
				hHeap = 0;
	}

	void operator delete[] (void* p)
	{
		if( HeapFree(hHeap,0,p) )
			examples -= sizeof(&p)/sizeof(elem);

		if(!examples)
			if(HeapDestroy(hHeap))
				hHeap = 0;
	}
	
	friend ostream& operator << (ostream& out, const elem* e)
	{
		e->print(out);
		return out;
	}
	friend istream& operator >> (istream& in, elem* e)
	{
		e->fill(in);
		return in;
	}
};

HANDLE elem::hHeap = 0;
int elem::examples = 0;
#endif