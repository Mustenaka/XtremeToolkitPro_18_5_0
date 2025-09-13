// GridSampleView.cpp
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

#include "StdAfx.h"
#include "GridSample.h"
#include "GridSampleDoc.h"
#include "GridSampleView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_REMOVE_ITEM  1
#define ID_SORT_ASC     2
#define ID_SORT_DESC        3
#define ID_SORT_NO      99
#define ID_GROUP_BYTHIS 4
#define ID_SHOW_GROUPBOX        5
#define ID_SHOW_FIELDCHOOSER 6

/////////////////////////////////////////////////////////////////////////////
// CGridSampleView

IMPLEMENT_DYNCREATE(CGridSampleView, CXTPReportView)

BEGIN_MESSAGE_MAP(CGridSampleView, CXTPReportView)
	//{{AFX_MSG_MAP(CGridSampleView)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()

	// Report behavior
	ON_COMMAND(ID_BEHAVIOR_CODEJOCKDEFAULT, OnBehaviorCodejockDefault)
	ON_COMMAND(ID_BEHAVIOR_CODEJOCK1502,    OnBehaviorCodejock1502)
	ON_COMMAND(ID_BEHAVIOR_OUTLOOK2003,     OnBehaviorOutlook2003)
	ON_COMMAND(ID_BEHAVIOR_OUTLOOK2007,     OnBehaviorOutlook2007)
	ON_COMMAND(ID_BEHAVIOR_OUTLOOK2010,     OnBehaviorOutlook2010)
	ON_COMMAND(ID_BEHAVIOR_EXCEL2003,       OnBehaviorExcel2003)
	ON_COMMAND(ID_BEHAVIOR_EXCEL2007,       OnBehaviorExcel2007)
	ON_COMMAND(ID_BEHAVIOR_EXCEL2010,       OnBehaviorExcel2010)
	ON_COMMAND(ID_BEHAVIOR_CUSTOM,          OnBehaviorCustom)

	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_CODEJOCKDEFAULT, OnUpdateBehaviorCodejockDefault)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_CODEJOCK1502,    OnUpdateBehaviorCodejock1502)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_OUTLOOK2003,     OnUpdateBehaviorOutlook2003)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_OUTLOOK2007,     OnUpdateBehaviorOutlook2007)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_OUTLOOK2010,     OnUpdateBehaviorOutlook2010)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_EXCEL2003,       OnUpdateBehaviorExcel2003)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_EXCEL2007,       OnUpdateBehaviorExcel2007)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_EXCEL2010,       OnUpdateBehaviorExcel2010)
	ON_UPDATE_COMMAND_UI(ID_BEHAVIOR_CUSTOM,          OnUpdateBehaviorCustom)

	// Report control
	ON_COMMAND(ID_REPORTCONTROL_DOUBLEBUFFERING,  OnReportDoubleBuffering)
	ON_COMMAND(ID_REPORTCONTROL_LOCKEXPAND,       OnReportLockExpand)
	ON_COMMAND(ID_REPORTCONTROL_WATERMARK,        OnReportWatermark)
	ON_COMMAND(ID_REPORTCONTROL_SMOOTH_SCROLLING, OnReportSmoothScrolling)

	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_DOUBLEBUFFERING,  OnUpdateReportDoubleBuffering)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_LOCKEXPAND,       OnUpdateReportLockExpand)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_WATERMARK,        OnUpdateReportWatermark)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_SMOOTH_SCROLLING, OnUpdateReportSmoothScrolling)


	ON_COMMAND(ID_ENABLE_PREVIEW, OnEnablePreview)
	ON_COMMAND(ID_TEST_GROUPBY, OnGroupBy)
	ON_COMMAND(ID_TEST_GROUPSHADE, OnGroupShade)
	ON_COMMAND(ID_TEST_GROUPSBOLD, OnGroupBold)	
	ON_COMMAND(ID_REPORTCONTROL_AUTOMATICFORMATTINGSAMPLE, OnReportcontrolAutomaticformattingsample)

	ON_UPDATE_COMMAND_UI(ID_ENABLE_PREVIEW, OnUpdateEnablePreview)
	ON_UPDATE_COMMAND_UI(ID_TEST_GROUPBY, OnUpdateGroupBy)
	ON_UPDATE_COMMAND_UI(ID_TEST_GROUPSHADE, OnUpdateGroupShade)
	ON_UPDATE_COMMAND_UI(ID_TEST_GROUPSBOLD, OnUpdateGroupBold)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_AUTOMATICFORMATTINGSAMPLE, OnUpdateReportcontrolAutomaticformattingsample)
	
	ON_COMMAND(ID_OPTIONS_ALLOWCOLUMNRESIZE, OnOptionsAllowcolumnresize)
	ON_COMMAND(ID_OPTIONS_ALLOWCOLUMNSREMOVE, OnOptionsAllowcolumnsremove)
	ON_COMMAND(ID_OPTIONS_MULTIPLESELECTION, OnOptionsMultipleselection)
	ON_COMMAND(ID_OPTIONS_SHOWITEMSINGROUPS, OnOptionsShowitemsingroups)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ALLOWCOLUMNRESIZE, OnUpdateOptionsAllowcolumnresize)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_ALLOWCOLUMNSREMOVE, OnUpdateOptionsAllowcolumnsremove)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_MULTIPLESELECTION, OnUpdateOptionsMultipleselection)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_SHOWITEMSINGROUPS, OnUpdateOptionsShowitemsingroups)

	ON_COMMAND(ID_OPTIONS_AUTOMATICCOLUMNSIZING, OnOptionsAutomaticcolumnsizing)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_AUTOMATICCOLUMNSIZING, OnUpdateOptionsAutomaticcolumnsizing)
	ON_COMMAND(ID_OPTIONS_FULLCOLUMNSCROLING, OnOptionsFullColumnScrolling)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FULLCOLUMNSCROLING, OnUpdateOptionsFullColumnScrolling)
	ON_COMMAND(ID_REPORTHEADER_ALLOWCOLUMNREORDER, OnReportheaderAllowcolumnreorder)
	ON_UPDATE_COMMAND_UI(ID_REPORTHEADER_ALLOWCOLUMNREORDER, OnUpdateReportheaderAllowcolumnreorder)
	ON_COMMAND_RANGE(ID_COLUMNSTYLE_SHADED, ID_COLUMNSTYLE_OFFICE2007, OnColumnStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_COLUMNSTYLE_SHADED, ID_COLUMNSTYLE_OFFICE2007, OnUpdateColumnStyle)

	ON_COMMAND(ID_REPORTCONTROL_RIGHTTOLEFT, OnReportcontrolRighttoleft)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_RIGHTTOLEFT, OnUpdateReportcontrolRighttoleft)

	// Freeze columns
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_0, OnOptionsFreezecolumns0)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_1, OnOptionsFreezecolumns1)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_2, OnOptionsFreezecolumns2)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_3, OnOptionsFreezecolumns3)
	
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_0, OnUpdateOptionsFreezecolumns0)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_1, OnUpdateOptionsFreezecolumns1)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_2, OnUpdateOptionsFreezecolumns2)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_3, OnUpdateOptionsFreezecolumns3)

	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_1, OnOptionsFreezecolumnsDivider1)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_2, OnOptionsFreezecolumnsDivider2)
	
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_1, OnUpdateOptionsFreezecolumnsDivider1)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_2, OnUpdateOptionsFreezecolumnsDivider2)

	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_HEADER, OnOptionsFreezecolumnsDividerHeader)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_NONE,   OnOptionsFreezecolumnsDividerNone)
	ON_COMMAND(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_SHADE,  OnOptionsFreezecolumnsDividerShade)
	
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_HEADER, OnUpdateOptionsFreezecolumnsDividerHeader)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_NONE,   OnUpdateOptionsFreezecolumnsDividerNone)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FREEZECOLUMNS_DIVIDER_SHADE,  OnUpdateOptionsFreezecolumnsDividerShade)
	//}}AFX_MSG_MAP
	// Standard printing commands

	ON_COMMAND_RANGE(ID_GRID_HORIZONTAL_NOGRIDLINES, ID_GRID_HORIZONTAL_SOLID, OnGridHorizontal)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GRID_HORIZONTAL_NOGRIDLINES, ID_GRID_HORIZONTAL_SOLID, OnUpdateGridHorizontal)

	ON_COMMAND_RANGE(ID_GRID_VERTICAL_NOGRIDLINES, ID_GRID_VERTICAL_SOLID, OnGridVertical)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GRID_VERTICAL_NOGRIDLINES, ID_GRID_VERTICAL_SOLID, OnUpdateGridVertical)

	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CGridSampleView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PAGE_SETUP, CXTPReportView::OnFilePageSetup)

	ON_NOTIFY(NM_CLICK, XTP_ID_REPORT_CONTROL, OnReportItemClick)
	ON_NOTIFY(XTP_NM_REPORT_HYPERLINK , XTP_ID_REPORT_CONTROL, OnReportHyperlinkClick)
	ON_NOTIFY(NM_RCLICK, XTP_ID_REPORT_CONTROL, OnReportItemRClick)
	ON_NOTIFY(NM_DBLCLK, XTP_ID_REPORT_CONTROL, OnReportItemDblClick)
	ON_NOTIFY(XTP_NM_REPORT_HEADER_RCLICK, XTP_ID_REPORT_CONTROL, OnReportColumnRClick)
	ON_NOTIFY(NM_KEYDOWN, XTP_ID_REPORT_CONTROL, OnReportKeyDown)
	ON_NOTIFY(LVN_BEGINDRAG, XTP_ID_REPORT_CONTROL, OnReportBeginDrag)
	ON_NOTIFY(XTP_NM_REPORT_BEFORE_PASTE_FROMTEXT, XTP_ID_REPORT_CONTROL, OnReportBeforePasteFromText)
	ON_NOTIFY(XTP_NM_REPORT_BEFORE_PASTE, XTP_ID_REPORT_CONTROL, OnReportBeforePaste)

	ON_COMMAND(ID_REPORTCONTROL_WYSIWYG_PRINT, OnReportWYSIWYG)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_WYSIWYG_PRINT, OnUpdateReportWYSIWYG)

	ON_COMMAND(ID_REPORTCONTROL_ICONVIEW, OnReportIconview)
	ON_UPDATE_COMMAND_UI(ID_REPORTCONTROL_ICONVIEW, OnUpdateReportIconview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGridSampleView construction/destruction

CGridSampleView::CGridSampleView()
	: m_pWndMerge       (NULL)
	, m_pWndSelection   (NULL)
	, m_pWndSmoothScroll(NULL)
{
	m_bAutomaticFormating = FALSE;
	m_pTaskFrame = 0;
	m_pHeaderFooterFrame = 0;
	m_pPropertiesFrame = 0;
	m_bMultilineSample = FALSE;
	m_bWYSIWYG = FALSE;
}

CGridSampleView::~CGridSampleView()
{
}

BOOL CGridSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CView::PreCreateWindow(cs))
		return FALSE;

	//cs.dwExStyle |= WS_EX_STATICEDGE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGridSampleView diagnostics

