#ifndef _ELEM_H_
#define _ELEM_H_
class elem
{
protected:
	virtual void print(ostream&)const=0;
	virtual void fill(istream&)=0;
public:
	virtual elem* getcopy() const=0;
	virtual ~elem(){};
	
	friend ostream& operator << (ostream& out, const elem* e)
	{
		e->print(out);
		return out;
	}
	friend istream& operator >> (istream& in, elem* e)
	{
		e->fill(in);
		return in;
	}
};
#endif