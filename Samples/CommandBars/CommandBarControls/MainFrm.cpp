// MainFrm.cpp
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
#include "CommandBarControls.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CXTPMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_COMMAND(XTP_ID_CUSTOMIZE, OnCustomize)
	ON_XTP_CREATECONTROL()

	// Styles
	ON_COMMAND(ID_OPTIONS_RIGHTTOLEFT, OnOptionsRighttoleft)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_RIGHTTOLEFT, OnUpdateOptionsRighttoleft)

	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2000,     ID_OPTIONS_STYLE_RIBBON,            OnOptionsStyle)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2007BLUE, ID_OPTIONS_STYLE_OFFICE2007SYSTEM,  OnOptionsStyleOffice2007)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2010BLUE, ID_OPTIONS_STYLE_OFFICE2010BLACK,   OnOptionsStyleOffice2010)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2013WORD, ID_OPTIONS_STYLE_OFFICE2013OUTLOOK, OnOptionsStyleOffice2013)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2013WORD, ID_OPTIONS_STYLE_OFFICE2013OUTLOOK, OnOptionsStyleOffice2013)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_WINDOWS7SCENIC, ID_OPTIONS_STYLE_WINDOWS8SCENIC,    OnOptionsStyle)
	
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2000,     ID_OPTIONS_STYLE_RIBBON,            OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2007BLUE, ID_OPTIONS_STYLE_OFFICE2007SYSTEM,  OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2010BLUE, ID_OPTIONS_STYLE_OFFICE2010BLACK,   OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2013WORD, ID_OPTIONS_STYLE_OFFICE2013OUTLOOK, OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_WINDOWS7SCENIC, ID_OPTIONS_STYLE_WINDOWS8SCENIC,    OnUpdateOptionsStyle)

	ON_COMMAND_RANGE(ID_THEME_VC6, ID_THEME_VC13_LIGHT, OnOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_THEME_VC6, ID_THEME_VC13_LIGHT, OnUpdateOptionsStyle)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
	: m_bCreated(FALSE)
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	XTPPaintManager()->SetTheme(xtpThemeRibbon);

	// Initialize the command bars
	if (!InitCommandBars())
		return -1;

	// Get a pointer to the command bars object.
	CXTPCommandBars* pCommandBars = GetCommandBars();
	if(pCommandBars == NULL)
	{
		TRACE0("Failed to create command bars object.\n");
		return -1;      // fail to create
	}

	pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME);
	pCommandBars->GetImageManager()->SetIcons(IDR_TOOLBAR_COLOR);

	// Add the menu bar
	CXTPMenuBar* pMenuBar = pCommandBars->SetMenu(
		_T("Menu Bar"), IDR_MAINFRAME);
	if(pMenuBar == NULL)
	{
		TRACE0("Failed to create menu bar.\n");
		return -1;      // fail to create
	}

	CXTPToolBar* pToolBarButtons = (CXTPToolBar*) pCommandBars->Add(_T("Buttons"), xtpBarTop);
	pToolBarButtons->SetBarID(IDR_MAINFRAME);

	pToolBarButtons->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlButton:"));
	pToolBarButtons->GetControls()->Add(xtpControlButton, ID_FILE_OPEN);
	pToolBarButtons->GetControls()->Add(xtpControlButton, ID_FILE_SAVE)->SetStyle(xtpButtonCaption);
	pToolBarButtons->GetControls()->Add(xtpControlButton, ID_FILE_PRINT)->SetStyle(xtpButtonIconAndCaption);


	CXTPToolBar* pToolBarPopups = pCommandBars->Add(_T("Popups"), xtpBarTop);
	pToolBarPopups->SetBarID(IDR_MAINFRAME + 2);

	pToolBarPopups->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlPopup:"));
	pToolBarPopups->GetControls()->Add(xtpControlPopup, ID_EDIT_PASTE);
	pToolBarPopups->GetControls()->Add(xtpControlPopup, ID_EDIT_COPY)->SetStyle(xtpButtonIcon);
	pToolBarPopups->GetControls()->Add(xtpControlButtonPopup, ID_EDIT_CUT)->SetStyle(xtpButtonIconAndCaption);
	pToolBarPopups->GetControls()->Add(xtpControlSplitButtonPopup, ID_EDIT_SELECT_ALL)->SetStyle(xtpButtonIconAndCaption);

	DockRightOf(pToolBarPopups, pToolBarButtons);

	CXTPToolBar* pToolBarCombo = pCommandBars->Add(_T("Combo"), xtpBarTop);
	pToolBarCombo->SetBarID(IDR_MAINFRAME + 3);
	pToolBarCombo->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlComboBox:"));
	pToolBarCombo->GetControls()->Add(xtpControlComboBox, ID_FILE_NEW);
	CXTPControlComboBox* pControlCombo = (CXTPControlComboBox*)pToolBarCombo->GetControls()->Add(xtpControlComboBox, ID_FILE_NEW);
	pControlCombo->SetDropDownListStyle();
	DockRightOf(pToolBarCombo, pToolBarPopups);


	CXTPToolBar* pToolBarEdit = pCommandBars->Add(_T("Edit"), xtpBarTop);
	pToolBarEdit->SetBarID(IDR_MAINFRAME + 4);
	pToolBarEdit->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlEdit:"));
	CXTPControlEdit* pControlEdit = (CXTPControlEdit*)pToolBarEdit->GetControls()->Add(xtpControlEdit, ID_FILE_NEW);
	pControlEdit->ShowSpinButtons(TRUE);
	pControlEdit->SetEditIconId(ID_EDIT_COPY);
	
	CXTPToolBar* pToolBarRadio = pCommandBars->Add(_T("Radio"), xtpBarTop);
	pToolBarRadio->SetBarID(IDR_MAINFRAME + 5);
	pToolBarRadio->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlRadioButton:"));
	pToolBarRadio->GetControls()->Add(xtpControlRadioButton, 0);
	DockRightOf(pToolBarRadio, pToolBarEdit);

	CXTPToolBar* pToolBarCheckBox = pCommandBars->Add(_T("CheckBox"), xtpBarTop);
	pToolBarCheckBox->SetBarID(IDR_MAINFRAME + 7);
	pToolBarCheckBox->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlCheckBox:"));
	pToolBarCheckBox->GetControls()->Add(xtpControlCheckBox, 0);
	DockRightOf(pToolBarCheckBox, pToolBarRadio);


	CXTPToolBar* pToolBarListBox = pCommandBars->Add(_T("ListBox"), xtpBarTop);
	pToolBarListBox->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlListBox:"));
	CXTPControlPopup* pPopup = (CXTPControlPopup*)pToolBarListBox->GetControls()->Add(xtpControlPopup, 0);
	pPopup->SetCaption(_T("ListBox"));
	CXTPControlListBox* pListBox = (CXTPControlListBox*)pPopup->GetCommandBar()->GetControls()->Add(new CXTPControlListBox, 0);
	pListBox->GetListCtrl()->AddString(_T("Item 1"));
	pListBox->GetListCtrl()->AddString(_T("Item 2"));

	CXTPToolBar* pToolBarGallery = pCommandBars->Add(_T("Gallery"), xtpBarTop);
	pToolBarGallery->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlGallery:"));

	CXTPControlGalleryItems* pGalleryItems = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_CONTROL_GALLERY);

	CXTPControlGallery* pControlGallery = (CXTPControlGallery*)pToolBarGallery->GetControls()->Add(new CXTPControlGallery(), ID_CONTROL_GALLERY);
	pGalleryItems->AddItem(_T("Item 1"));
	pGalleryItems->AddItem(_T("Item 2"));
	pGalleryItems->AddItem(_T("Item 3"));
	pGalleryItems->AddItem(_T("Item 4"));
	pGalleryItems->AddItem(_T("Item 5"));
	pGalleryItems->SetItemSize(CSize(40, 22));

	pControlGallery->SetHeight(22);
	pControlGallery->SetWidth(140);
	pControlGallery->SetItems(pGalleryItems);
	pControlGallery->SetFlags(xtpFlagManualUpdate);
	
	DockRightOf(pToolBarGallery, pToolBarListBox);

	CXTPToolBar* pToolBarColor = pCommandBars->Add(_T("ColorButton"), xtpBarTop);
	pToolBarColor->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlColorSelector:"));

	CXTPControlPopupColor* pControlButtonColor = (CXTPControlPopupColor*)
		pToolBarColor->GetControls()->Add(new CXTPControlPopupColor(), ID_COLOR_FORE);
	pControlButtonColor->SetColor(0xFF);
	CXTPPopupToolBar* pPopupToolBar = CXTPPopupToolBar::CreatePopupToolBar(pCommandBars);
	pControlButtonColor->SetCommandBar(pPopupToolBar);
	pPopupToolBar->GetControls()->Add(new CXTPControlColorSelector());
	pPopupToolBar->InternalRelease();
	pControlButtonColor->SetFlags(xtpFlagManualUpdate);

	DockRightOf(pToolBarColor, pToolBarGallery);

	CXTPToolBar* pToolBarSlider = pCommandBars->Add(_T("Slider"), xtpBarTop);
	pToolBarSlider->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlSlider:"));
	pToolBarSlider->GetControls()->Add(new CXTPControlSlider());

	CXTPToolBar* pToolBarScrollBar = pCommandBars->Add(_T("ScrollBar"), xtpBarTop);
	pToolBarScrollBar->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlScrollBar:"));
	pToolBarScrollBar->GetControls()->Add(new CXTPControlScrollBar());

	CXTPControlScrollBar* pControlScrolBar = (CXTPControlScrollBar*)pToolBarScrollBar->GetControls()->Add(new CXTPControlScrollBar());
	pControlScrolBar->SetScrollBarStyle(xtpScrollStyleSlider);

	DockRightOf(pToolBarScrollBar, pToolBarSlider);

	CXTPToolBar* pToolBarProgress = pCommandBars->Add(_T("Progress"), xtpBarTop);
	pToolBarProgress->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlProgress:"));
	CXTPControlProgress* pProgressControl = new CXTPControlProgress();
	pToolBarProgress->GetControls()->Add(pProgressControl);
	pProgressControl->SetPos(30);
	DockRightOf(pToolBarProgress, pToolBarScrollBar);
	
	CXTPToolBar* pWorkspaceBar = (CXTPToolBar*)
		pCommandBars->Add(_T("WorkspaceBar"), xtpBarTop);
	if (!pWorkspaceBar)
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	pWorkspaceBar->EnableCustomization(FALSE);

	pCommandBars->GetShortcutManager()->SetAccelerators(IDR_MAINFRAME);

	pWorkspaceBar->GetControls()->Add(xtpControlLabel, 0)->SetCaption(_T("CXTPControlTabWorkspace:"));
	CXTPControlTabWorkspace* pControl = (CXTPControlTabWorkspace*)pWorkspaceBar->GetControls()->Add(new CXTPControlTabWorkspace());
	
	m_wndClient.Attach(this);

	m_wndClient.SetTabWorkspace(pControl);

	pControl->GetPaintManager()->m_bFillBackground = FALSE;
	//pControl->GetPaintManager()->GetAppearanceSet()->m_rcHeaderMargin.top = 1;
	pControl->GetPaintManager()->SetLayout(xtpTabLayoutSizeToFit);
	pControl->SetWidth(400);

	pControl->SetFlags(pControl->GetFlags() | xtpFlagControlStretched);
	pWorkspaceBar->EnableDocking(xtpFlagAlignAny | xtpFlagFloating | xtpFlagStretched);

	m_wndClient.SetFlags(xtpWorkspaceHideAll);

	pWorkspaceBar->SetBarID(IDR_MAINFRAME + 1);
	pWorkspaceBar->GetControls()->CreateOriginalControls();

	OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013WORD);

	m_bCreated = TRUE;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	return TRUE;
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	BOOL bHandled = FALSE;

	if (XTP_CN_UPDATE_CUSTOMIZE_COMMAND_UI == nCode)
	{
		// Manually added toolbar controls have to be made enabled explicitly if necessary.
		CXTPControl** pControls = reinterpret_cast<CXTPControl**>(pExtra);
		CXTPControl* pCustomizedMenuControl = pControls[0];
		CXTPControl* pControl = pControls[1];
		ASSERT(nID == (UINT)pControl->GetID());
		pCustomizedMenuControl->SetEnabled(TRUE);
		bHandled = TRUE;
	}

	return bHandled ? TRUE : CXTPMDIFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

	
