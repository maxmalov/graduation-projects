// ChesnutDonkeyView.cpp : implementation of the CChesnutDonkeyView class
//

#include "stdafx.h"
#include "MainFrm.h"

#include "ChesnutDonkey.h"

#include "ChesnutDonkeyDoc.h"
#include "ChesnutDonkeyView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChesnutDonkeyView

IMPLEMENT_DYNCREATE(CChesnutDonkeyView, CView)

BEGIN_MESSAGE_MAP(CChesnutDonkeyView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()

	ON_COMMAND(ID_GAME_REDO, &CChesnutDonkeyView::OnRedo)
	ON_COMMAND(ID_GAME_UNDO, &CChesnutDonkeyView::OnUndo)

	ON_COMMAND(ID_COLOR_BLOCK, &CChesnutDonkeyView::OnColorBlock)
	ON_COMMAND(ID_COLOR_SELECTEDBLOCK, &CChesnutDonkeyView::OnColorSelectedBlock)
	ON_COMMAND(ID_COLOR_WAYTIPS, &CChesnutDonkeyView::OnColorWayTip)
	ON_COMMAND(ID_COLOR_BACKGROUND, &CChesnutDonkeyView::OnColorBackground)
	ON_COMMAND(ID_CHANGEFONT, &CChesnutDonkeyView::OnFontText)
	ON_COMMAND(ID_GAME_NOTATION, &CChesnutDonkeyView::OnViewNotation)
END_MESSAGE_MAP()

// CChesnutDonkeyView construction/destruction

CChesnutDonkeyView::CChesnutDonkeyView()
{
	// TODO: add construction code here
}

CChesnutDonkeyView::~CChesnutDonkeyView()
{
}

BOOL CChesnutDonkeyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CChesnutDonkeyView drawing

void CChesnutDonkeyView::OnDraw(CDC* pDC)
{
	CChesnutDonkeyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: add draw code for native data here

	ReDrawField();

	pDC->SetStretchBltMode(STRETCH_HALFTONE);//хороший вариант
	pDC->BitBlt(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), 
		pm_MemDC, 0, 0, SRCCOPY);
	CMainFrame *pFrame = (CMainFrame *)this->GetParentFrame();
	pFrame->SetMessageText(AFX_IDS_IDLEMESSAGE);
}

// CChesnutDonkeyView printing

BOOL CChesnutDonkeyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CChesnutDonkeyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CChesnutDonkeyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CChesnutDonkeyView::NewGame ()
{
	delete pcbf;
	pcbf = new CBlocksFactory(CBlocksFactoryState(),FieldPosition, cFieldWidth,cFieldHeight);
	Invalidate(0);
}

void CChesnutDonkeyView::LoadSettings()
{
	//TODO: Load settings from the registry

	CChesnutDonkeyApp *pApp = (CChesnutDonkeyApp*)AfxGetApp();
	LPCTSTR lpszKeyName = pApp->m_pszRegistryKey;
	LPCTSTR lpszAppName = pApp->m_pszAppName;

	HKEY hKeySoftWare, hKeyApp, hKey, hKeySettings;
	RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software"), 0, 0, 0, KEY_READ, 0, &hKeySoftWare, 0);
	RegCreateKeyEx(hKeySoftWare, lpszKeyName, 0, 0, 0, KEY_READ, 0, &hKey, 0);
	RegCreateKeyEx(hKey, lpszAppName, 0, 0, 0, KEY_READ, 0, &hKeyApp, 0);
	RegCreateKeyEx(hKeyApp, _T("Settings"), 0, 0, 0, KEY_READ, 0, &hKeySettings, 0);
	DWORD cbData;

	//cbData = sizeof(DWORD);
	//DWORD dwDims;
	//if(RegQueryValueEx(hKeySettings, _T("Field dimensions"), 0, 0, (BYTE*)&dwDims, &cbData) 
	//		!= ERROR_SUCCESS)
	//{
		cFieldHeight = 500;
		cFieldWidth = 400;
	//}
	//else
	//{
	//	cFieldWidth = LOWORD(dwDims);
	//	cFieldHeight = HIWORD(dwDims);
	//}

	if(RegQueryValueEx(hKeySettings, _T("Background color"), 0, 0, (BYTE*)&BackgroundColor, &cbData) 
			!= ERROR_SUCCESS)
	{
		BackgroundColor = RGB(220,220,220);
	}
	if(RegQueryValueEx(hKeySettings, _T("Block color"), 0, 0, (BYTE*)&BlocksColor, &cbData) 
			!= ERROR_SUCCESS)
	{
		BlocksColor = RGB(128,128,128);
	}
	if(RegQueryValueEx(hKeySettings, _T("Selected block color"), 0, 0, (BYTE*)&SelectedBlocksColor, &cbData) 
			!= ERROR_SUCCESS)
	{
		SelectedBlocksColor = RGB(50,50,200);
	}
	if(RegQueryValueEx(hKeySettings, _T("Way tip color"), 0, 0, (BYTE*)&WayTipColor, &cbData) 
			!= ERROR_SUCCESS)
	{
		WayTipColor = RGB(200,10,10);
	}
	if(RegQueryValueEx(hKeySettings, _T("Text color"), 0, 0, (BYTE*)&TextColor, &cbData) 
			!= ERROR_SUCCESS)
	{
		TextColor = RGB(0,0,0);
	}

	cbData = sizeof(LOGFONT);
	pTextFont = new CFont();
	if(RegQueryValueEx(hKeySettings, _T("Font"), 0, 0, (BYTE*)&lfCurFont, &cbData) 
			!= ERROR_SUCCESS)
	{
		pTextFont->CreateFontW(20,12,0,0,0,0,0,0,0,0,0,0,0, _T("Courier"));
		pTextFont->GetLogFont(&lfCurFont);
	}
	else pTextFont->CreateFontIndirectW(&lfCurFont);

	RegCloseKey(hKeySettings);
	RegCloseKey(hKeyApp);
	RegCloseKey(hKey);
	RegCloseKey(hKeySoftWare);
}

