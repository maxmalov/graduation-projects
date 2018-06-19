// API 3_2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "API 3_2.h"

#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib" )

#include<time.h>
#include <tchar.h>
#include "dialogs.h"

using namespace Gdiplus;



ATOM				RegisterParentClass(HINSTANCE);
ATOM				RegisterViewClass(HINSTANCE);
//ATOM				RegisterTextClass(HINSTANCE );
BOOL				InitInstance(HINSTANCE, int);
//LRESULT CALLBACK	TextProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	ViewProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

void				ShowLoadedBmp(HWND, HDC, HBITMAP, HBITMAP);
void				SaveCurrentBmp(LPCTSTR , HBITMAP);
void				AdjustMenuItem(HMENU, HWND, HWND, UINT, UINT);
void				DrawCircle(HDC, POINT, COLORREF, int);	
void				DrawRectangle(HDC, POINT, COLORREF, int, int);
void				DrawTriangle(HDC, POINT, POINT, POINT, COLORREF);

void DrawCircle(HDC hdc, POINT center, COLORREF color, int nRadius)
{
	Graphics g(hdc);
	g.DrawEllipse(&Pen(color), RectF(center.x-nRadius, center.y+nRadius, 2*nRadius, 2*nRadius));
	g.FillEllipse(&SolidBrush(color), RectF(center.x-nRadius, center.y+nRadius, 2*nRadius, 2*nRadius));
	
	
	//HPEN hPen=CreatePen(PS_SOLID,1,color), 
	//	hPenOld=(HPEN)SelectObject(hdc,hPen);
	//HBRUSH hBrush=CreateSolidBrush(color),
	//	hBrushOld=(HBRUSH)SelectObject(hdc,hBrush);

	//Ellipse(hdc,center.x-nRadius, center.y+nRadius, center.x+nRadius, center.y-nRadius);
	//SelectObject(hdc,hPenOld);
	//SelectObject(hdc,hBrushOld);
	//DeleteObject(hPen);
	//DeleteObject(hBrush);
}
void DrawRectangle(HDC hdc, POINT LeftTop, COLORREF color, int nWidth, int nHeight)
{
	Graphics g(hdc);
	g.DrawEllipse(&Pen(color), RectF(LeftTop.x, LeftTop.y, nWidth, nHeight));
	g.FillEllipse(&SolidBrush(color), RectF(LeftTop.x, LeftTop.y, nWidth, nHeight));

	//HPEN hPen=CreatePen(PS_SOLID,1,color), 
	//	hPenOld=(HPEN)SelectObject(hdc,hPen);
	//HBRUSH hBrush=CreateSolidBrush(color),
	//	hBrushOld=(HBRUSH)SelectObject(hdc,hBrush);
	//
	//Rectangle(hdc, LeftTop.x, LeftTop.y, LeftTop.x + nWidth , LeftTop.y - nHeight);
	//SelectObject(hdc,hPenOld);
	//SelectObject(hdc,hBrushOld);
	//DeleteObject(hPen);
	//DeleteObject(hBrush);
}
void DrawTriangle(HDC hdc, POINT A, POINT B, POINT C, COLORREF color)
{
	PointF points[] = { PointF(A.x,A.y), PointF(B.x,B.y), PointF(C.x,C.y) }; 
	Graphics g(hdc);
	g.DrawPolygon(&Pen(color), &points, 3);
	g.FillPolygon(&SolidBrush(color), &points, 3);
	
	//HPEN hPen=CreatePen(PS_SOLID,1,color), 
	//	hPenOld=(HPEN)SelectObject(hdc,hPen);
	//HBRUSH hBrush=CreateSolidBrush(color),
	//	hBrushOld=(HBRUSH)SelectObject(hdc,hBrush);
	//POINT Points[]={A,B,C};

	//Polygon(hdc,Points,3);
	//SelectObject(hdc,hPenOld);
	//SelectObject(hdc,hBrushOld);
	//DeleteObject(hPen);
	//DeleteObject(hBrush);
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


#define CIRCLE			1 
#define RECTANGLE		2 
#define TRIANGLE		3 
#define COMBO			4

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int nCmdShow)
{
	MSG msg;
	
	InitCommonControls();
	// Initialize global strings
	
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_API3_2, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDC_API3_2_VIEW, szViewClass, MAX_LOADSTRING);
	//LoadString(hInstance, IDS_TEXTCLASS, szTextClass, MAX_LOADSTRING);

	RegisterParentClass(hInstance);
	RegisterViewClass(hInstance);
	//RegisterTextClass(hInstance);
	
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;

	GdiplusStartupInput gpSI;
	ULONG_PTR gpToken;

	GdiplusStartup(&gpToken, &gpSI, 0);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	GdiplusShutdown(gpToken);

	return (int) msg.wParam;
}

