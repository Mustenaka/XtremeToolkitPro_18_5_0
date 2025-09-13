// CustomizeTreeCtrl.h
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

#if !defined(AFX_CUSTOMIZETREECTRL_H__3A7ACA47_586C_4AF0_ACB5_AF785AE1B360__INCLUDED_)
#define AFX_CUSTOMIZETREECTRL_H__3A7ACA47_586C_4AF0_ACB5_AF785AE1B360__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCustomizeTreeCtrl : public CXTPCoreTreeControl  
{
public:
	CCustomizeTreeCtrl();
	virtual ~CCustomizeTreeCtrl();

protected:
	virtual void StartDragItem(CXTPCoreTreeItem* pItem);
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);

	int GetItemLevel(CXTPCoreTreeItem* pItem) const;

public:
	BOOL m_bItemsTree;

};

#endif // !defined(AFX_CUSTOMIZETREECTRL_H__3A7ACA47_586C_4AF0_ACB5_AF785AE1B360__INCLUDED_)
