// ComboBoxSearch.h
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

#if !defined(AFX_COMBOBOXSEARCH_H__342A6E15_31D3_489A_A841_11E6DC0A069E__INCLUDED_)
#define AFX_COMBOBOXSEARCH_H__342A6E15_31D3_489A_A841_11E6DC0A069E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define ID_LINK_STARTDRAG 1002

class CComboBoxURL : public CXTPControlComboBox  
{
	DECLARE_XTP_CONTROL(CComboBoxURL);
public:
	CComboBoxURL(CXTPCommandBars* pCommandBars = 0);

	void UpdateComboBox();
	void SaveTypedURL();

	void OnClick(BOOL bKeyboard = FALSE, CPoint pt = CPoint(0, 0));
	void OnMouseMove(CPoint point);

	void DoPropExchange(CXTPPropExchange* pPX);
};






class CComboBoxSearch : public CXTPControlComboBox  
{
	DECLARE_XTP_CONTROL(CComboBoxSearch);
public:
	CComboBoxSearch(CXTPCommandBars* pCommandBars = 0);
	virtual ~CComboBoxSearch();

	virtual BOOL OnSetPopup(BOOL bPopup);
	virtual void OnSelChanged();
	virtual void OnEditChanged();

public:
	int m_nCurrentEngine;
	CBrush m_brWindow;
};

#endif // !defined(AFX_COMBOBOXSEARCH_H__342A6E15_31D3_489A_A841_11E6DC0A069E__INCLUDED_)
