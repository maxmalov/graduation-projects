#ifndef _MAN_CHN_H_
#define _MAN_CHN_H_

#include "man.h"
class man_chn: public man
{
	void print(ostream& out)	const
	{
		out<<name<<", "<<sname<<" has children";
	}
public:
	man_chn():man(){}

	man_chn(char* n, char* s): man(n,s){}

	man_chn(const man_chn& m):man(m){}

	~man_chn(){}

	man_chn& operator = (const man_chn& m)
	{
		if(this!=&m) *((man*)this) = m;
		return *this;
	}

	elem* getcopy()	const
	{
		return new man_chn(*this);
	}
};
#endif