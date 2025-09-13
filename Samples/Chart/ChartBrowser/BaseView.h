// BaseView.h
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

#pragma once

class CResizeGroupBox : public CXTPButton
{
	DECLARE_DYNAMIC(CResizeGroupBox)
		
public:
	
	//-----------------------------------------------------------------------
	// Summary:
	//     Constructs a CXTPResizeGroupBox object
	//-----------------------------------------------------------------------
	CResizeGroupBox();
	
	//-----------------------------------------------------------------------
	// Summary:
	//     Destroys a CXTPResizeGroupBox object, handles cleanup and
	//     deallocation
	//-----------------------------------------------------------------------
	virtual ~CResizeGroupBox();
	
protected:
	//-----------------------------------------------------------------------
	// Summary:
	//     Called during paint operations to exclude the control windows
	//     that are grouped by this control.
	// Parameters:
	//     pDC      - Pointer to device context.
	//     rcClient - Client area of group box.
	//-----------------------------------------------------------------------
	virtual void Exclude(CDC* pDC, CRect& rcClient);

	
	
protected:
//{{AFX_CODEJOCK_PRIVATE
	DECLARE_MESSAGE_MAP()
		
	//{{AFX_VIRTUAL(CXTPResizeGroupBox)
	//}}AFX_VIRTUAL
		
	//{{AFX_MSG(CXTPResizeGroupBox)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
//}}AFX_CODEJOCK_PRIVATE
};



template <class TBase>
class CChartBorder : public TBase
{
public:
	CChartBorder()
	{
#ifdef _XTP_INCLUDE_DOCKINGPANE
		CXTPChartColor color;
		color.SetFromCOLORREF(0xDBDDE6);

		GetContent()->GetBorder()->SetColor(color);
#endif
	}

};

// CBaseView form view

class CBaseView : public CFormView
{
	DECLARE_DYNAMIC(CBaseView)

public:
	CBaseView(UINT nID, BOOL bTabbedOptions = FALSE);           // protected constructor used by dynamic creation
	virtual ~CBaseView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	virtual void OnInitialUpdate();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTabChanged(NMHDR *pNMHDR, LRESULT *pResult);

public:
	void AddTab(int nTab, CDialog* pTabDialog);
	void StretchTabSelection();
	void SetActiveTab(int nTab);

	CString m_strCaption;
	CBrush m_hBrush;

	CChartBorder<CXTPChartControl> m_wndChartControl;

	BOOL m_bTabbedOptions;
	CResizeGroupBox m_wndGroupBoxLabels;

	CTabCtrl m_wndTabControl;
	CDialog* m_pSelectedTabDlg;

	int m_nTopGap;
	int m_nLeftGap;
};

class C3dParametersDlg;

class CBase3dView  : public CBaseView
{
	DECLARE_DYNAMIC(CBase3dView)

public:
	CBase3dView(UINT nID);           // protected constructor used by dynamic creation
	virtual ~CBase3dView();

public:
	virtual void OnInitialUpdate();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

	C3dParametersDlg* m_p3dParametersDlg;
};

class CTabCtrlDialog : public CDialog
{
protected:
	CTabCtrlDialog(UINT nTemplateID, CWnd* pParent = NULL);

	virtual void OnOK() { }
	virtual void OnCancel() { }

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CBrush m_hBrush;
};
