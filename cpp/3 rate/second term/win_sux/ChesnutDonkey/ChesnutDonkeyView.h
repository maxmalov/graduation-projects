// ChesnutDonkeyView.h : interface of the CChesnutDonkeyView class
//


#pragma once
#include "CMovesDlg.h"

class CChesnutDonkeyView : public CView
{
protected: // create from serialization only
	
	CChesnutDonkeyView();
	DECLARE_DYNCREATE(CChesnutDonkeyView  )

private:
	COLORREF BlocksColor, SelectedBlocksColor, WayTipColor, BackgroundColor, TextColor;
	LOGFONT lfCurFont;
	
	CBitmap* pm_OffBmp;
	CDC* pm_MemDC;	int cFieldWidth, cFieldHeight;

	CPoint FieldPosition;

// Attributes

public:
	CBlocksFactory* pcbf;
	CFont* pTextFont;
	CMovesDlg* dlgM;

	CChesnutDonkeyDoc* GetDocument() const;

// Operations
private:
	
	void SaveSettings ();
	void LoadSettings ();
	void ReDrawField  ();
	COLORREF CallColorDlg (COLORREF);

public:

	void NewGame ();


// Overrides
public:
	
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:

	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);


// Implementation
public:

	virtual ~CChesnutDonkeyView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnColorBlock();
	afx_msg void OnColorSelectedBlock();
	afx_msg void OnColorWayTip();
	afx_msg void OnColorBackground();
	afx_msg void OnFontText();

	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnRedo ();
	afx_msg void OnUndo ();
	afx_msg void OnViewNotation();
protected:
	virtual void PostNcDestroy();
};

#ifndef _DEBUG  // debug version in ChesnutDonkeyView.cpp
inline CChesnutDonkeyDoc* CChesnutDonkeyView::GetDocument() const
   { return reinterpret_cast<CChesnutDonkeyDoc*>(m_pDocument); }
#endif

