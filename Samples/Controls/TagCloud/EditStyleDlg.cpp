// EditStyleDlg.cpp : implementation file
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
#include "EditStyleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreviewText

CPreviewText::CPreviewText()
{
	SetStyle(::GetSysColor(COLOR_WINDOW), ::GetSysColor(COLOR_WINDOWTEXT), ::GetSysColor(COLOR_WINDOWTEXT));
}

BEGIN_MESSAGE_MAP(CPreviewText, CStatic)
	//{{AFX_MSG_MAP(CPreviewText)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_NCPAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

HBRUSH CPreviewText::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(m_clrText);
	return m_brBack;
}

void CPreviewText::OnNcPaint() 
{
	CXTPWindowRect rc(this);

	CWindowDC dc(this);
	dc.Draw3dRect(0, 0, rc.Width(), rc.Height(),
		m_clrBorder, m_clrBorder);
}

void CPreviewText::SetStyle(COLORREF clrBack, COLORREF clrText, COLORREF clrBorder)
{
	m_clrBack   = clrBack;
	m_clrText   = clrText;
	m_clrBorder = clrBorder;

	if (m_brBack.GetSafeHandle())
		m_brBack.DeleteObject();

	m_brBack.CreateSolidBrush(m_clrBack);

	if (::IsWindow(m_hWnd))
	{
		RedrawWindow();
		SetWindowPos(NULL, 0,0,0,0,
			SWP_NOMOVE|SWP_NOSIZE|SWP_FRAMECHANGED);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEditStyleDlg dialog

CEditStyleDlg::CEditStyleDlg(COLORREF clrBack, COLORREF clrBorder, LPCTSTR lpszTitle, CXTPTagCloudStyle* pTagStyle, CWnd* pParent /*=NULL*/)
	: CDialog(CEditStyleDlg::IDD, pParent)
	, m_clrBack(clrBack)
	, m_clrBorder(clrBorder)
{
	//{{AFX_DATA_INIT(CEditStyleDlg)
	m_strFont = _T("");
	//}}AFX_DATA_INIT

	// initialize the CXTPTagCloudStyle class.
	m_tagStyle = *pTagStyle;

	// format the dialog title.
	m_strTitle.Format(_T("%s ( Score: %d )"), lpszTitle, m_tagStyle.m_nScore);
}

CEditStyleDlg::CEditStyleDlg(COLORREF clrBack, COLORREF clrBorder, LPCTSTR lpszTitle, int nScore, CWnd* pParent /*=NULL*/)
	: CDialog(CEditStyleDlg::IDD, pParent)
	, m_clrBack(clrBack)
	, m_clrBorder(clrBorder)
{
	CXTPNonClientMetrics ncm;
	ncm.lfMenuFont.lfCharSet = XTPResourceManager()->GetFontCharset();

	if (XTPSystemVersion()->IsClearTypeTextQualitySupported())
	{
		ncm.lfMenuFont.lfQuality = CLEARTYPE_QUALITY;
	}
	
	CWindowDC dc(NULL);
	ncm.lfMenuFont.lfHeight = -::MulDiv(9, dc.GetDeviceCaps(LOGPIXELSY), 72);

	// initialize the CXTPTagCloudStyle class.
	m_tagStyle.m_nScore       = nScore;
	m_tagStyle.m_clrText      = RGB(66,66,66);
	m_tagStyle.m_clrTextHover = RGB(255,152,29);
	m_tagStyle.m_clrBorder    = COLORREF_NULL;
	m_tagStyle.SetFont(ncm.lfMenuFont);
	
	// format the dialog title.
	m_strTitle.Format(_T("%s ( Score: %d )"), lpszTitle, m_tagStyle.m_nScore);
}

void CEditStyleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditStyleDlg)
	DDX_Control(pDX, IDC_BTN_NORMAL, m_cpNormal);
	DDX_Control(pDX, IDC_BTN_HILIGHT, m_cpHilight);
	DDX_Control(pDX, IDC_BTN_BORDER, m_cpBorder);
	DDX_Control(pDX, IDC_STATIC_NORMAL, m_wndNormal);
	DDX_Control(pDX, IDC_STATIC_HIGHLIGHT, m_wndHighlight);
	DDX_Text(pDX, IDC_STATIC_FONT, m_strFont);
	//}}AFX_DATA_MAP
	DDX_XTPColorPicker(pDX, IDC_BTN_NORMAL,  m_tagStyle.m_clrText);
	DDX_XTPColorPicker(pDX, IDC_BTN_HILIGHT, m_tagStyle.m_clrTextHover);
	DDX_XTPColorPicker(pDX, IDC_BTN_BORDER,  m_tagStyle.m_clrBorder);
}

