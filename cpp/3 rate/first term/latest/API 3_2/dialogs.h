#include <windows.h>
#include <commdlg.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR szViewClass[MAX_LOADSTRING];
TCHAR szTextClass[MAX_LOADSTRING];

static BOOL NeedSave = FALSE;

struct dims
{
	int rectWidth, rectHeight, circRadius;
};

struct item
{
	LPSTR name, itemfrom, type;
	int date;

	void Clear()
	{
		delete[] name; name = 0;
		delete[] type; type = 0;
		delete[] itemfrom; itemfrom = 0;
	}
};
static item curItem;
static dims curDims;

INT_PTR CALLBACK	NeedSaveDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ChooseStdBmpDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	SetDimensionsDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	AnimationDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ListViewDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	AddDlg(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	StealCopyDlg(HWND, UINT, WPARAM, LPARAM);

static OPENFILENAME ofn ;

void PopFileInitialize (HWND hwnd)
{
	memset(&ofn,0,sizeof(ofn));
	static char szFilter[] = "Bitmap Files (*.bmp)\0*.bmp\0"  \
					  "All Files (*.*)\0*.*\0\0" ;

	ofn.lStructSize       = sizeof (OPENFILENAME) ;
	ofn.hwndOwner         = hwnd ;
	ofn.lpstrFilter       = szFilter ;
	ofn.nMaxFile          = _MAX_PATH ;
	ofn.nMaxFileTitle     = _MAX_FNAME + _MAX_EXT ;
	ofn.lpstrDefExt       = "bmp" ;
}

BOOL PopFileOpenDlg (HWND hwnd, LPSTR lpszFileName, LPSTR lpszTitleName)
{
	 ofn.hwndOwner         = hwnd ;
	 ofn.lpstrFile         = lpszFileName ;
	 ofn.lpstrFileTitle    = lpszTitleName ;
	 ofn.Flags             = OFN_HIDEREADONLY | OFN_CREATEPROMPT ;

	 return GetOpenFileName (&ofn) ;
}

BOOL PopFileSaveDlg (HWND hwnd, LPSTR lpszFileName, LPSTR lpszTitleName)
{
     ofn.hwndOwner         = hwnd ;
     ofn.lpstrFile         = lpszFileName ;
     ofn.lpstrFileTitle    = lpszTitleName ;
     ofn.Flags             = OFN_OVERWRITEPROMPT;

     return GetSaveFileName (&ofn) ;
}

static CHOOSECOLOR cc;

BOOL PopChooseColorDlg()
{
	static COLORREF crCustColors[16];
	
	memset(&cc,0,sizeof(cc));

	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.rgbResult = RGB(0,0,0);
	cc.lpCustColors = crCustColors;
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;
	
	return ChooseColor(&cc);
}

INT_PTR CALLBACK NeedSaveDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, 1);
			return 0;
		}
		if(LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, 0);
			return 0;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK SetDimensionsDlg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	const int nWMax = 256, nHMax = 256, nRMax = 256;
	char* tmp = 0;
	switch(msg)
	{
	
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_RECTWSPIN, UDM_SETBUDDY, 
			(WPARAM)GetDlgItem(hDlg, IDC_RECTWEDIT), 0);
		SendDlgItemMessage(hDlg, IDC_RECTWSPIN, UDM_SETRANGE, 0, (LPARAM)MAKELONG(nWMax,0));

		SendDlgItemMessage(hDlg, IDC_RECTHSPIN, UDM_SETBUDDY, 
			(WPARAM)GetDlgItem(hDlg, IDC_RECTHEDIT), 0);
		SendDlgItemMessage(hDlg, IDC_RECTHSPIN, UDM_SETRANGE, 0, (LPARAM)MAKELONG(nHMax,0));
		
		SendDlgItemMessage(hDlg, IDC_CIRCSLIDER, TBM_SETRANGE, 0, (LPARAM) MAKELONG (0, nRMax));

		char* tmp = new char[16]; 
		
		tmp[sprintf(tmp, "%d\n",curDims.rectWidth)-1]=0;
		SetDlgItemText(hDlg,IDC_RECTWEDIT,(LPCTSTR)tmp);
		
		tmp[sprintf(tmp, "%d\n",curDims.rectHeight)-1]=0;
		SetDlgItemText(hDlg,IDC_RECTHEDIT,(LPCTSTR)tmp);

		SendDlgItemMessage(hDlg, IDC_CIRCSLIDER, TBM_SETPOS, 1, curDims.circRadius); 

		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			curDims.rectWidth = min(SendDlgItemMessage(hDlg, IDC_RECTWSPIN, UDM_GETPOS, 0, 0), nWMax);
			curDims.rectHeight = min(SendDlgItemMessage(hDlg, IDC_RECTHSPIN, UDM_GETPOS, 0, 0), nHMax);
			curDims.circRadius = SendDlgItemMessage(hDlg, IDC_CIRCSLIDER, TBM_GETPOS, 0, 0);
			EndDialog(hDlg, 1);
			delete tmp;
			return 0;
			break;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			delete tmp;
			return 0;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK AnimationDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hAnim;
	static TCHAR szAnim[MAX_LOADSTRING];
	static int q;
