// API 3_2.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "API 3_2.h"
#include "queue.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR szButtonLBTitle[MAX_LOADSTRING];			// the title buttot text
TCHAR szButtonCBTitle[MAX_LOADSTRING];			// the title buttot text
TCHAR szButtonAddTitle[MAX_LOADSTRING];

WNDPROC OldEditProc;
WNDPROC OldComboProc;
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//int					AdjustScrolling(HWND);


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_API3_2, szWindowClass, MAX_LOADSTRING);
	LoadString(hInstance, IDS_BUTTON_ADD_LB, szButtonLBTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDS_BUTTON_ADD_CB, szButtonCBTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDS_BUTTON_ADD, szButtonAddTitle, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_API3_2));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_API3_2));
	wcex.hCursor		= LoadCursor(hInstance, MAKEINTRESOURCE(IDC_MY_CURSOR));
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_API3_2);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
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

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK EditProc(HWND hEdit, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
	case WM_KEYDOWN:
		if(wParam == VK_RETURN)
		{
			SendMessage(GetParent(hEdit),msg,wParam,lParam);
			return 0;
		}
	}
	return CallWindowProc(OldEditProc,hEdit,msg,wParam,lParam);
}
LRESULT CALLBACK ComboProc(HWND hCombobox, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int ind;
	switch(msg)
	{
	case WM_KEYDOWN:
		if(wParam == VK_RETURN)
		{
			int nLen = SendMessage(hCombobox,WM_GETTEXTLENGTH,0,0);
			char* tmp = new char [nLen+1];
			GetWindowText(hCombobox,tmp, nLen+1);
			if(ind = SendMessage(hCombobox,CB_FINDSTRINGEXACT,0,(LPARAM)tmp) == CB_ERR)
			{
				SendMessage(hCombobox,CB_ADDSTRING,0,(LPARAM)tmp);
			}
			delete[] tmp;
			return 0;
		}
	}
	return CallWindowProc(OldComboProc,hCombobox,msg,wParam,lParam);
}
//int AdjustScrolling(HWND hWnd)
//{
//	HDC hdc;
//	HFONT hFont, hFontOld;
//	hFont = (HFONT)SendMessage(hWnd,WM_GETFONT,0,0);
//	SIZE size;
//	int max_len=-1, cur_len=0, q = SendMessage(hWnd,LB_GETCOUNT,0,0);
//	if(q != LB_ERR)
//	{
//		char* tmp = 0;
//		hdc = GetDC(hWnd);
//		hFontOld = (HFONT)SelectObject(hdc,hFont);
//		for(int i=0; i<q; ++i)
//		{
//			int nLen = SendMessage(hWnd,LB_GETTEXTLEN,i,0);
//			tmp = new char [nLen+1];
//			SendMessage(hWnd,LB_GETTEXT,i,(LPARAM)tmp);
//			GetTextExtentPoint32(hdc,tmp,nLen,&size);
//			if(size.cx > max_len) max_len = size.cx;
//			delete[] tmp;
//		}
//		SelectObject(hdc, hFontOld);
//		ReleaseDC(hWnd,hdc);
//	}
//	return max_len;
//}