ATOM RegisterParentClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_API3_2));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)CreateSolidBrush(RGB(128,128,128));
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_API3_2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
ATOM RegisterViewClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= NULL;
	wcex.lpfnWndProc	= (WNDPROC)ViewProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= 0;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szViewClass;
	wcex.hIconSm		= 0;

	return RegisterClassEx(&wcex);
}
//ATOM RegisterTextClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//
//	wcex.style			= NULL;
//	wcex.lpfnWndProc	= (WNDPROC)TextProc;
//	wcex.cbClsExtra		= 0;
//	wcex.cbWndExtra		= 0;
//	wcex.hInstance		= hInstance;
//	wcex.hIcon			= 0;
//	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground	= (HBRUSH)GetStockObject(COLOR_WINDOW+1);
//	wcex.lpszMenuName	= NULL;
//	wcex.lpszClassName	= szTextClass;
//	wcex.hIconSm		= 0;
//
//	return RegisterClassEx(&wcex);
//}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void ShowLoadedImage(HWND hWnd, Image i)
{
	HDC hdc = GetDC(hWnd);
	Graphics g(hdc);
	g.FillRectangle(Brush(Color(255,255,255,0)), 
		RectF(0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN) ) );
	g.DrawImage(&i, Point(0,0));
	ReleaseDC(hWnd, hdc);
}

