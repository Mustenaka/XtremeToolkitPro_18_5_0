// ComponentSliderCtrl.h
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

#if !defined(AFX_COMPONENTSLIDERCTRL_H__EE643C26_453B_4FDF_9DC6_4AD6597C845D__INCLUDED_)
#define AFX_COMPONENTSLIDERCTRL_H__EE643C26_453B_4FDF_9DC6_4AD6597C845D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct IComponentSliderCtrlCallback
{
	virtual void OnBeforeValueChanged(int nItem)
	{
		UNREFERENCED_PARAMETER(nItem);
	}

	virtual void OnValueChanged(int nItem, int nValue)
	{
		UNREFERENCED_PARAMETER(nItem);
		UNREFERENCED_PARAMETER(nValue);
	}

	virtual void OnValueChanged(int nItem, float nValue)
	{
		UNREFERENCED_PARAMETER(nItem);
		UNREFERENCED_PARAMETER(nValue);
	}

	virtual void OnAfterValueChanged(int nItem)
	{
		UNREFERENCED_PARAMETER(nItem);
	}
};

/////////////////////////////////////////////////////////////////////////////
// CComponentSliderCtrl dialog

class CComponentSliderCtrl : public CTabCtrlDialog
{
// Construction
public:
	CComponentSliderCtrl(IComponentSliderCtrlCallback& callback, CWnd* pParent = NULL);   // standard constructor

public:
	BOOL Create(CWnd* pParent, CRect rc);
	int AddValue(LPCTSTR lpName, int nFrom, int nTo, int nCurrent, LPCTSTR lpFormat = NULL);
	int AddValue(LPCTSTR lpName, float nFrom, float nTo, float nCurrent, LPCTSTR lpFormat = NULL);
	void SetValue(int nItem, int nValue);
	void SetValue(int nItem, float fValue);

// Dialog Data
	//{{AFX_DATA(CComponentSliderCtrl)
	enum { IDD = IDD_COMPONENT_SLIDER };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComponentSliderCtrl)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	virtual void OnOK() { }
	virtual void OnCancel() { }
	//}}AFX_VIRTUAL

	struct ValueInfo;

	void SetActiveValue(int nItem);
	int ValueToSliderPos(const ValueInfo& value);
	void SliderPosToValue(int nPos, ValueInfo& value);
	CString GetValueString(const ValueInfo& value) const;

// Implementation
protected:


	CComboBox m_wndValueList;
	CSliderCtrl m_wndSlider;
	CEdit m_wndValue;
	IComponentSliderCtrlCallback& m_callback;
	BOOL m_bBeingDragged;

	// Generated message map functions
	//{{AFX_MSG(CComponentSliderCtrl)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnValueSelected();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPONENTSLIDERCTRL_H__EE643C26_453B_4FDF_9DC6_4AD6597C845D__INCLUDED_)