void CMainFrame::OnCustomize()
{
	CXTPCustomizeSheet cs(GetCommandBars());

	CXTPCustomizeKeyboardPage pageKeyboard(&cs);
	cs.AddPage(&pageKeyboard);
	pageKeyboard.AddCategories(IDR_COMMANTYPE);

	CXTPCustomizeMenusPage pageMenus(&cs);
	cs.AddPage(&pageMenus);

	CXTPCustomizeOptionsPage pageOptions(&cs);
	cs.AddPage(&pageOptions);



	CXTPCustomizeCommandsPage* pCommands = cs.GetCommandsPage();
	pCommands->AddCategories(IDR_COMMANTYPE);

	pCommands->InsertAllCommandsCategory();
	pCommands->InsertBuiltInMenus(IDR_COMMANTYPE);
	pCommands->InsertNewMenuCategory();


	cs.DoModal();
}

int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	UNREFERENCED_PARAMETER(lpCreateControl);
	return FALSE;
}

void CMainFrame::OnOptionsRighttoleft() 
{
	if (GetExStyle() & WS_EX_LAYOUTRTL)
	{
		GetCommandBars()->SetLayoutRTL(FALSE);
		ModifyStyleEx(WS_EX_LAYOUTRTL, 0);
	}
	else
	{
		GetCommandBars()->SetLayoutRTL(TRUE);
		ModifyStyleEx(0, WS_EX_LAYOUTRTL);
	}	
}

