// FlowGraphSampleView.cpp
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

#include "FlowGraphSampleDoc.h"
#include "FlowGraphSampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const UINT ID_FLOWGRAPH_CONTROL = 100;

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView

IMPLEMENT_DYNCREATE(CFlowGraphSampleView, CView)

BEGIN_MESSAGE_MAP(CFlowGraphSampleView, CView)
	//{{AFX_MSG_MAP(CFlowGraphSampleView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_EDIT_SELECT_ALL, OnEditSelectAll)
	ON_COMMAND(ID_FLOWGRAPH_SHOWNODEGROUPSALWAYS, OnFlowgraphShowNodegroupsAlways)
	ON_UPDATE_COMMAND_UI(ID_FLOWGRAPH_SHOWNODEGROUPSALWAYS, OnUpdateFlowgraphShowNodegroupsAlways)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)

	ON_COMMAND(ID_FILE_SAVEASIMAGE, OnSaveToFile)

#ifdef _XTP_INCLUDE_COMMANDBARS
	ON_NOTIFY(XTP_SBN_SCROLL, ID_INDICATOR_ZOOMSLIDER, OnZoomSliderScroll)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_ZOOM, OnUpdateViewZoom)
#endif

	ON_COMMAND(ID_VIEW_ZOOM_TOSELECTION, OnZoomToSelection)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ZOOM_TOSELECTION, OnUpdateHasSelection)
	ON_COMMAND(ID_VIEW_ZOOM_FITWINDOW, OnZoomFitToWindow)

	ON_COMMAND(ID_EDIT_ARRANGE, OnEditArrange)

	ON_NOTIFY(NM_RCLICK, ID_FLOWGRAPH_CONTROL, OnGraphRClick)

	ON_NOTIFY(XTP_FGN_SELECTIONCHANGED, ID_FLOWGRAPH_CONTROL, OnSelectionChanged)

	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_UPDATE_COMMAND_UI(ID_EDIT_COPY, OnUpdateEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)

	ON_COMMAND(ID_DIAGRAMS_DATABASERELATIONS, OnSwitchGraphType0)
	ON_COMMAND(ID_DIAGRAMS_NETWORKDIAGRAM, OnSwitchGraphType1)
	ON_COMMAND(ID_DIAGRAMS_FLOWCHART, OnSwitchGraphType2)

	ON_COMMAND(ID_FLOWGRAPH_SHOWGRID, OnShowGrid)
	ON_UPDATE_COMMAND_UI(ID_FLOWGRAPH_SHOWGRID, OnUpdateShowGrid)

	ON_COMMAND_RANGE(ID_FLOWGRAPH_CONNECTOR_TYPE_0, ID_FLOWGRAPH_CONNECTOR_TYPE_8, OnConnectorType)
	ON_UPDATE_COMMAND_UI_RANGE(ID_FLOWGRAPH_CONNECTOR_TYPE_0, ID_FLOWGRAPH_CONNECTOR_TYPE_8, OnUpdateConnectorType)
	
	ON_COMMAND_RANGE(ID_FLOWGRAPH_QUALITY_HIGHQUALITY, ID_FLOWGRAPH_QUALITY_AUTOQUALITY, OnQuality)
	ON_UPDATE_COMMAND_UI_RANGE(ID_FLOWGRAPH_QUALITY_HIGHQUALITY, ID_FLOWGRAPH_QUALITY_AUTOQUALITY, OnUpdateQuality)

	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_UPDATE_COMMAND_UI(ID_EDIT_DELETE, OnUpdateEditDelete)

#ifdef _XTP_INCLUDE_TASKPANEL
	ON_MESSAGE(XTPWM_TASKPANEL_NOTIFY, OnTaskPanelNotify)
#endif

#ifdef _XTP_INCLUDE_PROPERTYGRID
	ON_MESSAGE(XTPWM_PROPERTYGRID_NOTIFY, OnPropertyGridNotify)
#endif

END_MESSAGE_MAP()

//#define RGBA(r, g, b, a) ((COLORREF) (((a) << 24) | ((b) << 16) | ((g) << 8) | (r)))

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView construction/destruction

CFlowGraphSampleView::CFlowGraphSampleView() 
	: m_pGrid(NULL)
{
}

CFlowGraphSampleView::~CFlowGraphSampleView()
{
}

BOOL CFlowGraphSampleView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView drawing

void CFlowGraphSampleView::OnDraw(CDC* /*pDC*/)
{
	CFlowGraphSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}



/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView printing

void CFlowGraphSampleView::OnPrint(CDC* pDC, CPrintInfo*)
{
	CFlowGraphSampleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CXTPFlowGraphDrawContextGdiPlus dc(pDC->m_hDC, pDC->m_hAttribDC, TRUE);
	m_wndControl.OnDraw(&dc);
}

BOOL CFlowGraphSampleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	pInfo->m_nNumPreviewPages = 1;
	pInfo->SetMinPage(1);
	pInfo->SetMaxPage(1);
	
	
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFlowGraphSampleView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	if (!pInfo)
		return;
	
	pDC->SetMapMode(MM_ANISOTROPIC);
	
	pDC->SetViewportExt(pDC->GetDeviceCaps(LOGPIXELSX),	pDC->GetDeviceCaps(LOGPIXELSY));
	
	pDC->SetWindowExt(96, 96);
	
	// ptOrg is in logical coordinates
	pDC->OffsetWindowOrg(0, 0);
	
}


void CFlowGraphSampleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFlowGraphSampleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFlowGraphSampleView::OnFilePrintPreview()
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
	CView::OnFilePrintPreview();
#endif

}

void CFlowGraphSampleView::OnSaveToFile()
{
	CString strFilter = _T("PNG Files(*.png)|*.png|GIF Files(*.gif)|*.gif|JPG Files(*.jpg)|*.jpg|Bitmap Files(*.bmp)|*.bmp|All files (*.*)|*.*||");
	CFileDialog fd(FALSE, _T("xml"), NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, strFilter);
	if (fd.DoModal() == IDOK)
	{
		m_wndControl.SaveToFile(fd.GetPathName());
	}
	
}

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView diagnostics

#ifdef _DEBUG
void CFlowGraphSampleView::AssertValid() const
{
	CView::AssertValid();
}

void CFlowGraphSampleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFlowGraphSampleDoc* CFlowGraphSampleView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFlowGraphSampleDoc)));
	return (CFlowGraphSampleDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFlowGraphSampleView message handlers

COLORREF clrOfficeColors[] = 
{
	RGB( 79, 129, 189), // Blue
	RGB(192,  80,  77), // Red
	RGB(155, 187,  89), // Green
	RGB(128, 100, 162), // Purple
	RGB( 75, 172, 198), // Aqua
	RGB(247, 150,  70), // Orange
	RGB( 31,  73, 125)
}; 

void CFlowGraphSampleView::InsertNewShape(FG_SHAPES_ID id, CPoint point, UINT uResShapeID)
{
	if (id == -1)
		return;

	CXTPFlowGraphNode *pNode = NULL;
	CXTPFlowGraphNodeCustom *pNodeCustom = NULL;

	if (id != FG_SHAPE_CUSTOM)
		m_wndControl.GetUndoManager()->StartGroup();

	point = m_wndControl.TransformPoint(point);

	switch (id)
	{
		case FG_SHAPE_TABLE:
		{
			pNode = m_wndControl.GetActivePage()->GetNodes()->AddNode(new CXTPFlowGraphNode());
			pNode->SetLocation(point);
			pNode->SetCaption(_T("New Node"));
			
			pNode->AddNamedConnectionPoints( _T("Output"), xtpFlowGraphPointOutput);
			pNode->AddNamedConnectionPoints( _T("Input"), xtpFlowGraphPointInput);

			break;
		}
		case FG_SHAPE_PICTURE:
		{
			CXTPFlowGraphNodeCustom* pImage = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_IMAGE, point, 
				XTP_DPI(CSize(128, 128)));

			pImage->SetImageIndex(2);
			pImage->SetCaptionPosition(xtpFlowGraphCustomNodeCaptionBelow);
			pImage->SetCaption(_T("Firewall"));

			pNode = pImage;

			break;
		}

		case FG_SHAPE_FROM_RESOURCE:
		{
			pNodeCustom = AddCustomFlowGraphShape(m_wndControl, uResShapeID, point, XTP_DPI(CSize(150, 110)));

			break;
		}

		case FG_SHAPE_USERCARD:
		{
			CStringList list;

			if (rand() % 2)
			{
				list.AddTail(_T("Sarah Haras"));
				list.AddTail(_T("Lunch"));
				list.AddTail(_T("CJ Diner"));
				list.AddTail(_T("Kitchen Remodel"));
				list.AddTail(_T("15 min"));
				list.AddTail(_T("10"));
			}
			else
			{
				list.AddTail(_T("John Doe"));
				list.AddTail(_T("Consulting"));
				list.AddTail(_T("Plant 2"));
				list.AddTail(_T("Chart Support"));
				list.AddTail(_T("18 Hours"));
				list.AddTail(_T("9"));
			}

			CString xaml;
			XTPResourceManager()->LoadHTML(&xaml, _T("USERCARD_XAML"));
			
			pNodeCustom = AddUserCardNode(m_wndControl, xaml, point, XTP_DPI(CSize(340, 172)), list);
		
			break;
		}

		case FG_SHAPE_CUSTOM:
		{
			if (!m_wndControl.GetActivePage())
				return;

			CXTPFlowGraphNodeCustom *pNode = NULL;
			
			CString xaml = _T("<Canvas xmlns='http://schemas.microsoft.com/winfx/2006/xaml/presentation' ")
				_T("xmlns:x='http://schemas.microsoft.com/winfx/2006/xaml' x:Name='nodeCanvas' Width='100' Height='100'>")
				_T("<Path x:Name='nodePath' Stretch='Fill' Width='100' Height='100' Stroke='Black' ")
				_T("Data='M 0,0 L 200,0 L 200,100 L 300,100 L 300,200 L 100,200 L 100,100 L 0,100 Z'>")
				_T("</Path><TextBlock x:Name='nodeCaption'/></Canvas>");
			
			ASSERT(xaml.GetLength());
			
			m_wndControl.GetUndoManager()->StartGroup();
			
			pNode = m_wndControl.GetActivePage()->GetNodes()->AddCustomNode();
					
			pNode->SetMarkupText(xaml);
			pNode->SetCaption(_T("Z-Shape"));
			pNode->SetTooltip(_T("Z-Shape"));
			pNode->SetLocation(point);
			pNode->SetSize(XTP_DPI(CSize(150, 110)));
			pNode->SetColor(RGB(255, 0, 0), 128);

			m_wndControl.GetUndoManager()->EndGroup();
			
			return;
		}
	}

	if (pNodeCustom)
	{
		COLORREF clr = clrOfficeColors[rand() % 7];
		COLORREF clr2 = m_wndControl.GetPaintManager()->GetDarkColor(clr);

		pNodeCustom->SetColor(clr, clr2, xtpFlowGraphCustomNodeFillGradientCenterVertical);
	}

	m_wndControl.GetUndoManager()->EndGroup();

	CXTPFlowGraphSelectedElements *pSelection = m_wndControl.GetActivePage()->GetSelection();

	if (pNode && pSelection)
		pSelection->SetSelection(pNode);
}

BOOL CFlowGraphSampleView::OnDrop(COleDataObject* pDataObject, DROPEFFECT /*dropEffect*/, CPoint point )
{
#ifdef _XTP_INCLUDE_TASKPANEL

	CXTPTaskPanelItem *pItemDrag = CXTPTaskPanelItem::CreateFromOleData(pDataObject);

	if (pItemDrag)
	{
		InsertNewShape((FG_SHAPES_ID)pItemDrag->GetID(), point, (UINT)pItemDrag->GetItemData());

		pItemDrag->InternalRelease();
		pItemDrag = NULL;
	}

#endif

	return TRUE;
}

DROPEFFECT CFlowGraphSampleView::OnDragOver(COleDataObject* pDataObject, DWORD /*dwKeyState*/, CPoint /*point*/)
{
	DROPEFFECT retReflect = DROPEFFECT_NONE;

#ifdef _XTP_INCLUDE_TASKPANEL

	CXTPTaskPanelItem *pItemDrag = CXTPTaskPanelItem::CreateFromOleData(pDataObject);

	if (pItemDrag)
	{
		if (pItemDrag->GetID() > xtpFlowGraphConnectorElbowDoubleArrow)
			retReflect = DROPEFFECT_COPY;

		pItemDrag->InternalRelease();
		pItemDrag = NULL;
	}

#endif

	return retReflect;
}

DROPEFFECT CFlowGraphSampleView::OnDragEnter(COleDataObject* pDataObject, DWORD /*dwKeyState*/, CPoint /*point*/)
{
	DROPEFFECT retReflect = DROPEFFECT_NONE;

#ifdef _XTP_INCLUDE_TASKPANEL

	CXTPTaskPanelItem *pItemDrag = CXTPTaskPanelItem::CreateFromOleData(pDataObject);

	if (pItemDrag)
	{
		if (pItemDrag->GetID() > xtpFlowGraphConnectorElbowDoubleArrow)
			retReflect = DROPEFFECT_COPY;

		pItemDrag->InternalRelease();
		pItemDrag = NULL;
	}

#endif

	return retReflect;
}

void CFlowGraphSampleView::InitFlowGraphImages()
{
	// 0
	CXTPFlowGraphImage* pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), IDB_NODEIMAGE_CUSTOMERS);

	// 1
	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_ORDERDETAILS), _T("PNG"));

	// 2
	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_FIREWALL), _T("PNG"));

	// 3
	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_CLOUD), _T("PNG"));

	// 4
	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_DESKTOP), _T("PNG"));

	// 5
	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_LAPTOP), _T("PNG"));

	// 6
	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_PHONE), _T("PNG"));

	// 7
	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_TABLET), _T("PNG"));

	// 8
	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_DEVICE), _T("PNG"));

	// 9
	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_JOHN), _T("PNG"));

	// 10
	pImage = m_wndControl.GetImages()->AddImage(new CXTPFlowGraphImage());
	pImage->LoadFromResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_NODEIMAGE_SARAH), _T("PNG"));
}

