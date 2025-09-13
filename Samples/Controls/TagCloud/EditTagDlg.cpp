// EditTagDlg.cpp : implementation file
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
#include "EditTagDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditTagDlg dialog


CEditTagDlg::CEditTagDlg(COLORREF clrBack, COLORREF clrBorder, LPCTSTR lpszTitle, XTP_TAGCLOUDTAG* pSelTag, CWnd* pParent /*=NULL*/)
	: CDialog(CEditTagDlg::IDD, pParent)
	, m_clrBack(clrBack)
	, m_clrBorder(clrBorder)
	, m_strTitle(lpszTitle)
{
	//{{AFX_DATA_INIT(CEditTagDlg)
	m_nIndex = 0;
	m_strTagName = _T("");
	//}}AFX_DATA_INIT

	if (pSelTag)
	{
		CXTPTagCloudStyle* pStyle = XTPTabCloudStyleManager()->GetStyle(pSelTag->nScore);
		ASSERT(pStyle != NULL);
		
		if (pStyle)
		{
			m_tagStyle = *pStyle;
			m_strTagName = pSelTag->strItem;
			m_nIndex = pSelTag->nScore-1;
		}
	}
	else
	{
		CXTPTagCloudStyleArray& arrStyles = XTPTabCloudStyleManager()->GetCloudStyleArray();
		ASSERT(arrStyles.GetSize() != 0);
		m_tagStyle = *arrStyles[m_nIndex];
	}
}


void CEditTagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditTagDlg)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDC_COMBO_SCORE, m_wndComboScore);
	DDX_Control(pDX, IDC_STATIC_NORMAL, m_wndNormal);
	DDX_Control(pDX, IDC_STATIC_HIGHLIGHT, m_wndHighlight);
	DDX_Text(pDX, IDC_STATIC_FONT, m_strFont);
	DDX_CBIndex(pDX, IDC_COMBO_SCORE, m_nIndex);
	DDX_Text(pDX, IDC_EDIT_TAG, m_strTagName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditTagDlg, CDialog)
	//{{AFX_MSG_MAP(CEditTagDlg)
	ON_CBN_SELENDOK(IDC_COMBO_SCORE, OnSelEndOkComboScore)
	ON_EN_CHANGE(IDC_EDIT_TAG, OnChangeEditTag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditTagDlg message handlers

BOOL CEditTagDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// set the default font for all dialog controls.
	SendMessageToDescendants(WM_SETFONT,
		(WPARAM)(HFONT)XTPFontManager()->GetFont());
	
	CXTPTagCloudStyleArray& arrStyles = XTPTabCloudStyleManager()->GetCloudStyleArray();

	for (int i = 0; i < arrStyles.GetSize(); ++i)
	{
		CString strBuffer;
		strBuffer.Format(_T("%d"), arrStyles[i]->m_nScore);

		m_wndComboScore.SetItemData(m_wndComboScore.AddString(strBuffer),
			(DWORD)arrStyles[i]->m_nScore);
	}

	SetWindowText(m_strTitle);
	UpdateControls();
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditTagDlg::UpdateControls()
{
	m_wndNormal.SetFont(&m_tagStyle.m_xtpFont);
	m_wndHighlight.SetFont(&m_tagStyle.m_xtpFont);

	m_wndNormal.SetStyle(m_clrBack,
		m_tagStyle.m_clrText, m_clrBorder);

	m_wndHighlight.SetStyle(m_clrBack,
		m_tagStyle.m_clrTextHover, m_clrBorder);

	LOGFONT lf;
	m_tagStyle.m_xtpFont.GetLogFont(&lf);

	CClientDC dc(this);
	m_strFont.Format(_T("%s - %d pt"),
		lf.lfFaceName, ::MulDiv(-lf.lfHeight, 72, dc.GetDeviceCaps(LOGPIXELSY)));
}

void CEditTagDlg::OnSelEndOkComboScore() 
{
	UpdateData();

	int nScore = (int)m_wndComboScore.GetItemData(m_nIndex);
	CXTPTagCloudStyle* pTagStyle = XTPTabCloudStyleManager()->GetStyle(nScore);

	if (pTagStyle)
	{
		m_tagStyle = *pTagStyle;
		UpdateControls();
		UpdateData(FALSE);

		m_btnOk.EnableWindow(!m_strTagName.IsEmpty());
	}
}

void CEditTagDlg::OnChangeEditTag() 
{
	UpdateData();
	m_btnOk.EnableWindow(!m_strTagName.IsEmpty());
}
