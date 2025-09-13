// BaseView.cpp
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
#include "ChartBrowser.h"
#include "BaseView.h"
#include "ComponentSliderCtrl.h"
#include "3dParametersDlg.h"

#ifdef _XTP_INCLUDE_CONTROLS
#define DLG_BACKGROUND_COLOR RGB(246, 246, 246)
#else
#define DLG_BACKGROUND_COLOR RGB(255, 255, 255)
#endif


/////////////////////////////////////////////////////////////////////////////
// CResizeGroupBox

CResizeGroupBox::CResizeGroupBox()
{
}

CResizeGroupBox::~CResizeGroupBox()
{
}

IMPLEMENT_DYNAMIC(CResizeGroupBox, CXTPButton)

BEGIN_MESSAGE_MAP(CResizeGroupBox, CXTPButton)
//{{AFX_MSG_MAP(CResizeGroupBox)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResizeGroupBox message handlers

void CResizeGroupBox::Exclude(CDC* pDC, CRect& rcClient)
{
	// get a pointer to the parent.
	CWnd* pWndParent = GetParent();
	if (!pWndParent)
		return;
	
	// get a pointer to the parents first child.
	CWnd* pWnd = pWndParent->GetWindow(GW_CHILD);
	if (pWnd == NULL)
		return;
	
	// iterate thru all children and exclude those children that
	// are located inside the group box.
	CWnd* pChildWnd = pWnd->GetWindow(GW_HWNDFIRST);
	while (pChildWnd != NULL)
	{
		// make sure we do not exclude ourself
		if (pChildWnd != this && pChildWnd->IsWindowVisible())
		{
			CRect rc;
			pChildWnd->GetWindowRect(&rc);
			ScreenToClient(&rc);
			
			// if the parent's child is located in our group box, exclude
			// it from painting.
			if (rcClient.PtInRect(rc.TopLeft()) ||
				rcClient.PtInRect(rc.BottomRight()))
			{
				pDC->ExcludeClipRect(&rc);
			}
		}
		
		pChildWnd = pChildWnd->GetWindow(GW_HWNDNEXT);
	}
}

BOOL CResizeGroupBox::OnEraseBkgnd(CDC* /*pDC*/)
{
	return TRUE;
}

void CResizeGroupBox::OnPaint()
{
	CPaintDC dc(this);
	
	// get the client area size.
	CRect rcClient;
	GetClientRect(&rcClient);
	
	// exclude controls that we "group"
	Exclude(&dc, rcClient);
	
	// Paint to a memory device context to help
	// eliminate screen flicker.
	CXTPBufferDC memDC(dc);
	
	HBRUSH hBrush = (HBRUSH)GetParent()->SendMessage(WM_CTLCOLORBTN, (WPARAM)memDC.GetSafeHdc(), (LRESULT)m_hWnd);
	if (hBrush)
	{
		::FillRect(memDC, rcClient, hBrush);
	}
	else
	{
		memDC.FillSolidRect(rcClient, GetSysColor(COLOR_3DFACE));
	}
	
#ifdef _XTP_INCLUDE_CONTROLS
	OnDraw(&memDC);
#else
	// Let the window do its default painting...
	CButton::DefWindowProc(WM_PAINT, (WPARAM)memDC.m_hDC, 0);
#endif
}

///////////////////////////////////////////////////////////////////////////////
// CBaseView

IMPLEMENT_DYNAMIC(CBaseView, CFormView)

CBaseView::CBaseView(UINT nID, BOOL bTabbedOptions /*= FALSE*/)
	: CFormView(nID)
	, m_pSelectedTabDlg(NULL)
	, m_bTabbedOptions(bTabbedOptions)
{
	m_hBrush.CreateSolidBrush(DLG_BACKGROUND_COLOR);
}

CBaseView::~CBaseView()
{
}

void CBaseView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	if (m_bTabbedOptions)
	{
		DDX_Control(pDX, IDC_TAB_CONTROLS, m_wndTabControl);
	}
	else
	{
		DDX_Control(pDX, IDC_STATIC_LABELS, m_wndGroupBoxLabels);
	}
}

BEGIN_MESSAGE_MAP(CBaseView, CFormView)
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROLS, OnTabChanged)
END_MESSAGE_MAP()


// CBaseView diagnostics

#ifdef _DEBUG
void CBaseView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBaseView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBaseView message handlers

BOOL CBaseView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CFormView::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return TRUE;
}

void CBaseView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	CRect rc;
	if (m_bTabbedOptions)
	{
		m_wndTabControl.GetWindowRect(&rc);
	}
	else
	{
		m_wndGroupBoxLabels.GetWindowRect(&rc);
	}

	ScreenToClient(&rc);
	m_nTopGap = rc.top;
	m_nLeftGap = rc.left;

#ifdef _XTP_INCLUDE_CONTROLS
	if (!m_bTabbedOptions)
	{
		m_wndGroupBoxLabels.SetTheme(xtpControlThemeVisualStudio2012Light);
	}
#endif
}

HBRUSH CBaseView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = m_hBrush;
	}

	return hbr;
}

