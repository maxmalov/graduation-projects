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

	CRITICAL_SECTION g_cs;


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
		
		head=end=0;
		leng=0;
	}
public:
	_queue():head(0), end(0), leng(0)
	{
		InitializeCriticalSection(&g_cs);
	}

	_queue(const _queue& q)
	{
		InitializeCriticalSection(&g_cs);
		
		EnterCriticalSection((LPCRITICAL_SECTION)&q.g_cs);
		
		leng=q.leng;
		elemq* tmp=q.head;
		if(tmp)
		{
			head=new elemq(tmp->info);
			end=head;
			tmp=tmp->next;
			for(tmp;tmp;tmp=tmp->next)
				push(tmp->info);
			
			LeaveCriticalSection((LPCRITICAL_SECTION)&q.g_cs);
			return;
		}

		LeaveCriticalSection((LPCRITICAL_SECTION)&q.g_cs);
		head=end=0;
	}

	~_queue()
	{
		EnterCriticalSection(&g_cs);
		destroy();
		LeaveCriticalSection(&g_cs);
		
		DeleteCriticalSection(&g_cs);
	}

	_queue& operator = (const _queue& q)
	{
		EnterCriticalSection( &g_cs );
		
		if(this != &q)
		{
			EnterCriticalSection((LPCRITICAL_SECTION)&q.g_cs);
			
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
				
				LeaveCriticalSection((LPCRITICAL_SECTION)&q.g_cs);
				LeaveCriticalSection(&g_cs);
				
				return *this;
			}
			
			LeaveCriticalSection((LPCRITICAL_SECTION)&q.g_cs);
			head=end=0;
		}

		LeaveCriticalSection(&g_cs);
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
			EnterCriticalSection(&g_cs);

			elemq* tmp = head;
			head = head->next;		
			leng--;
			tmp->next = 0;
			
			LeaveCriticalSection(&g_cs);
						
			//elemq* new_h=head->next;
			//head=new_h;

			elem* info = tmp->info->getcopy();
			delete tmp;
		
			return info;
		}
	}

	const elem* get_end() const
	{
		return end->info;
	}
	
	void push(const elem* e)
	{
		elemq* tmp=new elemq(e);
		
		EnterCriticalSection(&g_cs);
		
		leng++;
		if(end) end=end->next=tmp;
		else end=head=tmp; 
		end->next=0;

		LeaveCriticalSection(&g_cs);
	}

	void clear()
	{
		destroy();
	}

	friend ostream& operator << (ostream& out, const _queue& q)
	{
		q.print(out);
		return out;
	}
};
#endif