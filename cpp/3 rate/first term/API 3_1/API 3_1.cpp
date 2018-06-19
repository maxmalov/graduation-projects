// API 3_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"
#include<tchar.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void DrawRectOutLine(HWND , POINT , POINT ,int ,int , int , int , int );
void SetModeMap(HDC , int , int , int , int , int );

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_API3_1, szWindowClass, MAX_LOADSTRING);
	
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= 0;

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
	  NULL, NULL, hInstance, NULL);

   if (!hWnd) return FALSE;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
void SetModeMap(HDC hdc, int nMapMode, int nWidth, int nHeight, int cxClient, int cyClient)
{
		SetMapMode(hdc,nMapMode);
		SetWindowExtEx(hdc,nWidth,nHeight,NULL);
		SetViewportExtEx(hdc, cxClient, -cyClient,NULL);
		SetViewportOrgEx(hdc,cxClient/2,2*cyClient/3,0);
}

void DrawRectOutLine(HWND hWnd, POINT ptLT, POINT ptRB,int nMapMode, int nWidth, int nHeight, int cxClient, int cyClient)
{
	HDC hdc=GetDC(hWnd);
	SetMapMode(hdc,nMapMode);
	SetWindowExtEx(hdc,nWidth,nHeight,NULL);
	SetViewportExtEx(hdc, cxClient, -cyClient,NULL);
	SetViewportOrgEx(hdc,cxClient/5,cyClient/2,0);

	SetROP2(hdc,R2_NOTXORPEN);
	DPtoLP(hdc,&ptLT,1);
	DPtoLP(hdc,&ptRB,1);
	SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(0,0,0)));
	Rectangle(hdc,ptLT.x, ptLT.y, ptRB.x, ptRB.y);

	ReleaseDC(hWnd,hdc);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static _queue* pq=0;
	POINT A,B,C;
	int nRad;
	static int xMouse, yMouse;		//mouse coordinates after any click
	const int nRem=512;
	static BOOL fIsInWnd;
	static POINT ptLT, ptRB;
	static RECT rClient;
	
	static int nHeight = 1200,nWidth = 1600,
		cxClient,cyClient;
	static int cxCenter, cyCenter;

	static int xDocSize=1500, yDocSize=1000;
	static SCROLLINFO siVert, siHorz;
	static int xDif, yDif;

	static int cxText, cyText;

	static LOGFONT lf;
	static HFONT hCurFont, hFont;
	static HRGN hRectRgn;
	static HBRUSH hBrush;

	switch (message)
	{
	case WM_CREATE:
		pq=new _queue;
		srand(time(0));
		for(int i=0;i<20;++i)
		{
			switch(rand()%3)
			{
			case 0:
				{
					rectangle elem(nRem);
					pq->push(&elem);
					break;
				}
			case 1:
				{
					circle elem(nRem);
					pq->push(&elem);
					break;
				}
			case 2:
				{
					triangle elem(nRem);
					pq->push(&elem);
					break;
				}
			}
		}
		GetClientRect(hWnd,&rClient);
		cxClient=rClient.right-rClient.left;
		cyClient=rClient.bottom-rClient.top;
		cxCenter=cxClient/5;
		cyCenter=cyClient/7;
		cxText=cyText=0;

		siVert.cbSize=sizeof(siVert);					siHorz.cbSize=sizeof(siHorz);
		siVert.nMin=siVert.nPos=0;						siHorz.nMin=siVert.nPos=0;
		siVert.nMax=yDocSize-1;							siHorz.nMax=xDocSize-1;
		siVert.fMask= SIF_RANGE | SIF_POS;				siHorz.fMask= SIF_RANGE | SIF_POS;
		SetScrollInfo(hWnd,SB_VERT,&siVert,TRUE);		SetScrollInfo(hWnd,SB_HORZ,&siHorz,TRUE);

		hdc=GetDC(hWnd);
		SetWindowOrgEx(hdc,-cxCenter+siHorz.nPos,-cyCenter+siVert.nPos,NULL);
		hCurFont=(HFONT)GetCurrentObject(hdc,OBJ_FONT);
		ReleaseDC(hWnd,hdc);
		
		lf.lfHeight=900;
		lf.lfWidth=150;
		lf.lfQuality=ANTIALIASED_QUALITY;
		_tcscpy(lf.lfFaceName,_T("Courier New"));
		lf.lfWeight=1000;

		hFont=CreateFontIndirect(&lf);
		hBrush=CreateHatchBrush(HS_DIAGCROSS,RGB(0,0,0));		

		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_SIZE:
		cxClient=LOWORD(lParam);
		cyClient=HIWORD(lParam);
		siVert.nPage=cyClient;							siHorz.nPage=cxClient;
		siVert.fMask= SIF_RANGE | SIF_POS | SIF_PAGE;	siHorz.fMask= SIF_RANGE | SIF_POS | SIF_PAGE;
		SetScrollInfo(hWnd,SB_VERT,&siVert,TRUE);		SetScrollInfo(hWnd,SB_HORZ,&siHorz,TRUE);
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_VSCROLL:
		yDif=siVert.nPos;
		switch(LOWORD(wParam))
		{
		case SB_LINEUP:
			siVert.nPos--;
			break;
		case SB_LINEDOWN:
			siVert.nPos++;
			break;
		case SB_PAGEUP:
			siVert.nPos-=siVert.nPage;
			break;
		case SB_PAGEDOWN:
			siVert.nPos+=siVert.nPage;
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			siVert.fMask=SIF_ALL;
			GetScrollInfo(hWnd,SB_VERT,&siVert);
			siVert.nPos=siVert.nTrackPos;
			break;
		}
		
		if(siVert.nPos>0) siVert.nPos=max(0,min(siVert.nPos,siVert.nMax-siVert.nPage));
		else siVert.nPos=0;
		
		yDif=siVert.nPos-yDif;
		if(siVert.nPos!=GetScrollPos(hWnd,SB_VERT))
		{
			siVert.fMask=SIF_RANGE | SIF_POS | SIF_PAGE;
			SetScrollInfo(hWnd,SB_VERT,&siVert,TRUE);
			ScrollWindow(hWnd,0,-yDif,NULL,NULL);
		}
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////
	case WM_HSCROLL:
		xDif=siHorz.nPos;
		switch(LOWORD(wParam))
		{
		case SB_LINEDOWN:
			siHorz.nPos++;
			break;
		case SB_LINEUP:
			siHorz.nPos--;
			break;
		case SB_PAGEDOWN:
			siHorz.nPos+=siHorz.nPage;
			break;
		case SB_PAGEUP:
			siHorz.nPos-=siHorz.nPage;
			break;
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			siHorz.fMask=SIF_ALL;
			GetScrollInfo(hWnd,SB_HORZ,&siHorz);
			siHorz.nPos=siHorz.nTrackPos;
			break;
		}
		if(siHorz.nPos>0) siHorz.nPos=max(0,min(siHorz.nPos,siHorz.nMax-siHorz.nPage));
		else siHorz.nPos=0;
		xDif=siHorz.nPos-xDif;
		if(siHorz.nPos!=GetScrollPos(hWnd,SB_HORZ))
		{
			siHorz.fMask=SIF_RANGE | SIF_POS;
			SetScrollInfo(hWnd,SB_HORZ,&siHorz,TRUE);
			ScrollWindow(hWnd,-xDif,0,NULL,NULL);
		}
		break;
	
/////////////////////////////////////////////////////////////////////////////////////////////////////
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			//SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
			SetWindowOrgEx(hdc,-cxCenter+siHorz.nPos,-cyCenter+siVert.nPos,NULL);
			wchar_t wExample[] = L"HELLO!";
			
			(HFONT)SelectObject(hdc,hFont);
			SetBkMode(hdc,TRANSPARENT);

			BeginPath(hdc);
			TextOut(hdc,cxText,cyText,wExample,wcslen(wExample));
			EndPath(hdc);

			SelectClipPath(hdc,RGN_AND);
			//RECT rText;
			GetClientRect(hWnd,&rClient);
			//rText.left=cxText;
			//rText.right=cxText+20*lf.lfWidth;
			//rText.top=cyText;
			//rText.bottom=cyText+lf.lfHeight;
			FillRect(hdc, &rClient ,hBrush);
			
			StrokeAndFillPath(hdc);
			//pq->print(hdc);
			EndPaint(hWnd, &ps);
			break;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_LBUTTONDOWN:
		xMouse=LOWORD(lParam);
		yMouse=HIWORD(lParam);
		ptLT.x=xMouse;
		ptLT.y=yMouse;
		
		hdc=GetDC(hWnd);
		SetWindowOrgEx(hdc,-cxCenter+siHorz.nPos,-cyCenter+siVert.nPos,NULL);
		DPtoLP(hdc,&ptLT,1);
		ptRB=ptLT;
		SetCapture(hWnd);
		ReleaseDC(hWnd,hdc);

		fIsInWnd = TRUE;
		SetTimer(hWnd,1,GetDoubleClickTime(),NULL); //start timer
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_TIMER:
		{
			KillTimer(hWnd,1);	//kill timer
			hdc=GetDC(hWnd);
			//SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
			SetWindowOrgEx(hdc,-cxCenter+siHorz.nPos,-cyCenter+siVert.nPos,NULL);
			A.x=xMouse;
			A.y=yMouse;
			DPtoLP(hdc,&A,1);
			B.x=rand()%nRem;
			B.y=rand()%nRem;
			rectangle elem (A,B,RGB(rand()%256,rand()%256,rand()%256), 
				RGB(rand()%256,rand()%256,rand()%256));
			pq->push(&elem);
			//elem.draw(hdc);
			ReleaseDC(hWnd,hdc);
			break;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_MOUSEMOVE:
		if(fIsInWnd)
		{
			KillTimer(hWnd,1);
			SetCursor(LoadCursor(NULL, IDC_CROSS));
			hdc=GetDC(hWnd);
			SetWindowOrgEx(hdc,-cxCenter+siHorz.nPos,-cyCenter+siVert.nPos,NULL);

			//SelectObject(hdc,GetStockObject(NULL_BRUSH));
			SetROP2(hdc, R2_NOTXORPEN);
			SelectObject(hdc,CreatePen(PS_SOLID,1,RGB(0,0,0)));
			Rectangle(hdc, ptLT.x, ptLT.y, ptRB.x, ptRB.y);
			
			ptRB.x=LOWORD(lParam);
			ptRB.y=HIWORD(lParam);
			DPtoLP(hdc,&ptRB,1);
			
			Rectangle(hdc, ptLT.x, ptLT.y, ptRB.x, ptRB.y);

			ReleaseDC(hWnd,hdc);				
		}
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////
	case WM_LBUTTONUP:
		{
			if(fIsInWnd)
			{	
				SetCursor(LoadCursor(NULL,IDC_ARROW));
				ReleaseCapture();
				hdc=GetDC(hWnd);
				//SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
				SetWindowOrgEx(hdc,-cxCenter+siHorz.nPos,-cyCenter+siVert.nPos,NULL);
				//DPtoLP(hdc,&ptLT,1);
				//DPtoLP(hdc,&ptRB,1);
				rectangle elem (ptLT,ptRB,RGB(rand()%256,rand()%256,rand()%256), 
						RGB(rand()%256,rand()%256,rand()%256));
				ReleaseDC(hWnd,hdc);
				pq->push(&elem);
				fIsInWnd = FALSE;
				InvalidateRect(hWnd,NULL,TRUE);
				UpdateWindow(hWnd);
			}
			break;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	case WM_LBUTTONDBLCLK:
		{
			KillTimer(hWnd,1);	//kill timer
			hdc=GetDC(hWnd);
			//SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
			SetWindowOrgEx(hdc,-cxCenter+siHorz.nPos,-cyCenter+siVert.nPos,NULL);
			A.x=xMouse;
			A.y=yMouse;
			DPtoLP(hdc,&A,1);
			B.x=rand()%nRem;
			B.y=rand()%nRem;
			C.x=rand()%nRem;
			C.y=rand()%nRem;
			triangle elem(A,B,C,RGB(rand()%256,rand()%256,rand()%256), 
				RGB(rand()%256,rand()%256,rand()%256));
			pq->push(&elem);
			//elem.draw(hdc);
			ReleaseDC(hWnd,hdc);
			break;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_RBUTTONDOWN:
		{
			xMouse=LOWORD(lParam);
			yMouse=HIWORD(lParam);
			hdc=GetDC(hWnd);
			//SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
			SetWindowOrgEx(hdc,-cxCenter+siHorz.nPos,-cyCenter+siVert.nPos,NULL);
			A.x=xMouse;
			A.y=yMouse;
			DPtoLP(hdc,&A,1);
			nRad=rand()%64+32;
			circle elem(A,nRad,RGB(rand()%256,rand()%256,rand()%256),
				RGB(rand()%256,rand()%256,rand()%256));
			pq->push(&elem);
			//elem.draw(hdc);
			ReleaseDC(hWnd,hdc);
			break;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	case WM_MOUSEWHEEL:
		{
			int tmp=siVert.nPos;
			if(GET_WHEEL_DELTA_WPARAM(wParam)<0)  yDif=20;
			else yDif=-20;
			
			siVert.nPos+=yDif;		
			if(siVert.nPos>0) 
				siVert.nPos=max(0,min(siVert.nPos,siVert.nMax-siVert.nPage));
			else siVert.nPos=0;

			if(siVert.nPos!=GetScrollPos(hWnd,SB_VERT))
			{
				siVert.fMask=SIF_RANGE | SIF_POS | SIF_PAGE;
				SetScrollInfo(hWnd,SB_VERT,&siVert,TRUE);
				ScrollWindow(hWnd,0,-(siVert.nPos-tmp),NULL,NULL);
			}
			break;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	case WM_KEYDOWN:
		hdc=GetDC(hWnd);
		//SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
		SetWindowOrgEx(hdc,-cxCenter+siHorz.nPos,-cyCenter+siVert.nPos,NULL);
		switch(wParam)
		{
		case 'O':
			{
				circle elem(nRem);
				pq->push(&elem);
				//elem.draw(hdc);
				break;
			}
		case 'T':
			{
				triangle elem(nRem);
				pq->push(&elem);
				//elem.draw(hdc);
				break;
			}
		case 'P':
			{
				rectangle elem(nRem);
				pq->push(&elem);
				//elem.draw(hdc);
				break;
			}
		case VK_PRIOR:
			SendMessage(hWnd,WM_VSCROLL,SB_PAGEUP,NULL);
			break;
		case VK_NEXT:
			SendMessage(hWnd,WM_VSCROLL,SB_PAGEDOWN,NULL);
			break;
		case VK_LEFT:
			SendMessage(hWnd,WM_HSCROLL,SB_LINEUP,NULL);
			break;
		case VK_RIGHT:
			SendMessage(hWnd,WM_HSCROLL,SB_LINEDOWN,NULL);
			break;
		case VK_UP:
			SendMessage(hWnd,WM_VSCROLL,SB_LINEUP,NULL);
			break;
		case VK_DOWN:
			SendMessage(hWnd,WM_VSCROLL,SB_LINEDOWN,NULL);
			break;
		}
		ReleaseDC(hWnd,hdc);
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////
	case WM_DESTROY:
		delete pq;
		DeleteObject(hFont);
		DeleteObject(hBrush);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
