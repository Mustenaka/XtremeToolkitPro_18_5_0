// EditTagCloudDlg.cpp : implementation file
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
#include "tagcloud.h"
#include "EditTagCloudDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditTagCloudDlg dialog

CEditTagCloudDlg::CEditTagCloudDlg(CXTPTagCloudCtrl& wndTagCloud, CWnd* pParent /*=NULL*/)
	: CDialog(CEditTagCloudDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditTagCloudDlg)
	m_nStyle = -1;
	m_nMargin = -1;
	m_nPadding = -1;
	//}}AFX_DATA_INIT

	m_clrDark = wndTagCloud.GetBackColor().clrDark;
	m_clrLight = wndTagCloud.GetBackColor().clrLight;
	m_clrBorder = wndTagCloud.GetBorderColor();

	m_nStyle = (m_clrDark == m_clrLight) ? 0 : wndTagCloud.IsFillHorz() ? 2 : 1;
	m_nMargin = wndTagCloud.GetMargin();
	m_nPadding = wndTagCloud.GetPadding();
}

void CEditTagCloudDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditTagCloudDlg)
	DDX_Control(pDX, IDC_COMBO_PADDING, m_wndComboPadding);
	DDX_Control(pDX, IDC_COMBO_MARGIN, m_wndComboMargin);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_wndComboStyle);
	DDX_Control(pDX, IDC_STATIC_DARK, m_txtDark);
	DDX_Control(pDX, IDC_BTN_DARK, m_cpDark);
	DDX_Control(pDX, IDC_BTN_LIGHT, m_cpLight);
	DDX_Control(pDX, IDC_BTN_BORDER, m_cpBorder);
	DDX_CBIndex(pDX, IDC_COMBO_STYLE, m_nStyle);
	DDX_CBIndex(pDX, IDC_COMBO_MARGIN, m_nMargin);
	DDX_CBIndex(pDX, IDC_COMBO_PADDING, m_nPadding);
	//}}AFX_DATA_MAP
	DDX_XTPColorPicker(pDX, IDC_BTN_DARK,  m_clrDark);
	DDX_XTPColorPicker(pDX, IDC_BTN_LIGHT, m_clrLight);
	DDX_XTPColorPicker(pDX, IDC_BTN_BORDER,  m_clrBorder);
}

BEGIN_MESSAGE_MAP(CEditTagCloudDlg, CDialog)
	//{{AFX_MSG_MAP(CEditTagCloudDlg)
	ON_CBN_SELENDOK(IDC_COMBO_STYLE, OnSelEndOkComboStyle)
	ON_CBN_SELENDOK(IDC_COMBO_MARGIN, OnSelEndOk)
	ON_CBN_SELENDOK(IDC_COMBO_PADDING, OnSelEndOk)
	//}}AFX_MSG_MAP
	ON_CPN_XTP_SELENDOK(IDC_BTN_DARK,  OnSelEndOkBackDark)
	ON_CPN_XTP_SELENDOK(IDC_BTN_LIGHT, OnSelEndOkBackLight)
	ON_CPN_XTP_SELENDOK(IDC_BTN_BORDER,  OnSelEndOkBorder)
	ON_CPN_XTP_SELNOFILL(IDC_BTN_BORDER,  OnSelEndOkBorder)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditTagCloudDlg message handlers

BOOL CEditTagCloudDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// set the default font for all dialog controls.
	SendMessageToDescendants(WM_SETFONT,
		(WPARAM)(HFONT)XTPFontManager()->GetFont());
	
	m_wndComboStyle.AddString(_T("Solid"));
	m_wndComboStyle.AddString(_T("Gradient Vertical"));
	m_wndComboStyle.AddString(_T("Gradient Horizontal"));

	CClientDC dc(this);
	CXTPFontDC fontDC(&dc, m_wndComboStyle.GetFont());
	int nWidth = dc.GetTextExtent(_T("Gradient Horizontal")).cx + ::GetSystemMetrics(SM_CXVSCROLL) + 2*::GetSystemMetrics(SM_CXEDGE);
	m_wndComboStyle.SetDroppedWidth(nWidth);

	for (int i = 0; i < 10; i++)
	{
		CString strBuffer;
		strBuffer.Format(_T("%d"), i);
		m_wndComboPadding.AddString(strBuffer);
		m_wndComboMargin.AddString(strBuffer);
	}

	m_cpDark.EnableWindow(m_nStyle != 0);
	m_txtDark.EnableWindow(m_nStyle != 0);
	m_cpBorder.ShowText(m_clrBorder == COLORREF_NULL);

	theApp.InitColorPicker(m_cpDark, ::GetSysColor(COLOR_WINDOW));
	theApp.InitColorPicker(m_cpLight, ::GetSysColor(COLOR_WINDOW));
	theApp.InitColorPicker(m_cpBorder, COLORREF_NULL);

	m_cpBorder.ModifyCPStyle(0, CPS_XTP_NOFILL);

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditTagCloudDlg::OnSelEndOk()
{
	UpdateData();
}

void CEditTagCloudDlg::OnSelEndOkBackLight()
{
	if (m_cpLight.GetColor() == COLORREF_NULL)
	{
		AfxMessageBox(_T("Background colors cannot be set to NULL"));
		UpdateData(FALSE);
	}
	else
	{
		UpdateData();
	}
}

void CEditTagCloudDlg::OnSelEndOkBackDark()
{
	if (m_cpDark.GetColor() == COLORREF_NULL)
	{
		AfxMessageBox(_T("Background colors cannot be set to NULL"));
		UpdateData(FALSE);
	}
	else
	{
		UpdateData();
	}
}

void CEditTagCloudDlg::OnSelEndOkBorder()
{
	UpdateData();
	m_cpBorder.ShowText(m_clrBorder == COLORREF_NULL);
}

void CEditTagCloudDlg::OnSelEndOkComboStyle() 
{
	UpdateData();
	m_cpDark.EnableWindow(m_nStyle != 0);
	m_txtDark.EnableWindow(m_nStyle != 0);
}
