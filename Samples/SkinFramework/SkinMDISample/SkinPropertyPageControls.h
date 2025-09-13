// SkinPropertyPageControls.h
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

#ifndef __SKINPROPERTYPAGECONTROLS_H__
#define __SKINPROPERTYPAGECONTROLS_H__

/////////////////////////////////////////////////////////////////////////////
// CSkinPropertyPageControls dialog

class CSkinPropertyPageControls : public CPropertyPage
{
	DECLARE_DYNCREATE(CSkinPropertyPageControls)

public:
	CSkinPropertyPageControls();
	virtual ~CSkinPropertyPageControls();

	//{{AFX_DATA(CSkinPropertyPageControls)
	enum { IDD = IDD_PROPPAGE_CONTROLS };
	CProgressCtrl	m_wndProgress;
	CSliderCtrl	m_wndSlider;
	CListBox	m_wndListBox;
	CComboBox	m_comboNormal;
	CComboBox	m_comboDisabled;
	CScrollBar	m_sbarNormal;
	CTreeCtrl	m_wndTreeCtrl;
	CListCtrl	m_wndListCtrl;
	CTabCtrl	m_wndTabControl;
	int		m_radioSelected;
	BOOL	m_bSelected;
	CString	m_csNormal;
	CString	m_csDisabled;
	CString	m_csSample;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CSkinPropertyPageControls)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CSkinPropertyPageControls)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // __SKINPROPERTYPAGECONTROLS_H__
