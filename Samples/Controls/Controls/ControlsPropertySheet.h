// ControlsPropertySheet.h : header file
//

#if !defined(AFX_CONTROLSPROPERTYSHEET_H__C1B20BC5_C6ED_474B_BED0_42ACF8C06513__INCLUDED_)
#define AFX_CONTROLSPROPERTYSHEET_H__C1B20BC5_C6ED_474B_BED0_42ACF8C06513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CControlsPropertySheet

class CControlsPropertySheet : public CXTPResizePropertySheet
{
public:
	CControlsPropertySheet();
	CControlsPropertySheet(const UINT nCaption, CWnd* pParent = 0, const UINT nSelectPage = 0, const UINT nFlags = 0);
	CControlsPropertySheet(LPCTSTR pszCaption, CWnd* pParent = 0, const UINT nSelectPage = 0, const UINT nFlags = 0);

	DECLARE_DYNAMIC(CControlsPropertySheet)
	//{{AFX_VIRTUAL(CControlsPropertySheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

protected:
	CStatic m_txtTheme;
	CComboBox m_comboTheme;

	//{{AFX_MSG(CControlsPropertySheet)
	afx_msg void OnSelChangeTheme();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLSPROPERTYSHEET_H__C1B20BC5_C6ED_474B_BED0_42ACF8C06513__INCLUDED_)