void CChesnutDonkeyView::SaveSettings()
{
	CChesnutDonkeyApp *pApp = (CChesnutDonkeyApp*)AfxGetApp();
	LPCTSTR lpszKeyName = pApp->m_pszRegistryKey;
	LPCTSTR lpszAppName = pApp->m_pszAppName;
	HKEY hKeySoftWare, hKeyApp, hKey, hKeySettings;

	RegCreateKeyEx(HKEY_CURRENT_USER, _T("Software"), 0, 0, 0, KEY_SET_VALUE, 0, &hKeySoftWare, 0);
	RegCreateKeyEx(hKeySoftWare, lpszKeyName, 0, 0, 0, KEY_SET_VALUE, 0, &hKey, 0);
	RegCreateKeyEx(hKey, lpszAppName, 0, 0, 0, KEY_SET_VALUE, 0, &hKeyApp, 0);
	RegCreateKeyEx(hKeyApp, _T("Settings"), 0, 0, 0, KEY_SET_VALUE, 0, &hKeySettings, 0);

	//DWORD dwDim = MAKELONG(cFieldWidth,cFieldHeight);
	//RegSetValueEx(hKeySettings, _T("Field dimensions"), 0, REG_DWORD, (BYTE*)&dwDim, sizeof(DWORD)); 
	
	RegSetValueEx(hKeySettings, _T("Background color"), 0, REG_DWORD, (BYTE*)&BackgroundColor, sizeof(DWORD)); 
	RegSetValueEx(hKeySettings, _T("Block color"), 0, REG_DWORD, (BYTE*)&BlocksColor, sizeof(DWORD)); 
	RegSetValueEx(hKeySettings, _T("Selected block color"), 0, REG_DWORD, (BYTE*)&SelectedBlocksColor, sizeof(DWORD)); 
	RegSetValueEx(hKeySettings, _T("Way tip color"), 0, REG_DWORD, (BYTE*)&WayTipColor, sizeof(DWORD)); 
	RegSetValueEx(hKeySettings, _T("Text color"), 0, REG_DWORD, (BYTE*)&TextColor, sizeof(DWORD)); 
	RegSetValueEx(hKeySettings, _T("Font"), 0, REG_BINARY, (BYTE*)&lfCurFont, sizeof(LOGFONT));

	RegCloseKey(hKeySettings);
	RegCloseKey(hKeyApp);
	RegCloseKey(hKey);
	RegCloseKey(hKeySoftWare);
}

COLORREF CChesnutDonkeyView::CallColorDlg(COLORREF curColor)
{
	CColorDialog colorDlg(curColor);
	if(colorDlg.DoModal() == IDOK)
		return colorDlg.GetColor();
}

void CChesnutDonkeyView::ReDrawField()
{
	RECT r;
	GetClientRect(&r);
	pm_MemDC->FillRect(CRect(0,0,GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)),
		&CBrush(RGB(255,255,255)));
	
	pm_MemDC->SelectObject(pTextFont);
	pm_MemDC->SetTextColor(TextColor);
	if(pcbf)
		pcbf->Draw(pm_MemDC, BlocksColor, SelectedBlocksColor, WayTipColor, BackgroundColor);
}

void CChesnutDonkeyView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CChesnutDonkeyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	delete pcbf;
	pcbf = new CBlocksFactory(pDoc->CurrentState(), FieldPosition, cFieldWidth,cFieldHeight);
	dlgM->UpdateInfo(pDoc);
	Invalidate(0);
}


