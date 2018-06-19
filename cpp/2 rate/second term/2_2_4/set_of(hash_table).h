#ifndef _SET_OF_
#define _SET_OF_

#include "fail.h"
#include<typeinfo>
#include <list>
#include<vector>
#include<string>

const int default_high = 16;
template<typename T> class iter_set;

template<typename T> class set_of
{
	friend class iter_set<T>;
	vector< list<int>* > data;
	string type;
	int high;			//высота хэш-таблицы
	int _card;			//мощность мнножества
	
	int hash(const T& elem) const
	{
		return int(elem)%high;
	}
public:
	set_of()
	{
		high=default_high;
		_card=0;
		data.resize(high);
		for(int i=0;i<high-1;++i) data[i]=0;
		type=typeid(T).name();
	}
	set_of(const set_of<T>& S)
	{
		high=S.high;
		_card=S._card;
		type=S.type;
		data.resize(high);
		for(int i=0;i<high;++i)
		{	
			data[i]=0;
			if(S.data[i])
			{ 
				data[i]=new list<int>;
				for(list<int>::iterator tmp=S.data[i]->begin();tmp!=S.data[i]->end();tmp++)
				data[i]->push_back(*tmp);
			}
		}
	}
	~set_of()
	{
		for(int i=0;i<high;++i) delete data[i];
	}

	set_of<T>& operator = (const set_of<T>& S)
	{
		if(this==&S) return *this;
		data.resize(S.high);
		high=S.high;
		_card=S._card;
		type=S.type;
		for(int i=0;i<high;++i)
		{
			if(data[i]) delete data[i]; 
			data[i]=0; data[i]=new list<int>;
			for(list<int>::iterator tmp=S.data[i]->begin();tmp!=S.data[i]->end();tmp++)
				data[i]->push_back(*tmp);
		}
		return *this;
	}
	
	bool empty() const
	{
		return(_card==0);
	}
	int card() const			//мощность множества
	{
		return _card;
	}
	
	void add(const T& elem)		//добавить элемент
	{
		if((*this)>elem) return;
		int i=hash(elem);
		if(!data[i]) data[i]=new list<int>; 
		data[i]->push_front(int(elem)); _card++;
	}
	void del(const T& elem)		//удалить элемент
	{
		int i=hash(elem);
		if( data[i] && (*this)>elem )
		{
			data[i]->remove(int(elem)); 
			_card--; 
		}
	}
  bool operator > (const T& elem) const		//есть ли элемент в множестве
	{
		int i=hash(elem);
		if(data[i]&&!data[i]->empty()) 
			for(list<int>::iterator tmp=data[i]->begin(); tmp!=data[i]->end();tmp++) 
				if(int(elem)==(*tmp)) return true;
		return false;
	}
	
	void clear()		//очистить множество
	{
		for(int i=0;i<high;i++) 
			if(data[i]) data[i]->clear();
	}
	
	friend ostream& operator << (ostream& out, const set_of<T>& SO)
	{
		for(int i=0;i<SO.high;++i)
		{
			if(SO.data[i] && !SO.data[i]->empty())
			{
				for(list<int>::iterator tmp=SO.data[i]->begin(); tmp!=SO.data[i]->end();tmp++)
					out<<T(*tmp)<<" ";
				out<<"\n";
			}
		}
		return out;
	}

	friend istream& operator >> (istream& in, set_of<T>& SO)
	{
		T elem;
		char buf;
		
		do
		{
			in>>elem;
			SO.add(elem);
			cout<<">"; in>>buf;
		}while(!in.eof() && buf!='e');
		return in;
	}

	bool operator == (const set_of<T>& SO) const		//равенство
	{
		if(type.compare(SO.type)) throw exSet(1);
		return ( (*this)<=SO && SO<=(*this) );
	}
	bool operator <= (const set_of<T> SO) const		//включение множества
	{
		if(type.compare(SO.type)) throw exSet(1);
		for(int i=0;i<high;++i)
			if(data[i]&&!data[i]->empty()) for(list<int>::iterator tmp=data[i]->begin(); tmp!=data[i]->end(); tmp++)
				if(!(SO>(*tmp))) return false;
		return true;
	}
	set_of<T> operator & (const set_of<T> SO) const	//пересечение
	{
		if(type.compare(SO.type)) throw exSet(1);
		set_of<T> SoT;
		for(int i=0;i<high;++i)
			if(data[i]&&!data[i]->empty()) for(list<int>::iterator tmp=data[i]->begin(); tmp!=data[i]->end(); tmp++)
				if((SO>(*tmp))) SoT.add(*tmp);
		return SoT;
	}
	set_of<T> operator | (const set_of<T> SO) const	//объединение
	{
		if(type.compare(SO.type)) throw exSet(1);
		set_of<T> SoT(SO);
		for(int i=0;i<high;++i)
			if(data[i]&&!data[i]->empty()) for(list<int>::iterator tmp=data[i]->begin(); tmp!=data[i]->end(); tmp++)
				SoT.add(*tmp);
		return SoT;
	}
	set_of<T> operator - (const set_of<T> SO) const	//разность
	{
		if(type.compare(SO.type)) throw exSet(1);
		set_of<T> SoT; SoT.high=high;
		for(int i=0;i<high;++i)
			if(data[i]&&!data[i]->empty()) for(list<int>::iterator tmp=data[i]->begin(); tmp!=data[i]->end(); tmp++)
				if(!(SO>(*tmp))) SoT.add(*tmp);
		return SoT;
	}
	set_of<T> operator ^ (const set_of<T> SO) const	//симметрическая разность
	{
		if(type.compare(SO.type)) throw exSet(1);
		return ((SO-(*this))|((*this)-SO));
	}
};

template<typename T> class iter_set
{
	const set_of<T>* set;
	int clevel;							//номер уровня
	list<int>::iterator celem;			//указатель итератора на элемент на соответствующем уровне
public:
	iter_set(const set_of<T>& SO)
	{
		set=&SO;
	}
	~iter_set()
	{
		set=0;
	}
	void begin()
	{
		int i;
		if(set->empty()) throw exIter(1);
		for(i=0;i<set->high && !set->data[i];++i);
		clevel=i;
		celem=set->data[i]->begin();
	}
    void end()
	{
		int i;
		if(set->empty()) throw exIter(1);
		for(i=set->high-1;i>=0 && !set->data[i];--i);
		clevel=i;
		celem=set->data[i]->end();
	}
	bool start()
	{
		for(int i=clevel-1;i>=0;--i)
			if(set->data[i]) return false;
		if(celem==set->data[clevel]->begin()) return true;
		return false;	
	}
	bool done()
	{
		for(int i=clevel+1;i<set->high;++i)
			if(set->data[i]) return false;
		if(celem==set->data[clevel]->end()) return true;
		return false;
	}
	void operator ++ ()
	{
		if(end()) return;
		celem++;
		if(celem!=set->data[clevel]->end()) return;
		for(int i=clevel+1;i<set->high;++i)
			if(set->data[i]) 
			{
				clevel=i;
				celem=set->data[i]->begin();
				return;
			}
	}
	void operator -- ()
	{
		if(start()) return;
		if(celem!=set->data[clevel]->begin()){ celem--; return; }
		if(clevel>1)
			for(int i=clevel-1; i>=0; --i)
				if(set->data[i])
				{
					clevel=i;
					for(celem=set->data[i]->begin(); (*celem)!=set->data[i]->back(); celem++);
					return;
				}
	}
	T operator *()
	{
		if(!set->empty()) return *celem;
		throw exIter(1);
	}
};

#endif