#ifndef _HASH_
#define _HASH_
#include"set_of(hash_table).h"

template <typename T> class iter_hash;

template <typename SET> class hash_table
{
	friend class iter_hash<SET>;
	vector< list<SET>* > data;
	int high;
	int hash(const SET& S)
	{
		return (S.card()%high);
	}
public:
	hash_table()
	{
		high=default_high;
		data.resize(default_high);
	}
	hash_table(const hash_table<SET>& h)
	{
		high=h.high;
		data.resize(high);
		for(int i=0;i<high;++i)
		{	
			data[i]=0;
			if(S.data[i])
			{ 
				data[i]=new list<SET>;
				for(list<SET>::iterator tmp=S.data[i]->begin();tmp!=S.data[i]->end();tmp++)
				data[i]->push_back(*tmp);
			}
		}
	}
	~hash_table()
	{
		for(int i=0;i<high;++i) delete data[i];
	}
	hash_table<SET>& operator = (const hash_table<SET>& h)
	{
		if(this==&h) return *this;
		data.resize(h.high);
		high=S.high;
		for(int i=0;i<high;++i)
		{
			if(data[i]) delete data[i]; 
			data[i]=0; data[i]=new list<set_of<T>>;
			for(list<SET>::iterator tmp=S.data[i]->begin();tmp!=S.data[i]->end();tmp++)
				data[i]->push_back(*tmp);
		}
		return *this;
	}
	bool empty()	const
	{
		for(int i=0;i<high;++i)
			if(!data[i]) return false;
			else if(data[i]->empty()) return false;
		return true;
	}
	void add(const SET& S)
	{
		int i=hash(S);
		if(!data[i]) data[i]=new list<SET>;
		for(list<SET>::iterator tmp=data[i]->begin(); tmp!=data[i]->end(); tmp++)
			if(*tmp==S) return;
		data[i]->push_front(S);
	}
	void del(const SET& S)
	{
		int i=hash(S);
		if(data[i]) data[i]->remove(S);
	}
	void clear()
	{
		for(int i=0;i<high;++i)
			if(data[i]) data[i]->clear();
	}
	const list<SET>& operator [](int elem) const
	{
		if(elem>=0 && elem<high && data[elem]) return *data[elem];
		else throw exHT(1);
	}

	list<SET>& operator [](int elem)
	{
		if(elem>=0 && elem<high && data[elem]) return *data[elem];
		else throw exHT(1);
	}
};

template <typename SET> class iter_hash
{
	const hash_table<SET>* ht;
	int clevel;									//номер уровня
	typename list<SET>::iterator celem;			//указатель итератора на элемент на соответствующем уровне
public:
	iter_hash(const hash_table<SET>& H)
	{
		ht=&H;
	}
	~iter_hash()
	{
		ht=0;
	}
	void begin()
	{
		int i;
		if(ht->empty()) throw exIter(1);
		for(i=0;i<ht->high && !ht->data[i];++i);
		clevel=i;
		celem=ht->data[i]->begin();
	}
    void end()
	{
		int i;
		if(ht->empty()) throw exIter(1);
		for(i=ht->high-1;i>=0 && !ht->data[i];--i);
		clevel=i;
		celem=ht->data[i]->end();
	}
	bool start()	const
	{
		for(int i=clevel-1;i>=0;--i)
			if(ht->data[i]) return false;
		if(celem==ht->data[clevel]->begin()) return true;
		return false;	
	}
	bool done()		const
	{
		for(int i=clevel+1;i<ht->high;++i) if(ht->data[i]) return false;
		if(celem==ht->data[clevel]->end()) return true;
		return false;
	}
	void operator ++ ()
	{
		if(done()) return;
		celem++;
		if(celem!=ht->data[clevel]->end()) return;
		for(int i=clevel+1;i<ht->high;++i)
			if(ht->data[i]) 
			{
				clevel=i;
				celem=ht->data[i]->begin();
				return;
			}
	}
	void operator -- ()
	{
		if(start()) return;
		if(celem!=ht->data[clevel]->begin()){ celem--; return; }
		if(clevel>1)
			for(int i=clevel-1; i>=0; --i)
				if(ht->data[i])
				{
					clevel=i;
					for(celem=ht->data[i]->begin(); !((*celem)==ht->data[i]->back()); );
					return;
				}
	}
	SET operator *()		const
	{
		if(!ht->empty()) return *celem;
		throw exIter(1);
	}
};
#endif