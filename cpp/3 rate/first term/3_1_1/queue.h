#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "man_adv.h"
#include "man_chn.h"
#include "room.h"

struct elemq
{
	elem* info;
	elemq* next;

	elemq(const elem* e):next(0)
	{
		info=e->getcopy();
	}
	
	elemq(const elemq& e)
	{
		info=e.info->getcopy();
		next=e.next;
	}
	
	~elemq()
	{
		delete info;
	}

	elemq& operator = (const elemq& e)
	{
		if(this==&e) return *this;

		delete info;
		info=e.info->getcopy();
		next=e.next;

		return *this;
	}

	friend ostream& operator << (ostream& out, const elemq& e)
	{
		out<<e.info;
		return out;
	}
	friend ostream& operator << (ostream& out, const elemq* e)
	{
		out<<e->info;
		return out;
	}
	
};

class _queue:public elem
{
	elemq* head;
	elemq* end;
	int leng;

	void print(ostream& out)	const
	{
		if(head)
			for(elemq* tmp=head;tmp!=end->next;tmp=tmp->next)
				cout<<tmp<<endl;
	}
	void fill(istream& in){}
	void destroy()
	{
		while(head)
		{
			elemq* tmp = head;
			head = head->next;
			delete tmp;
		}
	}
public:
	_queue():head(0), end(0), leng(0)
	{
	}

	_queue(const _queue& q)
	{
		leng=q.leng;
		elemq* tmp=q.head;
		if(tmp)
		{
			head=new elemq(tmp->info);
			end=head;
			tmp=tmp->next;
			for(tmp;tmp;tmp=tmp->next)
				push(tmp->info);
			return;
		}
		head=end=0;
	}

	~_queue()
	{
		destroy();
	}

	_queue& operator =(const _queue& q)
	{
		if(this==&q) return *this;

		leng=q.leng;

		destroy();

		elemq* tmp=q.head;
					
		if(tmp)
		{
			head=new elemq(tmp->info);
			end=head;
			tmp=tmp->next;
			for(tmp;tmp;tmp=tmp->next)
				push(tmp->info);
		}
		else head=end=0;
		return *this;
	}

	elem* getcopy()		const
	{
		return new _queue(*this);
	}


	const elem* get_head() const
	{
		return head->info;
	}
	const elem* pop()
	{
		if(head)
		{
			elemq* new_h=head->next;
			elemq* tmp=head;
			head->next=0;
			head=new_h;
			return tmp->info;
			leng--;
		}
	}

	const elem* get_end() const
	{
		return end->info;
	}
	
	void push(const elem* e)
	{
		elemq* tmp=new elemq(e);
		
		leng++;
		if(end) end=end->next=tmp;
		else end=head=tmp; 
		end->next=0;
	}

	void clear()
	{
		destroy();
		head=end=0;
		leng=0;
	}

	friend ostream& operator << (ostream& out, const _queue& q)
	{
		q.print(out);
		return out;
	}
};
#endif