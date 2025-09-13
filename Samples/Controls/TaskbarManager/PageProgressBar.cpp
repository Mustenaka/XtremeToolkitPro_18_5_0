// PageProgressBar.cpp
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
#include "TaskbarManager.h"
#include "PageProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageProgressBar property page

IMPLEMENT_DYNCREATE(CPageProgressBar, CPropertyPage)

CPageProgressBar::CPageProgressBar() : CPropertyPage(CPageProgressBar::IDD)
{
	//{{AFX_DATA_INIT(CPageProgressBar)
	m_nStatus = 0;
	m_nValue = 0;
	//}}AFX_DATA_INIT
}

CPageProgressBar::~CPageProgressBar()
{
}

void CPageProgressBar::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageProgressBar)
	DDX_CBIndex(pDX, IDC_COMBO_STATUS, m_nStatus);
	DDX_Slider(pDX, IDC_SLIDER_PROGRESS, m_nValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageProgressBar, CPropertyPage)
	//{{AFX_MSG_MAP(CPageProgressBar)
	ON_CBN_SELCHANGE(IDC_COMBO_STATUS, OnSelChangeComboStatus)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_PROGRESS, OnReleasedCaptureSliderProgress)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int nProgressData[] = 
{
	xtpProgressFlagNormal,
	xtpProgressFlagError,
	xtpProgressFlagPaused,
	xtpProgressFlagIndeterminate,
	xtpProgressFlagNoProgress
};

/////////////////////////////////////////////////////////////////////////////
// CPageProgressBar message handlers

void CPageProgressBar::OnSelChangeComboStatus() 
{
	UpdateData();

	m_mgrTaskBar.SetProgressBarState(AfxGetMainWnd()->GetSafeHwnd(), nProgressData[m_nStatus]);

	GetDlgItem(IDC_SLIDER_PROGRESS)->EnableWindow(m_nStatus < 3);
	
}

void CPageProgressBar::OnReleasedCaptureSliderProgress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();

	m_mgrTaskBar.SetProgressBarPosition(AfxGetMainWnd()->GetSafeHwnd(), m_nValue);
	
	*pResult = 0;
}
