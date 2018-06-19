// ChesnutDonkeyDoc.cpp : implementation of the CChesnutDonkeyDoc class
//

#include "stdafx.h"
#include "MainFrm.h"

#include "ChesnutDonkey.h"
#include "ChesnutDonkeyDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChesnutDonkeyDoc

IMPLEMENT_DYNCREATE(CChesnutDonkeyDoc, CDocument)

BEGIN_MESSAGE_MAP(CChesnutDonkeyDoc, CDocument)
END_MESSAGE_MAP()


// CChesnutDonkeyDoc construction/destruction

CChesnutDonkeyDoc::CChesnutDonkeyDoc()
{
	// TODO: add one-time construction code here
}

CChesnutDonkeyDoc::~CChesnutDonkeyDoc()
{
}

BOOL CChesnutDonkeyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	MovesHistory.NewGame();
	return TRUE;
}


BOOL CChesnutDonkeyDoc::OnOpenDocument(LPCTSTR lpszSaveFileName)
{
	if(!MovesHistory.Load(lpszSaveFileName))
	{
		AfxMessageBox(_T("Invalid file format!"), MB_ICONSTOP | MB_OK);
		return false;
	}
	SetModifiedFlag(FALSE);
	UpdateAllViews(NULL);
	return true;
}
BOOL CChesnutDonkeyDoc::OnSaveDocument(LPCTSTR lpszSaveFileName)
{
	if(!MovesHistory.Save(lpszSaveFileName))
	{
		AfxMessageBox(_T("Error saving file!"), MB_ICONSTOP | MB_OK);
		return false;
	}
	SetModifiedFlag(FALSE);
	UpdateAllViews(NULL);
	return true;
}

// CChesnutDonkeyDoc serialization

void CChesnutDonkeyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

CBlocksFactoryState CChesnutDonkeyDoc::Redo ()
{
	return MovesHistory.Redo();
}
CBlocksFactoryState CChesnutDonkeyDoc::Undo ()
{
	return MovesHistory.Undo();
}

void CChesnutDonkeyDoc::Run (const CBlocksFactoryState& cbfs, const MOVE* mv)
{
	MovesHistory.Run(cbfs,mv);
	SetModifiedFlag(TRUE);
	if(MovesHistory.IsFinished())
	{
		CString cs("Congratulations! You've won! Moves: ");
		cs.AppendFormat(_T("%d"),MovesHistory.MovesCount());
		AfxMessageBox(cs, MB_ICONINFORMATION | MB_OK);
	}
	UpdateAllViews(0,0,0);
}

CBlocksFactoryState CChesnutDonkeyDoc::CurrentState ()
{
	return MovesHistory.CurrentState();
}

int CChesnutDonkeyDoc::MovesCount()
{
	return MovesHistory.MovesCount();
}
bool CChesnutDonkeyDoc::IsFinished()
{
	return MovesHistory.IsFinished();
}

CString CChesnutDonkeyDoc::GetMoveString(int ind)
{
	return MovesHistory.GetMoveString(ind);
}

// CChesnutDonkeyDoc diagnostics

#ifdef _DEBUG
void CChesnutDonkeyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChesnutDonkeyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CChesnutDonkeyDoc commands
