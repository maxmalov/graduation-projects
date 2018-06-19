#include "Figure.h"
#include "stdafx.h"

Circle::Circle()
{
	ptCenter.x = 0;
	ptCenter.y = 0;
	iR = 0;
	rgbBrushColor = 0;
	rgbPenColor = 0;
}

Circle::Circle(int xCenter, int yCenter, int i, COLORREF rgbBC, COLORREF rgbPC)
{
	ptCenter.x = xCenter;
	ptCenter.y = yCenter;
	iR = i;
	rgbBrushColor = rgbBC;
	rgbPenColor = rgbPC;
}

Figure* Circle::Copy() const
{
	return new Circle(*this);
}


void Circle::Draw(HDC hdc)const
{
	HPEN hPen = CreatePen(PS_SOLID, 1, rgbPenColor);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);
	
	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(rgbBrushColor);
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	
	Ellipse(hdc, ptCenter.x-iR, ptCenter.y-iR, ptCenter.x+iR, ptCenter.y+iR);
	
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}
//*****************************************************************
Triangle::Triangle()
{
	rgbBrushColor = 0;
	rgbPenColor = 0;

	ptA.x = 0;
	ptA.y = 0;
	ptB.x = 0;
	ptB.y = 0;
	ptC.x = 0;
	ptC.y = 0;
}

Triangle::Triangle(POINT pt1, POINT pt2, POINT pt3, COLORREF rgbBC, COLORREF rgbPC)
{
	ptA = pt1;
	ptB = pt2;
	ptC = pt3;
	rgbBrushColor = rgbBC;
	rgbPenColor = rgbPC;
}

Figure* Triangle::Copy() const
{
	return new Triangle(*this);
}

void Triangle::Draw(HDC hdc)const
{
	HPEN hPen = CreatePen(PS_SOLID, 1, rgbPenColor);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);
	
	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(rgbBrushColor);
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	
	POINT pt[3] = {ptA, ptB, ptC};
	Polygon(hdc, pt, 3);
	
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}
//*****************************************************************

Rectangl::Rectangl()
{
	rgbBrushColor = 0;
	rgbPenColor = 0;
	
	rect.left = 0;
	rect.top = 0;
	rect.right = 0;
	rect.bottom = 0;
}

Rectangl::Rectangl(int xLeft, int yTop, int xRight, int yBottom, COLORREF rgbBC, COLORREF rgbPC)
{
	rect.left = xLeft;
	rect.top = yTop;
	rect.right = xRight;
	rect.bottom = yBottom;
	rgbBrushColor = rgbBC;
	rgbPenColor = rgbPC;
}

Figure* Rectangl::Copy() const
{
	return new Rectangl(*this);
}

void Rectangl::Draw(HDC hdc)const
{
	HPEN hPen = CreatePen(PS_SOLID, 1, rgbPenColor);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);
	
	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(rgbBrushColor);
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}
