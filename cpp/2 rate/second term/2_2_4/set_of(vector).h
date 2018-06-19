#ifndef _SET_OF_
#define _SET_OF_
#include "fail.h"
#include<typeinfo>
#include<vector>
#include<list>
#include<string>

const int msize=256;
template <typename T> class iter_set;

template <typename T> class set_of
{
	friend class iter_set<T>;
	struct space
	{
		int lind, rind;
		vector<bool> interval;
	};

	list<space> data;
	int _card;
	string type;
	int hash(const T&x)
	{
		int ind=int(x);
		int cur=0;
		list<space>::iterator tmp=data.begin();
		while((*tmp).rind<ind){ tmp++; cur++; }
		if((*tmp).lind>ind) throw exSet(2);
		return cur;
	}
public:
	set_of()
	{
		space tmp;
		tmp.lind=0; tmp.rind=msize-1;
		tmp.interval.resize(msize);
		for(int i=0;i<msize;++i) tmp.interval[i]=0;
		data.push_front(tmp);
		type=typeid(T).name();
		_card=0;
	}
	set_of(const T& x, const T& y)
	{
		int l=int(x), r=int(y);
		if(l>r) throw exSet(1);
		space tmp;
		int len;
		if(len=r-l+1<257)
		{
			tmp.lind=l; tmp.rind=r;
			tmp.interval.resize(len);
			for(int i=0;i<len;++i) tmp.interval[i]=0;
			data.push_front(tmp);
		}
		else
		{
			tmp.lind=0; tmp.rind=-1;
			do
			{
				tmp.lind=tmp.rind+1;
				tmp.rind+=msize;
				tmp.interval.resize(msize);
				for(int i=0;i<msize;++i) tmp.interval[i]=0;
				data.push_back(tmp);
				len-=256;
			}while(len>257);
			tmp.lind=tmp.rind+1;
			tmp.rind+=len;
			tmp.interval.resize(len+1);
			for(int i=0;i<len+1;++i) tmp.interval[i]=0;
			data.push_back(tmp);
		}
		type=typeid(T).name();
		_card=0;
	}

	int card() const
	{
		return _card;
	}
	bool empty() const
	{
		for(list<space>::const_iterator tmp=data.begin(); tmp!=data.end(); tmp++)
			for(int i=0;i<(*tmp).rind-(*tmp).lind+1;++i)
				if((*tmp).interval[i]==1) return false;
		return true;
	}
	
	void add(const T& x)
	{
		int tmp=hash(x), ind=int(x);
		list<space>::iterator cur;
		for(cur=data.begin(), tmp; tmp>0; cur++, tmp--);
		if(!(*cur).interval[ind]){ (*cur).interval[ind]=1; ++_card; }		
	}
	void del(const T& x)
	{
		int tmp=hash(x), ind=int(x);
		list<space>::iterator cur=data.begin(); cur++;
		for(cur=data.begin(), tmp; tmp>=0; cur++, tmp--);
		if((*cur).interval[ind]){ (*cur).interval[ind]=0; --_card; }				
	}

	bool operator > (const T& x) const
	{
		try
		{
			int tmp=hash(x);
			list<space>::iterator cur
			for(cur=data.begin(), tmp; tmp>=0; cur++, tmp--);
			return (*cur).interval[int(x)-tmp.lind];
		}
		catch(exSet){return false;}
	}

	void clear()
	{
		data.clear();
	}
	
	friend ostream& operator << (ostream& out, const set_of<T>& S)
	{
		for(list<space>::const_iterator tmp=S.data.begin(); tmp!=S.data.end(); tmp++)
		{
			for(int i=(*tmp).lind;i<(*tmp).rind;++i)
				if((*tmp).interval[i-(*tmp).lind]) out<<T(i)<<" ";
			out<<"\n";
		}
		return out;
	}
	friend istream& operator >> (istream& in, set_of<T>& S)
	{
		T elem;
		char buf;
		
		do
		{
			try
			{
				in>>elem;
				S.add(elem);
				cout<<">"; in>>buf;
			}
			catch(exSet){buf='n';}
		}while(!in.eof() && buf!='e');
		return in;
	}
};
#endif