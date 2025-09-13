// CalendarEventColorDlg.cpp : implementation file
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
#include "Resource.h"
#include "CalendarEventColorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCalendarEventColorDlg dialog

CCalendarEventColorDlg::CCalendarEventColorDlg(CXTPCalendarControl* pCalendarCtrl, CWnd* pParent /*=NULL*/)
	: CDialog(CCalendarEventColorDlg::IDD, pParent)
	, m_pCalendarCtrl(pCalendarCtrl)
{
	ASSERT(m_pCalendarCtrl);

	//{{AFX_DATA_INIT(CCalendarEventColorDlg)
	//}}AFX_DATA_INIT

	CXTPCalendarViewEvent* pViewEvent = XTP_SAFE_GET2(
		pCalendarCtrl, GetActiveView(), GetLastSelectedViewEvent(), NULL);

	if (pViewEvent && pViewEvent->IsShowingToolTip()) 
	{ 
		pViewEvent->HideToolTip(); 
	}

	CXTPCalendarEvent* pEvent = XTP_SAFE_GET1(
		pViewEvent, GetEvent(), NULL);

	m_pEvent.SetPtr(pEvent->CloneEvent(), TRUE);
}

void CCalendarEventColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCalendarEventColorDlg)
	DDX_Control(pDX, IDC_EVENT_INFO, m_wndEventInfo);
#ifdef _XTP_INCLUDE_CONTROLS
	DDX_Control(pDX, IDC_EVENT_COLORPICKER, m_cpEvent);
#endif
	DDX_Control(pDX, IDC_EVENT_LBOX_LABEL, m_lboxLabel);
	DDX_Control(pDX, IDC_EVENT_LBOX_CATEGORY, m_lboxCategory);
	DDX_Control(pDX, IDC_EVENT_TAB, m_wndTabCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCalendarEventColorDlg, CDialog)
	//{{AFX_MSG_MAP(CCalendarEventColorDlg)
	ON_NOTIFY(TCN_SELCHANGE, IDC_EVENT_TAB, OnSelChangeEventTab)
	ON_NOTIFY(TCN_SELCHANGING, IDC_EVENT_TAB, OnSelChangingEventTab)
	ON_BN_CLICKED(IDC_EVENT_RENAME, OnBtnRename)
	ON_BN_CLICKED(IDC_EVENT_DELETE, OnBtnDelete)
	ON_BN_CLICKED(IDC_EVENT_NEW, OnBtnNew)
	ON_LBN_SELCHANGE(IDC_EVENT_LBOX_CATEGORY, OnSelChangeListCategory)
	ON_LBN_SELCHANGE(IDC_EVENT_LBOX_LABEL, OnSelChangeListLabel)
	ON_BN_CLICKED(IDC_EVENT_OK, OnBtnOK)
	ON_BN_CLICKED(IDC_EVENT_RESET, OnEventReset)
	//}}AFX_MSG_MAP
#ifdef _XTP_INCLUDE_CONTROLS
	ON_CPN_XTP_SELENDOK(IDC_EVENT_COLORPICKER, OnSelEndOkColor)
#endif
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCalendarEventColorDlg message handlers

BOOL CCalendarEventColorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// initialize tab and listbox controls.
	m_wndTabCtrl.InsertItem(0, _T("Categories"));
	m_wndTabCtrl.InsertItem(1, _T("Labels"));
	m_wndTabCtrl.SetCurSel(0);

	CRect rClient;
	m_wndTabCtrl.GetWindowRect(&rClient);
	m_wndTabCtrl.AdjustRect(FALSE, &rClient);

	rClient.top += ::GetSystemMetrics(SM_CYEDGE);
	ScreenToClient(&rClient);

	CXTPCalendarData* pData = XTP_SAFE_GET1(m_pCalendarCtrl, GetDataProvider(), NULL);
	if (pData)
	{
		m_lboxCategory.MoveWindow(&rClient);
		m_lboxCategory.Init(pData, m_pEvent, TRUE);

		m_lboxLabel.MoveWindow(&rClient);
		m_lboxLabel.Init(pData, m_pEvent, FALSE);
	}

	ShowSelListBox();

#ifdef _XTP_INCLUDE_CONTROLS
	m_cpEvent.ShowText(FALSE);
	m_cpEvent.ModifyCPStyle(0, CPS_XTP_SHOWEYEDROPPER);
#endif
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CCalendarEventColorDlg::IsCategory()
{
	ASSERT(::IsWindow(m_wndTabCtrl.m_hWnd));
	return (m_wndTabCtrl.GetCurSel() == 0);
}

void CCalendarEventColorDlg::ShowSelListBox()
{
	if (IsCategory())
	{
		m_lboxCategory.ShowWindow(SW_SHOW);
		m_wndEventInfo.SetWindowText(CXTPCalendarUtils::LoadString(IDS_CALENDAR_CATEGORYINFO));
	}
	else
	{
		m_lboxLabel.ShowWindow(SW_SHOW);
		m_wndEventInfo.SetWindowText(CXTPCalendarUtils::LoadString(IDS_CALENDAR_LABELINFO));
	}

	UpdateData(FALSE);
	UpdateSelColor();	
}