// CChesnutDonkeyView diagnostics

#ifdef _DEBUG
void CChesnutDonkeyView::AssertValid() const
{
	CView::AssertValid();
}

void CChesnutDonkeyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CChesnutDonkeyDoc* CChesnutDonkeyView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChesnutDonkeyDoc)));
	return (CChesnutDonkeyDoc*)m_pDocument;
}
#endif //_DEBUG


// CChesnutDonkeyView message handlers
int CChesnutDonkeyView::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CView::OnCreate(lpcs) == -1)
		return -1;
	
	LoadSettings();
	pm_MemDC = new CDC();
	pm_OffBmp = new CBitmap();

	CClientDC dc(this);
	pm_MemDC->CreateCompatibleDC(&dc);
	pm_OffBmp->CreateCompatibleBitmap(&dc, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	pm_MemDC->SelectObject(pm_OffBmp);

	pm_MemDC->SetBkMode(TRANSPARENT);
	pm_MemDC->SetTextColor(TextColor);
	pm_MemDC->SelectObject(pTextFont);

	pcbf = new CBlocksFactory(FieldPosition,cFieldWidth,cFieldHeight);

	dlgM = new CMovesDlg(GetDocument());
	dlgM->Create(dlgM->IDD);

	return 0;
}
void CChesnutDonkeyView::OnDestroy()
{
	SaveSettings();
	delete pcbf;
	delete pTextFont;
	delete pm_MemDC;
	delete pm_OffBmp;
	dlgM->DestroyWindow();
	delete dlgM;

	CView::OnDestroy();
}

void CChesnutDonkeyView::OnSize(UINT nType, int cx, int cy)
{
	FieldPosition.x = ( cx - cFieldWidth) / 2; 
	FieldPosition.y = ( cy - cFieldHeight) / 2; 

	CBlocksFactoryState cbfs = pcbf->FactoryState();
	delete pcbf;
	pcbf = new CBlocksFactory(cbfs,FieldPosition, cFieldWidth, cFieldHeight);
	CView::OnSize(nType,cx,cy);
}
BOOL CChesnutDonkeyView::OnEraseBkgnd(CDC* pDC)
{
	return 1;
}
void CChesnutDonkeyView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CChesnutDonkeyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	//TODO: handle with notation!!!
	MOVE* mv = pcbf->OnMouseClick(point);
	if(mv) pDoc->Run(pcbf->FactoryState(), mv);
	delete mv;
	Invalidate(0);
}

void CChesnutDonkeyView::OnRedo ()
{
	CChesnutDonkeyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	try
	{
		CBlocksFactory *tmp = pcbf;
		pcbf = new CBlocksFactory(pDoc->Redo(), FieldPosition, cFieldWidth,cFieldHeight);
		dlgM->UpdateInfo(pDoc);
		delete tmp;

		Invalidate(0);
	}
	catch(MotionListEx){}
}
void CChesnutDonkeyView::OnUndo ()
{
	CChesnutDonkeyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	try
	{
		CBlocksFactory *tmp = pcbf;
		pcbf = new CBlocksFactory(pDoc->Undo(), FieldPosition, cFieldWidth,cFieldHeight);
		dlgM->UpdateInfo(pDoc);
		delete tmp;

		Invalidate(0);
	}
	catch(MotionListEx){}
}

void CChesnutDonkeyView::OnColorBlock()
{
	BlocksColor = CallColorDlg(BlocksColor);
	Invalidate(0);
}
void CChesnutDonkeyView::OnColorSelectedBlock()
{
	SelectedBlocksColor = CallColorDlg(SelectedBlocksColor);
	Invalidate(0);
}
void CChesnutDonkeyView::OnColorWayTip()
{
	WayTipColor = CallColorDlg(WayTipColor);
	Invalidate(0);
}

void CChesnutDonkeyView::OnColorBackground()
{
	BackgroundColor = CallColorDlg(BackgroundColor);
	Invalidate(0);
}
void CChesnutDonkeyView::OnFontText()
{
	CFontDialog cFontDlg(&lfCurFont);
	if(cFontDlg.DoModal() == IDOK)
	{
		cFontDlg.GetCurrentFont(&lfCurFont);
		TextColor = cFontDlg.GetColor();
	}
	pTextFont->DeleteObject();
	pTextFont->CreateFontIndirectW(&lfCurFont);
	Invalidate(0);
}
void CChesnutDonkeyView::OnViewNotation()
{
	dlgM->ShowWindow(SHOW_OPENWINDOW);
}

void CChesnutDonkeyView::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CView::PostNcDestroy();
}