void CFlowGraphSampleView::CreateDatabaseRelationships()
{
	m_wndControl.GetPaintManager()->m_clrConnection = RGB(255,80,60);

	CXTPFlowGraphPage* pPage = m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());
	
	// Customers

	CXTPFlowGraphNode* pTableCustomers = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());

	pTableCustomers->AddNamedConnectionPoints(_T("ID"), xtpFlowGraphPointInput);
	pTableCustomers->AddNamedConnectionPoints(_T("Company"));
	pTableCustomers->AddNamedConnectionPoints(_T("Last Name"));
	pTableCustomers->AddNamedConnectionPoints(_T("First Name"));
	pTableCustomers->AddNamedConnectionPoints(_T("Job Title"));
	pTableCustomers->AddNamedConnectionPoints(_T("Business Phone"));

	pTableCustomers->SetCaption(_T("Customers"));
	pTableCustomers->SetTooltip(_T("Customers Table"));
	pTableCustomers->SetColor(clrOfficeColors[2]);
	pTableCustomers->SetLocation(XTP_DPI(CPoint(720, 360)));
	pTableCustomers->SetImageIndex(0);

	// Orders

	CXTPFlowGraphNode* pTableOrders = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableOrders->SetCaption(_T("Orders"));
	pTableOrders->SetTooltip(_T("Orders Table"));
	pTableOrders->SetLocation(XTP_DPI(CPoint(320, 90)));
	//pTableOrders->SetColor(clrOfficeColors[1]);

	pTableOrders->AddNamedConnectionPoints(_T("Order ID"), xtpFlowGraphPointInput);
	pTableOrders->AddNamedConnectionPoints(_T("Employee ID"), xtpFlowGraphPointOutput);
	pTableOrders->AddNamedConnectionPoints(_T("Customer ID"), xtpFlowGraphPointOutput);
	pTableOrders->AddNamedConnectionPoints(_T("Order Date"));
	pTableOrders->AddNamedConnectionPoints(_T("Shipped Date"));
	pTableOrders->AddNamedConnectionPoints(_T("Shipper ID"), xtpFlowGraphPointOutput);
	pTableOrders->AddNamedConnectionPoints(_T("Taxes"));
	pTableOrders->AddNamedConnectionPoints(_T("Payment Type"));
	pTableOrders->AddNamedConnectionPoints(_T("Paid Date"));
	pTableOrders->AddNamedConnectionPoints(_T("Notes"));

	// Employees

	CXTPFlowGraphNode* pTableEmployees = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableEmployees->SetCaption(_T("Employees"));
	pTableEmployees->SetTooltip(_T("Employees Table"));
	pTableEmployees->SetLocation(XTP_DPI(CPoint(720, 90)));
	pTableEmployees->SetColor(clrOfficeColors[4]);

	pTableEmployees->AddNamedConnectionPoints(_T("ID"), xtpFlowGraphPointInput);
	pTableEmployees->AddNamedConnectionPoints(_T("Company"));
	pTableEmployees->AddNamedConnectionPoints(_T("Last Name"));
	pTableEmployees->AddNamedConnectionPoints(_T("First Name"));
	pTableEmployees->AddNamedConnectionPoints(_T("E-mail Address"));
	pTableEmployees->AddNamedConnectionPoints(_T("Job Title"));
	pTableEmployees->AddNamedConnectionPoints(_T("Business Phone"));

	// Order Details

	CXTPFlowGraphNode* pTableOrderDetails = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableOrderDetails->SetCaption(_T("Order Details"));
	pTableOrderDetails->SetTooltip(_T("Order Details Table"));
	pTableOrderDetails->SetLocation(XTP_DPI(CPoint(90, 200)));
	pTableOrderDetails->SetColor(clrOfficeColors[1]);
	pTableOrderDetails->SetImageIndex(1);

	pTableOrderDetails->AddNamedConnectionPoints(_T("ID"), xtpFlowGraphPointInput);
	pTableOrderDetails->AddNamedConnectionPoints(_T("Order ID"), xtpFlowGraphPointOutput);
	pTableOrderDetails->AddNamedConnectionPoints(_T("Product ID"), xtpFlowGraphPointOutput);
	pTableOrderDetails->AddNamedConnectionPoints(_T("Quantity"));
	pTableOrderDetails->AddNamedConnectionPoints(_T("Unit Price"));
	pTableOrderDetails->AddNamedConnectionPoints(_T("Discount"));
	pTableOrderDetails->AddNamedConnectionPoints(_T("Status ID"));

	// apply some colors to connection points

	pTableOrders->GetConnectionPoints()->FindConnectionPoint(_T("Order ID"))->SetColor(RGB(0,0,255));
	pTableOrderDetails->GetConnectionPoints()->FindConnectionPoint(_T("Order ID"))->SetColor(RGB(0,0,255));

	// Shippers

	CXTPFlowGraphNode* pTableShippers = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableShippers->SetCaption(_T("Shippers"));
	pTableShippers->SetTooltip(_T("Shippers Table"));
	pTableShippers->SetLocation(XTP_DPI(CPoint(520, 360)));
	//pTableShippers->SetColor(clrOfficeColors[3]);

	pTableShippers->AddNamedConnectionPoints(_T("ID"), xtpFlowGraphPointInput);
	pTableShippers->AddNamedConnectionPoints(_T("Company"));
	pTableShippers->AddNamedConnectionPoints(_T("Last Name"));
	pTableShippers->AddNamedConnectionPoints(_T("First Name"));
	pTableShippers->AddNamedConnectionPoints(_T("E-mail Address"));
	pTableShippers->AddNamedConnectionPoints(_T("Job Title"));
	pTableShippers->AddNamedConnectionPoints(_T("Business Phone"));

	// Products

	CXTPFlowGraphNode* pTableProducts = pPage->GetNodes()->AddNode(new CXTPFlowGraphNode());
	pTableProducts->SetCaption(_T("Products"));
	pTableProducts->SetTooltip(_T("Products Table"));
	pTableProducts->SetLocation(XTP_DPI(CPoint(320, 360)));
	//pTableProducts->SetColor(clrOfficeColors[4]);

	pTableProducts->AddNamedConnectionPoints(_T("ID"), xtpFlowGraphPointInput);
	pTableProducts->AddNamedConnectionPoints(_T("Product Code"));
	pTableProducts->AddNamedConnectionPoints(_T("Product Name"));
	pTableProducts->AddNamedConnectionPoints(_T("Description"));
	pTableProducts->AddNamedConnectionPoints(_T("Price"));
	pTableProducts->AddNamedConnectionPoints(_T("Category"));

	// Manage connections

	CXTPFlowGraphConnection* pConnection;
	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pTableOrders->GetConnectionPoints()->FindConnectionPoint(_T("Customer ID")));
	pConnection->SetInputPoint(pTableCustomers->GetConnectionPoints()->FindConnectionPoint(_T("ID")));

	pConnection->SetStyle(xtpFlowGraphConnectorCurvedDoubleArrow);
	pConnection->SetCaption(_T("Customer relations"));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pTableOrders->GetConnectionPoints()->FindConnectionPoint(_T("Shipper ID")));
	pConnection->SetInputPoint(pTableShippers->GetConnectionPoints()->FindConnectionPoint(_T("ID")));
	
	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pTableOrders->GetConnectionPoints()->FindConnectionPoint(_T("Employee ID")));
	pConnection->SetInputPoint(pTableEmployees->GetConnectionPoints()->FindConnectionPoint(_T("ID")));
	pConnection->SetStyle(xtpFlowGraphConnectorElbowArrow);

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pTableOrderDetails->GetConnectionPoints()->FindConnectionPoint(_T("Order ID")));
	pConnection->SetInputPoint(pTableOrders->GetConnectionPoints()->FindConnectionPoint(_T("Order ID")));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pTableOrderDetails->GetConnectionPoints()->FindConnectionPoint(_T("Product ID")));
	pConnection->SetInputPoint(pTableProducts->GetConnectionPoints()->FindConnectionPoint(_T("ID")));

#if 0
	CXTPFlowGraphNodeGroups* pGroups = pPage->GetGroups();
	CXTPFlowGraphNodeGroup* pGroup = pGroups->AddGroup();
	pGroup->AddNode(pTableEmployees);
	pGroup->AddNode(pTableCustomers);
#endif

	m_wndControl.SetActivePage(pPage);

}

void CFlowGraphSampleView::CreateNetworkDiagram()
{
	m_wndControl.GetPaintManager()->m_clrConnection = RGB(40,40, 150);

	CXTPFlowGraphPage* pPage = m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());

	m_wndControl.SetActivePage(pPage);
	m_wndControl.SetZoomRange(0.5, 5.0);

	CXTPFlowGraphNodeCustom* pImageCloud = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_IMAGE, 
		XTP_DPI(CPoint(400, 100)), XTP_DPI(CSize(128, 112)));

	pImageCloud->SetImageIndex(3);
	pImageCloud->SetCaptionPosition(xtpFlowGraphCustomNodeCaptionBelow);
	pImageCloud->SetCaption(_T("Cloud Data Storage"));
	pImageCloud->SetTooltip(_T("Centralized cloud storage"));

	CXTPFlowGraphNodeCustom* pImageDesktop = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_IMAGE, 
		XTP_DPI(CPoint(150, 320)), XTP_DPI(CSize(64, 64)));

	pImageDesktop->SetImageIndex(4);
	pImageDesktop->SetCaptionPosition(xtpFlowGraphCustomNodeCaptionBelow);
	pImageDesktop->SetCaption(_T("Desktop PC"));
	pImageDesktop->SetTooltip(_T("A normal desktop PC"));

	CXTPFlowGraphNodeCustom* pImageLaptop = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_IMAGE, 
		XTP_DPI(CPoint(150, 90)), XTP_DPI(CSize(64, 64)));

	pImageLaptop->SetImageIndex(5);
	pImageLaptop->SetCaptionPosition(xtpFlowGraphCustomNodeCaptionBelow);
	pImageLaptop->SetCaption(_T("Laptop"));
	pImageLaptop->SetTooltip(_T("A laptop"));

	CXTPFlowGraphNodeCustom* pImagePhone = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_IMAGE, 
		XTP_DPI(CPoint(700, 90)), XTP_DPI(CSize(64, 64)));

	pImagePhone->SetImageIndex(6);
	pImagePhone->SetCaptionPosition(xtpFlowGraphCustomNodeCaptionBelow);
	pImagePhone->SetCaption(_T("Mobile Phone"));
	pImagePhone->SetTooltip(_T("Android or iOS mobile phone"));

	CXTPFlowGraphNodeCustom* pImageTablet = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_IMAGE, 
		XTP_DPI(CPoint(700, 320)), XTP_DPI(CSize(64, 64)));

	pImageTablet->SetImageIndex(7);
	pImageTablet->SetCaptionPosition(xtpFlowGraphCustomNodeCaptionBelow);
	pImageTablet->SetCaption(_T("Tablet PC"));
	pImageTablet->SetTooltip(_T("Android or iOS tablet PC"));

	CXTPFlowGraphNodeCustom* pImageDevice = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_IMAGE, 
		XTP_DPI(CPoint(430, 320)), XTP_DPI(CSize(64, 64)));

	pImageDevice->SetImageIndex(8);
	pImageDevice->SetCaptionPosition(xtpFlowGraphCustomNodeCaptionBelow);
	pImageDevice->SetCaption(_T("Your network device"));
	pImageDevice->SetTooltip(_T("Custom network device"));

	// manage connections

	CXTPFlowGraphConnection* pConnection;
	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pImageCloud->GetConnectionPoints()->GetAt(0));
	pConnection->SetInputPoint(pImageDesktop->GetConnectionPoints()->GetAt(0));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pImageCloud->GetConnectionPoints()->GetAt(0));
	pConnection->SetInputPoint(pImageLaptop->GetConnectionPoints()->GetAt(0));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pImageCloud->GetConnectionPoints()->GetAt(0));
	pConnection->SetInputPoint(pImagePhone->GetConnectionPoints()->GetAt(0));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pImageCloud->GetConnectionPoints()->GetAt(0));
	pConnection->SetInputPoint(pImageTablet->GetConnectionPoints()->GetAt(0));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pImageCloud->GetConnectionPoints()->GetAt(0));
	pConnection->SetInputPoint(pImageDevice->GetConnectionPoints()->GetAt(0));

}

