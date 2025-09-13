// FrameShadowDlg.h
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

#if !defined(AFX_FrameShadowDLG_H__D149CDDD_5019_4FC8_9FFD_B7ADC600E278__INCLUDED_)
#define AFX_FrameShadowDLG_H__D149CDDD_5019_4FC8_9FFD_B7ADC600E278__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFrameShadowDlg dialog

class CFrameShadowDlg : public CDialog
{
// Construction
public:
	CFrameShadowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFrameShadowDlg)
	enum { IDD = IDD_FRAMESHADOW_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameShadowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual BOOL OnInitDialog();
	void SyncControls();
	void SetBorderless(BOOL bBorderless = TRUE, BOOL bUpdateCheckbox = FALSE);

	HICON m_hIcon;
	CSliderCtrl m_ctlOuterSize;
	CSliderCtrl m_ctlInnerSize;
	CSliderCtrl m_ctlAngle;
	CSliderCtrl m_ctlDistance;
	CSliderCtrl m_ctlRed;
	CSliderCtrl m_ctlGreen;
	CSliderCtrl m_ctlBlue;
	CSliderCtrl m_ctlTransparency;
	CSliderCtrl m_ctlCenterPos;
	CSliderCtrl m_ctlInnerIntensity;
	CSliderCtrl m_ctlCenterIntensity;
	CSliderCtrl m_ctlOuterIntensity;
	CButton m_ctlBorderless;
	CButton m_ctlSizeableToolWindows;
	CButton m_ctlFlagDisabled;
	CButton m_ctlFlagInvisible;
	CButton m_ctlFlagNotResizeable;
	CButton m_ctlFlagDisabledTss;
	CButton m_ctlFlagInvisibleTss;
	int m_nToolWndCounter;

	// Generated message map functions
	//{{AFX_MSG(CFrameShadowDlg)
	DECLARE_MESSAGE_MAP()
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedButtonAddToolWindow();
	afx_msg void OnBnClickedCheckBorderless();
	afx_msg void OnBnClickedSizeableToolWindows();
	afx_msg void OnBnClickedRadioSample2();
	afx_msg void OnBnClickedRadioSample1();
	afx_msg void OnBnClickedRadioSample3();
	afx_msg void OnBnClickedRadioSample4();
	afx_msg void OnBnClickedCheckFlags();
	//}}AFX_MSG
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FrameShadowDLG_H__D149CDDD_5019_4FC8_9FFD_B7ADC600E278__INCLUDED_)
