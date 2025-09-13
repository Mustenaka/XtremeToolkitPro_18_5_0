// GUI_VisualStudioView.cpp 
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
#include "GUI_VisualStudio.h"

#include "GUI_VisualStudioDoc.h"
#include "GUI_VisualStudioView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioView

IMPLEMENT_DYNCREATE(CGUI_VisualStudioView, CXTPSyntaxEditView)

BEGIN_MESSAGE_MAP(CGUI_VisualStudioView, CXTPSyntaxEditView)
	//{{AFX_MSG_MAP(CGUI_VisualStudioView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CXTPSyntaxEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CXTPSyntaxEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CXTPSyntaxEditView::OnFilePrintPreview)

	ON_XTP_EXECUTE(ID_EDIT_FIND_EX, OnEditFind)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FIND_EX, OnUpdateEditFind)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioView construction/destruction

CGUI_VisualStudioView::CGUI_VisualStudioView()
{

	m_theme = themeNone;

#ifdef _XTP_INCLUDE_SYNTAXEDIT

	GetEditCtrl().m_bUseMonitor = TRUE;
	CGUI_VisualStudioView::bLoadConfigOnce = TRUE;

	RefreshColors();

#endif
}

CGUI_VisualStudioView::~CGUI_VisualStudioView()
{
}

void CGUI_VisualStudioView::RefreshColors()
{
	if(m_theme == theApp.m_theme)
		return;

	if (sIni.IsEmpty())
	{
		switch(theApp.m_theme)
		{
			case themeVS2012Light:
			case themeVS2015Light:
			case themeVS2015Blue:
				sIni = _T("EditConfig\\SyntaxEditLight.ini");
				break;
			case themeVS2012Dark:
			case themeVS2015Dark:
				sIni = _T("EditConfig\\SyntaxEditDark.ini");
				break;
			default:
				sIni = _T("EditConfig\\SyntaxEdit.ini");
				break;
		}
	}

	COLORREF clrBackColor = RGB(255, 255, 255);
	COLORREF clrLineNumberBackColor = RGB(255, 255, 255);
	COLORREF clrLineNumberTextColor = RGB(43, 145, 175);

	BOOL bSelMargin = TRUE;
	CString sSchema = _T("EditConfig\\Schemas\\_cpp.schclass");

	switch(theApp.m_theme)
	{
		case themeVS2012Light:
		case themeVS2015Light:
		case themeVS2015Blue:
			clrBackColor = RGB(246, 246, 246);	
			clrLineNumberBackColor = RGB(246, 246, 246);
			clrLineNumberTextColor = RGB(43, 145, 175);

			bSelMargin = TRUE;
			sSchema = _T("EditConfig\\Schemas\\_cppLight.schclass");
			break;
		case themeVS2012Dark:
		case themeVS2015Dark:
			clrBackColor = RGB(28, 28, 28);		
			clrLineNumberBackColor = RGB(28, 28, 28);
			clrLineNumberTextColor = RGB(86, 156, 214);

			bSelMargin = FALSE;
			sSchema = _T("EditConfig\\Schemas\\_cppDark.schclass");
			break;
		default:
			clrBackColor = RGB(255, 255, 255);
			clrLineNumberBackColor = RGB(255, 255, 255);
			clrLineNumberTextColor = RGB(43, 145, 175);

			bSelMargin = TRUE;
			sSchema = _T("EditConfig\\Schemas\\_cpp.schclass");
			break;
	}

	m_theme = theApp.m_theme;

	GetEditCtrl().GetPaintManager()->SetBackColor(clrBackColor, FALSE);
	GetEditCtrl().GetPaintManager()->SetLineNumberBackColor(clrLineNumberBackColor, FALSE);
	GetEditCtrl().GetPaintManager()->SetLineNumberTextColor(clrLineNumberTextColor, FALSE);
	GetEditCtrl().SetSelMargin(bSelMargin);

	if (GetEditCtrl().GetEditBuffer())
		GetEditCtrl().GetEditBuffer()->SetFileExt(_T(".cpp"));	

	if (CGUI_VisualStudioView::bLoadConfigOnce)
	{
		CGUI_VisualStudioView::bLoadConfigOnce = FALSE;

		GetEditCtrl().SetConfigFile(CXTPSyntaxEditCtrl::GetModulePath() + sIni, TRUE);
	}
	else
	{
		if (theApp.strSchema.IsEmpty())
		{
			CStdioFile file;
			CString strLine;
			CString strINI;
			CString strSchema;

			if (file.Open(CXTPSyntaxEditCtrl::GetModulePath() + sIni, CFile::modeRead))	
			{
				while(file.ReadString(strLine))
				{
					strINI += strLine + _T("\r\n");
				}
				
				file.Close();
			}
			else
			{
				AfxMessageBox(_T("Could not load file"));
			}

			strLine   = _T("");
			strSchema = _T("");

			if (file.Open(CXTPSyntaxEditCtrl::GetModulePath() + sSchema, CFile::modeRead))
			{
				while (file.ReadString(strLine))	
				{
					strSchema += strLine + _T("\r\n");
				}
				
				file.Close();
			}
			else
			{
				AfxMessageBox(_T("Could not load file"));
			}

			theApp.strSchema = strSchema;
			theApp.strColor  = strINI;

			GetEditCtrl().SetSyntaxAndColorScheme(strSchema, strINI, FALSE, FALSE);
		}
		else
		{
			GetEditCtrl().SetSyntaxAndColorScheme(theApp.strSchema, theApp.strColor, FALSE, FALSE);
		}
	}
}

