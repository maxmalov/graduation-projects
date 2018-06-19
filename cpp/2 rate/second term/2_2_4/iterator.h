//#ifndef _ITER_
//#define _ITER_
//#include"set_of.h"
//template<typename T> class iter_set
//{
//	const set_of<T>* set;
//	int clevel;			//номер уровня
//	list<int>::iterator celem;			//указатель итератора на элемент на соответствующем уровне
//public:
//	iter_set(const set_of<T>& SO)
//	{
//		set=&SO;
//		begin();
//	}
//	~iter_set()
//	{
//		set=0;
//	}
//	void begin()
//	{
//		int i;
//		if(set->empty()) throw exIter(1);
//		for(i=set->high-1;i>=0 && !set->data[i];--i);
//		clevel=i;
//		celem=set->data[i]->end();
//	}
//    void end()
//	{
//		int i;
//		if(set->empty()) throw exIter(1);
//		for(i=0;i<set->high-1 && !set->data[i];++i);
//		clevel=i;
//		celem=set->data[i]->end();
//	}
//	bool start()
//	{
//		for(int i=clevel-1;i>=0;--i)
//			if(set->data[i]) return false;
//		if(celem==set->data[i]->begin()) return true;
//		return false;	
//	}
//	bool done()
//	{
//		for(int i=clevel+1;i<set->high-1;++i)
//			if(set->data[i]) return false;
//		if(celem==set->data[i]->back()) return true;
//		return false;
//	}
//	void operator ++ ()
//	{
//		if(celem!=set->data[clevel]->back();){ celem++; return; }
//		int i;
//		for(i=clevel+1;i<set->high-1 && !set->data[i]; ++i);
//		if(!set->data[i]) return;
//		clevel=i;
//		celem=set->data[i]->begin();
//	}
//	void operator -- ()
//	{
//		if(celem!=set->data[clevel]->begin();){ celem--; return; }
//		int i;
//		for(i=clevel-1; i>=0 && !set->data[i]; --i);
//		if(!set->data[i]) return;
//		clevel=i;
//		celem=set->data[i]->end();
//	}
//	T operator *()
//	{
//		if(!set->empty()) return *celem;
//		throw exIter(1);
//	}
//};
//#endif