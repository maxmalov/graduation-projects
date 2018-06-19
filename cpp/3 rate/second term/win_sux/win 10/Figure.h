#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

class Figure
{
	public:
		virtual Figure* Copy()const = 0;
		virtual void Draw(HDC hdc)const = 0;
		virtual~Figure(){}
};

class Circle: public Figure
{
	private:
		POINT ptCenter;
		int iR;
		COLORREF rgbBrushColor, rgbPenColor;
	public:
		Circle();
		Circle(int xCenter, int yCenter, int i, COLORREF rgbBC, COLORREF rgbPC);
		Figure* Copy()const;
		void Draw(HDC hdc)const;
};

class Triangle: public Figure
{
	private:
		POINT ptA, ptB, ptC;
		COLORREF rgbBrushColor, rgbPenColor;
	public:
		Triangle();
		Triangle(POINT pt1, POINT pt2, POINT pt3, COLORREF rgbBC, COLORREF rgbPC);
		Figure* Copy()const;
		void Draw(HDC hdc)const;
};

class Rectangl: public Figure
{
	private:
		RECT rect;
		COLORREF rgbBrushColor, rgbPenColor;
	public:
		Rectangl();
		Rectangl(int xLeft, int yTop, int xRight, int yBottom, COLORREF rgbBC, COLORREF rgbPC);
		Figure* Copy()const;
		void Draw(HDC hdc)const;
};
#endif