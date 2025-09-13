// DialogControlsTest.cpp
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
#include "FlowGraphSample.h"
#include "DialogControlsTest.h"


class CCustomDrawWindowNode : public CXTPFlowGraphNode
{
	virtual void DrawWindowContent(CXTPFlowGraphDrawContext* pDC);
};

void CCustomDrawWindowNode::DrawWindowContent(CXTPFlowGraphDrawContext* pDC)
{
	CRect rc(m_rcWindow);
	rc.OffsetRect(m_ptLocation);

	pDC->SetPen(RGB(0, 0, 0), 0);
	pDC->SetBrush(clrOfficeColors[4]);
	pDC->Ellipse(rc);
}


// CDialogControlsTest dialog

IMPLEMENT_DYNAMIC(CDialogControlsTest, CDialog)

CDialogControlsTest::CDialogControlsTest(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogControlsTest::IDD, pParent)
{

}

CDialogControlsTest::~CDialogControlsTest()
{
}

void CDialogControlsTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRAPHCONTROL, m_wndControl);
}


BEGIN_MESSAGE_MAP(CDialogControlsTest, CDialog)
END_MESSAGE_MAP()


// CDialogControlsTest message handlers

BOOL CDialogControlsTest::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_wndControl.ModifyStyle(0, WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	if (!m_wndTreeCtrl.Create( WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | WS_CHILD,
		CRect(0,0,0,0), &m_wndControl, 0xFF ))
	{
		TRACE0( "Unable to create tree control.\n" );
		return 0;
	}
	// Add the parent item
	HTREEITEM htItem = m_wndTreeCtrl.InsertItem(_T("Root Item"));
	m_wndTreeCtrl.SetItemState( htItem, TVIS_BOLD, TVIS_BOLD );

	// Add children
	m_wndTreeCtrl.InsertItem(_T("Child Item 1"), 3, 3, htItem);
	m_wndTreeCtrl.InsertItem(_T("Child Item 2"), 4, 4, htItem);


	if (!m_wndListView.Create(WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CHILD | WS_VISIBLE| LVS_AUTOARRANGE,
		CRect(0,0,0,0), &m_wndControl, 0xFF ))
	{
		TRACE0( "Unable to create tree control.\n" );
		return 0;
	}
	m_wndListView.InsertItem (0, _T("Item 1"), 0); 
	m_wndListView.InsertItem (1, _T("Item 2"), 0);
	m_wndListView.InsertItem (2, _T("Item 3"), 0);


	CXTPFlowGraphPage* pPage = m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());

	CXTPFlowGraphNode* pNode = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());

	pNode->SetCaption(_T("Tree Control"));
	pNode->SetColor(clrOfficeColors[1]);
	pNode->SetLocation(XTP_DPI(CPoint(20, 50)));
	
	pNode->SetWindowHandle(m_wndTreeCtrl);
	pNode->SetWindowSize(XTP_DPI(CSize(80, 100)));

	pNode->AddNamedConnectionPoints(_T("Item 1"), xtpFlowGraphPointInputAndOutput);
	pNode->AddNamedConnectionPoints(_T("Item 2"), xtpFlowGraphPointInputAndOutput);

	pNode = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pNode->SetCaption(_T("List View"));
	pNode->SetColor(clrOfficeColors[2]);
	pNode->SetLocation(XTP_DPI(CPoint(200, 50)));
	pNode->SetWindowHandle(m_wndListView);
	pNode->SetWindowSize(XTP_DPI(CSize(100, 100)));

	pNode->AddNamedConnectionPoints(_T("Item 1"), xtpFlowGraphPointInputAndOutput);
	pNode->AddNamedConnectionPoints(_T("Item 2"), xtpFlowGraphPointInputAndOutput);

	pNode = pPage->GetNodes()->AddNode(new CCustomDrawWindowNode());
	pNode->SetCaption(_T("Other node"));
	pNode->SetColor(clrOfficeColors[3]);
	pNode->SetLocation(XTP_DPI(CPoint(350, 50)));
	
	pNode->AddNamedConnectionPoints(_T("Item 1"), xtpFlowGraphPointInputAndOutput);
	pNode->AddNamedConnectionPoints(_T("Item 2"), xtpFlowGraphPointInputAndOutput);
	pNode->AddNamedConnectionPoints(_T("First Name"));
	pNode->AddNamedConnectionPoints(_T("Last Name"));
	pNode->AddNamedConnectionPoints(_T("Address"));
	pNode->AddNamedConnectionPoints(_T("Work Phone"));
	pNode->AddNamedConnectionPoints(_T("Cell Phone"));

	CXTPFlowGraphConnection* pConnection;
	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	
	pConnection->SetInputPoint(pPage->GetNodes()->GetAt(0)->GetConnectionPoints()->FindConnectionPoint(_T("Item 1"), xtpFlowGraphPointInput));
	pConnection->SetOutputPoint(pPage->GetNodes()->GetAt(1)->GetConnectionPoints()->FindConnectionPoint(_T("Item 2"), xtpFlowGraphPointOutput));
	
	m_wndControl.SetActivePage(pPage);

	m_wndControl.SetZoomRange(1, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
