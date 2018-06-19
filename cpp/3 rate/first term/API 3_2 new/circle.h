#include "figure.h"
class circle:public figure
{
	POINT center;
	INT nRadius;
	circle(){}
public:
	circle(POINT c, INT nRad, COLORREF BC, COLORREF IC)
	{
		center=c;
		nRadius=nRad;
		IColor=IC;
		BColor=BC;
	}
	circle(int nRem)
	{
		center.x=rand()%nRem;
		center.y=rand()%nRem;
		nRadius=rand()%(int)(nRem/4);
		IColor=RGB(rand()%256,rand()%256,rand()%256);
		BColor=RGB(rand()%256,rand()%256,rand()%256);
	}

	~circle(){}

	figure* copy()	const
	{
		return new circle(*this);
	}

	void SetAll(POINT c, INT nRad, COLORREF BC, COLORREF IC)
	{
		center=c;
		nRadius=nRad;
		IColor=IC;
		BColor=BC;
	}
	
	void draw(HDC hdc)	const
	{
		HPEN hPen=CreatePen(PS_SOLID,1,BColor), hPenOld=(HPEN)SelectObject(hdc,hPen);
		HBRUSH hBrush=CreateSolidBrush(IColor), hBrushOld=(HBRUSH)SelectObject(hdc,hBrush);

		Ellipse(hdc,center.x-nRadius, center.y+nRadius, center.x+nRadius, center.y-nRadius);
		SelectObject(hdc,hPenOld);
		SelectObject(hdc,hBrushOld);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}

};