// API 3_1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
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
		SetViewportOrgEx(hdc,cxClient/5,cyClient/2,0);
}
void SetMap(HDC hdc, int nWidth, int nHeight, int cxCenter, int cyCenter)
{
	SetWindowExtEx(hdc,nWidth,nHeight,NULL);
	SetWindowOrgEx(hdc,cxCenter,cyCenter,NULL);
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
	
	static int nHeight = 1200,nWidth = 1600,
		cxClient = 1024,cyClient = 768;

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
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_SIZE:
		cxClient=LOWORD(lParam);
		cyClient=HIWORD(lParam);
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	//case WM_VSCROLL:
	//	hdc=GetDC(hWnd);
	//	switch(LOWORD(wParam))
	//	{
	//	case SB_LINEUP:
	//		yScrollDif=1;
	//		yScrollPos++;
	//		break;
	//	case SB_LINEDOWN:
	//		yScrollDif=-1;
	//		yScrollPos--;
	//		break;
	//	//case SB_PAGEUP:
	//	//	nVScrollInc=-min(nVScrollPos,
	//	//	break;
	//	//case SB_PAGEDOWN:
	//	//	break;
	//	//case SB_THUMBTRACK:
	//	//	nVScrollInc=HIWORD(lParam)-nVScrollPos;
	//	//	break;
	//	//default:
	//	//	nVScrollInc=0;
	//	}
	//	ScrollWindow(hWnd,0,yScrollDif,0,0);
	//	SetScrollInfo(hWnd,SB_VERT,&siVert,TRUE);
	//	SetMap(hdc,xDocSize,yDocSize,cxCenter,cyCenter-yScrollDif);
	//	ReleaseDC(hWnd,hdc);
	//	break;
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
		pq->print(hdc);
		EndPaint(hWnd, &ps);
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_LBUTTONDOWN:
		xMouse=LOWORD(lParam);
		yMouse=HIWORD(lParam);
		ptLT.x=ptRB.x=xMouse;
		ptLT.y=ptRB.y=yMouse;
		
		DrawRectOutLine(hWnd,ptLT,ptRB,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
		SetCapture(hWnd);
		fIsInWnd = TRUE;
		
		SetTimer(hWnd,1,GetDoubleClickTime(),NULL); //start timer

		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_TIMER:
		{
			KillTimer(hWnd,1);	//kill timer
			hdc=GetDC(hWnd);
			SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
			A.x=xMouse;
			A.y=yMouse;
			DPtoLP(hdc,&A,1);
			B.x=rand()%nRem;
			B.y=rand()%nRem;
			rectangle elem (A,B,RGB(rand()%256,rand()%256,rand()%256), 
				RGB(rand()%256,rand()%256,rand()%256));
			pq->push(&elem);
			elem.draw(hdc);
			ReleaseDC(hWnd,hdc);
			break;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_MOUSEMOVE:
		{
			if(fIsInWnd)
			{
				KillTimer(hWnd,1);
				SetCursor(LoadCursor(NULL, IDC_CROSS));
				
				DrawRectOutLine(hWnd,ptLT,ptRB,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
													
				ptRB.x=LOWORD(lParam);
				ptRB.y=HIWORD(lParam);

				DrawRectOutLine(hWnd,ptLT,ptRB,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
				
			}
			break;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	case WM_LBUTTONUP:
		{
			if(fIsInWnd)
			{	
				SetCursor(LoadCursor(NULL,IDC_ARROW));
				ReleaseCapture();
				hdc=GetDC(hWnd);
				SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
				DPtoLP(hdc,&ptLT,1);
				DPtoLP(hdc,&ptRB,1);
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
			SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
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
			elem.draw(hdc);
			ReleaseDC(hWnd,hdc);
			break;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////	
	case WM_RBUTTONDOWN:
		{
			xMouse=LOWORD(lParam);
			yMouse=HIWORD(lParam);
			hdc=GetDC(hWnd);
			SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
			A.x=xMouse;
			A.y=yMouse;
			DPtoLP(hdc,&A,1);
			nRad=rand()%64;
			circle elem(A,nRad,RGB(rand()%256,rand()%256,rand()%256),
				RGB(rand()%256,rand()%256,rand()%256));
			pq->push(&elem);
			elem.draw(hdc);
			ReleaseDC(hWnd,hdc);
			break;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////
	case WM_KEYDOWN:
		hdc=GetDC(hWnd);
		SetModeMap(hdc,MM_ANISOTROPIC,nWidth,nHeight,cxClient,cyClient);
		switch(wParam)
		{
		case 'O':
			{
				circle elem(nRem);
				pq->push(&elem);
				elem.draw(hdc);
				break;
			}
		case 'T':
			{
				triangle elem(nRem);
				pq->push(&elem);
				elem.draw(hdc);
				break;
			}
		case 'P':
			{
				rectangle elem(nRem);
				pq->push(&elem);
				elem.draw(hdc);
				break;
			}
		}
		ReleaseDC(hWnd,hdc);
		break;
/////////////////////////////////////////////////////////////////////////////////////////////////////
	case WM_DESTROY:
		delete pq;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