#ifdef _DEBUG
void CGridSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CGridSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGridSampleDoc* CGridSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGridSampleDoc)));
	return (CGridSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGridSampleView message handlers

int CGridSampleView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPReportView::OnCreate(lpCreateStruct) == -1)
		return -1;

	VERIFY(m_ilIcons.Create(16,16, ILC_COLOR24|ILC_MASK, 0, 1));
	CBitmap bmp;
	VERIFY(bmp.LoadBitmap(IDB_BMREPORT));
	m_ilIcons.Add(&bmp, RGB(255, 0, 255));

	CXTPReportControl& wndReport = GetReportCtrl();
	wndReport.SetImageList(&m_ilIcons);


	CXTPReportColumn *pColumnFixed = wndReport.AddColumn(new CXTPReportColumn(0, _T(""), 50));
	pColumnFixed->SetFixed(TRUE);
	pColumnFixed->SetAutoNumbering(TRUE);

	enum
	{
		ColumnCount = 10,
		RecordCount = 25
	};

	LPCTSTR lpszColumnName[] = {
		_T("A"), _T("B"), _T("C"), _T("D"), _T("E"), _T("F"), _T("G"), _T("H"),
		_T("I"), _T("J"), _T("K"), _T("L"), _T("M"), _T("N"), _T("O"), _T("P"),
		_T("Q"), _T("R"), _T("S"), _T("T"), _T("U"), _T("V"), _T("W"), _T("X"),
		_T("Y"), _T("Z")
	};

	for (int nColumn=0; nColumn<ColumnCount; nColumn++)
	{
		wndReport.AddColumn(new CXTPReportColumn(wndReport.GetColumns()->GetCount(), lpszColumnName[nColumn], 100));
	}

	for (int nRecord=0; nRecord<RecordCount; nRecord++)
	{
		CXTPReportRecord *pRecord = wndReport.AddRecord(new CXTPReportRecord());
		pRecord->AddItem(new CXTPReportRecordItemNumber());

		for (int nColumn=0; nColumn<ColumnCount; nColumn++)
		{
			CXTPReportRecordItemText *pItem = new CXTPReportRecordItemText();
			pRecord->AddItem(pItem);
		}
	}

	wndReport.Populate();
	wndReport.FocusSubItems(TRUE);
	wndReport.AllowEdit(TRUE);
	wndReport.GetPaintManager()->SetGridStyle(TRUE, xtpReportLineStyleSolid);
	wndReport.GetReportHeader()->SetAutoColumnSizing(FALSE);

