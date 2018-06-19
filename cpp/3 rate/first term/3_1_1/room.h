#ifndef _ROOM_H_
#define _ROOM_H_
#include "elem.h"

class room: public elem
{
	int number;
	room(){}
	void print(ostream& out)	const
	{
		out<<"Room #"<<number;
	}
	void fill(istream& in)
	{
		cout<<"Set number: "; in>>number;
	}
public:
	room(int n):number(n)
	{
	}

	int get_number()	const
	{
		return number;
	}
	void set_number(int n)
	{
		number=n;
	}

	elem* getcopy() const
	{
		return new room(*this);
	}
};
#endif