LRESULT CALLBACK ViewProc(HWND hWndView,UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static int dID;
	POINT A,B,C;
	static int xMouse, yMouse;
	static COLORREF CurrentColor;

	#define nRem			128

	#define BarH			15
	#define ButW			17

	static RECT rClient;
	static RECT rScreen;
	static int cxClient, cyClient;
	static int nHeight = 1200,nWidth = 1600,
			cxCenter, cyCenter;

	static int xDocSize=1500, yDocSize=1000;
	static SCROLLINFO siVert, siHorz;
	static int xDif, yDif;
	
	static HDC hMemDC;
	static HBITMAP hBmpOld, hBmpOff;
	static BITMAP bm, bmc;

	static HBITMAP hBmpCopy;

	static Image iMem(L"default.bmp",FALSE);

	static int xScreen, yScreen;

	switch(msg)
	{
	case WM_CREATE:
	{
		curDims.circRadius = curDims.rectHeight = curDims.rectWidth = 16;

		hdc = GetDC(hWndView);
		hMemDC = CreateCompatibleDC(hdc);
		
		xScreen = GetSystemMetrics(SM_CXSCREEN);
		yScreen = GetSystemMetrics(SM_CYSCREEN);
		//hBmpOff = CreateCompatibleBitmap(hdc,xScreen,yScreen);
		//hBmpOld = (HBITMAP)SelectObject(hMemDC,hBmpOff);

		rScreen.top = rScreen.left = 0;
		rScreen.right = xScreen;
		rScreen.bottom = yScreen;
		//FillRect(hMemDC,&rScreen,(HBRUSH)(COLOR_WINDOW+1));

		CurrentColor = RGB(0,0,0);

		//ReleaseDC(hWndView, hdc);

		break;
	}
	case WM_APP:
		switch(wParam)
		{
		case MYI_SETDRAWMODE:
			dID = lParam;
			break;
		case MYI_OPENBMP:
			{
				//HANDLE hFile = CreateFile( (LPCSTR)lParam, GENERIC_READ, 0, NULL, OPEN_EXISTING,
				//	FILE_ATTRIBUTE_NORMAL, NULL);
				//
				//HBITMAP hBmpLoad = (HBITMAP)LoadImage(hInst,(LPCSTR)lParam,IMAGE_BITMAP, 
				//	0, 0, LR_LOADFROMFILE);
				//ShowLoadedBmp(hWndView, hMemDC, hBmpLoad, hBmpOld,rScreen);
				Image iLoad( (TCHAR)lParam, FALSE);
				ShowLoadedImage(hWndView, iLoad);

				NeedSave = TRUE;
				InvalidateRect(hWndView,NULL,TRUE);
				//CloseHandle(hFile);
				break;
			}
		case MYI_SAVEBMP:
			SaveCurrentBmp((LPCSTR)lParam, hBmpOff);
			NeedSave = FALSE;
			break;
		//case MYI_DRAWSTDPICT:
		//	{
		//		HBITMAP hCurrBmp;
		//		hCurrBmp = LoadBitmap(hInst, MAKEINTRESOURCE(lParam));
		//		ShowLoadedBmp(hWndView, hMemDC, hCurrBmp, hBmpOld,rScreen);
		//		InvalidateRect(hWndView,NULL,TRUE);
		//		NeedSave = TRUE;
		//	}
			break;
		case MYI_SETCOLOR:
			CurrentColor = cc.rgbResult;
			break;
		case MYI_CLIPBOARDCOPY:
			{
				HDC hdc = GetDC(hWndView);
				HDC hTmpDC = CreateCompatibleDC(hdc);
				
				hBmpCopy = CreateCompatibleBitmap(hdc,xScreen, yScreen);
				SelectObject(hTmpDC, hBmpCopy);
				BitBlt(hTmpDC,0,0, xScreen, yScreen, hMemDC, 0,0, SRCCOPY);
				
				OpenClipboard(hWndView);
				EmptyClipboard();
				SetClipboardData(CF_BITMAP,hBmpCopy);
				CloseClipboard();
				
				DeleteDC(hTmpDC);
				ReleaseDC(hWndView, hdc);
			}
			break;
		case MYI_CLIPBOARDPASTE:
			{
				bool bAvailable = IsClipboardFormatAvailable(CF_BITMAP);
				if(bAvailable)
				{
					OpenClipboard(hWndView);
					ShowLoadedBmp(hWndView, hMemDC, (HBITMAP)GetClipboardData(CF_BITMAP), hBmpOld, rScreen);
					CloseClipboard();
					InvalidateRect(hWndView,NULL,TRUE);
				}
			}
			break;
		default:
			return DefWindowProc(hWndView, msg, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWndView,&ps);
		BitBlt(hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left +1,
			ps.rcPaint.bottom - ps.rcPaint.top +1, hMemDC, ps.rcPaint.left,ps.rcPaint.top,SRCCOPY);
		EndPaint(hWndView,&ps);
		break;
	case WM_ERASEBKGND:
		return 1;
	case WM_LBUTTONDOWN:
	{
		A.x=xMouse=LOWORD(lParam);
		A.y=yMouse=HIWORD(lParam);
		switch(dID)
		{
		case CIRCLE:
			DrawCircle(hMemDC, A, CurrentColor, curDims.circRadius);
			break;
		case RECTANGLE:
			DrawRectangle(hMemDC, A, CurrentColor, curDims.rectWidth, curDims.rectHeight);
			break;
		case TRIANGLE:
			B.x=rand()%nRem;
			B.y=rand()%nRem;
			C.x=rand()%nRem;
			C.y=rand()%nRem;
			DrawTriangle(hMemDC, A, B, C, CurrentColor);
			break;
		}
		NeedSave = TRUE;
		InvalidateRect(hWndView,NULL,TRUE);
		break;
	}
	case WM_DESTROY:
		SelectObject(hMemDC,hBmpOld);
		DeleteObject(hBmpOff);
		DeleteDC(hMemDC);
		break;
	default:
		return DefWindowProc(hWndView,msg,wParam,lParam);
		break;
	}
	return 0;
}



//LRESULT CALLBACK TextProc(HWND hWndText, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	static LOGFONT lf;
//	static CHOOSEFONT cf; 
//	static HFONT hFont, hFontOld;
//	HDC hdc;
//	static HDC hMemDC;
//	PAINTSTRUCT ps;
//	static int xScreen, yScreen;
//	static HBITMAP hBmpOff, hBmpOld;
//	static RECT rScreen;
//
//	switch(msg)
//	{
//	case WM_CREATE:
//		hdc = GetDC(hWndText);
//		hMemDC = CreateCompatibleDC(hdc);
//		xScreen = GetSystemMetrics(SM_CXSCREEN);
//		yScreen = GetSystemMetrics(SM_CYSCREEN);
//		hBmpOff = CreateCompatibleBitmap(hdc,xScreen,yScreen);
//		hBmpOld = (HBITMAP)SelectObject(hMemDC,hBmpOff);
//		
//		rScreen.top = rScreen.left = 0;
//		rScreen.right = xScreen;
//		rScreen.bottom = yScreen;
//		FillRect(hMemDC,&rScreen,(HBRUSH)(COLOR_WINDOW+1));
//		
//		SetTextColor(hMemDC,RGB(0,0,0));
//		TextOut(hMemDC, 0,0, (LPCSTR)szTextClass, _tcslen(szTextClass));
//		ReleaseDC(hWndText, hdc);
//		break;
//	case WM_PAINT:
//		hdc = BeginPaint(hWndText,&ps);
//		BitBlt(hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left +1,
//			ps.rcPaint.bottom - ps.rcPaint.top +1, hMemDC, ps.rcPaint.left,ps.rcPaint.top,SRCCOPY);
//		EndPaint(hWndText,&ps);
//		break;
//	case WM_APP:
//		if(wParam == MYI_SETFONT)
//		{
//			FillRect(hMemDC,&rScreen,(HBRUSH)(COLOR_WINDOW+1));
//			cf = *((LPCHOOSEFONT)lParam);
//			DeleteObject(SelectObject(hMemDC, hFont));
//			
//			hFont = CreateFontIndirect(cf.lpLogFont);
//			hFontOld = (HFONT)SelectObject(hMemDC,hFont);
//			
//			SetTextColor(hMemDC,cf.rgbColors);
//			TextOut(hMemDC, 0,0, (LPCSTR)szTextClass, _tcslen(szTextClass));
//
//			InvalidateRect(hWndText,NULL,TRUE);
//		}
//		break;
//	case WM_ERASEBKGND:
//		return 1;
//	case WM_DESTROY:
//		DeleteObject(SelectObject(hMemDC,hBmpOld));
//		DeleteObject(SelectObject(hMemDC, hFontOld));
//		DeleteDC(hMemDC);
//		break;
//	default:
//		return DefWindowProc(hWndText,msg,wParam,lParam);
//		break;
//	}
//	return 0;
//}

LRESULT CALLBACK WndProc(HWND hWndParent, UINT message, WPARAM wParam, LPARAM lParam)
{
	static char szFileName[_MAX_PATH], szTitleName[_MAX_FNAME + _MAX_EXT];
	static HINSTANCE hInst;
	
	int wmId, wmEvent;
	static int dID;
	
	static HCURSOR hCursor;
	static HMENU hMenu;
	static RECT rClient, rcClient, rEdit;
	static int cxClient, cyClient;
	static HWND hWndToolB, hWndStB, hWndView, hWndText;
	static HBITMAP hLoadBmp;

	static LOGFONT lf;
	static CHOOSEFONT cf;

	static int	xStB, yStB,
		xView, yView,
		wStB, hStB,
		wView, hView,
		xText, yText,
		hText, wText;

	static TBBUTTON tbButtons[5] = 
	{
		{0, IDM_CIRCLE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0 ,0},
		{1, IDM_RECT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0 ,0},
		{2, IDM_TRIANGLE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0 ,0},
		{3, IDM_BRUSH, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0 ,0},
		{4, IDM_FONT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0 ,0}
	};

	#define BarH			15
	#define ButW			17
		
	switch (message)
	{
	case WM_CREATE:
		{
			hInst =((LPCREATESTRUCT) lParam) -> hInstance;
			PopFileInitialize(hWndParent);
						
			HDC hdc = GetDC(hWndParent);
			HFONT hFont = (HFONT)GetCurrentObject(hdc, OBJ_FONT);
			ReleaseDC(hWndParent, hdc);

			lstrcpy(szFileName,(PSTR)(((LPCREATESTRUCT) lParam)->lpCreateParams));
			if(strlen(szFileName) > 0)
				GetFileTitle(szFileName, szTitleName, sizeof(szTitleName));
			
			GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(lf), &lf);
			lf.lfHeight = 10;
			memset(&cf, 0, sizeof(cf));
			cf.lStructSize = sizeof (cf);
			cf.hwndOwner = hWndParent;
			cf.lpLogFont = &lf;
			cf.rgbColors = RGB(0,0,0);
			SendMessage(hWndText, WM_APP, MYI_SETFONT, (LPARAM)&cf);
			cf.Flags = CF_SCREENFONTS | CF_EFFECTS | CF_INITTOLOGFONTSTRUCT;
						
			GetClientRect(hWndParent,&rClient);
			cxClient = rClient.right-rClient.left;
			cyClient = -rClient.top+rClient.bottom;
			
			xView = 0;
			yView = 2*BarH-1;
			wView = cxClient;
			//hText = 40;
			hView = cyClient - 2*BarH;

			//xText = 0;
			//yText = hView + BarH;
			//wText = cxClient;

			xStB = 0;
			yStB = hView + 40 + BarH;
			hStB = BarH;
			wStB = cxClient;

			hWndToolB = CreateToolbarEx(hWndParent,WS_CHILD | WS_VISIBLE | WS_BORDER | TBSTYLE_TOOLTIPS |
				CCS_TOP, IDT_MY_TOOLBAR, 5, hInst, IDB_TOOLBAR_BITMAP, tbButtons, 5, 
				ButW, BarH, 5*ButW,BarH,sizeof(TBBUTTON));
			
			hWndView = CreateWindow(szViewClass,NULL,WS_CHILD | WS_BORDER | WS_VISIBLE, xView, yView,
				wView, hView, hWndParent, NULL, hInst, NULL);
			ShowWindow(hWndView,SW_SHOWDEFAULT);
			UpdateWindow(hWndView);

			//hWndText = CreateWindow(szTextClass, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, xText, yText, 
			//	wText, hText, hWndParent, NULL, ((LPCREATESTRUCT) lParam) -> hInstance, NULL);
			//ShowWindow(hWndText,SW_SHOWDEFAULT);
			//UpdateWindow(hWndText);

			hWndStB = CreateStatusWindow(WS_CHILD | WS_VISIBLE | WS_BORDER, "", hWndParent,IDT_MY_STATUSBAR);
			
			hMenu = GetMenu(hWndParent);
			AdjustMenuItem(hMenu,hWndView,hWndStB, CIRCLE, IDS_TOOLTIP_CIRCLE);
			break;
		}
	case WM_SETFOCUS:
		SetFocus(hWndView);
		break;
	case WM_SIZE:
	{
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		
		SendMessage(hWndToolB, TB_AUTOSIZE, 0, 0L);
		int x, y, cx, cy;
		RECT rStB;

		GetWindowRect(hWndStB,&rStB);
		cy = rStB.bottom - rStB.top;
		x = 0;
		y = cyClient - cy;
		cx = cxClient;
		MoveWindow(hWndStB,x,y,cx,cy,TRUE);

		//GetWindowRect(hWndText,&rEdit);
		//cy = rEdit.bottom - rEdit.top;
		//x = 0;
		//y = cyClient - cy - hStB-5;
		//cx = cxClient;
		//MoveWindow(hWndText,x,y,cx,cy,TRUE);

		cy = cyClient-3*BarH;
		x = 0;
		y = 2*BarH-3;
		cx = cxClient;
		MoveWindow(hWndView,x,y,cx,cy,TRUE);		
		break;
	}
	case WM_ERASEBKGND:
		return 1;
	case WM_NOTIFY:
	{
		LPNMHDR pHDR = (LPNMHDR)lParam;
		TCHAR pInfo[MAX_LOADSTRING];
		if(pHDR->code == TTN_NEEDTEXT)
		{
			LPTOOLTIPTEXT pTTI = (LPTOOLTIPTEXT)lParam;
			pTTI->hinst = hInst;
			pTTI->lpszText = MAKEINTRESOURCE(pTTI->hdr.idFrom);
		}
		break;
	}
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		case IDM_CIRCLE:
			AdjustMenuItem(hMenu,hWndView,hWndStB,CIRCLE, IDS_TOOLTIP_CIRCLE);
			break;
		case IDM_RECT:
			AdjustMenuItem(hMenu,hWndView,hWndStB,RECTANGLE, IDS_TOOLTIP_RECTANGLE);
			break;
		case IDM_TRIANGLE:
			AdjustMenuItem(hMenu,hWndView,hWndStB,TRIANGLE, IDS_TOOLTIP_TRIANGLE);
			break;
		//case IDM_OPEN:
		//	SendMessage(hWndView, WM_APP, (WPARAM)MYI_DRAWSTDPICT, 
		//		(LPARAM)DialogBox(hInst, MAKEINTRESOURCE(IDD_CHOOSEBMP), hWndParent, ChooseStdBmpDlg));
		//	break;
		case IDM_LOAD:
			if(PopFileOpenDlg(hWndParent, szFileName, szTitleName))
				SendMessage(hWndView,WM_APP, (WPARAM)MYI_OPENBMP, (LPARAM)szFileName);
			break;
		case IDM_SAVEAS:
			if(PopFileSaveDlg(hWndParent, szFileName, szTitleName))
				SendMessage(hWndView,WM_APP, (WPARAM)MYI_SAVEBMP, (LPARAM)szFileName);
			break;
		case IDM_BRUSH:
			if(PopChooseColorDlg())
				SendMessage(hWndView, WM_APP, (WPARAM)MYI_SETCOLOR, 0);
			break;
		//case IDM_FONT:
		//	//if(ChooseFont(&cf))
		//		
		//	break;
		case IDM_EXIT:
			PostMessage(hWndParent, WM_CLOSE, 0, 0);
			break;
		case IDM_SETDIMS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_SETDIMS), hWndParent, SetDimensionsDlg);
			break;
		case IDM_ANIMATION_SEEDEMO:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ANIM), hWndParent, AnimationDlg);
			break;
		case IDM_BOOKLIST:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_LISTVIEW), hWndParent, ListViewDlg);
			break;
		case IDM_COPY:
			SendMessage(hWndView, WM_APP, (WPARAM)MYI_CLIPBOARDCOPY, 0);
			break;
		case IDM_PASTE:
			SendMessage(hWndView, WM_APP, (WPARAM)MYI_CLIPBOARDPASTE, 0);
			break;
		default:
			return DefWindowProc(hWndParent, message, wParam, lParam);
		}
		break;
	//case WM_CLOSE:
	//	if(NeedSave && DialogBox(hInst, MAKEINTRESOURCE(IDD_EXITASKBOX), hWndParent, NeedSaveDlg))
	//	{
	//		PopFileSaveDlg(hWndParent, szFileName, szTitleName);
	//		SendMessage(hWndView,WM_APP, MYI_SAVEBMP, (LPARAM)szFileName);
	//	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWndParent, message, wParam, lParam);
	}
	return 0;
}
INT_PTR CALLBACK ListViewDlg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hWndList;
	LVCOLUMN lvc;
	LV_ITEM lvi;
	static int nCurElem = 0;
	static RECT rc;
	TCHAR tmp[MAX_LOADSTRING];
	switch(msg)
	{
	case WM_INITDIALOG:
		{
			hWndList = GetDlgItem(hDlg, IDC_LIST);
			
			HIMAGELIST himlSmall = ImageList_Create( 
				GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),
				ILC_MASK, 4, 1);

			HICON hIcon;
			for(int i = IDI_CAR; i < IDI_OTHER + 1; ++i)
			{
				hIcon = (HICON)LoadIcon(hInst,(LPCSTR)i);
				ImageList_AddIcon(himlSmall, hIcon);
			}
			ListView_SetImageList(hWndList, himlSmall, LVSIL_SMALL);

			GetClientRect(hWndList, &rc);
			memset(&lvc, 0, sizeof(lvc));
			lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			lvc.fmt = LVCFMT_LEFT;
			lvc.cx = (rc.right - rc.left)/4;
			  
			lvc.iSubItem = 0;
			lvc.pszText = "Name";
			ListView_InsertColumn(hWndList, 0, &lvc);

			lvc.iSubItem = 1;
			lvc.pszText = "Creator/producer";
			ListView_InsertColumn(hWndList, 1, &lvc);
			
			lvc.iSubItem = 2;
			lvc.pszText = "Manufacture date";
			ListView_InsertColumn(hWndList, 2, &lvc);

			lvc.iSubItem = 3;
			lvc.pszText = "Type";
			ListView_InsertColumn(hWndList, 3, &lvc);

			ListView_SetExtendedListViewStyle(hWndList, LVS_EX_FULLROWSELECT);
			
			return 1;
		}
	case WM_NOTIFY:
		{
			LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)lParam;
			LPNMKEY lpnmk = (LPNMKEY) lParam;
			
			switch(lpnmitem->hdr.code)
			{
			case NM_DBLCLK:
				SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_EDITITEM,BN_CLICKED), 
							(LPARAM)GetDlgItem(hDlg, IDC_EDITITEM ));
				break;
			case NM_KEYDOWN:
				if(lpnmk->nVKey == VK_DELETE)
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_REMOVEITEM,BN_CLICKED), 
							(LPARAM)GetDlgItem(hDlg, IDC_REMOVEITEM ));
				else if(lpnmk->nVKey == VK_RETURN)
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_EDITITEM,BN_CLICKED), 
							(LPARAM)GetDlgItem(hDlg, IDC_EDITITEM ));
				break;
			}

			return 1;
		}
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_ADDITEM:
			{
				curItem.Clear();
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ADDITEM), hDlg, AddDlg);
				memset(&lvi, 0, sizeof(lvi));
				lvi.mask = LVIF_IMAGE | LVIF_TEXT;

				lvi.iItem = nCurElem;
				lvi.iSubItem = 0;
				lvi.cchTextMax = 70;
				
				switch(curItem.type[0])
				{
				case 'A':
					lvi.iImage = 0;
					break;
				case 'B':
					lvi.iImage = 1;
					break;
				case 'F':
					lvi.iImage = 2;
					break;
				case 'O':
					lvi.iImage = 3;
					break;
				}
				ListView_InsertItem(hWndList, &lvi);
				ListView_SetItemText(hWndList, nCurElem, 0, curItem.name); 
				ListView_SetItemText(hWndList, nCurElem, 1, curItem.itemfrom);
				ListView_SetItemText(hWndList, nCurElem, 3, curItem.type);
				
				
				char* tmp = new char [7];
				int k;
				tmp[ k = sprintf(tmp,"%d/n",curItem.date) - 2 ] = 0;
				ListView_SetItemText(hWndList, nCurElem, 2, tmp);
				
				ListView_SetItemState(hWndList,nCurElem, LVIS_FOCUSED | LVIS_SELECTED, 
					LVIS_FOCUSED | LVIS_SELECTED);
				nCurElem++;
				delete tmp;

				break;
			}
		case IDC_EDITITEM:
			{
				int nSel = ListView_GetSelectionMark(hWndList);
				curItem.name = new char [MAX_LOADSTRING];
				curItem.type = new char [7];
				curItem.itemfrom = new char [MAX_LOADSTRING];
				
				ListView_GetItemText(hWndList,nSel,0,curItem.name, MAX_LOADSTRING);
				ListView_GetItemText(hWndList,nSel,1,curItem.itemfrom, MAX_LOADSTRING);
				ListView_GetItemText(hWndList,nSel,3,curItem.type, 7);				

				char* tmp = new char [7];
				ListView_GetItemText(hWndList,nSel,2,tmp, 7);
				curItem.date = atoi(tmp);
				delete[] tmp;
				
				if(DialogBox(hInst, MAKEINTRESOURCE(IDD_ADDITEM), hDlg, AddDlg))
				{	
					ListView_SetItemText(hWndList, nSel, 0, curItem.name); 
					ListView_SetItemText(hWndList, nSel, 1, curItem.itemfrom);
					ListView_SetItemText(hWndList, nSel, 3, curItem.type);
		
					tmp = new char [7];
					int k;
					tmp[ k = sprintf(tmp,"%d/n",curItem.date) - 2 ] = 0;
					ListView_SetItemText(hWndList, nSel, 2, tmp);
					delete tmp;
				}
				break;
			}
		case IDC_REMOVEITEM:
			{
				int nNewSel = ListView_GetSelectionMark(hWndList);
				if(ListView_GetNextItem(hWndList,nNewSel, LVNI_BELOW) == -1)
				{
					ListView_SetItemState(hWndList,nNewSel - 1, LVIS_FOCUSED | LVIS_SELECTED, 
						LVIS_FOCUSED | LVIS_SELECTED);
				}
				else
				{
					ListView_SetItemState(hWndList,nNewSel + 1, LVIS_FOCUSED | LVIS_SELECTED, 
						LVIS_FOCUSED | LVIS_SELECTED);
				}
				ListView_DeleteItem(hWndList,nNewSel);
				break;
			}
		case IDCANCEL:
			EndDialog(hDlg,0);
			return 0;
		}
		return 1;
	}
	return 0;
}