#if defined(_XTP_INCLUDE_COMMANDBARS)
	wndReport.GetPaintManager()->SetColumnStyle(xtpReportColumnResource);
#endif

	return 0;
}

// Before self destroying destroy all child forms 
void CGridSampleView::OnDestroy()
{
	SaveReportState();

	if (m_pTaskFrame)
		m_pTaskFrame->DestroyWindow();
	if (m_pPropertiesFrame)
		m_pPropertiesFrame->DestroyWindow();
	if (m_pHeaderFooterFrame)
		m_pHeaderFooterFrame->DestroyWindow();

	if (m_pWndMerge)
	{
		m_pWndMerge->DestroyWindow();
	}

	if (m_pWndSelection)
	{
		m_pWndSelection->DestroyWindow();
	}

	CView::OnDestroy();
}

// Preview is a text message which is shown for every row, 
// if ReportControl is in Preview mode.
// In this sample preview text is equal to Message text, 
// but it doesn't have to be always used in such way 
void CGridSampleView::OnEnablePreview()
{
	GetReportCtrl().EnablePreviewMode(!GetReportCtrl().IsPreviewMode());
	GetReportCtrl().Populate();
}

void CGridSampleView::OnUpdateEnablePreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsPreviewMode());
}

void CGridSampleView::OnGroupBy()
{
	GetReportCtrl().ShowGroupBy(!GetReportCtrl().IsGroupByVisible());
}

