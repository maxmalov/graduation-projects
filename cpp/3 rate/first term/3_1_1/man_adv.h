#ifndef _MAN_ADV_H_
#define _MAN_ADV_H_

#include "man.h"
class man_adv :public man
{
	void print(ostream& out)	const
	{
		out<<name<<", "<<sname<<" has advantages";
	}
public:
	man_adv():man(){}

	man_adv(char* n, char* s): man(n,s){}

	man_adv(const man_adv& m):man(m){}

	~man_adv(){}

	man_adv& operator = (const man_adv& m)
	{
		if(this!=&m) *((man*)this) = m;
		return *this;
	}
	
	elem* getcopy()	const
	{
		return new man_adv(*this);
	}
};
#endif