void CFlowGraphSampleView::CreateFlowChart()
{
	m_wndControl.GetPaintManager()->m_clrConnection = RGB(80,80,80);

	COLORREF clr1 = RGB(255, 191, 201);
	COLORREF clr2 = RGB(255, 255, 138);
	COLORREF clr3 = RGB(139, 239, 145);

	CXTPFlowGraphPage* pPage = m_wndControl.GetPages()->AddPage(new CXTPFlowGraphPage());
	m_wndControl.SetActivePage(pPage);

	CXTPFlowGraphNodeCustom* pNode1 = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_RECTANGLE_ROUNDED, 
		XTP_DPI(CPoint(300, 30)), XTP_DPI(CSize(200, 60)));
	pNode1->SetColor(clr1);
	pNode1->SetCaption(_T("Lamp doesn't work") );

	CXTPFlowGraphNodeCustom* pNode2 = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_RHOMBUS, 
		XTP_DPI(CPoint(300, 120)), XTP_DPI(CSize(200, 120)));
	pNode2->SetColor(clr2);
	pNode2->SetCaption(_T("Lamp plugged in?") );

	CXTPFlowGraphNodeCustom* pNode3 = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_RECTANGLE_ROUNDED, 
		XTP_DPI(CPoint(550, 150)), XTP_DPI(CSize(160, 60)));
	pNode3->SetColor(clr3);
	pNode3->SetCaption(_T("Plug in lamp") );

	CXTPFlowGraphNodeCustom* pNode4 = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_RHOMBUS, 
		XTP_DPI(CPoint(300, 275)), XTP_DPI(CSize(200, 120)));
	pNode4->SetColor(clr2);
	pNode4->SetCaption(_T("Bulb burned out?") );

	CXTPFlowGraphNodeCustom* pNode5 = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_RECTANGLE_ROUNDED, 
		XTP_DPI(CPoint(550, 305)), XTP_DPI(CSize(160, 60)));
	pNode5->SetColor(clr3);
	pNode5->SetCaption(_T("Replace bulb") );

	CXTPFlowGraphNodeCustom* pNode6 = AddCustomFlowGraphShape(m_wndControl, XTP_FLOWGRAPH_SHAPE_RECTANGLE_ROUNDED, 
		XTP_DPI(CPoint(320, 420)), XTP_DPI(CSize(160, 60)));
	pNode6->SetColor(clr3);
	pNode6->SetCaption(_T("Repair lamp") );

	// manage connections

	CXTPFlowGraphConnection *pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pNode1->GetConnectionPoints()->GetAt(2));
	pConnection->SetInputPoint(pNode2->GetConnectionPoints()->GetAt(1));
	pConnection->SetStyle(xtpFlowGraphConnectorStraightArrow);

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pNode2->GetConnectionPoints()->GetAt(2));
	pConnection->SetInputPoint(pNode3->GetConnectionPoints()->GetAt(0));
	pConnection->SetStyle(xtpFlowGraphConnectorStraightArrow);
	pConnection->SetCaption(_T("No"));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pNode2->GetConnectionPoints()->GetAt(3));
	pConnection->SetInputPoint(pNode4->GetConnectionPoints()->GetAt(1));
	pConnection->SetStyle(xtpFlowGraphConnectorStraightArrow);
	pConnection->SetCaption(_T("Yes"));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pNode4->GetConnectionPoints()->GetAt(2));
	pConnection->SetInputPoint(pNode5->GetConnectionPoints()->GetAt(0));
	pConnection->SetStyle(xtpFlowGraphConnectorStraightArrow);
	pConnection->SetCaption(_T("Yes"));

	pConnection = pPage->GetConnections()->AddConnection(new CXTPFlowGraphConnection());
	pConnection->SetOutputPoint(pNode4->GetConnectionPoints()->GetAt(3));
	pConnection->SetInputPoint(pNode6->GetConnectionPoints()->GetAt(2));
	pConnection->SetStyle(xtpFlowGraphConnectorStraightArrow);
	pConnection->SetCaption(_T("No"));
}

void CFlowGraphSampleView::SwitchGraph(int nGraphType)
{
	m_wndControl.GetPages()->RemoveAll();
	
	switch (nGraphType)
	{
		case 0:
		{
			CreateDatabaseRelationships();

			break;
		}

		case 1:
		{
			CreateNetworkDiagram();

			break;
		}

		case 2:
		{
			CreateFlowChart();

			break;
		}
	}
}

int CFlowGraphSampleView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_wndControl.Create(WS_VSCROLL | WS_HSCROLL | WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), 
		this, ID_FLOWGRAPH_CONTROL);

	InitFlowGraphImages();
	
	SwitchGraph(0);
	
	return 0;
}

void CFlowGraphSampleView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// Register our view as a drop target.
	static bool bOnce = true;

	if (bOnce)
		{ m_droptarget.Register ( this ); bOnce = false; }

	m_wndControl.SetScrollbarTheme(xtpScrollBarThemeOffice2013);
	m_wndControl.Reposition();
}

void CFlowGraphSampleView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	if (m_wndControl.GetSafeHwnd())
	{
		m_wndControl.MoveWindow(0, 0, cx, cy);
	}
	
}

BOOL CFlowGraphSampleView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

#ifdef _XTP_INCLUDE_COMMANDBARS


// Convert 0 -> 10%, 500 -> 100 %, 1000 -> 500 %

int PosToZoom(int nPos) {
	return nPos <= 500 ? 10 + MulDiv(nPos, 90, 500) : 100 + MulDiv(nPos - 500, 400, 500);
}
int ZoomToPos(int nZoom) {
	return nZoom < 100 ? MulDiv(nZoom - 10, 500, 90) : 500 + MulDiv(nZoom - 100, 500, 400);
}

