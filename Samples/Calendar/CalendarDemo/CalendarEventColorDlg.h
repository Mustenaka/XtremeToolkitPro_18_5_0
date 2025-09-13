// CalendarEventColorDlg.h : header file
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

#if !defined(__CALENDAREVENTCOLORDLG_H__)
#define __CALENDAREVENTCOLORDLG_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//===========================================================================
// Summary: This class is used to edit Calendar Event Category and Label 
//          information.
//===========================================================================
class CCalendarEventColorDlg : public CDialog
{
public:
	// ------------------------------------------------------------------
	// Summary:    Constructs a CXTPCalendarEventColorDlg object used to
	//             edit calendar event categories and labels.
	// Parameters: pCalendarCtrl : Points to a valid CXTPCalendarControl
	//                             object.
	//             pParent       : A pointer to the dialog box’s parent 
	//                             or owner window.
	// ------------------------------------------------------------------
	CCalendarEventColorDlg(CXTPCalendarControl* pCalendarCtrl, CWnd* pParent = NULL);

protected:
	// ------------------------------------------------------------------
	// Summary:    This member function is called to update the diplayed
	//             color for the color picker whenever a listbox 
	//             selection changes.
	// Parameters: nIndex : Index of the listbox item to retrieve color
	//                      information from.  If LB_ERR, the currently
	//                      selected item is used.
	// ------------------------------------------------------------------
	void UpdateSelColor(int nIndex = LB_ERR);

	// ------------------------------------------------------------------
	// Summary: This member function is called to display the currently
	//          selected color list box.
	// ------------------------------------------------------------------
	void ShowSelListBox();

	// ------------------------------------------------------------------
	// Summary: This member funciton is called to determine if the 
	//          Category tab is currently selected.
	// Returns: TRUE if the Category tab is selected, otherwise FALSE.
	// ------------------------------------------------------------------
	BOOL IsCategory();

	CXTPCalendarControl* m_pCalendarCtrl; // Pointer to the calendar object.
	CXTPCalendarEventPtr m_pEvent;        // Pointer to the calendar event object.

	//{{AFX_DATA(CCalendarEventColorDlg)
	enum { IDD = IDD_CALENDAR_EVENT_COLOR };
	CStatic	m_wndEventInfo;
#ifdef _XTP_INCLUDE_CONTROLS
	CXTPColorPicker	m_cpEvent;
#endif
	CXTPCalendarEventColorListBox	m_lboxCategory;
	CXTPCalendarEventColorListBox	m_lboxLabel;
	CTabCtrl	m_wndTabCtrl;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CCalendarEventColorDlg)
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCalendarEventColorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelChangeEventTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelChangingEventTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnRename();
	afx_msg void OnBtnDelete();
	afx_msg void OnBtnNew();
	afx_msg void OnSelChangeListCategory();
	afx_msg void OnSelChangeListLabel();
	afx_msg void OnBtnOK();
	afx_msg void OnEventReset();
	//}}AFX_MSG
	afx_msg void OnSelEndOkColor();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__CALENDAREVENTCOLORDLG_H__)
