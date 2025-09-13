// MarkupPadDoc.h
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

#if !defined(AFX_MARKUPPADDOC_H__51982D4F_56C1_41CA_ABD5_877164B63440__INCLUDED_)
#define AFX_MARKUPPADDOC_H__51982D4F_56C1_41CA_ABD5_877164B63440__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMarkupPadView;

class CMarkupPadDoc : public CDocument
{
protected: // create from serialization only
	CMarkupPadDoc();
	DECLARE_DYNCREATE(CMarkupPadDoc)

// Attributes
public:

	CEditView* GetView() const;
	CMarkupPadView* GetMarkupView() const;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupPadDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

	static DWORD CALLBACK RichTextCtrlCallbackIn(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb);

	void SetTitle(LPCTSTR lpszTitle);


// Implementation
public:
	virtual ~CMarkupPadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMarkupPadDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	static BOOL IsValidBomByte(BYTE b, INT_PTR pos, BYTE* pBom, BOOL& bBomComplete);
	static LPCWSTR SkipXmlProcessingInstructions(LPCWSTR lpXml);

	BOOL m_bProcessingInstructionsFound;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKUPPADDOC_H__51982D4F_56C1_41CA_ABD5_877164B63440__INCLUDED_)