BEGIN_MESSAGE_MAP(CEditStyleDlg, CDialog)
	//{{AFX_MSG_MAP(CEditStyleDlg)
	ON_BN_CLICKED(IDC_BTN_FONT, OnBtnFont)
	//}}AFX_MSG_MAP
	ON_CPN_XTP_SELENDOK(IDC_BTN_NORMAL,  OnColorSelEndOkNormal)
	ON_CPN_XTP_SELENDOK(IDC_BTN_HILIGHT, OnColorSelEndOkHilight)
	ON_CPN_XTP_SELENDOK(IDC_BTN_BORDER,  OnColorSelEndOkBorder)
	ON_CPN_XTP_SELNOFILL(IDC_BTN_BORDER,  OnColorSelEndOkBorder)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditStyleDlg message handlers

BOOL CEditStyleDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// set the default font for all dialog controls.
	SendMessageToDescendants(WM_SETFONT,
		(WPARAM)(HFONT)XTPFontManager()->GetFont());
	
	SetWindowText(m_strTitle);

	m_wndNormal.SetFont(&m_tagStyle.m_xtpFont);
	m_wndHighlight.SetFont(&m_tagStyle.m_xtpFont);

	m_wndNormal.SetStyle(m_clrBack,
		m_tagStyle.m_clrText, m_clrBorder);

	m_wndHighlight.SetStyle(m_clrBack,
		m_tagStyle.m_clrTextHover, m_clrBorder);

	m_cpBorder.ShowText(
		m_tagStyle.m_clrBorder == COLORREF_NULL);

	theApp.InitColorPicker(m_cpNormal, ::GetSysColor(COLOR_WINDOWTEXT));
	theApp.InitColorPicker(m_cpHilight, ::GetSysColor(COLOR_WINDOWTEXT));
	theApp.InitColorPicker(m_cpBorder, COLORREF_NULL);
	
	m_cpBorder.ModifyCPStyle(0, CPS_XTP_NOFILL);

	LOGFONT lf;
	m_tagStyle.m_xtpFont.GetLogFont(&lf);

	// format the font size string.
	CClientDC dc(this);
	m_strFont.Format(_T("%s - %d pt"), lf.lfFaceName,
		::MulDiv(-lf.lfHeight, 72, dc.GetDeviceCaps(LOGPIXELSY)));

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditStyleDlg::OnBtnFont() 
{
	LOGFONT lf;
	m_tagStyle.m_xtpFont.GetLogFont(&lf);
	CFontDialog dlg(&lf, CF_SCREENFONTS, NULL, this);
	
	if (dlg.DoModal() == IDOK)
	{
		m_tagStyle.SetFont(dlg.m_lf);
		m_wndNormal.SetFont(&m_tagStyle.m_xtpFont);
		m_wndHighlight.SetFont(&m_tagStyle.m_xtpFont);

		CClientDC dc(this);

		m_strFont.Format(_T("%s - %d pt"),
			dlg.m_lf.lfFaceName, ::MulDiv(-dlg.m_lf.lfHeight, 72, dc.GetDeviceCaps(LOGPIXELSY)));

		UpdateData(FALSE);
	}
}

void CEditStyleDlg::OnColorSelEndOkNormal()
{
	UpdateData();

	m_wndNormal.SetStyle(m_clrBack,
		m_tagStyle.m_clrText, m_tagStyle.m_clrBorder);
}

void CEditStyleDlg::OnColorSelEndOkHilight()
{
	UpdateData();

	m_wndHighlight.SetStyle(m_clrBack,
		m_tagStyle.m_clrTextHover, m_tagStyle.m_clrBorder);
}

void CEditStyleDlg::OnColorSelEndOkBorder()
{
	UpdateData();

	if (m_tagStyle.m_clrBorder == COLORREF_NULL ||
		m_tagStyle.m_clrBorder == m_clrBack)
	{
		m_tagStyle.m_clrBorder = COLORREF_NULL;
		UpdateData(FALSE);
	}

	m_cpBorder.ShowText(
		m_tagStyle.m_clrBorder == COLORREF_NULL);

	m_wndNormal.SetStyle(m_clrBack,
		m_tagStyle.m_clrText, m_tagStyle.m_clrBorder);

	m_wndHighlight.SetStyle(m_clrBack,
		m_tagStyle.m_clrTextHover, m_tagStyle.m_clrBorder);
}