#define MY_TIMER	1 
	switch (message)
	{
	case WM_INITDIALOG:
		LoadString(hInst, IDS_ANIMPATH, szAnim, MAX_LOADSTRING);
		
		hAnim = GetDlgItem(hDlg, IDC_ANIMATE);
		Animate_Open(hAnim,szAnim);
		Animate_Play(hAnim,0,-1,7);

		SendDlgItemMessage(hDlg, IDC_PROGRESS, PBM_SETRANGE, 0, (LPARAM) MAKELPARAM (0, 4));
		SendDlgItemMessage(hDlg, IDC_PROGRESS, PBM_SETSTEP, 1, 0);
		SendDlgItemMessage(hDlg, IDC_PROGRESS, PBM_SETPOS, 0, 0);
		
		SetTimer(hDlg, MY_TIMER, 1000, NULL);
		q=0;
		return 1;
	case WM_TIMER:
		if(wParam == MY_TIMER)
			if(++q < 5)
			{
				SetTimer(hDlg, MY_TIMER, 1000, NULL);
				SendDlgItemMessage(hDlg, IDC_PROGRESS, PBM_STEPIT,0,0);
			}
		return 1;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL )
		{
			KillTimer(hDlg, MY_TIMER);
			EndDialog(hDlg, LOWORD(wParam));
			q=0;
			return 0;
		}
		return 1;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK ChooseStdBmpDlg(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int nPicture;

	switch (message)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, IDD_TRIANGLE, IDD_ALLTOGETHER, IDD_TRIANGLE);
		nPicture = IDB_TRIANGLE;
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg,nPicture);
			return (INT_PTR)TRUE;
		case IDCANCEL:
			EndDialog(hDlg,0);
			return (INT_PTR)TRUE;
		case IDD_TRIANGLE:
			nPicture = IDB_TRIANGLE;
			break;
		case IDD_RECTANGLE:
			nPicture = IDB_RECTANGLE;
			break;
		case IDD_CIRCLE:
			nPicture = IDB_CIRCLE;
			break;
		case IDD_ALLTOGETHER:
			nPicture = IDB_COMBO;
			break;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}
INT_PTR CALLBACK AddDlg(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	const int nDMax = 2010;
	TCHAR tmpN[MAX_LOADSTRING];
	switch(msg)
	{
	
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_ITEMDATESPIN, UDM_SETBUDDY, 
			(WPARAM)GetDlgItem(hDlg, IDC_ITEMDATE), 0);
		SendDlgItemMessage(hDlg, IDC_ITEMDATESPIN, UDM_SETRANGE, 0, (LPARAM)MAKELONG(nDMax,0));
		
		for(int i = IDS_AUTOMOBILEITEM; i < IDS_OTHERITEM + 1; ++i)
		{
			LoadString(hInst, i, tmpN, MAX_LOADSTRING);
			SendDlgItemMessage(hDlg, IDC_ITEMTYPE, CB_ADDSTRING, 0, (LPARAM)tmpN );
		}
		
		char* tmp = new char[16]; 
		if(curItem.type)
		{
			EnableWindow(GetDlgItem(hDlg, IDC_ITEMTYPE),FALSE);
			tmp[sprintf(tmp, "%d\n",curItem.date)-1]=0;
			SetDlgItemText(hDlg,IDC_ITEMNAME,(LPCTSTR)curItem.name);
			SetDlgItemText(hDlg,IDC_ITEMCREATOR,(LPCTSTR)curItem.itemfrom);
			
			SendDlgItemMessage(hDlg, IDC_ITEMTYPE, CB_SELECTSTRING, -1, (LPARAM)curItem.type);
		}
		else tmp[sprintf(tmp, "%d\n",2010)-1]=0;
		
		SetDlgItemText(hDlg,IDC_ITEMDATE,(LPCTSTR)tmp);

		curItem.Clear();
		delete[] tmp;
		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			{
				curItem.date = min(SendDlgItemMessage(hDlg, IDC_ITEMDATESPIN, UDM_GETPOS, 0, 0), 
					nDMax);
				
				int nLen = SendDlgItemMessage(hDlg, IDC_ITEMTYPE, CB_GETLBTEXTLEN,0,0) + 2;
				curItem.type = new char [ nLen ];
				GetDlgItemText(hDlg, IDC_ITEMTYPE, curItem.type, nLen );
 
				nLen = SendDlgItemMessage(hDlg, IDC_ITEMNAME, WM_GETTEXTLENGTH,0,0) + 1;
				curItem.name = new char [ nLen ];
				GetDlgItemText(hDlg, IDC_ITEMNAME, curItem.name, nLen );

				nLen = SendDlgItemMessage(hDlg, IDC_ITEMCREATOR, WM_GETTEXTLENGTH,0,0) + 1;
				curItem.itemfrom = new char [ nLen ];
				GetDlgItemText(hDlg, IDC_ITEMCREATOR, curItem.itemfrom, nLen);
				
				EndDialog(hDlg, 1);
				EnableWindow(GetDlgItem(hDlg, IDC_ITEMTYPE),TRUE);
				return 0;
			}
		case IDCANCEL:
			EndDialog(hDlg, 0);
			EnableWindow(GetDlgItem(hDlg, IDC_ITEMTYPE),TRUE);
			return 0;
		}
		return (INT_PTR)FALSE;
	}
	return (INT_PTR)FALSE;
}