void CGridSampleView::OnUpdateGroupBy(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsGroupByVisible());
}


// Toggles shady style for group heading
void CGridSampleView::OnGroupShade()
{
	GetReportCtrl().ShadeGroupHeadings(!GetReportCtrl().IsShadeGroupHeadingsEnabled());
}

void CGridSampleView::OnUpdateGroupShade(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsShadeGroupHeadingsEnabled());
}

// Toggles bold style for group heading
void CGridSampleView::OnGroupBold()
{
	GetReportCtrl().SetGroupRowsBold(!GetReportCtrl().IsGroupRowsBold());
	GetReportCtrl().RedrawControl();
}

void CGridSampleView::OnUpdateGroupBold(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsGroupRowsBold());
}


void CGridSampleView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();
	if (m_wndSubList.GetSafeHwnd() == NULL)
	{
		m_wndSubList.SubclassDlgItem(IDC_COLUMNLIST, &pWnd->m_wndFieldChooser);
		GetReportCtrl().GetColumns()->GetReportHeader()->SetSubListCtrl(&m_wndSubList);
	}

	if (m_wndFilterEdit.GetSafeHwnd() == NULL)
	{
		m_wndFilterEdit.SubclassDlgItem(IDC_FILTEREDIT, &pWnd->m_wndFilterEdit);
		GetReportCtrl().GetColumns()->GetReportHeader()->SetFilterEditCtrl(&m_wndFilterEdit);
	}

	GetReportCtrl().GetPaintManager()->m_bShowLockIcon = TRUE;
	//GetReportCtrl().GetPaintManager()->m_bUseShellIcon = TRUE;
}

void CGridSampleView::LoadReportState()
{
}

void CGridSampleView::SaveReportState()
{
}



CString LoadResourceString(UINT nID)
{
	CString str;
	VERIFY(str.LoadString(nID));
	return str;
}

void CGridSampleView::OnReportColumnRClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
}

void CGridSampleView::OnReportBeginDrag(NMHDR *pNotifyStruct, LRESULT *pResult)
{
}

void CGridSampleView::OnReportItemRClick(NMHDR * pNotifyStruct, LRESULT *pResult)
{
}

void CGridSampleView::OnReportHyperlinkClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
}

void CGridSampleView::OnReportItemClick(NMHDR * pNotifyStruct, LRESULT * /*result*/)
{
}

void CGridSampleView::OnReportKeyDown(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	NMKEY *pNMKey = reinterpret_cast<NMKEY*>(pNotifyStruct);
}

void CGridSampleView::OnReportItemDblClick(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	XTP_NM_REPORTRECORDITEM* pItemNotify = (XTP_NM_REPORTRECORDITEM*) pNotifyStruct;
}

// FieldChooser is used to add or remove fields (i.e. columns) using drag-and-drop. 
// FieldChooser is an analog of a pool with column headers of none-used columns
void CGridSampleView::OnShowFieldChooser()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	if (pMainFrm)
	{
		BOOL bShow = !pMainFrm->m_wndFieldChooser.IsVisible();
		pMainFrm->ShowControlBar(&pMainFrm->m_wndFieldChooser, bShow, FALSE);
	}
}

// If enabled -- allows automatic formating. 
void CGridSampleView::OnReportcontrolAutomaticformattingsample()
{
	m_bAutomaticFormating = !m_bAutomaticFormating;
	GetReportCtrl().RedrawControl();
}

void CGridSampleView::OnUpdateReportcontrolAutomaticformattingsample(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bAutomaticFormating);

}