void CMainFrame::OnUpdateOptionsRighttoleft(CCmdUI* pCmdUI) 
{
	if (XTPSystemVersion()->IsLayoutRTLSupported())
	{
		pCmdUI->SetCheck(GetExStyle() & WS_EX_LAYOUTRTL ? TRUE : FALSE);	
	}
	else
	{
		pCmdUI->Enable(FALSE);
	}
}

void CMainFrame::OnUpdateOptionsStyle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nRibbonStyle ? 1 : 0);

}

void CMainFrame::OnOptionsStyleOffice2007(UINT nStyle)
{
	OnOptionsStyle(nStyle);
}

void CMainFrame::OnOptionsStyleOffice2010(UINT nStyle)
{
	OnOptionsStyle(nStyle);
}

void CMainFrame::OnOptionsStyleOffice2013(UINT nStyle)
{
	OnOptionsStyle(nStyle);
}

void CMainFrame::OnOptionsStyle(UINT nStyle)
{
	m_nRibbonStyle = nStyle;

	GetCommandBars()->SetAllCaps(FALSE);
	GetCommandBars()->GetPaintManager()->RefreshMetrics();

	switch (nStyle)
	{
		case ID_OPTIONS_STYLE_OFFICE2007SYSTEM:

			SetCommandBarsTheme(xtpThemeOfficeXP, NULL, NULL);

			GetCommandBars()->GetPaintManager()->GetIconsInfo()->bUseFadedIcons = FALSE;
			GetCommandBars()->GetPaintManager()->GetIconsInfo()->bIconsWithShadow = FALSE;
			GetCommandBars()->GetPaintManager()->GetIconsInfo()->bUseDisabledIcons = TRUE;

			if (XTPSystemVersion()->IsWinVistaOrGreater())
			{
				GetCommandBars()->GetPaintManager()->m_bUseOfficeFont = TRUE;
				GetCommandBars()->GetPaintManager()->m_strOfficeFont = _T("Segoe UI");
				GetCommandBars()->GetPaintManager()->SetFontHeight(XTP_DPI_Y(12));
			}			
			break;

		// Office 2007
		case ID_OPTIONS_STYLE_OFFICE2007BLUE:
			SetCommandBarsTheme(xtpThemeResource, theApp.m_hModule2007, xtpIniOffice2007Blue);
			break;

		case ID_OPTIONS_STYLE_OFFICE2007SILVER:
			SetCommandBarsTheme(xtpThemeResource, theApp.m_hModule2007, xtpIniOffice2007Silver);
			break;
		
		case ID_OPTIONS_STYLE_OFFICE2007BLACK:
			SetCommandBarsTheme(xtpThemeResource, theApp.m_hModule2007, xtpIniOffice2007Black);
			break;

		case ID_OPTIONS_STYLE_OFFICE2007AQUA:
			SetCommandBarsTheme(xtpThemeResource, theApp.m_hModule2007, xtpIniOffice2007Aqua);
			break;

		// Office 2010 styles
		case ID_OPTIONS_STYLE_OFFICE2010BLUE:
			SetCommandBarsTheme(xtpThemeResource, theApp.m_hModule2010, xtpIniOffice2010Blue);
			break;

		case ID_OPTIONS_STYLE_OFFICE2010SILVER:
			SetCommandBarsTheme(xtpThemeResource, theApp.m_hModule2010, xtpIniOffice2010Silver);
			break;

		case ID_OPTIONS_STYLE_OFFICE2010BLACK:
			SetCommandBarsTheme(xtpThemeResource, theApp.m_hModule2010, xtpIniOffice2010Black);
			break;

		// Office 2013 styles
		case ID_OPTIONS_STYLE_OFFICE2013WORD:
			GetCommandBars()->SetAllCaps(TRUE);
			SetCommandBarsTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013Word);
			break;

		case ID_OPTIONS_STYLE_OFFICE2013EXCEL:
			GetCommandBars()->SetAllCaps(TRUE);
			SetCommandBarsTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013Excel);
			break;

		case ID_OPTIONS_STYLE_OFFICE2013ACCESS:
			GetCommandBars()->SetAllCaps(TRUE);
			SetCommandBarsTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013Access);
			break;

		case ID_OPTIONS_STYLE_OFFICE2013POWERPOINT:
			GetCommandBars()->SetAllCaps(TRUE);
			SetCommandBarsTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013PowerPoint);
			break;

		case ID_OPTIONS_STYLE_OFFICE2013ONENOTE:
			GetCommandBars()->SetAllCaps(TRUE);
			SetCommandBarsTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013OneNote);
			break;

		case ID_OPTIONS_STYLE_OFFICE2013OUTLOOK:
			GetCommandBars()->SetAllCaps(TRUE);
			SetCommandBarsTheme(xtpThemeOffice2013, theApp.m_hModule2013, xtpIniOffice2013Outlook);
			break;
			
		// Windows 7 styles
		case ID_OPTIONS_STYLE_WINDOWS7SCENIC:
			SetCommandBarsTheme(xtpThemeResource, theApp.m_hModuleWindows7, xtpIniWindows7Blue);
			break;

		case ID_THEME_VC6:
			SetCommandBarsTheme(xtpThemeVisualStudio6, NULL, NULL);
			break;

		case ID_THEME_VC7:
			SetCommandBarsTheme(xtpThemeOfficeXP, NULL, NULL);;
			break;

		case ID_THEME_VC8:
			SetCommandBarsTheme(xtpThemeVisualStudio2005, NULL, NULL);
			break;

		case ID_THEME_VC9:
			SetCommandBarsTheme(xtpThemeVisualStudio2008, NULL, NULL);
			break;

		case ID_THEME_VC10:
			SetCommandBarsTheme(xtpThemeVisualStudio2010, NULL, NULL);
			break;

		case ID_THEME_VC11_LIGHT:
			SetCommandBarsTheme(xtpThemeVisualStudio2012Light, theApp.m_hModuleVisualStudio2012, xtpIniVisualStudio2012Light);
			break;

		case ID_THEME_VC11_DARK:
			SetCommandBarsTheme(xtpThemeVisualStudio2012Dark, theApp.m_hModuleVisualStudio2012, xtpIniVisualStudio2012Dark);
			break;

		case ID_THEME_VC13_BLUE:
			SetCommandBarsTheme(xtpThemeVisualStudio2015, theApp.m_hModuleVisualStudio2015, xtpIniVisualStudio2015Blue);
			break;

		case ID_THEME_VC13_DARK:
			SetCommandBarsTheme(xtpThemeVisualStudio2015, theApp.m_hModuleVisualStudio2015, xtpIniVisualStudio2015Dark);
			break;

		case ID_THEME_VC13_LIGHT:
			SetCommandBarsTheme(xtpThemeVisualStudio2015, theApp.m_hModuleVisualStudio2015, xtpIniVisualStudio2015Light);
			break;

		case ID_OPTIONS_STYLE_OFFICE2000:
			SetCommandBarsTheme(xtpThemeOffice2000, NULL, NULL);
			break;

		case ID_OPTIONS_STYLE_OFFICEXP:
			SetCommandBarsTheme(xtpThemeOfficeXP, NULL, NULL);
			break;

		case ID_OPTIONS_STYLE_OFFICE2003:
			SetCommandBarsTheme(xtpThemeOffice2003, NULL, NULL);
			break;

		case ID_OPTIONS_STYLE_WINDOWSXP:
			SetCommandBarsTheme(xtpThemeNativeWinXP, NULL, NULL);
			break;

		case ID_OPTIONS_STYLE_RIBBON:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2007, xtpIniOffice2007Blue);
			break;
	}

	UpdateMDIChildrenTheme();

	// Update tooltip styles.
	CXTPToolTipContext* pToolTipContext = m_wndStatusBar.GetToolTipContext();
	if(NULL != pToolTipContext)
	{
		pToolTipContext->SetStyle(GetToolTipStyle());
	}

	pToolTipContext = GetCommandBars()->GetToolTipContext();
	if(NULL != pToolTipContext)
	{
		pToolTipContext->SetStyle(GetToolTipStyle());
	}

	switch(nStyle)
	{
		case ID_THEME_VC11_LIGHT:
		case ID_THEME_VC11_DARK:
		{
			GetCommandBars()->SetAllCaps(TRUE);
			for (int i=0; i<GetCommandBars()->GetCount(); i++)
			{
				CXTPToolBar *pToolBar = GetCommandBars()->GetAt(i);
				pToolBar->SetFlags(xtpFlagAlignTop, xtpFlagAlignBottom | xtpFlagAlignLeft | xtpFlagAlignRight | xtpFlagFloating);

				if (xtpBarTypeMenuBar == pToolBar->GetType())
				{
					pToolBar->SetShowGripper(FALSE);
				}
				else
				{
					pToolBar->SetShowGripper(TRUE);
				}
			}
		}
		break;
		default:
		{
			GetCommandBars()->SetAllCaps(FALSE);
			for (int i=0; i<GetCommandBars()->GetCount(); i++)
			{
				CXTPToolBar *pToolBar = GetCommandBars()->GetAt(i);
				pToolBar->SetFlags(xtpFlagAlignTop | xtpFlagAlignBottom | xtpFlagAlignLeft | xtpFlagAlignRight | xtpFlagFloating, 0);
				pToolBar->SetShowGripper(TRUE);
			}
		}
		break;
	}

	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, FALSE);
	GetCommandBars()->GetImageManager()->RefreshAll();
	GetCommandBars()->GetPaintManager()->RefreshMetrics();

	GetCommandBars()->RedrawCommandBars();
	SendMessage(WM_NCPAINT);

	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);
}

