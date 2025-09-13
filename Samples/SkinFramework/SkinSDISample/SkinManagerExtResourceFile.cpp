// SkinManagerExtResourceFile.cpp
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

#include "stdafx.h"
#include "SkinSDISample.h"
#include "SkinManagerExtResourceFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkinManagerExtResourceFile::CSkinManagerExtResourceFile()
{
	m_pIniFile = NULL;
}

CSkinManagerExtResourceFile::~CSkinManagerExtResourceFile()
{
	Close();
}

BOOL CSkinManagerExtResourceFile::Open(LPCTSTR lpszResourcePath, LPCTSTR lpszIniFileName)
{
	Close();

	m_strResourcePath = lpszResourcePath;
	m_strIniFileName = lpszIniFileName;

	CString strFileName = m_strResourcePath + _T('\\') + m_strIniFileName;
	m_pIniFile = new CStdioFile;
	
	if (!m_pIniFile->Open(strFileName, CFile::modeRead))
	{
		SAFE_DELETE(m_pIniFile);
		return FALSE;
	}

	return TRUE;
}

BOOL CSkinManagerExtResourceFile::ReadString(CString& str)
{
	if (!m_pIniFile)
		return FALSE;

	if (!m_pIniFile->ReadString(str))
	{
		SAFE_DELETE(m_pIniFile);
		return FALSE;
	}

	return TRUE;
}

void CSkinManagerExtResourceFile::Close()
{
	SAFE_DELETE(m_pIniFile);
}

CXTPSkinImage* CSkinManagerExtResourceFile::LoadImage(CString strImageFile)
{
	USES_CONVERSION;

	strImageFile = m_strResourcePath + _T('\\') + strImageFile;

	if (!FILEEXISTS_S(strImageFile))
		return NULL;

	BOOL bAlpha;
	HBITMAP hBitmap = NULL;

	hBitmap = CXTPImageManagerIcon::LoadBitmapFromFile(strImageFile, &bAlpha);
	
	if (!hBitmap)
		return NULL;
	
	CXTPSkinImage* pImage = new CXTPSkinImage;
	
	if (bAlpha)
	{
		HBITMAP hBitmapAlpha = CXTPImageManagerIcon::PreMultiplyAlphaBitmap(hBitmap);
		
		pImage->SetBitmap(hBitmapAlpha, TRUE);
		
		DeleteObject(hBitmap);
	}
	else 
	{
		pImage->SetBitmap(hBitmap);
	}
	
	return pImage;
}