// Set horizontal grid lines style.
// Following styles are available:
//  No Grid lines;
//  Small dots
//  Large Dots
//  Dashes
//  Solid
void CGridSampleView::OnGridHorizontal(UINT nID)
{
	GetReportCtrl().SetGridStyle(FALSE, (XTPReportGridStyle)(nID - ID_GRID_HORIZONTAL_NOGRIDLINES));
}

void CGridSampleView::OnUpdateGridHorizontal(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(((int)pCmdUI->m_nID - ID_GRID_HORIZONTAL_NOGRIDLINES) == GetReportCtrl().GetGridStyle(FALSE));
}

// Set vertical grid lines style.
// Following styles are available:
//  No Grid lines;
//  Small dots
//  Large Dots
//  Dashes
//  Solid
void CGridSampleView::OnGridVertical(UINT nID)
{
	GetReportCtrl().SetGridStyle(TRUE, (XTPReportGridStyle)(nID - ID_GRID_VERTICAL_NOGRIDLINES));
}

void CGridSampleView::OnUpdateGridVertical(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(((int)pCmdUI->m_nID - ID_GRID_VERTICAL_NOGRIDLINES) == GetReportCtrl().GetGridStyle(TRUE));
}

// Allow or forbid column resize  
void CGridSampleView::OnOptionsAllowcolumnresize()
{
	GetReportCtrl().GetReportHeader()->AllowColumnResize(!GetReportCtrl().GetReportHeader()->IsAllowColumnResize());
}

void CGridSampleView::OnUpdateOptionsAllowcolumnresize(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().GetReportHeader()->IsAllowColumnResize());
}

// Allow or forbid columns removal 
void CGridSampleView::OnOptionsAllowcolumnsremove()
{
	GetReportCtrl().GetReportHeader()->AllowColumnRemove(!GetReportCtrl().GetReportHeader()->IsAllowColumnRemove());
}

void CGridSampleView::OnUpdateOptionsAllowcolumnsremove(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().GetReportHeader()->IsAllowColumnRemove());
}

// Allow or forbid columns reordering
void CGridSampleView::OnReportheaderAllowcolumnreorder() 
{
	GetReportCtrl().GetReportHeader()->AllowColumnReorder(!GetReportCtrl().GetReportHeader()->IsAllowColumnReorder());
}

void CGridSampleView::OnUpdateReportheaderAllowcolumnreorder(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetReportHeader()->IsAllowColumnReorder());
}

// Allow or forbid simultaneous selection of several records
void CGridSampleView::OnOptionsMultipleselection()
{
	GetReportCtrl().SetMultipleSelection(!GetReportCtrl().IsMultipleSelection());
}

void CGridSampleView::OnUpdateOptionsMultipleselection(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsMultipleSelection());
}
// Allow or forbid records grouping
void CGridSampleView::OnOptionsShowitemsingroups()
{
	GetReportCtrl().GetReportHeader()->ShowItemsInGroups(!GetReportCtrl().GetReportHeader()->IsShowItemsInGroups());

	if (!GetReportCtrl().GetReportHeader()->IsShowItemsInGroups())
	{
		GetReportCtrl().GetColumns()->GetGroupsOrder()->Clear();
		GetReportCtrl().Populate();
	}
}

void CGridSampleView::OnUpdateOptionsShowitemsingroups(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().GetReportHeader()->IsShowItemsInGroups());	
}

// Allow or forbid automatic columns resizing
void CGridSampleView::OnOptionsAutomaticcolumnsizing()
{
	GetReportCtrl().GetReportHeader()->SetAutoColumnSizing(!GetReportCtrl().GetReportHeader()->IsAutoColumnSizing());

#ifdef _XTP_INCLUDE_COMMANDBARS
	if (GetReportCtrl().GetReportHeader()->IsAutoColumnSizing())
	{
		SetScrollBarCtrl(NULL, TRUE);
		m_wndHScrollBar.ShowWindow(SW_HIDE);
	}
	else
	{
		m_wndHScrollBar.ShowWindow(SW_SHOW);
		SetScrollBarCtrl(&m_wndHScrollBar, TRUE);
	}
#endif
	GetReportCtrl().AdjustScrollBars();
}

void CGridSampleView::OnUpdateOptionsAutomaticcolumnsizing(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().GetReportHeader()->IsAutoColumnSizing());
}

void CGridSampleView::OnOptionsFullColumnScrolling()
{
	GetReportCtrl().SetFullColumnScrolling(!GetReportCtrl().IsFullColumnScrolling());
}

void CGridSampleView::OnUpdateOptionsFullColumnScrolling(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsFullColumnScrolling());
}


void CGridSampleView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	GetReportCtrl().SetFocus();
}

