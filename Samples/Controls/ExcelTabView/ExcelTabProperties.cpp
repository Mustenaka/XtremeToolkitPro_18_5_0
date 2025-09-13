// ExcelTabProperties.cpp
//
// (c)1998-2018 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ExcelTab.h"
#include "ExcelTabProperties.h"
#include "ExcelTabDoc.h"
#include "ExcelTabView.h"
#include "ExcelEditCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

template <class T>
class CAutoDestructCtrl : public T
{
protected:
	virtual void PostNcDestroy()
	{
		delete this;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CExcelTabProperties dialog

CExcelTabProperties::CExcelTabProperties(BOOL& bBottom, BOOL& bHasArrows, BOOL& bHasHomeEnd, BOOL& bHScroll, BOOL& bSquareTabs, CExcelTabView* pParent)
	: CDialog(CExcelTabProperties::IDD, pParent)
	, m_bBottom(bBottom)
	, m_bHasArrows(bHasArrows)
	, m_bHasHomeEnd(bHasHomeEnd)
	, m_bHScroll(bHScroll)
	, m_bSquareTabs(bSquareTabs)
	, m_pParentWnd(pParent)
{
	m_cyScroll = ::GetSystemMetrics(SM_CYHSCROLL);
		
	//{{AFX_DATA_INIT(CExcelTabProperties)
	m_iTabNum = 0;
	m_csText = _T("");
	m_bLargeTabs = FALSE;
	//}}AFX_DATA_INIT

    ASSERT_VALID(m_pParentWnd);
    if (m_pParentWnd)
    {
        m_bLargeTabs = (m_pParentWnd->m_pExcelTabCtrl->GetTabHeight() > m_cyScroll);
    }
}

void CExcelTabProperties::DoDataExchange(CDataExchange* pDX)
{
    const int nTabs = m_pParentWnd ? m_pParentWnd->m_pExcelTabCtrl->GetItemCount() - 1 : 0;

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExcelTabProperties)
	DDX_Control(pDX, IDC_MODIFY_TAB, m_btnModifyTab);
	DDX_Control(pDX, IDC_DELETE_TAB, m_btnDeleteTab);
	DDX_Control(pDX, IDC_DELETE_ALL, m_btnDeleteAll);
	DDX_Control(pDX, IDC_ADD_TAB, m_btnAddTab);
	DDX_Text(pDX, IDC_TAB_NUM, m_iTabNum);
	DDV_MinMaxUInt(pDX, m_iTabNum, 0, nTabs);
	DDX_Text(pDX, IDC_TEXT, m_csText);
	DDX_Check(pDX, IDC_FTS_XTP_BOTTOM, m_bBottom);
	DDX_Check(pDX, IDC_FTS_XTP_HASARROWS, m_bHasArrows);
	DDX_Check(pDX, IDC_FTS_XTP_HASHOMEEND, m_bHasHomeEnd);
	DDX_Check(pDX, IDC_FTS_XTP_HSCROLL, m_bHScroll);
	DDX_Check(pDX, IDC_FTS_XTP_SQUARETABS, m_bSquareTabs);
	DDX_Check(pDX, IDC_CHK_LARGETABS, m_bLargeTabs);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExcelTabProperties, CDialog)
	//{{AFX_MSG_MAP(CExcelTabProperties)
	ON_BN_CLICKED(IDC_FTS_XTP_BOTTOM, OnFtsXtBottom)
	ON_BN_CLICKED(IDC_FTS_XTP_HASARROWS, OnFtsXtHasarrows)
	ON_BN_CLICKED(IDC_FTS_XTP_HASHOMEEND, OnFtsXtHashomeend)
	ON_BN_CLICKED(IDC_FTS_XTP_HSCROLL, OnFtsXtHscroll)
	ON_BN_CLICKED(IDC_ADD_TAB, OnAddTab)
	ON_BN_CLICKED(IDC_DELETE_ALL, OnDeleteAll)
	ON_BN_CLICKED(IDC_DELETE_TAB, OnDeleteTab)
	ON_BN_CLICKED(IDC_MODIFY_TAB, OnModifyTab)
	ON_EN_CHANGE(IDC_TEXT, OnChangeText)
	ON_BN_CLICKED(IDC_FTS_XTP_SQUARETABS, OnSquareTabs)
	ON_BN_CLICKED(IDC_CHK_LARGETABS, OnChkLargeTabs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExcelTabProperties message handlers

BOOL CExcelTabProperties::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	UpdateDlgStatus();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CExcelTabProperties::OnFtsXtBottom() 
{
    if (!m_pParentWnd)
        return;

    UpdateData();
	m_pParentWnd->UpdateExcelTab();
}

void CExcelTabProperties::OnFtsXtHasarrows() 
{
    if (!m_pParentWnd)
        return;

	UpdateData();
	m_pParentWnd->UpdateExcelTab();
	GetDlgItem(IDC_FTS_XTP_HASHOMEEND)->EnableWindow(m_bHasArrows);
}

void CExcelTabProperties::OnFtsXtHashomeend() 
{
    if (!m_pParentWnd)
        return;

	UpdateData();
	m_pParentWnd->UpdateExcelTab();
}

void CExcelTabProperties::OnFtsXtHscroll() 
{
    if (!m_pParentWnd)
        return;

	UpdateData();
	m_pParentWnd->UpdateExcelTab();
}

void CExcelTabProperties::OnSquareTabs() 
{
    if (!m_pParentWnd)
        return;

	UpdateData();
	m_pParentWnd->UpdateExcelTab();
}

void CExcelTabProperties::OnAddTab()
{
    if (!m_pParentWnd)
        return;

	if (UpdateData())
	{
		CAutoDestructCtrl<CExcelEditCtrl> *pSheet = new CAutoDestructCtrl<CExcelEditCtrl>();
		pSheet->Create(WS_CHILD | WS_TABSTOP | WS_CLIPCHILDREN |
			WS_HSCROLL | WS_VSCROLL | ES_MULTILINE, CXTPEmptyRect(), m_pParentWnd->m_pExcelTabCtrl, 1000);
		pSheet->SetWindowText(m_csText);
		m_pParentWnd->m_pExcelTabCtrl->InsertItem(m_iTabNum, m_csText, pSheet);
	}
	UpdateDlgStatus();
}

void CExcelTabProperties::OnDeleteAll()
{
    if (!m_pParentWnd)
        return;

	int count = m_pParentWnd->m_pExcelTabCtrl->GetItemCount();
	for (int i = count - 1; i >= 0; i--)
	{
		CWnd *pTabWnd = m_pParentWnd->m_pExcelTabCtrl->GetItemWindow(i);
		m_pParentWnd->m_pExcelTabCtrl->DeleteItem(i);
		pTabWnd->DestroyWindow();
	}
	UpdateDlgStatus();
}

void CExcelTabProperties::OnDeleteTab()
{
    if (!m_pParentWnd)
        return;

	if (m_pParentWnd->m_pExcelTabCtrl->GetItemCount() > 0  &&  UpdateData())
	{
		CWnd *pTabWnd = m_pParentWnd->m_pExcelTabCtrl->GetItemWindow(m_iTabNum);
		m_pParentWnd->m_pExcelTabCtrl->DeleteItem(m_iTabNum);
		pTabWnd->DestroyWindow();
	}
	UpdateDlgStatus();
}

void CExcelTabProperties::OnModifyTab()
{
    if (!m_pParentWnd)
        return;

	if (m_pParentWnd->m_pExcelTabCtrl->GetItemCount() > 0  &&  UpdateData())
	{
		m_pParentWnd->m_pExcelTabCtrl->SetItemText(m_iTabNum, m_csText);
	}
	UpdateDlgStatus();
}

void CExcelTabProperties::UpdateDlgStatus()
{
    if (!m_pParentWnd)
        return;

	const bool bHasTabs = (m_pParentWnd->m_pExcelTabCtrl->GetItemCount() > 0);
	m_btnModifyTab.EnableWindow(bHasTabs);
	m_btnDeleteTab.EnableWindow(bHasTabs);
	m_btnModifyTab.EnableWindow(bHasTabs);
}

void CExcelTabProperties::OnChangeText() 
{
	UpdateData();
	m_btnAddTab.EnableWindow(!m_csText.IsEmpty());
}

void CExcelTabProperties::OnChkLargeTabs() 
{
    if (!m_pParentWnd)
        return;

	UpdateData();
	m_pParentWnd->m_pExcelTabCtrl->SetTabHeight(m_bLargeTabs ? XTP_DPI_Y(27) : m_cyScroll);
}
