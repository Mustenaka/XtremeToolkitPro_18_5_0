// SkinManagerExtResourceFile.h
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

#if !defined(AFX_SKINMANAGEREXTRESOURCEFILE_H__7FE7DFFB_793D_4C83_A70A_C8ABE2080EF4__INCLUDED_)
#define AFX_SKINMANAGEREXTRESOURCEFILE_H__7FE7DFFB_793D_4C83_A70A_C8ABE2080EF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSkinManagerExtResourceFile : public CXTPSkinManagerResourceFile  
{
public:
	CSkinManagerExtResourceFile();
	virtual ~CSkinManagerExtResourceFile();

public:
	virtual BOOL Open(LPCTSTR lpszResourcePath, LPCTSTR lpszIniFileName);

	virtual void Close();

	virtual CXTPSkinImage* LoadImage(CString strImageFile);

	virtual BOOL ReadString(CString& str);

protected:
	CStdioFile* m_pIniFile;
};

#endif // !defined(AFX_SKINMANAGEREXTRESOURCEFILE_H__7FE7DFFB_793D_4C83_A70A_C8ABE2080EF4__INCLUDED_)
