// SampleText.h
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

#if !defined(AFX_SAMPLETEXT_H__04ADB74E_787E_4DC2_B48A_1D59C7EDE8F3__INCLUDED_)
#define AFX_SAMPLETEXT_H__04ADB74E_787E_4DC2_B48A_1D59C7EDE8F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFontComboDlg;

/////////////////////////////////////////////////////////////////////////////
// CSampleText window

class CSampleText : public CXTPEdit
{
public:
	CSampleText();
	virtual ~CSampleText();

	void UpdateFont(const CXTPLogFont& lf, const COLORREF& cr);

	//{{AFX_VIRTUAL(CSampleText)
	//}}AFX_VIRTUAL

protected:
	COLORREF m_cr;
	CXTPLogFont m_lf;

	//{{AFX_MSG(CSampleText)
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLETEXT_H__04ADB74E_787E_4DC2_B48A_1D59C7EDE8F3__INCLUDED_)
