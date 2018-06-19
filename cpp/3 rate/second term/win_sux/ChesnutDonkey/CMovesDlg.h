#pragma once

#include "stdafx.h"
#include "ChesnutDonkeyDoc.h"
#include "afxwin.h"
// CMovesDlg dialog

class CMovesDlg : public CDialog
{
	DECLARE_DYNAMIC(CMovesDlg)

	public:
		CMovesDlg(CChesnutDonkeyDoc* pParent);   // standard constructor
		virtual ~CMovesDlg();

		void UpdateInfo(CChesnutDonkeyDoc* pParent);

		enum { IDD = IDD_MOVESDIALOG };

	// Dialog Data
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		DECLARE_MESSAGE_MAP()
	public:
		virtual BOOL OnInitDialog();
	private:
		CChesnutDonkeyDoc *m_pDoc;
		CListBox m_MovesList;
};