void CGUI_VisualStudioView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (pSender == this) 
	{
		return;
	}

//	RefreshColors();

	CXTPSyntaxEditView::OnUpdate(pSender, lHint, pHint);
}

void CGUI_VisualStudioView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	if (bActivate)
	{
		RefreshColors();
	}
}

BOOL CGUI_VisualStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	BOOL bPreCreated = CXTPSyntaxEditView::PreCreateWindow(cs);


	return bPreCreated;
}

void CGUI_VisualStudioView::OnInitialUpdate()
{
	static BOOL bLoadOnce = FALSE;
	if (!bLoadOnce && GetDocument()->GetPathName().IsEmpty())
	{
		bLoadOnce = TRUE;		

		CStdioFile file;
		CFileException ex;

		if (!file.Open(CXTPSyntaxEditCtrl::GetModulePath() + _T("res\\SampleFrm.txt"), CFile::modeRead | CFile::shareDenyWrite, &ex))
		{
		  TCHAR szError[1024];
		  ex.GetErrorMessage(szError, 1024);
		  TRACE(_T("Couldn't open source file: %s\n"), szError);
		}
		else
		{
			CString sText, sLine;
			
			while (file.ReadString(sLine))
			{
				sText += sLine + _T("\r\n");
			}

			GetEditCtrl().SetWindowText(sText);
		}

		GetDocument()->SetModifiedFlag(FALSE);

		// set the font size.
		CFont* pFont = GetEditCtrl().GetFont();
		if (pFont)
		{
			LOGFONT lf;
			pFont->GetLogFont(&lf);
			lf.lfHeight = -XTP_DPI_Y(11);
			GetEditCtrl().SetFontIndirect(&lf, TRUE);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioView drawing

void CGUI_VisualStudioView::OnDraw(CDC* /*pDC*/)
{
}

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioView printing

BOOL CGUI_VisualStudioView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CXTPSyntaxEditView preparation
	return CXTPSyntaxEditView::OnPreparePrinting(pInfo);
}

void CGUI_VisualStudioView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CXTPSyntaxEditView begin printing.
	CXTPSyntaxEditView::OnBeginPrinting(pDC, pInfo);
}

void CGUI_VisualStudioView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CXTPSyntaxEditView end printing
	CXTPSyntaxEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioView diagnostics

#ifdef _DEBUG
void CGUI_VisualStudioView::AssertValid() const
{
	CXTPSyntaxEditView::AssertValid();
}

void CGUI_VisualStudioView::Dump(CDumpContext& dc) const
{
	CXTPSyntaxEditView::Dump(dc);
}

CGUI_VisualStudioDoc* CGUI_VisualStudioView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGUI_VisualStudioDoc)));
	return (CGUI_VisualStudioDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGUI_VisualStudioView message handlers


void CGUI_VisualStudioView::OnEditFind(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlComboBox* pControl = (CXTPControlComboBox*)tagNMCONTROL->pControl;
	if (pControl->GetType() == xtpControlComboBox)
	{
		CString strFind = pControl->GetEditText();

		/*if (!FindText(strFind, TRUE,FALSE))
		{
			AfxMessageBox(_T("String not Found"));
		}*/

		*pResult = 1; // Handled;
	}
}

void CGUI_VisualStudioView::OnUpdateEditFind(CCmdUI* pCmd)
{
	pCmd->Enable(TRUE);
}
