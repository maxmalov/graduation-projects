// MovesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChesnutDonkey.h"
#include "CMovesDlg.h"

// CMovesDlg dialog

IMPLEMENT_DYNAMIC(CMovesDlg, CDialog)

CMovesDlg::CMovesDlg(CChesnutDonkeyDoc* pParent) : CDialog(IDD, 0)
{
	m_pDoc = pParent;
}

CMovesDlg::~CMovesDlg()
{
}

void CMovesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MOVESLIST, m_MovesList);
}

void CMovesDlg::UpdateInfo(CChesnutDonkeyDoc* pParent)
{
	m_pDoc = pParent;

	for(int i = 0; i < m_MovesList.GetCount();)
		m_MovesList.DeleteString(i);

	for(int i = m_pDoc->MovesCount() - 1; i > -1; i--)
		m_MovesList.AddString(m_pDoc->GetMoveString(i));
	m_MovesList.UpdateData();

}


BEGIN_MESSAGE_MAP(CMovesDlg, CDialog)
END_MESSAGE_MAP()


// CMovesDlg message handlers

BOOL CMovesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	for(int i = m_pDoc->MovesCount() - 1; i > -1; i--)
	{
		m_MovesList.AddString(m_pDoc->GetMoveString(i));
	}
	return TRUE;  
}