void CFlowGraphSampleView::OnZoomSliderScroll(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPSCROLL* pNMScroll = (NMXTPSCROLL*)pNMHDR;

	CXTPStatusBarSliderPane* pPane = DYNAMIC_DOWNCAST(CXTPStatusBarSliderPane, pNMScroll->pSender);

	ASSERT(pPane);

	int nZoom = int(m_wndControl.GetZoomLevel() * 100);
	int nPrevZoom = nZoom;

	int nLineDelta = nZoom <= 100 ? 10 : 50;

	switch (pNMScroll->nSBCode)
	{
	case SB_TOP: nZoom = 10; break;
	case SB_BOTTOM: nZoom = 500; break;
		
	case SB_LINEUP: nZoom = max(((nZoom / nLineDelta) - 1) * nLineDelta, 10); break;
	case SB_LINEDOWN: nZoom = min(((nZoom / nLineDelta) + 1) * nLineDelta, 500); break;
		
	case SB_THUMBTRACK: nZoom = PosToZoom(pNMScroll->nPos); if (nZoom > 90 && nZoom < 150) nZoom = 100; break;
		
	case SB_PAGEUP: nZoom = max(nZoom - nLineDelta, 10); break;
	case SB_PAGEDOWN: nZoom = min(nZoom + nLineDelta, 500); break;
	}

	*pResult = TRUE; // Handled
	
	if (nZoom == nPrevZoom)
		return;
	
	pPane->SetPos(ZoomToPos(nZoom));
	
	CXTPStatusBar* pStatusBar = pPane->GetStatusBar();
	
	CXTPStatusBarPane* pPaneZoomIndicator = pStatusBar->FindPane(ID_INDICATOR_ZOOM);
	
	CString strZoom;
	strZoom.Format(_T("%i%%"), nZoom);
	pPaneZoomIndicator->SetText(strZoom);

	m_wndControl.SetZoomLevel(nZoom / 100.0);
}

void CFlowGraphSampleView::OnUpdateViewZoom(CCmdUI* pCmdUI)
{
	CXTPStatusBar* pStatusBar = DYNAMIC_DOWNCAST(CXTPStatusBar, pCmdUI->m_pOther); 
	if (!pStatusBar)
		return;

	int nZoom = int(m_wndControl.GetZoomLevel() * 100);

	if (m_nZoom != nZoom)
	{
		CXTPStatusBarPane* pPane = pStatusBar->GetPane(pCmdUI->m_nIndex);

		m_nZoom = nZoom;

		CString strZoom;
		strZoom.Format(_T("%i%%"), m_nZoom);
		pPane->SetText(strZoom);

		CXTPStatusBarSliderPane* pSliderPane = (CXTPStatusBarSliderPane*)pStatusBar->GetPane(pCmdUI->m_nIndex + 1);

		pSliderPane->SetPos(ZoomToPos(nZoom));
	}
	
	
	pCmdUI->Enable(TRUE);
}

#endif

void CFlowGraphSampleView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	m_wndControl.SetFocus();
	
}

void CFlowGraphSampleView::OnUpdateHasSelection(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetActivePage()->GetSelection()->GetCount() > 0);
}

void CFlowGraphSampleView::OnZoomToSelection()
{
	m_wndControl.ZoomToSelection();
}

void CFlowGraphSampleView::OnZoomFitToWindow()
{
	m_wndControl.ZoomFitToWindow();
}
void CFlowGraphSampleView::OnEditSelectAll() 
{
	m_wndControl.SelectAll();
	
}

void CFlowGraphSampleView::OnEditArrange()
{
	m_wndControl.Arrange();
}


UINT CFlowGraphSampleView::TrackPopupMenu(CMenu* pMenu, UINT nFlags, int xPos, int yPos)
{
#ifdef _XTP_INCLUDE_COMMANDBARS
	return CXTPCommandBars::TrackPopupMenu(pMenu, nFlags, xPos, yPos, this);
#else
	return ::TrackPopupMenu(pMenu->GetSafeHmenu(), nFlags, xPos, yPos, 0, m_hWnd, 0);
#endif

};

void CFlowGraphSampleView::OnGraphRClick(NMHDR* /*pNMHDR*/, LRESULT* /*pResult*/)
{
	CPoint point;
	GetCursorPos(&point);

	m_wndControl.ScreenToClient(&point);

	CXTPFlowGraphNode* pNode = m_wndControl.HitTestNode(point);

	CXTPFlowGraphConnection* pConnection = m_wndControl.HitTestConnection(point);

	CXTPFlowGraphSelectedElements* pSelection = m_wndControl.GetActivePage()->GetSelection();

	if (pNode)
	{
		if (!pNode->IsSelected())
		{
			pSelection->Clear();
			pNode->Select();
		}
		m_wndControl.GetActivePage()->GetNodes()->MoveToFront(pNode);


		CMenu menu;
		menu.LoadMenu(IDR_MENU_CONTEXT);

		CPoint point;
		GetCursorPos(&point);

		CPoint pointClient = point;
		m_wndControl.ScreenToClient(&pointClient);

		CXTPFlowGraphConnectionPoint* pConnectionPoint = pNode->HitTestConnectionPoint(pointClient);

		UINT nCommand = TrackPopupMenu(menu.GetSubMenu(pConnectionPoint ? 3 : 0), TPM_RETURNCMD, point.x, point.y);

		if (nCommand == ID_COLOR_TRANSPARENT)
		{
			pNode->SetColor(RGB(255,255,255), 0);
		}
		else
		if (nCommand >= ID_NODE_COLOR_BLUE && nCommand <= ID_NODE_COLOR_ORANGE)
		{
			pNode->SetColor(clrOfficeColors[nCommand - ID_NODE_COLOR_BLUE]);

		}
		else if (nCommand == ID_NODE_DELETE)
		{
			pNode->Remove();
		}
		else if (nCommand == ID_CONNECTIONPOINT_DELETE)
		{
			pConnectionPoint->Remove();
		}
		else if (nCommand == ID_NODE_RENAME)
		{
			m_wndControl.RenameNode(pNode);
		}
		else if (nCommand == ID_CONNECTIONPOINT_ADD)
		{
			static int iConnectionPointN = 0;

			CString newPointName;
			newPointName.Format(_T("New connection point %d"), iConnectionPointN++);

			pNode->AddNamedConnectionPoints(newPointName, xtpFlowGraphPointInputAndOutput);
			
			m_wndControl.RedrawControl();
			
			m_wndControl.RenameConnectionPoint(pConnectionPoint);
		}
		else if (nCommand == ID_CONNECTIONPOINT_RENAME)
		{
			m_wndControl.RenameConnectionPoint(pConnectionPoint);
		}
		else if (nCommand == ID_GROUP_UNGROUP)
		{
			for (int i = 0; i < pSelection->GetCount(); i++)
			{
				CXTPFlowGraphNode* pNode = DYNAMIC_DOWNCAST(CXTPFlowGraphNode, pSelection->GetAt(i));
				if (!pNode)
					continue;

				if (pNode->GetGroup() != NULL)
				{
					pNode->GetGroup()->RemoveNode(pNode);
				}
			}
		}
		else if (nCommand == ID_GROUP_GROUP)
		{
			CXTPFlowGraphNodeGroup* pGroup = m_wndControl.GetActivePage()->GetGroups()->AddGroup();

			for (int i = 0; i < pSelection->GetCount(); i++)
			{
				CXTPFlowGraphNode* pNode = DYNAMIC_DOWNCAST(CXTPFlowGraphNode, pSelection->GetAt(i));
				if (!pNode)
					continue;

				pGroup->AddNode(pNode);
			}

			if (pGroup->GetCount() < 2)
			{
				pGroup->Remove();
			}
			else
			{				
				pGroup->GetAt(0)->Select();			
			}
		}

	}
	else if (pConnection)
	{
		if (!pConnection->IsSelected())
		{
			pSelection->Clear();
			pSelection->AddSelection(pConnection);
		}

		CMenu menu;
		menu.LoadMenu(IDR_MENU_CONTEXT);

		CPoint point;
		GetCursorPos(&point);

		UINT nCommand = TrackPopupMenu(menu.GetSubMenu(2), TPM_RETURNCMD, point.x, point.y);

		if (nCommand >= ID_FLOWGRAPH_CONNECTOR_TYPE_CONTEXT_0 && nCommand <= ID_FLOWGRAPH_CONNECTOR_TYPE_CONTEXT_8)
		{
			XTPFlowGraphConnectorType type = xtpFlowGraphConnectorStraight;

			switch (nCommand)
			{
				case ID_FLOWGRAPH_CONNECTOR_TYPE_CONTEXT_1:	{ type = xtpFlowGraphConnectorStraightArrow; break; }
				case ID_FLOWGRAPH_CONNECTOR_TYPE_CONTEXT_2:	{ type = xtpFlowGraphConnectorStraightDoubleArrow; break; }
				case ID_FLOWGRAPH_CONNECTOR_TYPE_CONTEXT_3:	{ type = xtpFlowGraphConnectorCurved; break; }
				case ID_FLOWGRAPH_CONNECTOR_TYPE_CONTEXT_4:	{ type = xtpFlowGraphConnectorCurvedArrow; break; }
				case ID_FLOWGRAPH_CONNECTOR_TYPE_CONTEXT_5:	{ type = xtpFlowGraphConnectorCurvedDoubleArrow; break; }
				case ID_FLOWGRAPH_CONNECTOR_TYPE_CONTEXT_6:	{ type = xtpFlowGraphConnectorElbow; break; }
				case ID_FLOWGRAPH_CONNECTOR_TYPE_CONTEXT_7:	{ type = xtpFlowGraphConnectorElbowArrow; break; }
				case ID_FLOWGRAPH_CONNECTOR_TYPE_CONTEXT_8:	{ type = xtpFlowGraphConnectorElbowDoubleArrow; break; }
			}

			pConnection->SetStyle(type);
		}
		else if (nCommand == ID_CONNECTION_DELETECONNECTION)
		{
			pConnection->Remove();
		}
		else if (nCommand == ID_CONNECTION_CLEANCONTROLPOINTS)
		{
			pConnection->SetControlPoint(CPoint(-1, -1));
		}

	}
	else
	{
		CMenu menu;
		menu.LoadMenu(IDR_MENU_CONTEXT);
		
		CPoint point;
		GetCursorPos(&point);
		
		UINT nCommand = TrackPopupMenu(menu.GetSubMenu(1), TPM_RETURNCMD, point.x, point.y);

		m_wndControl.ScreenToClient(&point);
		point = m_wndControl.GetActivePage()->ScreenToPage(point);

		switch (nCommand)
		{
			case ID_NODE_ADD:
			{
				InsertNewShape(FG_SHAPE_TABLE, point);

				break;
			}

			case ID_ADDCUSTOMNODE_RECTANGLE:
			{
				InsertNewShape(FG_SHAPE_FROM_RESOURCE, point, XTP_FLOWGRAPH_SHAPE_RECTANGLE);

				break;
			}

			case ID_ADDCUSTOMNODE_RHOMBUS:
			{
				InsertNewShape(FG_SHAPE_FROM_RESOURCE, point, XTP_FLOWGRAPH_SHAPE_RHOMBUS);

				break;
			}

			case ID_ADDCUSTOMNODE_ELLIPSE:
			{
				InsertNewShape(FG_SHAPE_FROM_RESOURCE, point, XTP_FLOWGRAPH_SHAPE_ELLIPSE);

				break;
			}

			case ID_ADDCUSTOMNODE_IMAGE_FIREWALL:
			{
				InsertNewShape(FG_SHAPE_PICTURE, point);
				
				break;
			}
		}
	}

}
void CFlowGraphSampleView::OnEditCopy()
{
	m_wndControl.GetActivePage()->Copy();
}

