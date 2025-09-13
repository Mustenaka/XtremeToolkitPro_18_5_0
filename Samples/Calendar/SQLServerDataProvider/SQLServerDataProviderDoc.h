// SQLServerDataProviderDoc.h
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

#if !defined(AFX_SQLSERVERDATAPROVIDERDOC_H__86EEF6EC_0C3E_4087_AA83_3039A0030F37__INCLUDED_)
#define AFX_SQLSERVERDATAPROVIDERDOC_H__86EEF6EC_0C3E_4087_AA83_3039A0030F37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalendarDataProviderSQL;

//////////////////////////////////////////////////////////////////////////
class CSQLServerDataProviderDoc : public CDocument
{
protected: // create from serialization only
	CSQLServerDataProviderDoc();
	DECLARE_DYNCREATE(CSQLServerDataProviderDoc)

// Attributes
public:

	enum EUpdateViewFlags 
	{
		uvfPopulate				= 0x1,
		uvfSetDataProvider		= 0x2,
		uvfDetachDataProvider	= 0x4,
	};

	CXTPCalendarData* GetDataProvider_SQLServer();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSQLServerDataProviderDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSQLServerDataProviderDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void SafeReleaseSQLDataProvider();

	CCalendarDataProviderSQL* m_pSQLDataProvider;

// Generated message map functions
protected:
	//{{AFX_MSG(CSQLServerDataProviderDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SQLSERVERDATAPROVIDERDOC_H__86EEF6EC_0C3E_4087_AA83_3039A0030F37__INCLUDED_)