LRESULT CALLBACK WndProc(HWND hWndParent, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	static int dID;
	PAINTSTRUCT ps;
	HDC hdc;
	POINT A,B,C;
	//static HWND hEdit, hButtonAdd, hButtonAddLB, hButtonAddCB, hListbox, hCombobox;
	//static RECT rClient;
	//static int cxClient, cyClient;
	//static int xDif=5, yDif=5;
	static HCURSOR hCursor;
	static HMENU hMenu, hDrawMenu;
	static _queue* q;
	static int xMouse, yMouse;

	#define bWidth			130
	#define bHeight			20

	#define CIRCLE			1 
	#define RECTANGLE		2 
	#define TRIANGLE		3 

	#define nRem			128

	switch (message)
	{
	case WM_CREATE:
		q = new _queue;
		dID = 0;
		hMenu = GetMenu(hWndParent);
		hDrawMenu = GetSubMenu(hMenu,1);
				
		hCursor = GetCursor();

		//GetClientRect(hWndParent,&rClient);
		//cxClient=rClient.right-rClient.left;
		//cyClient=-rClient.top+rClient.bottom;

		//hEdit = CreateWindow("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | 
		//	ES_LEFT | ES_AUTOHSCROLL , xDif, 0, cxClient/2-bWidth/2, bHeight, hWndParent, NULL, 
		//	((LPCREATESTRUCT) lParam) -> hInstance, NULL);
		//OldEditProc = (WNDPROC)SetWindowLong(hEdit,GWL_WNDPROC, (LONG)EditProc);

		//hListbox = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD | 
		//	WS_HSCROLL , xDif, bHeight+yDif, cxClient/2-bWidth/2, cyClient-yDif-bHeight, hWndParent,
		//	(HMENU)ID_LB, ((LPCREATESTRUCT) lParam) -> hInstance,NULL);

		//hCombobox = CreateWindow("combobox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_SORT,
		//	cxClient/2+bWidth/2+xDif, 0, cxClient/2-bWidth/2-2*xDif, cyClient, hWndParent, (HMENU)ID_CB, 
		//	((LPCREATESTRUCT) lParam) -> hInstance,NULL);
		//OldComboProc = (WNDPROC)SetWindowLong(hCombobox,GWL_WNDPROC,(LONG)ComboProc);

		//hButtonAddCB = CreateWindow("button", szButtonCBTitle, WS_CHILD | WS_VISIBLE |
		//	BS_PUSHBUTTON, xDif+cxClient/2-bWidth/2, 2*bHeight+2*yDif, bWidth, bHeight, hWndParent, 
		//	(HMENU)ID_BUTTON_ADD_CB, ((LPCREATESTRUCT) lParam) -> hInstance, NULL);
		//EnableWindow(hButtonAddCB,FALSE);

		//hButtonAddLB = CreateWindow("button", szButtonLBTitle, WS_CHILD | WS_VISIBLE |
		//	BS_PUSHBUTTON, xDif+cxClient/2-bWidth/2, 80+3*yDif, bWidth, bHeight, hWndParent, 
		//	(HMENU)ID_BUTTON_ADD_LB, ((LPCREATESTRUCT) lParam) -> hInstance, NULL);
		//EnableWindow(hButtonAddLB,FALSE);
		break;
	//case WM_KEYDOWN:
	//	if(wParam == VK_RETURN)
	//	{
	//		int nLen = SendMessage( hEdit, WM_GETTEXTLENGTH, 0, 0 );
	//		char* tmp = new char [ nLen + 1 ];
	//		GetWindowText( hEdit, tmp, nLen + 1 );
	//		if(SendMessage(hListbox,LB_FINDSTRINGEXACT,0,(LPARAM)tmp) == LB_ERR )
	//		{
	//			SendMessage( hListbox, LB_ADDSTRING, 0, (LPARAM)tmp );
	//			SendMessage(hListbox,LB_SETHORIZONTALEXTENT,AdjustScrolling(hListbox)+xDif,0);
	//		}
	//		delete[] tmp;
	//		return 0;
	//	}
	case WM_SIZE:
		return 0;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId)
		{
		//case ID_BUTTON_ADD_CB:
		//	{
		//		int nCurSel = SendMessage(hListbox,LB_GETCURSEL,0,0);
		//		if(nCurSel != LB_ERR)
		//		{
		//			int nLen = SendMessage(hListbox,LB_GETTEXTLEN,nCurSel,0);
		//			char* tmp = new char [nLen+1];
		//			SendMessage(hListbox, LB_GETTEXT, nCurSel, (LPARAM)tmp);
		//			if( SendMessage(hCombobox,CB_FINDSTRINGEXACT,0,(LPARAM)tmp) == CB_ERR)
		//			{
		//				SendMessage(hCombobox,CB_ADDSTRING,0,(LPARAM)tmp);
		//			}
		//			delete[] tmp;
		//		}
		//		return 0;
		//	}
		//case ID_BUTTON_ADD_LB:
		//	{
		//		int nCurSel = SendMessage(hCombobox,CB_GETCURSEL,0,0);
		//		if(nCurSel != CB_ERR)
		//		{
		//			int nLen = SendMessage(hCombobox,CB_GETLBTEXTLEN,nCurSel,0);
		//			char* tmp = new char [nLen+1];
		//			SendMessage(hCombobox, CB_GETLBTEXT, nCurSel, (LPARAM)tmp);
		//			if( SendMessage(hListbox,LB_FINDSTRINGEXACT,0,(LPARAM)tmp) == LB_ERR)
		//			{
		//				SendMessage(hListbox,LB_ADDSTRING,0,(LPARAM)tmp);
		//				SendMessage(hListbox,LB_SETHORIZONTALEXTENT,AdjustScrolling(hListbox)+xDif,0);
		//				
		//			}
		//			delete[] tmp;
		//		}
		//		return 0;
		//	}
		//case ID_LB:
		//	if(wmEvent == LBN_SELCHANGE) EnableWindow(hButtonAddCB,TRUE);
		//	if(wmEvent == LBN_DBLCLK)
		//	{
		//		int nCurSel = SendMessage(hListbox,LB_GETCURSEL,0,0);
		//		if(nCurSel != LB_ERR)
		//		{
		//			int nLen = SendMessage(hListbox,LB_GETTEXTLEN,nCurSel,0);
		//			char* tmp = new char [nLen+1];
		//			SendMessage(hListbox, LB_GETTEXT, nCurSel, (LPARAM)tmp);
		//			nLen = SendMessage( hEdit, WM_GETTEXTLENGTH, 0, 0 );
		//			SendMessage(hEdit,EM_SETSEL,0,nLen);
		//			SendMessage(hEdit,EM_REPLACESEL,TRUE,(LPARAM)tmp);
		//			delete[] tmp;
		//		}
		//	}
		//	break;
		//case ID_CB:
		//	if(wmEvent == CBN_SELCHANGE) EnableWindow(hButtonAddLB,TRUE);
		//	break;
		case IDM_CIRCLE:
			if(dID == (int)CIRCLE)
			{
				dID = 0;
				CheckMenuRadioItem(hMenu,IDM_CIRCLE,IDM_TRIANGLE,NULL,MF_BYCOMMAND);
			}
			else
			{
				CheckMenuRadioItem(hMenu,IDM_CIRCLE,IDM_TRIANGLE,IDM_CIRCLE,MF_BYCOMMAND);
				dID = (int)CIRCLE;
			}
			break;
		case IDM_RECT:
			if(dID == (int)RECTANGLE)
			{
				dID = 0;
				CheckMenuRadioItem(hMenu,IDM_CIRCLE,IDM_TRIANGLE,NULL,MF_BYCOMMAND);
			}
			else
			{
				CheckMenuRadioItem(hMenu,IDM_CIRCLE,IDM_TRIANGLE,IDM_RECT,MF_BYCOMMAND);
				dID = (int)RECTANGLE;
			}
			break;
		case IDM_TRIANGLE:
			if(dID == (int)TRIANGLE)
			{
				dID = 0;
				CheckMenuRadioItem(hMenu,IDM_CIRCLE,IDM_TRIANGLE,NULL,MF_BYCOMMAND);
			}
			else
			{
				CheckMenuRadioItem(hMenu,IDM_CIRCLE,IDM_TRIANGLE,IDM_TRIANGLE,MF_BYCOMMAND);
				dID = (int)TRIANGLE;
			}
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWndParent, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWndParent);
			break;
		default:
			return DefWindowProc(hWndParent, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWndParent,&ps);
		q->print(hdc);
		EndPaint(hWndParent,&ps);
		break;
	case WM_LBUTTONDOWN:
		{
			hdc=GetDC(hWndParent);
			A.x=xMouse=LOWORD(lParam);
			A.y=yMouse=HIWORD(lParam);
			figure* elem;
			switch(dID)
			{
			case CIRCLE:
				elem = new circle(A,rand()%nRem,RGB(rand()%256,rand()%256,rand()%256),
					RGB(rand()%256,rand()%256,rand()%256));
				q->push(elem);
				elem->draw(hdc);
				delete elem;
				break;
			case RECTANGLE:
				B.x=rand()%nRem;
				B.y=rand()%nRem;
				elem = new rectangle(A,B,RGB(rand()%256,rand()%256,rand()%256), 
					RGB(rand()%256,rand()%256,rand()%256));
				q->push(elem);
				elem->draw(hdc);
				delete elem;
				break;
			case TRIANGLE:
				B.x=rand()%nRem;
				B.y=rand()%nRem;
				C.x=rand()%nRem;
				C.y=rand()%nRem;
				elem = new triangle(A,B,C,RGB(rand()%256,rand()%256,rand()%256), 
					RGB(rand()%256,rand()%256,rand()%256));
				q->push(elem);
				elem->draw(hdc);
				delete elem;
				break;
			}
			ReleaseDC(hWndParent,hdc);
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWndParent, message, wParam, lParam);
	}
	return 0;
}

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
