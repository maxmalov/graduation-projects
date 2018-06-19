#include "rect.h"
#include "triangle.h"
#include "circle.h"

struct elemq
{
	figure* info;
	elemq* next;

	elemq(const figure* f):next(0)
	{
		info=f->copy();
	}
	
	elemq(const elemq& e)
	{
		info=e.info->copy();
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
		info=e.info->copy();
		next=e.next;

		return *this;
	}
};

class _queue
{
	elemq* head;
	elemq* end;
	int leng;
	
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

		destroy();

		elemq* tmp=q.head;
		leng=q.leng;		
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

	int get_leng()	const
	{
		return leng;
	}

	const figure* get_head() const
	{
		return head->info;
	}
	const figure* pop()
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

	const figure* get_end() const
	{
		return end->info;
	}
	
	void push(const figure* e)
	{
		elemq* tmp=new elemq(e);
		
		if(end) end=end->next=tmp;
		else end=head=tmp; 
		end->next=0;
		leng++;
	}

	void clear()
	{
		destroy();
		head=end=0;
		leng=0;
	}

	void print(HDC hdc)	const
	{
		if(head)
			for(elemq* tmp=head;tmp!=end->next;tmp=tmp->next)
				tmp->info->draw(hdc);
	}
};
