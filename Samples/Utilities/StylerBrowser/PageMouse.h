// PageMouse.h
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

#if !defined(AFX_PAGEMOUSE_H__34B20EF5_78A8_4E14_81AA_1214D5194CFF__INCLUDED_)
#define AFX_PAGEMOUSE_H__34B20EF5_78A8_4E14_81AA_1214D5194CFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OptionsPage.h"
#include <afxtempl.h>
//#include "KeyAssign.h"
/////////////////////////////////////////////////////////////////////////////
// CPageMouse dialog


class CPageMouse : public COptionsPage
{
	DECLARE_DYNCREATE(CPageMouse)

	class CComboBoxData : public CComboBox
	{
	public: 
		void AddStringData(CString str, DWORD dwData)
		{
			int nIndex = AddString(str);
			if (nIndex != CB_ERR)
				SetItemData(nIndex, dwData);
		}
	};

// Construction
public:
	void RefreshList();
	CPageMouse();
	~CPageMouse();

// Dialog Data
	//{{AFX_DATA(CPageMouse)
	enum { IDD = IDD_PAGE_MOUSE };
	CXTPShortcutManager::CKeyAssign	m_wndAssign;
	CListCtrl	m_wndCurrent;
	CComboBoxData	m_cmbMouse;
	CComboBoxData	m_cmbCommands;
	CComboBoxData	m_cmbArea;
	//}}AFX_DATA

protected:
	void GetMenuStrings(CXTPCommandBar* pBar, CString strPrefix);


	CMap< UINT, UINT, CString, CString& > m_mapCommands;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageMouse)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageMouse)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonRemove();
	afx_msg void OnButtonAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEMOUSE_H__34B20EF5_78A8_4E14_81AA_1214D5194CFF__INCLUDED_)