void CCalendarEventColorDlg::OnSelChangeEventTab(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	ShowSelListBox();
	*pResult = 0;
}

void CCalendarEventColorDlg::OnSelChangingEventTab(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
	m_lboxCategory.ShowWindow(SW_HIDE);
	m_lboxLabel.ShowWindow(SW_HIDE);
	
	*pResult = 0;
}

void CCalendarEventColorDlg::OnBtnRename() 
{
	if (IsCategory())
	{
		m_lboxCategory.BeginEdit();
	}
	else
	{
		m_lboxLabel.BeginEdit();
	}
}

void CCalendarEventColorDlg::OnBtnDelete() 
{
	if (IsCategory())
	{
		m_lboxCategory.DeleteItem();
	}
	else
	{
		m_lboxLabel.DeleteItem();
	}

	UpdateSelColor();
}

void CCalendarEventColorDlg::OnBtnNew() 
{
	int nIndex = IsCategory() ? m_lboxCategory.AddItem() : m_lboxLabel.AddItem();

	if (nIndex != LB_ERR)
	{
		UpdateSelColor(nIndex);
	}
}

void CCalendarEventColorDlg::UpdateSelColor(int nIndex /*=LB_ERR*/)
{
	if (nIndex == LB_ERR)
	{
		nIndex = IsCategory() ? m_lboxCategory.GetCurSel() : m_lboxLabel.GetCurSel();
	}

	if (IsCategory())
	{
		CXTPCalendarEventCategory* pCategory = m_lboxCategory.GetCategory(nIndex);

		if (!pCategory)
			return;

#ifdef _XTP_INCLUDE_CONTROLS
		m_cpEvent.SetColor(pCategory->GetBackgroundColor());
		m_cpEvent.SetDefaultColor(pCategory->GetBackgroundColor());
#endif

		m_lboxCategory.SetCurSel(nIndex);
	}
	else
	{
		CXTPCalendarEventLabel* pLabel = m_lboxLabel.GetLabel(nIndex);

		if (!pLabel)
			return;

#ifdef _XTP_INCLUDE_CONTROLS
		m_cpEvent.SetColor(pLabel->m_clrColor);
		m_cpEvent.SetDefaultColor(pLabel->m_clrColor);
#endif

		m_lboxLabel.SetCurSel(nIndex);
	}
}

void CCalendarEventColorDlg::OnSelChangeListCategory() 
{
	UpdateSelColor();	
}

void CCalendarEventColorDlg::OnSelChangeListLabel() 
{
	UpdateSelColor();	
}

void CCalendarEventColorDlg::OnSelEndOkColor()
{
#ifdef _XTP_INCLUDE_CONTROLS
	if (IsCategory())
	{
		m_lboxCategory.SetItemColor(m_cpEvent.GetColor());
	}
	else
	{
		m_lboxLabel.SetItemColor(m_cpEvent.GetColor());
	}
#endif
}

void CCalendarEventColorDlg::OnBtnOK() 
{
	if (!m_pCalendarCtrl)
		return;

	CXTPCalendarData* pData = XTP_SAFE_GET1(m_pCalendarCtrl, GetDataProvider(), NULL);
	ASSERT(pData);

	if (!pData)
		return;

	if (IsCategory())
	{
		m_lboxCategory.UpdateCategories(pData);
	}
	else
	{
		m_lboxLabel.UpdateLabels(pData);
	}

	CXTPCalendarControl::CUpdateContext updateContext(
		m_pCalendarCtrl, xtpCalendarUpdateLayout | xtpCalendarUpdateRedraw);
	
	VERIFY(pData->ChangeEvent(m_pEvent));

	CDialog::OnOK();
}

void CCalendarEventColorDlg::OnEventReset() 
{
	CXTPCalendarData* pData = XTP_SAFE_GET1(m_pCalendarCtrl, GetDataProvider(), NULL);
	ASSERT(pData);

	if (!pData)
		return;

	if (IsCategory())
	{
		if (AfxMessageBox(CXTPCalendarUtils::LoadString(XTP_IDS_CALENDAR_RESTORE_CATEGORYLIST), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			pData->RestoreEventCategoryList();

			XTP_SAFE_CALL2(m_pCalendarCtrl, GetPaintManager(), UpdateEventCategoriesDefaultColors());

			m_lboxCategory.Init(pData, m_pEvent, TRUE);
			UpdateSelColor(0);
		}
	}
	else
	{
		if (AfxMessageBox(CXTPCalendarUtils::LoadString(XTP_IDS_CALENDAR_RESTORE_LABELLIST), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			pData->RestoreEventLabelList();

			XTP_SAFE_CALL2(m_pCalendarCtrl, GetPaintManager(), UpdateEventLabelsDefaultColors());

			m_lboxLabel.Init(pData, m_pEvent, FALSE);
			UpdateSelColor(m_lboxLabel.GetCurSel());
		}
	}
}
