#include "figure.h"
class triangle:public figure
{
	POINT A,B,C;
public:
	triangle(POINT _A, POINT _B, POINT _C, COLORREF BC, COLORREF IC)
	{
		A=_A;
		B=_B;
		C=_C;
		IColor=IC;
		BColor=BC;
	}
	~triangle(){}
	triangle(int nRem)
	{
		A.x=rand()%nRem;
		A.y=rand()%nRem;
		B.x=rand()%nRem;
		B.y=rand()%nRem;
		C.x=rand()%nRem;
		C.y=rand()%nRem;
		IColor=RGB(rand()%256,rand()%256,rand()%256);
		BColor=RGB(rand()%256,rand()%256,rand()%256);
	}

	figure* copy() const
	{
		return new triangle(*this);
	}

	void SetAll(POINT _A, POINT _B, POINT _C, COLORREF BC, COLORREF IC)
	{
		A=_A;
		B=_B;
		C=_C;
		IColor=IC;
		BColor=BC;
	}
	void draw(HDC hdc) const
	{
		POINT Points[]={A,B,C};
		HPEN hPen=CreatePen(PS_SOLID,1,BColor), hPenOld=(HPEN)SelectObject(hdc,hPen);
		HBRUSH hBrush=CreateSolidBrush(IColor), hBrushOld=(HBRUSH)SelectObject(hdc,hBrush);

		Polygon(hdc,Points,3);
		SelectObject(hdc,hPenOld);
		SelectObject(hdc,hBrushOld);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}
};