// Set column header draw style.
// Following styles are available:
//   Shaded
//   Flat
//   Explorer
//   Office2003
//   Office2007
void CGridSampleView::OnColumnStyle(UINT nID) 
{
	GetReportCtrl().GetPaintManager()->SetColumnStyle(XTPReportColumnStyle(nID - ID_COLUMNSTYLE_SHADED));
	GetReportCtrl().RedrawControl();
	
}

void CGridSampleView::OnUpdateColumnStyle(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetPaintManager()->GetColumnStyle() == XTPReportColumnStyle(pCmdUI->m_nID - ID_COLUMNSTYLE_SHADED)? TRUE: FALSE);
	
}

void CGridSampleView::OnReportBeforePaste(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	*pResult = 1; // This result prevent report changes
}

void CGridSampleView::OnReportBeforePasteFromText(NMHDR *pNotifyStruct, LRESULT *pResult)
{
	*pResult = 1; // This result prevent report changes
}

void CGridSampleView::OnOptionsFreezecolumns0() 
{
	GetReportCtrl().SetFreezeColumnsCount(0);
	GetReportCtrl().RedrawControl();
}

void CGridSampleView::OnUpdateOptionsFreezecolumns0(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetFreezeColumnsCount() == 0 ? 1 : 0);
}

void CGridSampleView::OnOptionsFreezecolumns1() 
{
	GetReportCtrl().SetFreezeColumnsCount(1);	
	GetReportCtrl().RedrawControl();
}

void CGridSampleView::OnUpdateOptionsFreezecolumns1(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetFreezeColumnsCount() == 1 ? 1 : 0);	
}

void CGridSampleView::OnOptionsFreezecolumns2() 
{
	GetReportCtrl().SetFreezeColumnsCount(2);
	GetReportCtrl().RedrawControl();
}

void CGridSampleView::OnUpdateOptionsFreezecolumns2(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetFreezeColumnsCount() == 2 ? 1 : 0);	
}

void CGridSampleView::OnOptionsFreezecolumns3() 
{
	GetReportCtrl().SetFreezeColumnsCount(3);
	GetReportCtrl().RedrawControl();
}

void CGridSampleView::OnUpdateOptionsFreezecolumns3(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(GetReportCtrl().GetFreezeColumnsCount() == 3 ? 1 : 0);
}


void CGridSampleView::OnReportcontrolRighttoleft() 
{
	GetReportCtrl().SetLayoutRTL(GetReportCtrl().GetExStyle() & WS_EX_LAYOUTRTL ? FALSE : TRUE);
	
}

void CGridSampleView::OnUpdateReportcontrolRighttoleft(CCmdUI* pCmdUI) 
{
	if (!XTPSystemVersion()->IsLayoutRTLSupported())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->SetCheck(GetReportCtrl().GetExStyle() & WS_EX_LAYOUTRTL ? TRUE : FALSE);
	}	
}

void CGridSampleView::OnOptionsFreezecolumnsDivider1() 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	nStyle &= ~(xtpReportFreezeColsDividerBold | xtpReportFreezeColsDividerThin);
	nStyle |= xtpReportFreezeColsDividerThin;
	
	GetReportCtrl().GetPaintManager()->SetFreezeColsDividerStyle(nStyle);

	GetReportCtrl().RedrawControl();	
}

void CGridSampleView::OnOptionsFreezecolumnsDivider2() 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	nStyle &= ~(xtpReportFreezeColsDividerBold | xtpReportFreezeColsDividerThin);
	nStyle |= xtpReportFreezeColsDividerBold;
	
	GetReportCtrl().GetPaintManager()->SetFreezeColsDividerStyle(nStyle);

	GetReportCtrl().RedrawControl();	
	
}

void CGridSampleView::OnUpdateOptionsFreezecolumnsDivider1(CCmdUI* pCmdUI) 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	pCmdUI->SetCheck((nStyle & xtpReportFreezeColsDividerThin) != 0);
}

void CGridSampleView::OnUpdateOptionsFreezecolumnsDivider2(CCmdUI* pCmdUI) 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	pCmdUI->SetCheck((nStyle & xtpReportFreezeColsDividerBold) != 0);
}

void CGridSampleView::OnOptionsFreezecolumnsDividerHeader() 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	nStyle ^= xtpReportFreezeColsDividerHeader;
		
	GetReportCtrl().GetPaintManager()->SetFreezeColsDividerStyle(nStyle);

	GetReportCtrl().RedrawControl();		
}

void CGridSampleView::OnUpdateOptionsFreezecolumnsDividerHeader(CCmdUI* pCmdUI) 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	pCmdUI->SetCheck((nStyle & xtpReportFreezeColsDividerHeader) != 0);
}

void CGridSampleView::OnOptionsFreezecolumnsDividerNone() 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	nStyle = (nStyle & (xtpReportFreezeColsDividerHeader));
		
	GetReportCtrl().GetPaintManager()->SetFreezeColsDividerStyle(nStyle);

	GetReportCtrl().RedrawControl();
}

