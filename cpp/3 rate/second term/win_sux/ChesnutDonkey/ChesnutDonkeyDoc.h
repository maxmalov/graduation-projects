// ChesnutDonkeyDoc.h : interface of the CChesnutDonkeyDoc class
//

#pragma once
#include "History.h"

class CChesnutDonkeyDoc : public CDocument
{
protected: // create from serialization only
	CChesnutDonkeyDoc();
	DECLARE_DYNCREATE(CChesnutDonkeyDoc)

// Attributes
private:
	MotionList MovesHistory;
	// Operations
public:
	CBlocksFactoryState Redo ();
	CBlocksFactoryState Undo ();

	int MovesCount();
	bool IsFinished();
	CString GetMoveString(int ind);

	CBlocksFactoryState CurrentState ();

	void Run (const CBlocksFactoryState& cbfs, const MOVE* mv);

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszSaveFileName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszSaveFileName);
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CChesnutDonkeyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