void CMainFrame::SetCommandBarsTheme(XTPPaintTheme paintTheme, HMODULE hModule/*=NULL*/, LPCTSTR lpszINI/*=NULL*/)
{
	GetCommandBars()->EnableFrameTheme(FALSE);

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars != NULL)
	{
		pCommandBars->GetImageManager()->RemoveAll();
		
		switch (paintTheme)
		{
		case xtpThemeOffice2013:
		case xtpThemeVisualStudio2012Light:
		case xtpThemeVisualStudio2012Dark:
		case xtpThemeVisualStudio2015:
			{
				UINT uiSystemMenu[] = {ID_FILE_NEW,ID_FILE_OPEN,ID_FILE_SAVE,ID_EDIT_CUT,ID_EDIT_COPY,ID_EDIT_PASTE,ID_FILE_PRINT,ID_APP_ABOUT};				 
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_16, uiSystemMenu, _countof(uiSystemMenu), CSize(16, 16));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_24, uiSystemMenu, _countof(uiSystemMenu), CSize(24, 24));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_32, uiSystemMenu, _countof(uiSystemMenu), CSize(32, 32));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_40, uiSystemMenu, _countof(uiSystemMenu), CSize(40, 40));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_48, uiSystemMenu, _countof(uiSystemMenu), CSize(48, 48));
				pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME2013_64, uiSystemMenu, _countof(uiSystemMenu), CSize(64, 64));
			}
			break;
		default:
			pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME);
			break;
		}
		
		if (hModule != NULL && lpszINI != NULL)
		{
			XTPResourceImages()->SetHandle(hModule, lpszINI);
			XTPPaintManager()->SetTheme(paintTheme);
		}
		else
		{
			XTPPaintManager()->SetTheme(paintTheme);
		}

		switch(paintTheme)
		{
			case xtpThemeOffice2013:
			case xtpThemeResource:
			case xtpThemeRibbon:
			case xtpThemeVisualStudio2012:
			case xtpThemeVisualStudio2012Light:
			case xtpThemeVisualStudio2012Dark:
			case xtpThemeVisualStudio2015:
				CXTPCommandBarsFrameHook::m_bAllowDwm = FALSE;
				GetCommandBars()->EnableFrameTheme(TRUE);
				break;

			default:
				CXTPCommandBarsFrameHook::m_bAllowDwm = TRUE;
				GetCommandBars()->EnableFrameTheme(NULL);
				break;
		}
	}
}


XTPToolTipStyle CMainFrame::GetToolTipStyle() const
{
	XTPToolTipStyle style;

	switch(m_nRibbonStyle)
	{
		// Office 2007
		case ID_OPTIONS_STYLE_OFFICE2007BLUE:
		case ID_OPTIONS_STYLE_OFFICE2007SILVER:
		case ID_OPTIONS_STYLE_OFFICE2007BLACK:
		case ID_OPTIONS_STYLE_OFFICE2007AQUA:
			style = xtpToolTipOffice2007;
			break;

		// Office 2010 styles
		case ID_OPTIONS_STYLE_OFFICE2010BLUE:
		case ID_OPTIONS_STYLE_OFFICE2010SILVER:
		case ID_OPTIONS_STYLE_OFFICE2010BLACK:
			style = xtpToolTipOffice;
			break;

		// Windows styles
		case ID_OPTIONS_STYLE_WINDOWS7SCENIC:
			style = xtpToolTipLuna;
			break;

		default:
			style = xtpToolTipStandard;
			break;
	}

	return style;
}
