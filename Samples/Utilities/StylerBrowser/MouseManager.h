// MouseManager.h
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

#if !defined(AFX_MOUSEMANAGER_H__19F3DE40_E931_4E71_A2BF_C2F8406C520E__INCLUDED_)
#define AFX_MOUSEMANAGER_H__19F3DE40_E931_4E71_A2BF_C2F8406C520E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MOUSE_AREA_TAB		0
#define MOUSE_AREA_TABBAR	1
#define MOUSE_AREA_BROWSER	2


struct MOUSECLICKS
{
	DWORD dwMouse;
	int nArea;
	ACCEL accel;
};

class CMouseManager  
{
public:
	typedef CArray<MOUSECLICKS, MOUSECLICKS&> CMouseClicksArray;

	static BOOL Load();
	static void Save();
	
	static int FindMouseCommand(int nArea, DWORD dwMouse);
	static CString GetMouseString(DWORD dwMouse);
	static void AddCommand(DWORD dwMouse, ACCEL accel, int nArea);

	static CMouseClicksArray& GetArray() 
	{
		return m_arrMouse;
	}


protected:
	static CMap<DWORD, DWORD, CString, CString> m_mapStrings;
	static CMouseClicksArray m_arrMouse;
};

#endif // !defined(AFX_MOUSEMANAGER_H__19F3DE40_E931_4E71_A2BF_C2F8406C520E__INCLUDED_)