void CGridSampleView::OnUpdateOptionsFreezecolumnsDividerNone(CCmdUI* pCmdUI) 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	pCmdUI->SetCheck((nStyle & ~xtpReportFreezeColsDividerHeader) == 0);
}

void CGridSampleView::OnOptionsFreezecolumnsDividerShade() 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	nStyle ^= xtpReportFreezeColsDividerShade;
		
	GetReportCtrl().GetPaintManager()->SetFreezeColsDividerStyle(nStyle);

	GetReportCtrl().RedrawControl();	
}

void CGridSampleView::OnUpdateOptionsFreezecolumnsDividerShade(CCmdUI* pCmdUI) 
{
	int nStyle = GetReportCtrl().GetPaintManager()->GetFreezeColsDividerStyle();
	pCmdUI->SetCheck((nStyle & xtpReportFreezeColsDividerShade) != 0);
	
}


void CGridSampleView::OnFilePrintPreview()
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	// In derived classes, implement special window handling here
	// Be sure to Unhook Frame Window close if hooked.
	
	// must not create this on the frame.  Must outlive this function
	CPrintPreviewState* pState = new CPrintPreviewState;
	
	// DoPrintPreview's return value does not necessarily indicate that
	// Print preview succeeded or failed, but rather what actions are necessary
	// at this point.  If DoPrintPreview returns TRUE, it means that
	// OnEndPrintPreview will be (or has already been) called and the
	// pState structure will be/has been deleted.
	// If DoPrintPreview returns FALSE, it means that OnEndPrintPreview
	// WILL NOT be called and that cleanup, including deleting pState
	// must be done here.
	
	if ( !DoPrintPreview( XTP_IDD_PREVIEW_DIALOGBAR, this,
		RUNTIME_CLASS( CXTPPreviewView ), pState ))
	{
		// In derived classes, reverse special window handling here for
		// Preview failure case
		TRACE0( "Error: DoPrintPreview failed.\n" );
		AfxMessageBox( AFX_IDP_COMMAND_FAILURE );
		delete pState;      // preview failed to initialize, delete State now
		
	}
#else
	CXTPReportView::OnFilePrintPreview();
#endif
}

void CGridSampleView::OnReportWYSIWYG()
{
	m_bWYSIWYG = !m_bWYSIWYG;

	CXTPReportControl& wndReport = GetReportCtrl();

	wndReport.GetPaintManager()->SetColumnWidthWYSIWYG(m_bWYSIWYG);
	
	if (m_bWYSIWYG)
		wndReport.GetColumns()->GetGroupsOrder()->Clear();

	m_pPrintOptions->m_bRepeatFooterRows = TRUE;
	m_pPrintOptions->m_bRepeatHeaderRows = TRUE;

	wndReport.RedrawControl();
}

void CGridSampleView::OnUpdateReportWYSIWYG(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_bWYSIWYG);
}

void CGridSampleView::OnReportIconview()
{
	CXTPReportControl& wndReport = GetReportCtrl();

	wndReport.AssignIconViewPropNumAndIconNum(3, 3, TRUE, 25);

	wndReport.SetIconView(!wndReport.IsIconView());
}

void CGridSampleView::OnUpdateReportIconview(CCmdUI *pCmdUI)
{
	CXTPReportControl& wndReport = GetReportCtrl();
	pCmdUI->SetCheck(wndReport.IsIconView());
}


/////////////////////////////////////////////////////////////////////////////
// Report behavior
/////////////////////////////////////////////////////////////////////////////

void CGridSampleView::OnBehaviorCodejockDefault()
{
	m_behavior = xtpReportBehaviorCodejockDefault;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorCodejockDefault);
}

void CGridSampleView::OnBehaviorCodejock1502()
{
	m_behavior = xtpReportBehaviorCodejock1502;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorCodejock1502);
}

void CGridSampleView::OnBehaviorOutlook2003()
{
	m_behavior = xtpReportBehaviorOutlook2003;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorOutlook2003);
}

void CGridSampleView::OnBehaviorOutlook2007()
{
	m_behavior = xtpReportBehaviorOutlook2007;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorOutlook2007);
}

void CGridSampleView::OnBehaviorOutlook2010()
{
	m_behavior = xtpReportBehaviorOutlook2010;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorOutlook2010);
}

void CGridSampleView::OnBehaviorExcel2003()
{
	m_behavior = xtpReportBehaviorExcel2003;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorExcel2003);
}

void CGridSampleView::OnBehaviorExcel2007()
{
	m_behavior = xtpReportBehaviorExcel2007;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorExcel2007);
}

