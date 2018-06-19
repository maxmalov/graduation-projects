#include "figure.h"
class rectangle:public figure
{
	POINT LeftTop, RightBottom;
	rectangle(){}
public:
	rectangle(POINT LT, POINT RB, COLORREF BC, COLORREF IC)
	{
		LeftTop=LT;
		RightBottom=RB;
		IColor=IC;
		BColor=BC;
	}
	rectangle(int nRem)
	{
		LeftTop.x=rand()%nRem;
		LeftTop.y=rand()%nRem;
		RightBottom.x=rand()%nRem;
		RightBottom.y=rand()%nRem;
		IColor=RGB(rand()%256,rand()%256,rand()%256);
		BColor=RGB(rand()%256,rand()%256,rand()%256);
	}
		
	~rectangle(){}

	figure* copy()	const
	{
		return new rectangle(*this);
	}

	void SetAll(POINT LT, POINT RB, COLORREF BC, COLORREF IC)
	{
		LeftTop=LT;
		RightBottom=RB;
		IColor=IC;
		BColor=BC;
	}

	void draw(HDC hdc)	const
	{
		HPEN hPen=CreatePen(PS_SOLID,1,BColor), hPenOld=(HPEN)SelectObject(hdc,hPen);
		HBRUSH hBrush=CreateSolidBrush(IColor), hBrushOld=(HBRUSH)SelectObject(hdc,hBrush);
		
		Rectangle(hdc, LeftTop.x, LeftTop.y, RightBottom.x, RightBottom.y);
		SelectObject(hdc,hPenOld);
		SelectObject(hdc,hBrushOld);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}

};