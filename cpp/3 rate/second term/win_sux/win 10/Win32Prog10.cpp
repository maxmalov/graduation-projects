// Win32Prog10.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32Prog10.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;						// current instance
HACCEL hAccelTable;
TCHAR	szTitle[MAX_LOADSTRING];		// The title bar text
TCHAR	szWindowClass[MAX_LOADSTRING];	// the frame window class name
TCHAR	szViewClass[MAX_LOADSTRING];	// the view  window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
ATOM				MyRegisterViewClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndViewProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//-------------------------------------------------------------------------------------------
unsigned __stdcall ThreadFunc(void* lpV)
{
	HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	
	if(!hWnd)return 1;

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	MSG msg;
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

//-------------------------------------------------------------------------------------------
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	LoadString(hInstance, IDS_FRAME_CLASS, szWindowClass, MAX_LOADSTRING);
	//-------------------------------------------
	HANDLE hEvent = CreateEvent(NULL, TRUE, TRUE, _T("Local\\Prog10Event"));
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hEvent);
		HWND hWnd = FindWindow(szWindowClass, NULL);
		if(hWnd)
		{
			if(IsIconic(hWnd))
				ShowWindow(hWnd, SW_RESTORE);
			SetForegroundWindow(hWnd);
		}
		return 0;
	}
	//-------------------------------------------
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDS_VIEW_CLASS, szViewClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	MyRegisterViewClass(hInstance);

	// Perform application initialization:
	hInst = hInstance; // Store instance handle in our global variable

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROG10));

	unsigned int nThreadID[2];
	HANDLE hThread[2];
	hThread[0]  = (HANDLE)_beginthreadex(	NULL, //SECURITY_ATTRIBUTES
											0, //Stack size
											&ThreadFunc, //Start adress
											0, //parameter
											0, //Create and run
											&nThreadID[0]); //thread ID

	hThread[1]  = (HANDLE)_beginthreadex(	NULL, //SECURITY_ATTRIBUTES
											0, //Stack size
											&ThreadFunc, //Start adress
											0, //parameter
											0, //Create and run
											&nThreadID[1]); //thread ID


	if(WaitForMultipleObjects(2, hThread, TRUE, INFINITE)==WAIT_OBJECT_0)
	{
		CloseHandle(hThread[0]);
		CloseHandle(hThread[1]);
		CloseHandle(hEvent);
	}
	return 0;
}
//-------------------------------------------------------------------------------------------
ATOM MyRegisterViewClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndViewProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROG10));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szViewClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROG10));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROG10);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

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
//-------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	__declspec(thread) static int		cxClient, cyClient;
	__declspec(thread)static HWND		hWndView;
	int				wmId, wmEvent;
	PAINTSTRUCT		ps;
	HDC				hdc;

	switch (message)
	{
		case WM_CREATE:
		{
			hWndView = CreateWindow(szViewClass, 0, WS_CHILD | WS_VISIBLE,
				CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, hWnd, NULL, hInst, NULL);
			break;	
		}
		case WM_SIZE: 
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			MoveWindow(hWndView, 0, 0, cxClient, cyClient, TRUE);
			break;
		}
		case WM_SETFOCUS:
		{
			SetFocus(hWndView);
			return 0;
		}
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				case IDM_EXIT:
					DestroyWindow(hWnd);
					break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//-------------------------------------------------------------------------------------------
LRESULT CALLBACK WndViewProc(HWND hWndView, UINT message, WPARAM wParam, LPARAM lParam)
{
	__declspec(thread)static int		cxClient, cyClient;
	__declspec(thread)static List*		lFigures;
	PAINTSTRUCT		ps;
	HDC				hdc;
	const int		xW = 1200, yW = 700;
	int				wmId, wmEvent;

	switch (message)
	{
		case WM_CREATE:
		{
			lFigures = new List();
			FillList(*lFigures, xW, yW);
			return 0;
		}
		case WM_SIZE: 
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
			break;
		}
		case WM_COMMAND:
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWndView, About);
					break;
				default:
					return DefWindowProc(hWndView, message, wParam, lParam);
			}
			break;
		case WM_LBUTTONDOWN:
		{
			POINT ptCursor, ptA, ptB;
			ptCursor.x = LOWORD(lParam);
			ptCursor.y = HIWORD(lParam);

			ptA.x = ptCursor.x + rand()%100;
			ptA.y = ptCursor.y + rand()%100;
			ptB.x = ptCursor.x + rand()%100;
			ptB.y = ptCursor.y + rand()%100;
			
			Figure *fTriangle = new Triangle(ptCursor, ptA, ptB,
				RGB(rand()%256, rand()%256, rand()%256), RGB(rand()%256, rand()%256, rand()%256));
			lFigures->Insert(fTriangle);
			lFigures->Step();
			delete fTriangle;
			InvalidateRect(hWndView, NULL, TRUE);
			return 0;
		}
		case WM_RBUTTONDOWN:
		{
			POINT ptCursor;
			ptCursor.x = LOWORD(lParam);
			ptCursor.y = HIWORD(lParam);

			Figure *fCircle = new Circle(ptCursor.x, ptCursor.y, 50, 
				RGB(rand()%256, rand()%256, rand()%256), RGB(rand()%256, rand()%256, rand()%256));
			lFigures->Insert(fCircle);
			lFigures->Step();
			delete fCircle;

			InvalidateRect(hWndView, NULL, TRUE);
			return 0;
		}
		case WM_KEYUP:
			{
				POINT ptCursor;
				GetCursorPos(&ptCursor);
				RECT rClient;
				rClient.left = rClient.top = 0;
				rClient.right = cxClient;
				rClient.bottom = cyClient;
				ScreenToClient(hWndView, &ptCursor);
				Figure *f = 0;
				switch(wParam)
				{
					case 'T':
						{
							POINT ptA, ptB;
							ptA.x = ptCursor.x + rand()%100;
							ptA.y = ptCursor.y + rand()%100;
							ptB.x = ptCursor.x + rand()%100;
							ptB.y = ptCursor.y + rand()%100;
							
							f = new Triangle(ptCursor, ptA, ptB,
														RGB(rand()%256, rand()%256, rand()%256), 
														RGB(rand()%256, rand()%256, rand()%256));
							break;
						}
					case 'C':
						{
							f = new Circle(ptCursor.x, ptCursor.y, 30, 
											RGB(rand()%256, rand()%256, rand()%256), 
											RGB(rand()%256, rand()%256, rand()%256));
							break;
						}
					case 'R':
						{
							f = new Rectangl(ptCursor.x, ptCursor.y, ptCursor.x + 30, ptCursor.y + 20,
											RGB(rand()%256, rand()%256, rand()%256), 
											RGB(rand()%256, rand()%256, rand()%256));
							break;
						}
					default:
						return 0;
				}
				if (PtInRect(&rClient, ptCursor))
				{
					lFigures->Insert(f);
					lFigures->Step();
					InvalidateRect(hWndView, NULL, TRUE);
				}
				delete f;
				return 0;
			}
		case WM_PAINT:
		{
			hdc = BeginPaint(hWndView, &ps);
			lFigures->Draw(hdc);
			EndPaint(hWndView, &ps);
			return 0;
		}
		case WM_DESTROY:
			delete lFigures;
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWndView, message, wParam, lParam);
	}
	return 0;
}


//-------------------------------------------------------------------------------------------
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