void CGridSampleView::OnBehaviorExcel2010()
{
	m_behavior = xtpReportBehaviorExcel2010;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorExcel2010);
}

void CGridSampleView::OnBehaviorCustom()
{
	m_behavior = 100;
	GetReportCtrl().GetBehavior()->SetScheme(xtpReportBehaviorOutlook2003);
	GetReportCtrl().GetBehavior()->Row->MouseUp->Right->None->bFocusRowTemporarily = FALSE;
}


void CGridSampleView::OnUpdateBehaviorCodejockDefault(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorCodejockDefault == m_behavior ? 1 : 0);
}

void CGridSampleView::OnUpdateBehaviorCodejock1502(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorCodejock1502 == m_behavior ? 1 : 0);
}

void CGridSampleView::OnUpdateBehaviorOutlook2003(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorOutlook2003 == m_behavior ? 1 : 0);
}

void CGridSampleView::OnUpdateBehaviorOutlook2007(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorOutlook2007 == m_behavior ? 1 : 0);
}

void CGridSampleView::OnUpdateBehaviorOutlook2010(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorOutlook2010 == m_behavior ? 1 : 0);
}

void CGridSampleView::OnUpdateBehaviorExcel2003(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorExcel2003 == m_behavior ? 1 : 0);
}

void CGridSampleView::OnUpdateBehaviorExcel2007(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorExcel2007 == m_behavior ? 1 : 0);
}

void CGridSampleView::OnUpdateBehaviorExcel2010(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(xtpReportBehaviorExcel2010 == m_behavior ? 1 : 0);
}

void CGridSampleView::OnUpdateBehaviorCustom(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(100 == m_behavior ? 1 : 0);
}



/////////////////////////////////////////////////////////////////////////////

void CGridSampleView::OnReportLockExpand()
{
	GetReportCtrl().LockExpand(!GetReportCtrl().IsLockExpand());
	GetReportCtrl().RedrawControl();
}

void CGridSampleView::OnUpdateReportLockExpand(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(GetReportCtrl().IsLockExpand() ? 1 : 0);
}

/////////////////////////////////////////////////////////////////////////////
// Watermark
/////////////////////////////////////////////////////////////////////////////

void CGridSampleView::OnReportWatermark()
{
	CXTPReportControl &wndReport = GetReportCtrl();

	if (NULL == wndReport.GetWatermarkBitmap())
	{
		CBitmap bmpWatermark;

		if (bmpWatermark.LoadBitmap(IDB_CODEJOCKGEAR))
		{
			wndReport.SetWatermarkBitmap(bmpWatermark, 64);
			wndReport.SetWatermarkAlignment(xtpReportWatermarkCenter | xtpReportWatermarkVCenter);
			wndReport.GetPaintManager()->m_bPrintWatermark = TRUE;
		}
	}
	else
	{
		wndReport.SetWatermarkBitmap(HBITMAP(NULL), 0);
		wndReport.GetPaintManager()->m_bPrintWatermark = FALSE;
	}

	wndReport.RedrawControl();
}

void CGridSampleView::OnUpdateReportWatermark(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(NULL == GetReportCtrl().GetWatermarkBitmap() ? 0 : 1);
}

/////////////////////////////////////////////////////////////////////////////
// Double buffering
/////////////////////////////////////////////////////////////////////////////

void CGridSampleView::OnReportDoubleBuffering()
{
	CXTPReportControl &wndReport = GetReportCtrl();
	wndReport.EnableDoubleBuffering(!wndReport.IsDoubleBuffering());
	wndReport.RedrawControl();
}

void CGridSampleView::OnUpdateReportDoubleBuffering(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(GetReportCtrl().IsDoubleBuffering() ? 1 : 0);
}

/////////////////////////////////////////////////////////////////////////////
// Smooth scrolling
/////////////////////////////////////////////////////////////////////////////

void CGridSampleView::OnReportSmoothScrolling()
{
	CXTPReportControl &wndReport = GetReportCtrl();

	BOOL bSmooth = xtpReportScrollModeSmooth == wndReport.GetScrollMode(xtpReportOrientationVertical);

	if (bSmooth)
	{
		wndReport.SetScrollMode(xtpReportOrientationVertical, xtpReportScrollModeBlock);
	}
	else
	{
		wndReport.SetScrollMode(xtpReportOrientationVertical, xtpReportScrollModeSmooth);
	
	}
}

void CGridSampleView::OnUpdateReportSmoothScrolling(CCmdUI *pCmdUI)
{
	CXTPReportControl &wndReport = GetReportCtrl();

	BOOL bSmooth = xtpReportScrollModeSmooth == wndReport.GetScrollMode(xtpReportOrientationVertical);
	
	pCmdUI->Enable(TRUE);
	pCmdUI->SetCheck(bSmooth);
}
