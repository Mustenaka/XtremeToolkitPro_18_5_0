// FilterDialog.h
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

// CFilterDialog dialog

class CFilterDialog : public CDialog
{
	DECLARE_DYNAMIC(CFilterDialog)

public:
	CFilterDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFilterDialog();

	CXTPEditListBox m_LBEditor;

// Dialog Data
	enum { IDD = IDD_DIALOG_FILTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	

	static void LoadFilterList();

	static CStringArray m_lstFilter;
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
public:
	void SaveFilterList(void);
};
