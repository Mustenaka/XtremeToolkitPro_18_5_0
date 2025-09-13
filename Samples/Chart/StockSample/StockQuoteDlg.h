// StockQuoteDlg.h
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

#if !defined(AFX_STOCKQUOTEDLG_H__1D7C2A48_6FCE_40BE_AD59_D164C56C3773__INCLUDED_)
#define AFX_STOCKQUOTEDLG_H__1D7C2A48_6FCE_40BE_AD59_D164C56C3773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStockSampleView;

/////////////////////////////////////////////////////////////////////////////
// CStockQuoteDlg dialog

class CStockQuoteDlg : public CDialog
{
// Construction
public:
	CStockQuoteDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStockQuoteDlg)
	enum { IDD = IDD_STOCKQUOTE };
	CStatic	m_txtLow;
	CStatic	m_txtHigh;
	CStatic	m_txtClose;
	CStatic	m_txtDate;
	CStatic	m_txtVolume;
	CStatic	m_txtOpen;
	CStatic	m_txtCompany;
	CString	m_strCompany;
	CString	m_strOpen;
	CString	m_strPrevClose;
	CString	m_strVolume;
	CString	m_strDate;
	CString	m_strClose;
	CString	m_strHigh;
	CString	m_strLow;
	CString	m_strTicker;
	int		m_nStyle;
	CString	m_strSector;
	CString	m_strIndustry;
	BOOL	m_bThickLines;
	//}}AFX_DATA

	CFont m_fontBold;
	COLORREF m_crRed;
	COLORREF m_crGreen;
	CStockSampleView* m_pChart;

	BOOL Create(UINT nIDTemplate, CStockSampleView* pParentWnd);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStockQuoteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString FormatNumber(LONGLONG ulNumber);

	// Generated message map functions
	//{{AFX_MSG(CStockQuoteDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnGetQuote();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelendOkComboStyle();
	afx_msg void OnChkThickLines();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STOCKQUOTEDLG_H__1D7C2A48_6FCE_40BE_AD59_D164C56C3773__INCLUDED_)
