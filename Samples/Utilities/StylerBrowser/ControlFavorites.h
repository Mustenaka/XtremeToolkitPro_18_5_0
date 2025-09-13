// ControlFavorites.h
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

#if !defined(AFX_CONTROLFAVORITES_H__845657C3_FF0D_4909_8D8E_D9C9814C67F7__INCLUDED_)
#define AFX_CONTROLFAVORITES_H__845657C3_FF0D_4909_8D8E_D9C9814C67F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CControlFavoriteLink : public CXTPControlButton
{
	DECLARE_XTP_CONTROL(CControlFavoriteLink)

public:
	CString m_strFileName;
};


class CControlFavoriteFolder : public CXTPControlButton
{
	DECLARE_XTP_CONTROL(CControlFavoriteFolder)

public:
	CControlFavoriteFolder(LPCTSTR strRootDir = 0);
	
protected:
	virtual void OnCalcDynamicSize(DWORD dwMode);
	virtual BOOL IsCustomizeDragOverAvail(CXTPCommandBar* pCommandBar, CPoint point, DROPEFFECT& dropEffect);
	virtual void Copy(CXTPControl* pControl, BOOL bRecursive);
	virtual void DoPropExchange(CXTPPropExchange* pPX);

private:
	CString m_strRootDir;
};

#endif // !defined(AFX_CONTROLFAVORITES_H__845657C3_FF0D_4909_8D8E_D9C9814C67F7__INCLUDED_)
