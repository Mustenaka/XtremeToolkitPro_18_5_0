// FlowGraphSampleView.h
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

#if !defined(AFX_FLOWGRAPHSAMPLEVIEW_H__201D410B_7BFF_4FFB_AAED_7730FD305FB3__INCLUDED_)
#define AFX_FLOWGRAPHSAMPLEVIEW_H__201D410B_7BFF_4FFB_AAED_7730FD305FB3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum FG_SHAPES_ID
{
	FG_SHAPE_TABLE = 100, 
	FG_SHAPE_PICTURE,
	FG_SHAPE_FROM_RESOURCE,
	FG_SHAPE_USERCARD,
	FG_SHAPE_CUSTOM
};

enum TOOLBOX_GROUP_ID
{
	TOOLBOX_GROUP_SHAPES = 0,
	TOOLBOX_GROUP_GEO_FIGURES,
	TOOLBOX_GROUP_OTHER,
	TOOLBOX_GROUP_ARROWS,
	TOOLBOX_GROUP_CONNECTIONS
};

class CFlowGraphSampleDoc;
class CXTPPropertyGrid;

#include "FlowGraph/Includes.h"

class CFlowGraphSampleView : public CView
{
protected: // create from serialization only
	CFlowGraphSampleView();
	DECLARE_DYNCREATE(CFlowGraphSampleView)

// Attributes
public:
	CFlowGraphSampleDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFlowGraphSampleView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

	void OnZoomSliderScroll(NMHDR* pNMHDR, LRESULT* pResult);
	void OnUpdateViewZoom(CCmdUI* pCmdUI);

	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	
	void OnUpdateHasSelection(CCmdUI* pCmdUI);
	void OnZoomToSelection();
	void OnZoomFitToWindow();

	void InsertNewShape(FG_SHAPES_ID id, CPoint point, UINT uResShapeID = -1);

	void InitFlowGraphImages();

	void OnSwitchGraphType0();
	void OnSwitchGraphType1();
	void OnSwitchGraphType2();

	void CreateDatabaseRelationships();
	void CreateNetworkDiagram();
	void CreateFlowChart();

	void OnQuality(UINT nCmd);
	void OnUpdateQuality(CCmdUI *pCmdUI);

	UINT TrackPopupMenu(CMenu* pMenu, UINT nFlags, int xPos, int yPos);

	int m_nZoom;

public:

	void SwitchGraph(int nGraphType);

// Implementation
public:
	virtual ~CFlowGraphSampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:

	CXTPFlowGraphControl m_wndControl;

	COleDropTarget m_droptarget;

	CXTPPropertyGrid *m_pGrid;

// Generated message map functions
protected:
	//{{AFX_MSG(CFlowGraphSampleView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnEditSelectAll();
	afx_msg void OnFlowgraphShowNodegroupsAlways();
	afx_msg void OnUpdateFlowgraphShowNodegroupsAlways(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnGraphRClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelectionChanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnSaveToFile();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditArrange();
	afx_msg void OnEditCopy();
	afx_msg void OnUpdateEditCopy(CCmdUI *pCmdUI);
	afx_msg void OnEditCut();
	afx_msg void OnUpdateEditCut(CCmdUI *pCmdUI);
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI *pCmdUI);
	afx_msg void OnEditUndo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	virtual void OnInitialUpdate();

	afx_msg void OnShowGrid();
	afx_msg void OnUpdateShowGrid(CCmdUI *pCmdUI);

	afx_msg void OnConnectorType(UINT nCmd);
	afx_msg void OnUpdateConnectorType(CCmdUI *pCmdUI);
	afx_msg void OnEditDelete();
	afx_msg void OnUpdateEditDelete(CCmdUI *pCmdUI);

#ifdef _XTP_INCLUDE_TASKPANEL
	LRESULT OnTaskPanelNotify(WPARAM wParam, LPARAM lParam);
#endif

#ifdef _XTP_INCLUDE_PROPERTYGRID
	LRESULT OnPropertyGridNotify(WPARAM wParam, LPARAM lParam);
	void UpdatePropertyGrid();
#endif

	
};

#ifndef _DEBUG  // debug version in FlowGraphSampleView.cpp
inline CFlowGraphSampleDoc* CFlowGraphSampleView::GetDocument()
   { return (CFlowGraphSampleDoc*)m_pDocument; }
#endif

extern COLORREF clrOfficeColors[];
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FLOWGRAPHSAMPLEVIEW_H__201D410B_7BFF_4FFB_AAED_7730FD305FB3__INCLUDED_)
