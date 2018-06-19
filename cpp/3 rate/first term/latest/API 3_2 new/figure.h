#pragma once
#include"windows.h"
class figure
{
protected:
	COLORREF BColor, IColor;
public:
	virtual ~figure(){}

	virtual void draw(HDC hdc) const =0;

	virtual figure* copy() const = 0;
};