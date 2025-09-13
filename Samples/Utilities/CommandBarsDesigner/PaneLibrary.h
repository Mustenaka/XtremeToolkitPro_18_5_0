// PaneLibrary.h
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

#if !defined(AFX_PANELIBRARY_H__6C481840_FE83_4798_9524_1A01F1FB13DB__INCLUDED_)
#define AFX_PANELIBRARY_H__6C481840_FE83_4798_9524_1A01F1FB13DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CResourceManager;

class CTreeLibrary : public CTreeCtrl
{

protected:
	LRESULT WindowProc(UINT message,WPARAM wParam,LPARAM lParam);

protected:
	//{{AFX_MSG(CTreeLibrary)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

enum TreeType
{
	treeRoot,
	treeCategory,
	treeAction
};

class CPaneLibrary : public CPaneHolder 
{
public:
	CPaneLibrary();
	virtual ~CPaneLibrary();

public:
	TreeType GetItemType(HTREEITEM hItem);

	//{{AFX_MSG(CPaneLibrary)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	
	afx_msg void OnTreeSelChange(NMHDR*, LRESULT*);
	afx_msg void OnTreeSetFocus(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/);
	afx_msg void OnTreeRightClick(NMHDR*, LRESULT*);
	afx_msg void OnTreeBeginLabelEdit(NMHDR* pHdr, LRESULT*);
	afx_msg void OnTreeEndLabelEdit(NMHDR* pHdr, LRESULT*);
	afx_msg void OnTreeBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTreeCustomDraw(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLibraryNew();
	afx_msg void OnLibraryOpen();
	afx_msg void OnLibrarySave();
	afx_msg void OnSetFocus(CWnd*);

	BOOL LoadFromFile(CString strFileName);
	void SaveToFile(CString strFileName);
	CString m_strFileName;

	DECLARE_MESSAGE_MAP()

	void CreateStandardActions();
	void AddAction(int nID, LPCTSTR lpszKey, LPCTSTR lpszCategory);

	CImageList m_ilTreeIcons;

	CResourceManager* m_pResourceManager;
	void RefreshResourceManager();


	HTREEITEM AddCategory(CString strCategory);
	void ExchangeCategories(CXTPPropExchange* pPX);
	void RefreshItem(HTREEITEM hItem);
	CObject* RefreshPropertyGrid(CXTPPropertyGrid* pPropertyGrid);
	BOOL OnPropertyGridValueChanged(CObject* pActiveObject, CXTPPropertyGridItem* pItem);
	int FindLastId();
	int GetTreeChildCount(HTREEITEM hItem);
	void FillActions();


protected:
	
	class CActions : public CXTPControlActions
	{
	public:
		CActions()
			: CXTPControlActions(NULL)
		{
		}
	public:
		void ReplaceActionId(CXTPControlAction* pAction, int nID);
		void DeleteAction(CXTPControlAction* pAction);
	};

	CActions* m_pActions;
	CXTPToolBar m_wndToolBar;
	CTreeLibrary m_wndTreeCtrl;

public:
	CXTPControlAction* m_pDragAction;
	CXTPImageManager* m_pIcons;
	static CLIPFORMAT m_cfItem;
};

#endif // !defined(AFX_PANELIBRARY_H__6C481840_FE83_4798_9524_1A01F1FB13DB__INCLUDED_)