void CFlowGraphSampleView::OnUpdateEditCopy(CCmdUI *pCmdUI)
{
	BOOL bEnable = m_wndControl.GetActivePage() ? (m_wndControl.GetActivePage()->GetSelection()->GetCount() > 0) : FALSE;

	pCmdUI->Enable(bEnable);
}

void CFlowGraphSampleView::OnEditCut()
{
	//if (AfxMessageBox(_T("Are you sure you want delete selected objects"), MB_YESNO) == IDYES)
	m_wndControl.GetActivePage()->Cut();
}

void CFlowGraphSampleView::OnUpdateEditCut(CCmdUI *pCmdUI)
{
	BOOL bEnable = m_wndControl.GetActivePage() ? (m_wndControl.GetActivePage()->GetSelection()->GetCount() > 0) : FALSE;

	pCmdUI->Enable(bEnable);
}

void CFlowGraphSampleView::OnEditPaste()
{
	m_wndControl.GetActivePage()->Paste();
}

void CFlowGraphSampleView::OnUpdateEditPaste(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetActivePage()->CanPaste());
}

void CFlowGraphSampleView::OnEditUndo()
{
	m_wndControl.GetUndoManager()->Undo();
}

void CFlowGraphSampleView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetUndoManager()->CanUndo());
}

void CFlowGraphSampleView::OnEditRedo()
{
	m_wndControl.GetUndoManager()->Redo();
}

void CFlowGraphSampleView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetUndoManager()->CanRedo());
}

void CFlowGraphSampleView::OnShowGrid()
{
	m_wndControl.GetPaintManager()->m_bShowGrid ^= 1;
	
	m_wndControl.RedrawControl();
}

void CFlowGraphSampleView::OnUpdateShowGrid(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndControl.GetPaintManager()->m_bShowGrid ? 1 : 0);
	
}