void CBaseView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	int nWidth = max(m_totalDev.cx, cx);
	int nHeight = max(m_totalDev.cy, cy);

	CWnd* pControlPanel = (m_bTabbedOptions ? (CWnd*)&m_wndTabControl : (CWnd*)&m_wndGroupBoxLabels);
	if (NULL != pControlPanel->GetSafeHwnd())
	{
		CXTPWindowRect rc(*pControlPanel);
		ScreenToClient(&rc);
		pControlPanel->SetWindowPos(NULL, 0, 0, nWidth - 2 * m_nLeftGap, rc.Height(), SWP_NOMOVE | SWP_NOZORDER);

		if (m_bTabbedOptions)
		{
			StretchTabSelection();
		}
	}

	if (NULL != m_wndChartControl.GetSafeHwnd())
	{
		CXTPWindowRect rc(m_wndChartControl);
		ScreenToClient(&rc);
		m_wndChartControl.SetWindowPos(NULL, 0, 0, nWidth - 2 * m_nLeftGap, nHeight - m_nTopGap - rc.top, SWP_NOMOVE | SWP_NOZORDER);
	}
}

void CBaseView::AddTab(int nTab, CDialog* pTabDialog)
{
	ASSERT(m_bTabbedOptions);
	ASSERT_VALID(pTabDialog);

	CString strTitle;
	pTabDialog->GetWindowText(strTitle);

	TCITEM item;
	item.mask = TCIF_TEXT | TCIF_PARAM;
	item.pszText = const_cast<LPTSTR>(strTitle.operator LPCTSTR());
	item.lParam = reinterpret_cast<LPARAM>(pTabDialog);
	LONG nIndex = m_wndTabControl.InsertItem(nTab, &item);
}

void CBaseView::StretchTabSelection()
{
	ASSERT(m_bTabbedOptions);

	int nItem = m_wndTabControl.GetCurSel();
	if (-1 != nItem)
	{
		CRect rcItem;
		m_wndTabControl.GetItemRect(nItem, &rcItem);

		CRect rcTab;
		m_wndTabControl.GetClientRect(&rcTab);
		m_wndTabControl.AdjustRect(FALSE, &rcTab);

		m_pSelectedTabDlg->SetWindowPos(NULL, rcTab.left, rcTab.top,
			rcTab.Width(), rcTab.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
	}
}

void CBaseView::SetActiveTab(int nTab)
{
	ASSERT(m_bTabbedOptions);

	m_wndTabControl.SetCurSel(nTab);
	OnTabChanged(NULL, NULL);
}

void CBaseView::OnTabChanged(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/)
{
	ASSERT(m_bTabbedOptions);

	int nItem = m_wndTabControl.GetCurSel();

	TCITEM item;
	item.mask = TCIF_PARAM;
	if (m_wndTabControl.GetItem(nItem, &item))
	{
		if (NULL != m_pSelectedTabDlg)
		{
			m_pSelectedTabDlg->ShowWindow(SW_HIDE);
		}

		m_pSelectedTabDlg = reinterpret_cast<CDialog*>(item.lParam);
		ASSERT_VALID(m_pSelectedTabDlg);

		StretchTabSelection();
	}
}


///////////////////////////////////////////////////////////////////////////////
// CBase3dView

IMPLEMENT_DYNAMIC(CBase3dView, CBaseView);

BEGIN_MESSAGE_MAP(CBase3dView, CBaseView)
END_MESSAGE_MAP()

CBase3dView::CBase3dView(UINT nID)
	: CBaseView(nID, TRUE)
	, m_p3dParametersDlg(NULL)
{
}

CBase3dView::~CBase3dView()
{
	SAFE_DELETE(m_p3dParametersDlg);
}

void CBase3dView::DoDataExchange(CDataExchange* pDX)
{
	CBaseView::DoDataExchange(pDX);
}

void CBase3dView::OnInitialUpdate()
{
	CBaseView::OnInitialUpdate();

	m_p3dParametersDlg = new C3dParametersDlg(m_wndChartControl, &m_wndTabControl);
	if (m_p3dParametersDlg->Create(C3dParametersDlg::IDD, &m_wndTabControl))
	{
		m_p3dParametersDlg->SetWindowText(_T("3D Parameters"));
		AddTab(0, m_p3dParametersDlg);

		m_pSelectedTabDlg = m_p3dParametersDlg;
		SetActiveTab(0);
	}
	else
	{
		TRACE(_T("Unable to create C3dParametersDlg.\n"));
	}
}

///////////////////////////////////////////////////////////////////////////////
// CTabCtrlDialog

CTabCtrlDialog::CTabCtrlDialog(UINT nTemplateID, CWnd* pParent /*= NULL*/)
	: CDialog(nTemplateID, pParent)
{
	m_hBrush.CreateSolidBrush(DLG_BACKGROUND_COLOR);
}

BEGIN_MESSAGE_MAP(CTabCtrlDialog, CDialog)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

HBRUSH CTabCtrlDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog ::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_DLG || nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN)
	{
		pDC->SetBkMode(TRANSPARENT);
		hbr = m_hBrush;
	}

	return hbr;
}
