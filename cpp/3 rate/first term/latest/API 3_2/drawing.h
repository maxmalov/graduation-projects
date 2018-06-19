#include <commctrl.h>
#include<time.h>
#include <tchar.h>
#include "dialogs.h"

void				ShowLoadedBmp(HWND, HDC, HBITMAP, HBITMAP);
void				SaveCurrentBmp(LPCTSTR , HBITMAP);
void				AdjustMenuItem(HMENU, HWND, HWND, UINT, UINT);
void				DrawCircle(HDC, POINT, COLORREF, int);	
void				DrawRectangle(HDC, POINT, COLORREF, int, int);
void				DrawTriangle(HDC, POINT, POINT, POINT, COLORREF);

void DrawCircle(HDC hdc, POINT center, COLORREF color, int nRadius)
{
	HPEN hPen=CreatePen(PS_SOLID,1,color), 
		hPenOld=(HPEN)SelectObject(hdc,hPen);
	HBRUSH hBrush=CreateSolidBrush(color),
		hBrushOld=(HBRUSH)SelectObject(hdc,hBrush);

	Ellipse(hdc,center.x-nRadius, center.y+nRadius, center.x+nRadius, center.y-nRadius);
	SelectObject(hdc,hPenOld);
	SelectObject(hdc,hBrushOld);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}
void DrawRectangle(HDC hdc, POINT LeftTop, COLORREF color, int nWidth, int nHeight)
{
	HPEN hPen=CreatePen(PS_SOLID,1,color), 
		hPenOld=(HPEN)SelectObject(hdc,hPen);
	HBRUSH hBrush=CreateSolidBrush(color),
		hBrushOld=(HBRUSH)SelectObject(hdc,hBrush);
	
	Rectangle(hdc, LeftTop.x, LeftTop.y, LeftTop.x + nWidth , LeftTop.y - nHeight);
	SelectObject(hdc,hPenOld);
	SelectObject(hdc,hBrushOld);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}
void DrawTriangle(HDC hdc, POINT A, POINT B, POINT C, COLORREF color)
{
	HPEN hPen=CreatePen(PS_SOLID,1,color), 
		hPenOld=(HPEN)SelectObject(hdc,hPen);
	HBRUSH hBrush=CreateSolidBrush(color),
		hBrushOld=(HBRUSH)SelectObject(hdc,hBrush);
	POINT Points[]={A,B,C};

	Polygon(hdc,Points,3);
	SelectObject(hdc,hPenOld);
	SelectObject(hdc,hBrushOld);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}
///


void ShowLoadedBmp(HWND hWndView, HDC hMemDC, HBITMAP hBmpLoad, HBITMAP hBmpOld, RECT& rScreen)
{
	//int xScreen = GetSystemMetrics(SM_CXSCREEN), yScreen = GetSystemMetrics(SM_CYSCREEN);
	
	FillRect(hMemDC,&rScreen,(HBRUSH)(COLOR_WINDOW+1));
	HDC hdc = GetDC(hWndView);
	HDC hdcTmp = CreateCompatibleDC(hdc); 
	BITMAP bm; 
	GetObject(hBmpLoad,sizeof(bm),&bm);
	hBmpOld = (HBITMAP)SelectObject(hdcTmp,hBmpLoad);
	StretchBlt(hMemDC,0,0,bm.bmWidth, bm.bmHeight, hdcTmp, 0,0, bm.bmWidth, bm.bmHeight,SRCCOPY);
	SelectObject(hdcTmp,hBmpOld);
	DeleteObject(hBmpLoad);
	DeleteDC(hdcTmp);
	ReleaseDC(hWndView,hdc);
}

void SaveCurrentBmp(LPCTSTR lpszFileName, HBITMAP hSaveBmp)
{
	BITMAP bm;
	BITMAPFILEHEADER bh;
	BITMAPINFO bi;
	HDC hdc;
	LPBYTE Buf;
	DWORD ColorSize,DataSize;
	WORD BitCount;
	HANDLE hDestFile;
	DWORD dwTemp;

	GetObject(hSaveBmp, sizeof(BITMAP), (LPSTR)&bm);

	BitCount = (WORD)bm.bmPlanes * bm.bmBitsPixel;
	if(BitCount == 32) 
		ColorSize = sizeof(RGBQUAD) * (1 << BitCount);
	else ColorSize = 0;

	DataSize = (bm.bmWidth*BitCount)/8*bm.bmHeight;

	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = bm.bmWidth;
	bi.bmiHeader.biHeight = bm.bmHeight;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = BitCount;
	bi.bmiHeader.biCompression = 0;
	bi.bmiHeader.biSizeImage = DataSize;
	bi.bmiHeader.biXPelsPerMeter = bi.bmiHeader.biYPelsPerMeter = 0;
	(BitCount < 24)?(bi.bmiHeader.biClrUsed = (1<<BitCount)):(bi.bmiHeader.biClrUsed = 0);
	bi.bmiHeader.biClrImportant = 0;

	bh.bfType = 0x4d42;
	bh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+ bi.bmiHeader.biClrUsed * sizeof(RGBQUAD);
	bh.bfReserved1 = 0;
	bh.bfReserved2 = 0;
	bh.bfSize = bh.bfOffBits + DataSize;

	Buf = (LPBYTE)GlobalAlloc(GMEM_FIXED, DataSize);

	hdc = GetDC(0);
	GetDIBits(hdc, hSaveBmp, 0,(WORD)bm.bmHeight, Buf, &bi, DIB_RGB_COLORS);
	ReleaseDC(0, hdc);

	hDestFile=CreateFile(lpszFileName,GENERIC_READ | GENERIC_WRITE, 0, NULL, 
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	
	WriteFile(hDestFile,&bh,sizeof(BITMAPFILEHEADER),&dwTemp,NULL);
	WriteFile(hDestFile,&bi,sizeof(BITMAPINFOHEADER) + bi.bmiHeader.biClrUsed * sizeof(RGBQUAD),&dwTemp,NULL);
	WriteFile(hDestFile,Buf,DataSize,&dwTemp,NULL);

	CloseHandle(hDestFile);
	
	GlobalFree((HGLOBAL)Buf);
}

void AdjustMenuItem(HMENU hMenu, HWND hWndView, HWND hWndStB, UINT dID, UINT strID)
{
	TCHAR info[MAX_LOADSTRING];
	CheckMenuRadioItem(hMenu,IDM_CIRCLE,IDM_TRIANGLE,IDM_CIRCLE,MF_BYCOMMAND);
	SendMessage(hWndView,WM_APP,(WPARAM)MYI_SETDRAWMODE,(LPARAM)dID);
	LoadString(hInst, strID, info, MAX_LOADSTRING);
	SendMessage(hWndStB,SB_SETTEXT,0,(LPARAM)&info);
}