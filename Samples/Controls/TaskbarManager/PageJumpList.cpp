// PageJumpList.cpp
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
#include "TaskbarManager.h"
#include "PageJumpList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageJumpList property page

IMPLEMENT_DYNCREATE(CPageJumpList, CPropertyPage)

CPageJumpList::CPageJumpList() : CPropertyPage(CPageJumpList::IDD)
{
	//{{AFX_DATA_INIT(CPageJumpList)
	m_strPath = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
}

CPageJumpList::~CPageJumpList()
{
}

void CPageJumpList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageJumpList)
	DDX_Control(pDX, IDC_LIST_TASK, m_lboxTaskList);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strPath);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageJumpList, CPropertyPage)
	//{{AFX_MSG_MAP(CPageJumpList)
	ON_LBN_SELCHANGE(IDC_LIST_TASK, OnSelchangeEditList)
	ON_EN_CHANGE(IDC_EDIT_PATH, UpdateTaskData)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_EDIT_TITLE, UpdateTaskData)
	ON_BN_CLICKED(IDC_BUTTON_COMMIT, OnButtonCommit)
	//}}AFX_MSG_MAP

	ON_LBN_XTP_LABELEDITEND(IDC_LIST_TASK, OnLabelEditEnd)
	ON_LBN_XTP_LABELEDITCANCEL(IDC_LIST_TASK, OnLabelEditCancel)
	ON_LBN_XTP_NEWITEM(IDC_LIST_TASK, OnNewItem)
	ON_LBN_XTP_PREDELETEITEM(IDC_LIST_TASK, OnPreDeleteItem)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageJumpList message handlers

void CPageJumpList::AddTask(LPCTSTR lpszTitle, LPCTSTR lpszPath)
{
	CTaskRec* pRec = new CTaskRec;
	pRec->m_strTitle = lpszTitle;
	pRec->m_strPath = lpszPath;

	int nIndex = m_lboxTaskList.AddString(pRec->m_strTitle);
	m_lboxTaskList.SetItemData(nIndex, (DWORD_PTR)pRec);

}

BOOL CPageJumpList::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	
	m_lboxTaskList.Initialize(TRUE);
	m_lboxTaskList.SetListEditStyle( _T(" &Task List:"), LBS_XTP_DEFAULT);


	AddTask(_T("Notepad"), _T("notepad.exe"));
	AddTask(_T("Paint"), _T("mspaint.exe"));
	AddTask(_T("Explorer"), _T("explorer.exe"));
	
	m_lboxTaskList.SetCurSel( 0 );
	OnSelchangeEditList( );

	OnButtonCommit();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageJumpList::OnSelchangeEditList() 
{
	int iIndex = m_lboxTaskList.GetCurSel( );
	if ( iIndex == LB_ERR )
	{
		m_strPath = _T( "" );
		m_strTitle = _T( "" );
	}
	else if ( iIndex >= m_lboxTaskList.GetCount( ) )
	{
		return;
	}
	else
	{
		CTaskRec* pTool = ( CTaskRec* )m_lboxTaskList.GetItemData( iIndex );
		if ( pTool == NULL )
		{
			return;
		}
		
		m_strPath = pTool->m_strPath;
		m_strTitle = pTool->m_strTitle;
	}
	
	UpdateData( FALSE );
	
}


void CPageJumpList::UpdateTaskData()
{
	UpdateData();
	
	// get the index of the currently selected item.
	int iItem = m_lboxTaskList.GetCurSel( );
	if ( iItem == LB_ERR )
	{
		return;
	}
	
	// get a pointer to the item data for the selection.
	CTaskRec* pTool = ( CTaskRec* )m_lboxTaskList.GetItemData( iItem );
	if ( pTool != NULL )
	{
		pTool->m_strTitle = m_strTitle;
		pTool->m_strPath = m_strPath;
	}
}



void CPageJumpList::OnLabelEditEnd()
{
	
	int iIndex = m_lboxTaskList.GetCurrentIndex( );
	CTaskRec* pTool = ( CTaskRec* )m_lboxTaskList.GetItemData( iIndex );
	if ( pTool != NULL )
	{
		CString strText;
		m_lboxTaskList.GetText( iIndex, strText );
		
		pTool->m_strTitle = strText;
		m_lboxTaskList.SetCurSel( iIndex );
	}
}

void CPageJumpList::OnLabelEditCancel()
{
	m_lboxTaskList.SetCurSel(
		m_lboxTaskList.GetCurrentIndex( ) );
}


void CPageJumpList::OnNewItem()
{
	int iItem = m_lboxTaskList.GetCurrentIndex( );
	if ( iItem != -1 )
	{
		CString strTitle;
		m_lboxTaskList.GetText( iItem, strTitle );
		
		CTaskRec* pTool = new CTaskRec();
		pTool->m_strTitle = strTitle;
		
		m_lboxTaskList.SetCurSel( iItem );
		
		m_strPath = _T("");
		m_strTitle = strTitle;
		
		m_lboxTaskList.SetItemData( iItem, (DWORD_PTR)pTool);
		
		UpdateData( FALSE );
	}
}

void CPageJumpList::OnPreDeleteItem()
{
	int iIndex = m_lboxTaskList.GetCurSel( );
	if ( iIndex == LB_ERR )
		return;
	
	delete ( CTaskRec* )m_lboxTaskList.GetItemData( iIndex );
}


void CPageJumpList::OnDestroy() 
{	
	for (int i = 0; i < m_lboxTaskList.GetCount( ); ++i )
	{
		CTaskRec* pOldTool = ( CTaskRec* )m_lboxTaskList.GetItemData( i );
		if ( pOldTool == NULL )
			continue;
		
		delete pOldTool;
	}
	
	m_lboxTaskList.ResetContent();


	CPropertyPage::OnDestroy();
	
}

void CPageJumpList::OnButtonCommit() 
{
	m_mgrTaskbar.GetJumpList()->Clear();


	for (int i = 0; i < m_lboxTaskList.GetCount( ); ++i )
	{
		CTaskRec* pOldTool = ( CTaskRec* )m_lboxTaskList.GetItemData( i );
		if ( pOldTool == NULL )
			continue;
		
		m_mgrTaskbar.GetJumpList()->AddTask(pOldTool->m_strPath, NULL, pOldTool->m_strTitle, NULL, 0);
	}	
	
	m_mgrTaskbar.GetJumpList()->CommitList();
}