void CFlowGraphSampleView::OnConnectorType(UINT nCmd)
{
	XTPFlowGraphConnectorType type = xtpFlowGraphConnectorStraight;

	switch (nCmd)
	{
		case ID_FLOWGRAPH_CONNECTOR_TYPE_1:	{ type = xtpFlowGraphConnectorStraightArrow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_2:	{ type = xtpFlowGraphConnectorStraightDoubleArrow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_3:	{ type = xtpFlowGraphConnectorCurved; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_4:	{ type = xtpFlowGraphConnectorCurvedArrow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_5:	{ type = xtpFlowGraphConnectorCurvedDoubleArrow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_6:	{ type = xtpFlowGraphConnectorElbow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_7:	{ type = xtpFlowGraphConnectorElbowArrow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_8:	{ type = xtpFlowGraphConnectorElbowDoubleArrow; break; }
	}

	CXTPFlowGraphConnections *pConnections = m_wndControl.GetActivePage()->GetConnections();

	if (pConnections)
	{
		for (int i=0; i<pConnections->GetCount(); i++)
		{
			pConnections->GetAt(i)->SetStyle(type);
		}
	}

	//m_wndControl.GetPaintManager()->m_nConnectorType = type;

	m_wndControl.GetActivePage()->OnGraphChanged();
}

void CFlowGraphSampleView::OnUpdateConnectorType(CCmdUI *pCmdUI)
{
	XTPFlowGraphConnectorType type = xtpFlowGraphConnectorStraight;

	switch (pCmdUI->m_nID)
	{
		case ID_FLOWGRAPH_CONNECTOR_TYPE_1:	{ type = xtpFlowGraphConnectorStraightArrow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_2:	{ type = xtpFlowGraphConnectorStraightDoubleArrow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_3:	{ type = xtpFlowGraphConnectorCurved; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_4:	{ type = xtpFlowGraphConnectorCurvedArrow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_5:	{ type = xtpFlowGraphConnectorCurvedDoubleArrow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_6:	{ type = xtpFlowGraphConnectorElbow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_7:	{ type = xtpFlowGraphConnectorElbowArrow; break; }
		case ID_FLOWGRAPH_CONNECTOR_TYPE_8:	{ type = xtpFlowGraphConnectorElbowDoubleArrow; break; }
	}

	pCmdUI->SetCheck(m_wndControl.GetPaintManager()->m_nConnectorType == type);

}
void CFlowGraphSampleView::OnFlowgraphShowNodegroupsAlways() 
{
	m_wndControl.GetPaintManager()->m_bShowNodeGroupsAlways ^= 1;
	m_wndControl.RedrawControl();
}

void CFlowGraphSampleView::OnUpdateFlowgraphShowNodegroupsAlways(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndControl.GetPaintManager()->m_bShowNodeGroupsAlways ? 1 : 0);
}

void CFlowGraphSampleView::OnQuality(UINT nCmd)
{
	m_wndControl.SetSmoothingMode((XTPFlowGraphSmoothingMode)(nCmd - ID_FLOWGRAPH_QUALITY_HIGHQUALITY));	

}

void CFlowGraphSampleView::OnUpdateQuality(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_wndControl.GetSmoothingMode() == (XTPFlowGraphSmoothingMode)(pCmdUI->m_nID - ID_FLOWGRAPH_QUALITY_HIGHQUALITY) ? 1 : 0);
	
}
void CFlowGraphSampleView::OnEditDelete()
{
	CArray<CXTPFlowGraphNode *, CXTPFlowGraphNode *> nodesToRemove;

	CXTPFlowGraphSelectedElements *pSelection = m_wndControl.GetActivePage()->GetSelection();

	if (pSelection)
	{
		int c = pSelection->GetCount();

		for (int i=0; i<c; i++)
		{
			CXTPFlowGraphNode* pNode = DYNAMIC_DOWNCAST(CXTPFlowGraphNode, pSelection->GetAt(i));
			if (!pNode)
				continue;

			nodesToRemove.Add(pNode);
		}
	}

	for (int i=0; i<nodesToRemove.GetSize(); i++)
	{
		nodesToRemove[i]->Select(FALSE);
		nodesToRemove[i]->Remove();
	}
}

void CFlowGraphSampleView::OnUpdateEditDelete(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_wndControl.GetActivePage()->GetSelection()->GetCount() > 0);
}

#ifdef _XTP_INCLUDE_TASKPANEL

LRESULT CFlowGraphSampleView::OnTaskPanelNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case XTP_TPN_CLICK:
		{
			CXTPTaskPanelGroupItem* pItem = (CXTPTaskPanelGroupItem*)lParam;

			if (pItem && pItem->GetID() < FG_SHAPE_TABLE)
			{
				CXTPFlowGraphConnections *pConnections = m_wndControl.GetActivePage()->GetConnections();

				if (pConnections)
				{
					for (int i=0; i<pConnections->GetCount(); i++)
					{
						pConnections->GetAt(i)->SetStyle((XTPFlowGraphConnectorType)pItem->GetID());
					}
				}

				//m_wndControl.GetPaintManager()->m_nConnectorType = (XTPFlowGraphConnectorType)pItem->GetID();

				m_wndControl.GetActivePage()->OnGraphChanged();
			}			
			
			break;
		}
	}
	
	return 0;
}

#endif

enum GRID_ITEM_ID
{
	GRID_ITEM_CAPTION = 0,
	GRID_ITEM_COLOR,
	GRID_ITEM_COLOR_2,
	GRID_ITEM_FILL_TYPE,
	GRID_ITEM_SIZE,
	GRID_ITEM_SIZE_WIDTH,
	GRID_ITEM_SIZE_HEIGHT,
	GRID_CONNECTION_CAPTION,
	GRID_CONNECTION_COLOR,
	GRID_CONNECTION_TYPE,
	GRID_CONNECTION_WIDTH,
	GRID_CONNECTION_DASHED
};



void CFlowGraphSampleView::OnSelectionChanged(NMHDR* /*pNMHDR*/, LRESULT* pResult)
{
#ifdef _XTP_INCLUDE_PROPERTYGRID

	if (m_pGrid)
	{
		m_pGrid->ResetContent();

		UpdatePropertyGrid();
	}

#endif

	*pResult = 0;
}

#ifdef _XTP_INCLUDE_PROPERTYGRID

void CFlowGraphSampleView::UpdatePropertyGrid()
{
	ASSERT(m_pGrid);

	if (!m_pGrid)
		return;

	CXTPFlowGraphSelectedElements *pSelectedElements = m_wndControl.GetActivePage()->GetSelection();

	if (pSelectedElements->GetCount() == 1)
	{
		CXTPFlowGraphElement *pElement = pSelectedElements->GetAt(0);

		if (pElement)
		{
			CXTPFlowGraphNode *pNode = DYNAMIC_DOWNCAST(CXTPFlowGraphNode, pElement);
			CXTPFlowGraphConnection *pConnection = DYNAMIC_DOWNCAST(CXTPFlowGraphConnection, pElement);

			if (pNode)
			{
				CXTPPropertyGridItem *pGroupNode = m_pGrid->AddCategory(pNode->GetCaption() + CString(_T(" Node")));

				CXTPPropertyGridItem* pCaption = pGroupNode->AddChildItem(new CXTPPropertyGridItem(_T("Caption")) );
				pCaption->SetValue(pNode->GetCaption());
				pCaption->SetID(GRID_ITEM_CAPTION);

				CXTPPropertyGridItemColor* pColor = (CXTPPropertyGridItemColor *)pGroupNode->AddChildItem(new CXTPPropertyGridItemColor(_T("Color")) );
				pColor->SetID(GRID_ITEM_COLOR);
				pColor->SetColor(pNode->GetColor());

				if (pNode->IsKindOf(RUNTIME_CLASS(CXTPFlowGraphNodeCustom)))
				{
					CXTPFlowGraphNodeCustom *pNodeCustom = static_cast<CXTPFlowGraphNodeCustom *>(pNode);

					pColor = (CXTPPropertyGridItemColor *)pGroupNode->AddChildItem(new CXTPPropertyGridItemColor(_T("Color 2")) );
					pColor->SetID(GRID_ITEM_COLOR_2);
					pColor->SetColor(pNodeCustom->GetSecondColor());

					// fill type

					CXTPPropertyGridItem* pType = pGroupNode->AddChildItem(new CXTPPropertyGridItem(_T("Fill Type")) );
					pType->SetID(GRID_ITEM_FILL_TYPE);

					CXTPPropertyGridItemConstraints* pConstraints = pType->GetConstraints();

					pConstraints->AddConstraint(_T("Solid"), (DWORD_PTR)xtpFlowGraphCustomNodeFillSolid);
					pConstraints->AddConstraint(_T("Gradient Horz"), (DWORD_PTR)xtpFlowGraphCustomNodeFillGradientHorizontal);
					pConstraints->AddConstraint(_T("Gradient Vert"), (DWORD_PTR)xtpFlowGraphCustomNodeFillGradientVertical);
					pConstraints->AddConstraint(_T("Gradient Diagonal Left"), (DWORD_PTR)xtpFlowGraphCustomNodeFillGradientDiagonalLeft);
					pConstraints->AddConstraint(_T("Gradient Diagonal Right"), (DWORD_PTR)xtpFlowGraphCustomNodeFillGradientDiagonalRight);
					pConstraints->AddConstraint(_T("Gradient Center Horz"), (DWORD_PTR)xtpFlowGraphCustomNodeFillGradientCenterHorizontal);
					pConstraints->AddConstraint(_T("Gradient Center Vert"), (DWORD_PTR)xtpFlowGraphCustomNodeFillGradientCenterVertical);

					CXTPPropertyGridItemConstraint *pCurrValue = pConstraints->GetConstraintAt(pConstraints->FindConstraint((DWORD_PTR)pNodeCustom->GetFillType()));

					if (pCurrValue)
						pType->SetValue(pCurrValue->m_strConstraint);

					pType->SetFlags(xtpGridItemHasComboButton);
				}

				if (pNode->IsResizable())
				{
					CXTPPropertyGridItemSize *pSize = (CXTPPropertyGridItemSize *)pGroupNode->AddChildItem(new CXTPPropertyGridItemSize(_T("Size")) );

					CXTPPropertyGridItems *pChildren = pSize->GetChilds();

					ASSERT(pChildren->GetCount() == 2);

					if (pChildren->GetCount() == 2)
					{
						pChildren->GetAt(0)->SetID(GRID_ITEM_SIZE_WIDTH);
						pChildren->GetAt(1)->SetID(GRID_ITEM_SIZE_HEIGHT);
					}

					pSize->SetSize(pNode->GetSize());
					pSize->SetID(GRID_ITEM_SIZE);
					//pSize->SetMinSize () ?
				}

				pGroupNode->Expand();
			}
			else if (pConnection)
			{
				CXTPPropertyGridItem *pGroupConnection = m_pGrid->AddCategory(pConnection->GetCaption().GetLength() ? pConnection->GetCaption() : _T("Connection"));

				CXTPPropertyGridItem* pCaption = pGroupConnection->AddChildItem(new CXTPPropertyGridItem(_T("Caption")) );

				if (pConnection->GetCaption().GetLength())
					pCaption->SetValue(pConnection->GetCaption());

				pCaption->SetID(GRID_CONNECTION_CAPTION);

				CXTPPropertyGridItemColor* pColor = (CXTPPropertyGridItemColor *)pGroupConnection->AddChildItem(new CXTPPropertyGridItemColor(_T("Color")) );
				pColor->SetID(GRID_CONNECTION_COLOR);

				if (pConnection->GetColor() != -1) // not defined
					pColor->SetColor(pConnection->GetColor());
				else 
					pColor->SetColor(m_wndControl.GetPaintManager()->m_clrConnection);

				// type

				CXTPPropertyGridItem* pType = pGroupConnection->AddChildItem(new CXTPPropertyGridItem(_T("Type")) );
				pType->SetID(GRID_CONNECTION_TYPE);

				CXTPPropertyGridItemConstraints* pConstraints = pType->GetConstraints();

				pConstraints->AddConstraint(_T("Straight"), (DWORD_PTR)xtpFlowGraphConnectorStraight);
				pConstraints->AddConstraint(_T("Straight with arrow"), (DWORD_PTR)xtpFlowGraphConnectorStraightArrow);
				pConstraints->AddConstraint(_T("Straight with double arrow"), (DWORD_PTR)xtpFlowGraphConnectorStraightDoubleArrow);
				pConstraints->AddConstraint(_T("Curved"), (DWORD_PTR)xtpFlowGraphConnectorCurved);
				pConstraints->AddConstraint(_T("Curved with arrow"), (DWORD_PTR)xtpFlowGraphConnectorCurvedArrow);
				pConstraints->AddConstraint(_T("Curved with double arrow"), (DWORD_PTR)xtpFlowGraphConnectorCurvedDoubleArrow);
				pConstraints->AddConstraint(_T("Elbow"), (DWORD_PTR)xtpFlowGraphConnectorElbow);
				pConstraints->AddConstraint(_T("Elbow with arrow"), (DWORD_PTR)xtpFlowGraphConnectorElbowArrow);
				pConstraints->AddConstraint(_T("Elbow with double arrow"), (DWORD_PTR)xtpFlowGraphConnectorElbowDoubleArrow);

				int nStyle = (pConnection->GetStyle() != -1) ? pConnection->GetStyle() : m_wndControl.GetPaintManager()->m_nConnectorType;

				CXTPPropertyGridItemConstraint *pCurrValue = pConstraints->GetConstraintAt(pConstraints->FindConstraint((DWORD_PTR)nStyle));

				if (pCurrValue)
					pType->SetValue(pCurrValue->m_strConstraint);

				pType->SetFlags(xtpGridItemHasComboButton);

				CXTPPropertyGridItemNumber* pWidth = (CXTPPropertyGridItemNumber *)pGroupConnection->AddChildItem(new CXTPPropertyGridItemNumber(_T("Width")) );
				pWidth->SetNumber(pConnection->GetWidth());
				pWidth->SetID(GRID_CONNECTION_WIDTH);

				CXTPPropertyGridItemBool* pDashed = (CXTPPropertyGridItemBool *)pGroupConnection->AddChildItem(new CXTPPropertyGridItemBool(_T("Dashed")) );
				pDashed->SetBool(pConnection->GetDashed());
				pDashed->SetID(GRID_CONNECTION_DASHED);

				pGroupConnection->Expand();
			}
		}
	}
	else
	{
		CXTPPropertyGridItem *pGroupMultiple = m_pGrid->AddCategory( _T("Multiple items are selected") );

		// don't work with multiple items selected at the moment
	}
}

LRESULT CFlowGraphSampleView::OnPropertyGridNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case XTP_PGN_USER:
		{
			m_pGrid = (CXTPPropertyGrid *)lParam;

			break;
		}

		case XTP_PGN_ITEMVALUE_CHANGED:
		{
			CXTPFlowGraphSelectedElements *pSelectedElements = m_wndControl.GetActivePage()->GetSelection();

			if (pSelectedElements->GetCount() != 1)
				return 0;

			CXTPFlowGraphElement *pElement = pSelectedElements->GetAt(0);

			CXTPFlowGraphNode *pNode = DYNAMIC_DOWNCAST(CXTPFlowGraphNode, pElement);
			CXTPFlowGraphConnection *pConnection = DYNAMIC_DOWNCAST(CXTPFlowGraphConnection, pElement);

			CXTPPropertyGridItem *pChangedItem = reinterpret_cast<CXTPPropertyGridItem *>(lParam);

			switch (pChangedItem->GetID())
			{
				case GRID_ITEM_CAPTION:
				{
					if (pNode)
					{
						pNode->SetCaption(pChangedItem->GetValue());
					}

					break;
				}

				case GRID_ITEM_COLOR:
				{
					if (pNode)
					{
						CXTPPropertyGridItemColor *pChangedItemColor = static_cast<CXTPPropertyGridItemColor *>(pChangedItem);

						pNode->SetColor( pChangedItemColor->GetColor() );
					}

					break;
				}

				case GRID_ITEM_COLOR_2:
				{
					if (pNode)
					{
						CXTPPropertyGridItemColor *pChangedItemColor = static_cast<CXTPPropertyGridItemColor *>(pChangedItem);

						((CXTPFlowGraphNodeCustom *)pNode)->SetSecondColor( pChangedItemColor->GetColor() );
					}

					break;
				}
				
				case GRID_ITEM_FILL_TYPE:
				{
					if (pNode)
					{
						CXTPFlowGraphNodeCustom *pNodeCustom = static_cast<CXTPFlowGraphNodeCustom *>(pNode);

						CXTPPropertyGridItemConstraints* pConstraints = pChangedItem->GetConstraints();

						CXTPPropertyGridItemConstraint *pCurrValue = pConstraints->GetConstraintAt(pConstraints->GetCurrent());

						pNodeCustom->SetFillType((XTPFlowGraphCustomNodeFillType)pCurrValue->m_dwData);
					}

					break;
				}

				case GRID_ITEM_SIZE:
				{
					if (pNode)
					{
						CXTPPropertyGridItemSize *pChangedItemSize = static_cast<CXTPPropertyGridItemSize *>(pChangedItem);

						pNode->SetSize(pChangedItemSize->GetSize());
					}

					break;
				}

				case GRID_ITEM_SIZE_WIDTH:
				{
					if (pNode)
					{
						CXTPPropertyGridItemNumber *pChangedItemWidth = static_cast<CXTPPropertyGridItemNumber *>(pChangedItem);

						pNode->SetSize(CSize(pChangedItemWidth->GetNumber(), pNode->GetSize().cy));
					}

					break;
				}

				case GRID_ITEM_SIZE_HEIGHT:
				{
					if (pNode)
					{
						CXTPPropertyGridItemNumber *pChangedItemHeight = static_cast<CXTPPropertyGridItemNumber *>(pChangedItem);

						pNode->SetSize(CSize(pNode->GetSize().cx, pChangedItemHeight->GetNumber()));
					}

					break;
				}

				case GRID_CONNECTION_CAPTION:
				{
					if (pConnection)
					{
						pConnection->SetCaption(pChangedItem->GetValue());
					}

					break;
				}

				case GRID_CONNECTION_COLOR:
				{
					if (pConnection)
					{
						CXTPPropertyGridItemColor *pChangedItemColor = static_cast<CXTPPropertyGridItemColor *>(pChangedItem);

						pConnection->SetColor(pChangedItemColor->GetColor());
					}

					break;
				}

				case GRID_CONNECTION_TYPE:
				{
					if (pConnection)
					{
						CXTPPropertyGridItemConstraints* pConstraints = pChangedItem->GetConstraints();

						CXTPPropertyGridItemConstraint *pCurrValue = pConstraints->GetConstraintAt(pConstraints->GetCurrent());

						if (pCurrValue)
						{	
							pConnection->SetStyle((int)pCurrValue->m_dwData);
						}
					}

					break;
				}

				case GRID_CONNECTION_WIDTH:
				{
					if (pConnection)
					{
						CXTPPropertyGridItemNumber *pChangedItemNumber = static_cast<CXTPPropertyGridItemNumber *>(pChangedItem);
						pConnection->SetWidth(pChangedItemNumber->GetNumber());
					}

					break;
				}

				case GRID_CONNECTION_DASHED:
				{
					if (pConnection)
					{
						CXTPPropertyGridItemBool *pChangedItemBool = static_cast<CXTPPropertyGridItemBool *>(pChangedItem);
						pConnection->SetDashed(pChangedItemBool->GetBool());
					}

					break;
				}
			}

			break;
		}
	}

	return 0;
}

#endif

void CFlowGraphSampleView::OnSwitchGraphType0()
{
	SwitchGraph(0);
}

void CFlowGraphSampleView::OnSwitchGraphType1()
{
	SwitchGraph(1);
}

void CFlowGraphSampleView::OnSwitchGraphType2()
{
	SwitchGraph(2);
}
