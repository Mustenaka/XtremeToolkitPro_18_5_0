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
#include "RibbonControls.h"
#include "GalleryItems.h"
#include <vector>

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_XTP_CREATECONTROL()
	
	ON_COMMAND(ID_BUTTON_LARGETOGGLEBUTTON, OnToggleButton)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_LARGETOGGLEBUTTON, OnUpdateToggleButton)

	ON_UPDATE_COMMAND_UI_RANGE(ID_BUTTON_LARGESIMPLEBUTTON, ID_BUTTON_SMALLSPLITPOPUPBUTTON, OnEnableButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_POPUP_OPTION1, ID_POPUP_OPTION3, OnEnableButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_EDITOR_EDIT, ID_EDITOR_COMBO2, OnEnableButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_EDITOR_EXTENDEDEDIT, ID_EDITOR_EXTENDEDCOMBO, OnEnableButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GALLERY_FONTFACE, ID_EDITOR_POPUP, OnEnableButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GALLERY_STYLES, ID_GALLERY_TABLE, OnEnableButton)

	ON_UPDATE_COMMAND_UI(ID_GALLERY_COLOR, OnUpdateSelectorText)
	ON_XTP_EXECUTE(ID_GALLERY_COLOR, OnSelectorText)

	ON_UPDATE_COMMAND_UI(ID_GALLERY_UNDO, OnUpdateEditUndo)
	ON_XTP_EXECUTE(ID_GALLERY_UNDO, OnEditUndo)

	ON_COMMAND_RANGE(ID_BUTTON_CHECKBOX1, ID_BUTTON_CHECKBOX3, OnCheckbox)
	ON_COMMAND_RANGE(ID_BUTTON_RADIOBUTTON1, ID_BUTTON_RADIOBUTTON3, OnRadioButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BUTTON_CHECKBOX1, ID_BUTTON_CHECKBOX3, OnUpdateCheckbox)
	ON_UPDATE_COMMAND_UI_RANGE(ID_BUTTON_RADIOBUTTON1, ID_BUTTON_RADIOBUTTON3, OnUpdateRadioButton)

	ON_COMMAND(ID_OPTIONS_RIGHTTOLEFT, OnOptionsRighttoleft)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_RIGHTTOLEFT, OnUpdateOptionsRighttoleft)

	// Styles
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2007BLUE,   ID_OPTIONS_STYLE_OFFICE2007SYSTEM,  OnStyleOffice2007)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2010BLUE, ID_OPTIONS_STYLE_OFFICE2010BLACK,  OnStyleOffice2010)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_OFFICE2013WORD, ID_OPTIONS_STYLE_OFFICE2013ONENOTE, OnOptionsStyleOffice2013)
	ON_COMMAND_RANGE(ID_OPTIONS_STYLE_WINDOWS7SCENIC, ID_OPTIONS_STYLE_WINDOWS8SCENIC,    OnOptionsStyle)
	
	// Font
	ON_COMMAND_RANGE(ID_OPTIONS_FONT_SYSTEM, ID_OPTIONS_FONT_EXTRALARGE, OnOptionsFont)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_FONT_SYSTEM, ID_OPTIONS_FONT_EXTRALARGE, OnUpdateOptionsFont)

	ON_COMMAND(ID_OPTIONS_FONT_AUTORESIZEICONS, OnAutoResizeIcons)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FONT_AUTORESIZEICONS, OnUpdateAutoResizeIcons)

	ON_COMMAND(ID_OPTIONS_DPI_ICON_SCALING, OnDpiIconsScalling)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DPI_ICON_SCALING, OnUpdateDpiIconsScalling)

	//theme
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2007BLUE, ID_OPTIONS_STYLE_OFFICE2007SYSTEM,  OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2010BLUE, ID_OPTIONS_STYLE_OFFICE2010BLACK,  OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_OFFICE2013WORD, ID_OPTIONS_STYLE_OFFICE2013ONENOTE, OnUpdateOptionsStyle)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OPTIONS_STYLE_WINDOWS7SCENIC, ID_OPTIONS_STYLE_WINDOWS8SCENIC,    OnUpdateOptionsStyle)


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
{
	m_bCheckbox[0] = TRUE;
	m_bCheckbox[1] = FALSE;
	m_bCheckbox[2] = FALSE;
	m_nRadioButton = 1;
	m_bToggleButton = FALSE;

	m_nRibbonStyle = ID_OPTIONS_STYLE_OFFICE2007BLUE;
	m_clr = 0;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CXTPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	XTPPaintManager()->SetTheme(xtpThemeRibbon);

	if (!CreateStatusBar())
		return -1;

	if (!InitCommandBars())
		return -1;

	CXTPCommandBars* pCommandBars = GetCommandBars();
	m_wndStatusBar.SetCommandBars(pCommandBars);

	if (!CreateRibbonBar())
	{
		TRACE0("Failed to create ribbon\n");
		return -1;
	}

	CXTPToolTipContext* pToolTipContext = GetCommandBars()->GetToolTipContext();
	pToolTipContext->SetStyle(xtpToolTipResource);
	pToolTipContext->ShowTitleAndDescription();
	pToolTipContext->ShowImage(TRUE, 0, 64);
	pToolTipContext->SetMargin(XTP_DPI_RECT(CRect(2, 2, 2, 2)));
	pToolTipContext->SetMaxTipWidth(180);
	pToolTipContext->SetFont(pCommandBars->GetPaintManager()->GetIconFont());
	pToolTipContext->SetDelayTime(TTDT_INITIAL, 900);
	pToolTipContext->EnableImageDPIScaling(FALSE);

	pCommandBars->GetCommandBarsOptions()->bShowKeyboardTips = TRUE;

	OnOptionsStyleOffice2013(ID_OPTIONS_STYLE_OFFICE2013WORD);

	return 0;
}

BOOL CMainFrame::CreateStatusBar()
{
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return FALSE;      // fail to create
	}

	m_wndStatusBar.AddIndicator(0);
	m_wndStatusBar.AddIndicator(ID_INDICATOR_CAPS);
	m_wndStatusBar.AddIndicator(ID_INDICATOR_NUM);
	m_wndStatusBar.AddIndicator(ID_INDICATOR_SCRL);

	return TRUE;
}

BOOL CMainFrame::CreateRibbonBar()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	CMenu menu;
	menu.Attach(::GetMenu(m_hWnd));
	SetMenu(NULL);

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)pCommandBars->Add(_T("The Ribbon"), xtpBarTop, RUNTIME_CLASS(CXTPRibbonBar));
	if (!pRibbonBar)
	{
		return FALSE;
	}
	pRibbonBar->EnableDocking(0);

	CXTPControlPopup* pControlFile = (CXTPControlPopup*)pRibbonBar->AddSystemButton(ID_MENU_FILE);
	pControlFile->SetIconId(IDB_GEAR);
	
	CreateBackstage();
	
	CXTPRibbonTab* pTabHome = pRibbonBar->AddTab(ID_TAB_BUTTONS);

	// Large Buttons
	if (pTabHome)
	{
		CXTPControl* pControl;

		CXTPRibbonGroup* pGroup = pTabHome->AddGroup(ID_GROUP_LARGEBUTTONS);
		pGroup->ShowOptionButton();

		pControl = pGroup->Add(xtpControlButton, ID_BUTTON_LARGESIMPLEBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButton, ID_BUTTON_LARGETOGGLEBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlButtonPopup, ID_BUTTON_LARGEPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);

		pControl = pGroup->Add(xtpControlSplitButtonPopup, ID_BUTTON_LARGESPLITPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaptionBelow);
	}

	// Small Buttons
	if (pTabHome)
	{
		CXTPControl* pControl;

		CXTPRibbonGroup* pGroup = pTabHome->AddGroup(ID_GROUP_SMALLBUTTONS);

		pControl = pGroup->Add(xtpControlButton, ID_BUTTON_SMALLSIMPLEBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaption);

		pControl = pGroup->Add(xtpControlPopup, ID_BUTTON_SMALLPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaption);

		pControl = pGroup->Add(xtpControlSplitButtonPopup, ID_BUTTON_SMALLSPLITPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIconAndCaption);

		pControl = pGroup->Add(xtpControlButton, ID_BUTTON_SMALLSIMPLEBUTTON);
		pControl->SetStyle(xtpButtonIcon);

		pControl = pGroup->Add(xtpControlPopup, ID_BUTTON_SMALLPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIcon);

		pControl = pGroup->Add(xtpControlSplitButtonPopup, ID_BUTTON_SMALLSPLITPOPUPBUTTON);
		pControl->SetStyle(xtpButtonIcon);
	}

	// CheckBoxes and Radio Buttons
	if (pTabHome)
	{

		CXTPRibbonGroup* pGroup = pTabHome->AddGroup(ID_GROUP_CHECKBOXES);
		CXTPControl* pControl;

		pControl = pGroup->Add(xtpControlCheckBox, ID_BUTTON_CHECKBOX1);

		pControl = pGroup->Add(xtpControlCheckBox, ID_BUTTON_CHECKBOX2);

		pControl = pGroup->Add(xtpControlCheckBox, ID_BUTTON_CHECKBOX3);


		pControl = pGroup->Add(xtpControlRadioButton, ID_BUTTON_RADIOBUTTON1);
		pControl->SetBeginGroup(TRUE);

		pControl = pGroup->Add(xtpControlRadioButton, ID_BUTTON_RADIOBUTTON2);

		pControl = pGroup->Add(xtpControlRadioButton, ID_BUTTON_RADIOBUTTON3);
	}

	if (pTabHome)
	{
		CXTPRibbonGroup* pGroup = pTabHome->AddGroup(ID_GROUP_GROUP);
		pGroup->SetControlsGrouping(TRUE);
		pGroup->SetControlsCentering(TRUE);

		pGroup->LoadToolBar(IDR_MAINFRAME);
	}

	CXTPRibbonTab* pTabEditors = pRibbonBar->AddTab(ID_TAB_EDITORS);

	// Standard Editors
	if (pTabEditors)
	{
		CXTPRibbonGroup* pGroup = pTabEditors->AddGroup(ID_GROUP_STANDARDEDITORS);

		CXTPControlEdit* pControlEdit = (CXTPControlEdit*)pGroup->Add(xtpControlEdit, ID_EDITOR_EDIT);
		pControlEdit->SetEditText(_T("Edit"));
		//pControlEdit->ShowSpinButtons(TRUE);
		pControlEdit->SetWidth(XTP_DPI_X(150));
		pControlEdit->SetStyle(xtpButtonIcon);

		CXTPControlComboBox* pControlCombo = (CXTPControlComboBox*)pGroup->Add(xtpControlComboBox, ID_EDITOR_COMBO);
		
		pControlCombo->GetCommandBar()->SetCommandBars(pCommandBars);
		pControlCombo->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

		pControlCombo->SetWidth(XTP_DPI_X(150));
		pControlCombo->SetStyle(xtpButtonIcon);
		pControlCombo->SetDropDownListStyle();
		pControlCombo->SetEditText(_T("ComboBox"));
		pControlCombo->AddString(_T("Item 1"));
		pControlCombo->AddString(_T("Item 2"));

		pControlCombo = (CXTPControlComboBox*)pGroup->Add(xtpControlComboBox, ID_EDITOR_COMBO2);

		pControlCombo->GetCommandBar()->SetCommandBars(pCommandBars);
		pControlCombo->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

		pControlCombo->SetWidth(XTP_DPI_X(150));
		pControlCombo->SetStyle(xtpButtonIcon);

		pControlCombo->AddString(_T("ComboBox"));
		pControlCombo->AddString(_T("Item 1"));
		pControlCombo->AddString(_T("Item 2"));
		pControlCombo->SetCurSel(0);
	}

	// Extended Editors
	if (pTabEditors)
	{
		CXTPRibbonGroup* pGroup = pTabEditors->AddGroup(ID_GROUP_EXTENDEDEDITORS);

		CXTPControlEdit* pControlEdit = (CXTPControlEdit*)pGroup->Add(xtpControlEdit, ID_EDITOR_EXTENDEDEDIT);
		pControlEdit->SetEditText(_T("0"));
		pControlEdit->ShowSpinButtons(TRUE);
		pControlEdit->SetWidth(XTP_DPI_X(150));
		pControlEdit->SetStyle(xtpButtonIconAndCaption);

		CXTPControlComboBox* pControlCombo = (CXTPControlComboBox*)pGroup->Add(xtpControlComboBox, ID_EDITOR_EXTENDEDCOMBO);
		
		pControlCombo->GetCommandBar()->SetCommandBars(pCommandBars);
		pControlCombo->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

		pControlCombo->SetWidth(XTP_DPI_X(155));
		pControlCombo->SetStyle(xtpButtonIconAndCaption);
		pControlCombo->SetDropDownListStyle();
		pControlCombo->SetEditText(_T("ComboBox"));
		pControlCombo->AddString(_T("Item 1"));
		pControlCombo->AddString(_T("Item 2"));

		pControlCombo = (CXTPControlComboBox*)pGroup->Add(xtpControlComboBox, ID_EDITOR_EXTENDEDCOMBO);

		pControlCombo->GetCommandBar()->SetCommandBars(pCommandBars);
		pControlCombo->ModifyListBoxStyle(0, LBS_OWNERDRAWFIXED | LBS_HASSTRINGS);

		pControlCombo->SetWidth(XTP_DPI_X(155));
		pControlCombo->SetStyle(xtpButtonIconAndCaption);

		pControlCombo->AddString(_T("ComboBox"));
		pControlCombo->AddString(_T("Item 1"));
		pControlCombo->AddString(_T("Item 2"));
		pControlCombo->SetCurSel(0);
	}

	// Gallery Editors
	{
		CXTPRibbonGroup* pGroup = pTabEditors->AddGroup(ID_GROUP_GALLERY);

		
		CXTPControlGalleryItems* m_pItemsFontFace = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_FONTFACE);
		m_pItemsFontFace->SetItemSize(CSize(0, 26));
		CGalleryItemFontFace::AddFontItems(m_pItemsFontFace);


		CXTPControlComboBox* pComboFont = new CXTPControlComboBox();
		pGroup->Add(pComboFont, ID_GALLERY_FONTFACE);
		
		pComboFont->SetDropDownListStyle();
		pComboFont->EnableAutoComplete();
		pComboFont->SetWidth(XTP_DPI_X(150));
		
		CXTPPopupBar* pPopupBarGallery = CXTPControlComboBoxGalleryPopupBar::CreateComboBoxGalleryPopupBar(pCommandBars);
		
		pComboFont->SetCommandBar(pPopupBarGallery);
		
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(290, 508));
		pControlGallery->SetResizable(FALSE, TRUE);
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->SetItems(m_pItemsFontFace);
		
		pPopupBarGallery->GetControls()->Add(pControlGallery, ID_GALLERY_FONTFACE);
		
		pPopupBarGallery->InternalRelease();
		
		
		CXTPControlComboBox* pComboPopup = new CXTPControlComboBox();
		pComboPopup->SetWidth(XTP_DPI_X(150));

		pGroup->Add(pComboPopup, ID_EDITOR_POPUP);

		CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(pCommandBars);
		pPopupBar->SetWidth(XTP_DPI_X(150));
		
		pComboPopup->SetCommandBar(pPopupBar);

		CMenu menu;
		menu.LoadMenu(IDR_MENU_OPTIONS);
		pPopupBar->LoadMenu(menu.GetSubMenu(0));

		pPopupBar->InternalRelease();

	}


	CXTPRibbonTab* pTabGallery = pRibbonBar->AddTab(ID_TAB_GALLERIES);

	// Create Gallery Items
	{

		m_pItemsStyles = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_STYLES);
		
		m_pItemsStyles->GetImageManager()->SetMaskColor(0xFF00FF);
		m_pItemsStyles->GetImageManager()->SetIcons(ID_GALLERY_STYLES, 0, 0, CSize(64, 48));
		m_pItemsStyles->GetImageManager()->SetMaskColor(COLORREF_NULL); // Default TopLeft Pixel.
		
		m_pItemsStyles->SetItemSize(CSize(72, 56));
		
		for (int nStyle = 0; nStyle < 16; nStyle++)
			m_pItemsStyles->AddItem(nStyle, nStyle);

		m_pItemsTable = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_TABLE);
		m_pItemsTable->ClipItems(FALSE); //Redraw all Items if selection changed
		m_pItemsTable->SetItemSize(CSize(19, 19));
		
		CXTPControlGalleryItem* pItem = m_pItemsTable->AddItem(new CGalleryItemTableLabel());
		int nItem;
		for (nItem = 0; nItem < 10 * 8; nItem++)
			m_pItemsTable->AddItem(new CGalleryItemTable(nItem));

		m_pItemsFontTextColor = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_COLOR);
		m_pItemsFontTextColor->SetItemSize(XTP_DPI(CSize(17, 17)));
		
		pItem = m_pItemsFontTextColor->AddLabel(0);
		pItem->SetCaption(_T("Theme Colors"));
		CGalleryItemFontColor::AddThemeColors(m_pItemsFontTextColor, 0);
		
		pItem = m_pItemsFontTextColor->AddLabel(0);
		pItem->SetCaption(_T("Standard Colors"));
		CGalleryItemFontColor::AddStandardColors(m_pItemsFontTextColor);

		m_pItemsUndo = CXTPControlGalleryItems::CreateItems(GetCommandBars(), ID_GALLERY_UNDO);
		m_pItemsUndo->SetItemSize(CSize(0, 21));
		m_pItemsUndo->ClipItems(FALSE);	

	}

	// Create Popup Gallery
	if (pTabGallery)
	{
		CXTPRibbonGroup* pGroup = pTabGallery->AddGroup(ID_GROUP_POPUP);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlPopup* pControl = (CXTPControlPopup*)pGroup->Add(xtpControlButtonPopup, ID_GALLERY_STYLES);
		
		CMenu menu;
		menu.LoadMenu(ID_STYLES_QUICKSTYLES);
		
		CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
		pPopupBar->LoadMenu(menu.GetSubMenu(0));
		
		pControl->SetCommandBar(pPopupBar);
		pPopupBar->InternalRelease();

		pControl = (CXTPControlPopup*)pGroup->Add(xtpControlButtonPopup, ID_GALLERY_TABLE);

		CXTPControlGallery *pControlGallery = new CXTPControlGallery();
		
		pControlGallery->SetControlSize(8, 10, CSize(19, 19));
		
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->ShowScrollBar(FALSE);
		pControlGallery->SetItems(m_pItemsTable);

		pControl->GetCommandBar()->GetControls()->Add(pControlGallery);

		pControl = (CXTPControlPopup*)pGroup->Add(xtpControlButtonPopup, ID_GALLERY_COLOR);

		pControlGallery = new CXTPControlGallery();
		pControlGallery->ShowLabels(TRUE);
		pControlGallery->ShowScrollBar(FALSE);
		pControlGallery->SetItems(m_pItemsFontTextColor);

		pControlGallery->SetControlSize(7, 10, XTP_DPI(CSize(17, 15)));

		pControl->GetCommandBar()->GetControls()->Add(pControlGallery);

		CXTPControlPopup* pControlUndo = (CXTPControlPopup*)pGroup->Add(xtpControlSplitButtonPopup, ID_GALLERY_UNDO);

		pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
		pPopupBar->SetShowGripper(FALSE);
		
		pControlUndo->SetCommandBar(pPopupBar);
		
		pControlGallery = new CControlGalleryUndo();
		pControlGallery->SetItems(m_pItemsUndo);
		pControlGallery->SetWidth(XTP_DPI_X(120));
		pControlGallery->ShowScrollBar(FALSE);
		pPopupBar->GetControls()->Add(pControlGallery, ID_GALLERY_UNDO);
		
		CXTPControlStatic* pControlListBoxInfo = (CXTPControlStatic*)pPopupBar->GetControls()->Add(new CXTPControlStatic(), ID_GALLERY_UNDO);
		pControlListBoxInfo->SetWidth(XTP_DPI_X(120));
		pControlListBoxInfo->SetFlags(xtpFlagSkipFocus);
		
		pPopupBar->InternalRelease();	
	}

	// Create Inline Gallery
	if (pTabGallery)
	{
		CXTPRibbonGroup* pGroup = pTabGallery->AddGroup(ID_GROUP_INLINE);
		pGroup->SetControlsCentering(TRUE);

		const int nScrollWidth = XTP_DPI_X(19);
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetControlSize(CSize(XTP_DPI_X(17) * 10 + nScrollWidth, 60));
		pControlGallery->ShowLabels(FALSE);
		pControlGallery->ShowScrollBar(TRUE);
		pControlGallery->ShowBorders(TRUE);
		pControlGallery->SetItems(m_pItemsFontTextColor);

		pGroup->Add(pControlGallery, ID_GALLERY_STYLES);


		pControlGallery = new CXTPControlGallery();
		pControlGallery->SetBeginGroup(TRUE);
		pControlGallery->SetControlSize(CSize(235, 60));
		pControlGallery->SetResizable();
		pControlGallery->SetItemsMargin(0, 1, 0, 1);
		pControlGallery->ShowLabels(FALSE);
		pControlGallery->ShowBorders(TRUE);
		pControlGallery->SetItems(m_pItemsStyles);
		
		
		CMenu menu;
		menu.LoadMenu(ID_STYLES_QUICKSTYLES);
		
		CXTPPopupBar* pPopupBar = CXTPPopupBar::CreatePopupBar(GetCommandBars());
		pPopupBar->LoadMenu(menu.GetSubMenu(0));
		
		pControlGallery->SetCommandBar(pPopupBar);
		pPopupBar->InternalRelease();
		
		pGroup->Add(pControlGallery, ID_GALLERY_STYLES);
	}

	CXTPRibbonTab* pTabMisc = pRibbonBar->AddTab(ID_TAB_MISC);

	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_LABEL);
		pGroup->SetControlsCentering(TRUE);

		CXTPControl* pControl = pGroup->Add(xtpControlLabel, 0);
		pControl->SetCaption(_T("Label Text 1"));
		pControl->SetStyle(xtpButtonCaption);
		
		pControl = pGroup->Add(xtpControlLabel, 0);
		pControl->SetCaption(_T("Label Text 2"));
		pControl->SetStyle(xtpButtonCaption);

		pControl = pGroup->Add(xtpControlLabel, 0);
		pControl->SetCaption(_T("Label Text 3"));
		pControl->SetStyle(xtpButtonCaption);

#ifdef _XTP_INCLUDE_MARKUP
		CXTPControlMarkupLabel* pLabel = new CXTPControlMarkupLabel();
		pGroup->Add(pLabel, 0);

		pLabel->SetBeginGroup(TRUE);
		pLabel->SetCaption(_T("<TextBlock TextAlignment='Center'><Underline>This is</Underline><LineBreak/><Bold>Markup</Bold> <Run Foreground='Red'>Label</Run><LineBreak/><Italic>Control</Italic></TextBlock>"));
#endif
	}

	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_BITMAP);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlBitmap* pLabel = new CXTPControlBitmap();
		pGroup->Add(pLabel, ID_BUTTON_BITMAP);
	}

	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_HYPERLINK);
		pGroup->SetControlsCentering(TRUE);
		pGroup->GetControlGroupPopup()->SetIconSize(CSize(48, 48));

		CXTPControlHyperlink* pLabel = new CXTPControlHyperlink();
		pLabel->SetFlags(xtpFlagManualUpdate);
		pGroup->Add(pLabel, ID_BUTTON_URLLINK);

		pLabel = new CXTPControlHyperlink();
		pLabel->SetFlags(xtpFlagManualUpdate);
		pGroup->Add(pLabel, ID_BUTTON_EMAILLINK);
	}
	
	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_PROGRESS);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlProgress* pControl = (CXTPControlProgress*)pGroup->Add(new CXTPControlProgress(), 0);
		pControl->SetPos(30);
		pControl->SetFlags(xtpFlagNoMovable | xtpFlagSkipFocus);
	}

	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_SCROLLBAR);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlScrollBar* pControl = (CXTPControlScrollBar*)pGroup->Add(new CXTPControlScrollBar(), 0);
		pControl->SetFlags(xtpFlagNoMovable | xtpFlagSkipFocus);
		pControl->SetPos(30);
		pControl->SetWidth(XTP_DPI_X(100));
	}

	if (pTabMisc)
	{
		CXTPRibbonGroup* pGroup = pTabMisc->AddGroup(ID_GROUP_SLIDER);
		pGroup->SetControlsCentering(TRUE);

		CXTPControlScrollBar* pControl = (CXTPControlScrollBar*)pGroup->Add(new CXTPControlScrollBar(), 0);
		pControl->SetScrollBarStyle(xtpScrollStyleSlider);
		pControl->SetPos(30);
		pControl->SetFlags(xtpFlagNoMovable | xtpFlagSkipFocus);
		pControl->SetWidth(XTP_DPI_X(100));
	}


	// Options
	{
		CXTPControlPopup* pControlOptions = (CXTPControlPopup*)pRibbonBar->GetControls()->Add(xtpControlPopup, -1);
		pControlOptions->SetFlags(xtpFlagRightAlign);
		CMenu mnuOptions;
		mnuOptions.LoadMenu(IDR_MENU_OPTIONS);
		pControlOptions->SetCommandBar(mnuOptions.GetSubMenu(0));
		pControlOptions->SetCaption(_T("Options"));
		
		
		CXTPControl* pControlAbout = pRibbonBar->GetControls()->Add(xtpControlButton, ID_APP_ABOUT);
		pControlAbout->SetFlags(xtpFlagRightAlign);
	}

	// Quick Access
	{

		pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_NEW);
		pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_OPEN)->SetHideFlag(xtpHideCustomize, TRUE);
		pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_SAVE);
		
		pRibbonBar->GetQuickAccessControls()->Add(xtpControlButton, ID_FILE_PRINT);
		pRibbonBar->GetQuickAccessControls()->CreateOriginalControls();

	}

	pRibbonBar->SetCloseable(FALSE);
	pRibbonBar->EnableFrameTheme();

	return TRUE;
}

void CMainFrame::CreateBackstage()
{
	CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, GetCommandBars()->GetMenuBar());
	ASSERT (pRibbonBar);

	CXTPRibbonControlSystemButton* pButton = pRibbonBar->GetSystemButton();

	CXTPRibbonBackstageView* pView = CXTPRibbonBackstageView::CreateBackstageView(GetCommandBars());

	pView->AddCommand(ID_FILE_SAVE);
	pView->AddCommand(ID_FILE_OPEN);
	pView->AddCommand(ID_FILE_PRINT);
	pView->AddCommand(ID_FILE_PRINT_PREVIEW);
	pView->AddCommand(ID_FILE_PRINT_SETUP);

	pView->AddCommand(ID_APP_EXIT);

	pButton->SetCommandBar(pView);
	
	pView->InternalRelease();
}

void CMainFrame::CreateSystemMenuPopup()
{
	CXTPRibbonBar* pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, GetCommandBars()->GetMenuBar());
	ASSERT (pRibbonBar);
	
	
	CXTPRibbonControlSystemButton* pControlFile = pRibbonBar->GetSystemButton();

	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);

	
	CXTPPopupBar* pCommandBar = new CXTPRibbonSystemPopupBar();
	pCommandBar->SetCommandBars(GetCommandBars());
	
	pControlFile->SetCommandBar(pCommandBar);
	pCommandBar->InternalRelease();


	pCommandBar->LoadMenu(menu.GetSubMenu(0));

	pCommandBar->SetIconSize(CSize(36, 36));
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx = XTP_DPI_X(730);
	cs.cy = XTP_DPI_Y(600);

	cs.lpszClass = _T("XTPMainFrame");
	CXTPDrawHelpers::RegisterWndClass(AfxGetInstanceHandle(), cs.lpszClass, 
		CS_DBLCLKS, AfxGetApp()->LoadIcon(IDR_MAINFRAME));

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


int CMainFrame::OnCreateControl(LPCREATECONTROLSTRUCT lpCreateControl)
{
	if (lpCreateControl->nID == ID_FILE_RECENTDOCUMENTS)
	{		
		lpCreateControl->pControl = new CXTPRibbonControlSystemRecentFileList();
		return TRUE;
	}

	if (lpCreateControl->nID == ID_APP_EXIT || lpCreateControl->nID == ID_APP_OPTIONS)
	{		
		lpCreateControl->pControl = new CXTPRibbonControlSystemPopupBarButton();

		return TRUE;
	}

	if (lpCreateControl->nID == ID_GALLERY_STYLES)
	{
		
		CXTPControlGallery* pControlGallery = new CXTPControlGallery();
		pControlGallery->SetResizable();
		pControlGallery->SetControlSize(CSize(235 + 72, 56 * 3));
		pControlGallery->SetItems(m_pItemsStyles);
		
		lpCreateControl->pControl = pControlGallery;

		return TRUE;
	}
	return FALSE;

}

void CMainFrame::OnEnableButton(CCmdUI* pCmdUI)
{
	pCmdUI->Enable();
}


void CMainFrame::OnCheckbox(UINT nID)
{
	m_bCheckbox[nID - ID_BUTTON_CHECKBOX1] ^= 1;

}

void CMainFrame::OnRadioButton(UINT nID)
{
	m_nRadioButton = nID - ID_BUTTON_RADIOBUTTON1;
}

void CMainFrame::OnUpdateCheckbox(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bCheckbox[(int)pCmdUI->m_nID - ID_BUTTON_CHECKBOX1]);

}

void CMainFrame::OnUpdateRadioButton(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck((int)pCmdUI->m_nID - ID_BUTTON_RADIOBUTTON1 == m_nRadioButton);
}

void CMainFrame::OnToggleButton()
{
	m_bToggleButton ^= 1;
}

void CMainFrame::OnUpdateToggleButton(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bToggleButton);
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

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmd)
{
	CXTPControlGallery* pControlUndo = DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmd));

	if (pControlUndo)
	{
		pCmd->Enable(TRUE);

		CXTPControlGalleryItems* pItems = pControlUndo->GetItems();
		pItems->RemoveAll();

		int nCount = RAND_S() % 20 + 3;

		for (int i = 0; i < nCount; i++)
		{
			CString str;
			str.Format(_T("Undo String %i"), i + 1);
			pItems->AddItem(new CGalleryItemUndo(str), i);
		}

		pControlUndo->OnSelectedItemChanged();
		pControlUndo->SetHeight(pItems->GetItemSize().cy * nCount + 2);

	}
	else
	{
		pCmd->Enable();
	}

}

void CMainFrame::OnEditUndo(NMHDR* pNMHDR, LRESULT* pResult)
{
	CXTPControlGallery* pControlUndo = DYNAMIC_DOWNCAST(CXTPControlGallery, ((NMXTPCONTROL*)pNMHDR)->pControl);
	if (pControlUndo)
	{
		CString str;
		str.Format(_T("Undo last %i actions"), pControlUndo->GetSelectedItem() + 1);

		AfxMessageBox(str);
	}
	*pResult = 1; // Handled;
}


void CMainFrame::OnUpdateSelectorText(CCmdUI* pCmdUI)
{
	CXTPControlGallery* pControl = 	DYNAMIC_DOWNCAST(CXTPControlGallery, CXTPControl::FromUI(pCmdUI));

	if (pControl)
	{
		pControl->SetCheckedItem(m_clr);
	}

	pCmdUI->Enable(TRUE);

}

void CMainFrame::OnSelectorText(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMXTPCONTROL* tagNMCONTROL = (NMXTPCONTROL*)pNMHDR;

	CXTPControlGallery* pControl = DYNAMIC_DOWNCAST(CXTPControlGallery, tagNMCONTROL->pControl);
	
	if (pControl)
	{
		CXTPControlGalleryItem* pItem = pControl->GetItem(pControl->GetSelectedItem());
		if (pItem)
		{
			m_clr = (COLORREF)pItem->GetID();
		}

		*pResult = TRUE; // Handled
	}


	*pResult = 1;
}

void CMainFrame::OnUpdateOptionsStyle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nRibbonStyle ? 1 : 0);

}

void CMainFrame::OnStyleOffice2007(UINT nStyle)
{
	OnOptionsStyle(nStyle);
}

void CMainFrame::OnStyleOffice2010(UINT nStyle)
{
	OnOptionsStyle(nStyle);
}

void CMainFrame::OnOptionsStyleOffice2013(UINT nStyle)
{
	OnOptionsStyle(nStyle);
}

void CMainFrame::OnOptionsStyle(UINT nStyle)
{
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
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2007, _T("OFFICE2007BLUE.INI"));
			break;

		case ID_OPTIONS_STYLE_OFFICE2007SILVER:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2007, _T("OFFICE2007SILVER.INI"));
			break;
		
		case ID_OPTIONS_STYLE_OFFICE2007BLACK:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2007, _T("OFFICE2007BLACK.INI"));
			break;

		case ID_OPTIONS_STYLE_OFFICE2007AQUA:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2007, _T("OFFICE2007AQUA.INI"));
			break;

		// Office 2010 styles
		case ID_OPTIONS_STYLE_OFFICE2010BLUE:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2010, _T("OFFICE2010BLUE.INI"));
			break;

		case ID_OPTIONS_STYLE_OFFICE2010SILVER:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2010, _T("OFFICE2010SILVER.INI"));
			break;

		case ID_OPTIONS_STYLE_OFFICE2010BLACK:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModule2010, _T("OFFICE2010BLACK.INI"));
			break;

		// Office 2013 styles
		case ID_OPTIONS_STYLE_OFFICE2013WORD:
		case ID_OPTIONS_STYLE_OFFICE2013EXCEL:
		case ID_OPTIONS_STYLE_OFFICE2013ACCESS:
		case ID_OPTIONS_STYLE_OFFICE2013POWERPOINT:
		case ID_OPTIONS_STYLE_OFFICE2013ONENOTE:
			GetCommandBars()->SetAllCaps(TRUE);
			SetCommandBarsTheme(xtpThemeOffice2013, theApp.m_hModule2013, _T("OFFICE2013WHITE.INI"));
			break;

		// Windows 7 styles
		case ID_OPTIONS_STYLE_WINDOWS7SCENIC:
			SetCommandBarsTheme(xtpThemeRibbon, theApp.m_hModuleWindows7, _T("Windows7Blue.ini"));
			break;
	}

	CXTPRibbonBar *pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetMenuBar();

	if ( nStyle >= ID_OPTIONS_STYLE_OFFICE2010BLUE)
	{
		pRibbonBar->GetSystemButton()->SetStyle(xtpButtonCaption);
		CreateBackstage();
	}
	else
	{
		pRibbonBar->GetSystemButton()->SetStyle(xtpButtonAutomatic);
		CreateSystemMenuPopup();
	}

	if ( nStyle >= ID_OPTIONS_STYLE_OFFICE2013WORD)
		Load2013Icons();
	else
		LoadDefaultIcons();
	
	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons = TRUE;
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, !(nStyle >= ID_OPTIONS_STYLE_OFFICE2013WORD));
	GetCommandBars()->GetImageManager()->RefreshAll();
	GetCommandBars()->GetPaintManager()->RefreshMetrics();
	GetCommandBars()->RedrawCommandBars();
	SendMessage(WM_NCPAINT);

	RedrawWindow(0, 0, RDW_ALLCHILDREN|RDW_INVALIDATE);

	m_nRibbonStyle = nStyle;
}

void CMainFrame::SetCommandBarsTheme(XTPPaintTheme paintTheme, HMODULE hModule/*=NULL*/, LPCTSTR lpszINI/*=NULL*/)
{
	CXTPCommandBarsFrameHook::m_bAllowDwm = !(CXTPWinDwmWrapper().IsCompositionEnabled() && (xtpThemeOffice2013 == paintTheme || xtpThemeOffice2007System == paintTheme));
	CXTPRibbonBar *pRibbonBar = DYNAMIC_DOWNCAST(CXTPRibbonBar, GetCommandBars()->GetMenuBar());
	pRibbonBar->EnableFrameTheme(FALSE);

	CXTPCommandBars* pCommandBars = GetCommandBars();
	if (pCommandBars != NULL)
	{
		if (hModule != NULL && lpszINI != NULL)
		{
			XTPResourceImages()->SetHandle(hModule, lpszINI);
			CXTPPaintManager::SetTheme(paintTheme);
		}
		else if(paintTheme == xtpThemeOfficeXP) // System theme
		{
			CXTPPaintManager::SetTheme(paintTheme);
		}
		
		pRibbonBar->EnableFrameTheme(TRUE);
	}
}

void CMainFrame::LoadDefaultIcons()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->GetImageManager()->RemoveAll();
	
	UINT nIDs[] = {ID_BUTTON_LARGESIMPLEBUTTON, ID_BUTTON_LARGEPOPUPBUTTON, ID_BUTTON_LARGESPLITPOPUPBUTTON, ID_BUTTON_LARGETOGGLEBUTTON};
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_LARGEBUTTONS, nIDs, 4, CSize(32, 32), xtpImageNormal);
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_SMALLBUTTONS, nIDs, 4, CSize(16, 16), xtpImageNormal);

	UINT nIDs1[] = {ID_BUTTON_SMALLSIMPLEBUTTON, ID_BUTTON_SMALLPOPUPBUTTON, ID_BUTTON_SMALLSPLITPOPUPBUTTON};
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_SMALLBUTTONS, nIDs1, 3, CSize(16, 16), xtpImageNormal);


	UINT nIDs2[] = {ID_EDITOR_EXTENDEDEDIT, ID_EDITOR_EXTENDEDCOMBO};
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_EXTENDEDEDITORS, nIDs2, 2, CSize(16, 16), xtpImageNormal);

	UINT nIDs3[] = {ID_GALLERY_STYLES, ID_GALLERY_TABLE, ID_GALLERY_COLOR, ID_GALLERY_UNDO};
	pCommandBars->GetImageManager()->SetIcons(ID_GROUP_INLINE, nIDs3, 4, CSize(32, 32), xtpImageNormal);

	UINT nIDs4[] = {ID_BUTTON_BITMAP};
	pCommandBars->GetImageManager()->SetIcons(ID_BUTTON_BITMAP, nIDs4, 1, CSize(0, 0), xtpImageNormal);

	pCommandBars->GetImageManager()->SetIcons(IDR_MAINFRAME);

	UINT uCommand = {IDB_GEAR};
	pCommandBars->GetImageManager()->SetIcons(IDB_GEAR, &uCommand, 1, CSize(0, 0), xtpImageNormal);
}

void CMainFrame::Load2013Icons()
{
	CXTPCommandBars* pCommandBars = GetCommandBars();

	pCommandBars->GetImageManager()->RemoveAll();
	
	UINT ui16[] = {ID_FILE_NEW,ID_FILE_OPEN,ID_FILE_SAVE,ID_EDIT_CUT,ID_EDIT_COPY,ID_EDIT_PASTE,ID_EDIT_UNDO
		,ID_EDIT_REDO,ID_FILE_PRINT,ID_APP_ABOUT,ID_BUTTON_SMALLSIMPLEBUTTON,ID_BUTTON_SMALLPOPUPBUTTON,ID_BUTTON_SMALLSPLITPOPUPBUTTON
		,ID_EDITOR_EXTENDEDEDIT,ID_EDITOR_COMBO,ID_EDITOR_COMBO2,ID_EDITOR_EXTENDEDCOMBO
	};
	pCommandBars->GetImageManager()->SetIcons(ID_SMALLICONS_16, ui16, _countof(ui16), CSize(16, 16));
	pCommandBars->GetImageManager()->SetIcons(ID_SMALLICONS_24, ui16, _countof(ui16), CSize(24, 24));
	pCommandBars->GetImageManager()->SetIcons(ID_SMALLICONS_32, ui16, _countof(ui16), CSize(32, 32));
	pCommandBars->GetImageManager()->SetIcons(ID_SMALLICONS_40, ui16, _countof(ui16), CSize(40, 40));
	pCommandBars->GetImageManager()->SetIcons(ID_SMALLICONS_48, ui16, _countof(ui16), CSize(48, 48));

	UINT ui32[] = {ID_BUTTON_LARGESIMPLEBUTTON,ID_BUTTON_LARGETOGGLEBUTTON,ID_BUTTON_LARGEPOPUPBUTTON,ID_BUTTON_LARGESPLITPOPUPBUTTON
		,ID_GALLERY_STYLES,ID_GALLERY_TABLE,ID_GALLERY_COLOR,ID_GALLERY_UNDO
		,ID_GROUP_SMALLBUTTONS, ID_GROUP_CHECKBOXES, ID_GROUP_GROUP
		,ID_GROUP_STANDARDEDITORS, ID_GROUP_EXTENDEDEDITORS, ID_GROUP_GALLERY
		,ID_GROUP_LABEL
	};
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_16 , ui32, _countof(ui32), CSize( 16,  16));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_24 , ui32, _countof(ui32), CSize( 24,  24));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_32 , ui32, _countof(ui32), CSize( 32,  32));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_40 , ui32, _countof(ui32), CSize( 40,  40));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_48 , ui32, _countof(ui32), CSize( 48,  48));

	ui32[4] = 0;	//	prevent using bigger icon size for 'Styles' button and group

	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_56 , ui32, _countof(ui32), CSize( 56,  56));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_64 , ui32, _countof(ui32), CSize( 64,  64));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_72 , ui32, _countof(ui32), CSize( 72,  72));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_96 , ui32, _countof(ui32), CSize( 96,  96));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_128, ui32, _countof(ui32), CSize(128, 128));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_168, ui32, _countof(ui32), CSize(168, 168));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_216, ui32, _countof(ui32), CSize(216, 216));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_256, ui32, _countof(ui32), CSize(256, 256));

	//reuse icons for ID_GROUP_LARGEBUTTONS and ID_GROUP_HYPERLINK
	UINT ui32_1[] = {ID_GROUP_LARGEBUTTONS, 0, 0, ID_GROUP_HYPERLINK, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_16 , ui32_1, _countof(ui32_1), CSize( 16,  16));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_24 , ui32_1, _countof(ui32_1), CSize( 24,  24));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_32 , ui32_1, _countof(ui32_1), CSize( 32,  32));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_40 , ui32_1, _countof(ui32_1), CSize( 40,  40));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_48 , ui32_1, _countof(ui32_1), CSize( 48,  48));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_56 , ui32_1, _countof(ui32_1), CSize( 56,  56));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_64 , ui32_1, _countof(ui32_1), CSize( 64,  64));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_72 , ui32_1, _countof(ui32_1), CSize( 72,  72));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_96 , ui32_1, _countof(ui32_1), CSize( 96,  96));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_128, ui32_1, _countof(ui32_1), CSize(128, 128));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_168, ui32_1, _countof(ui32_1), CSize(168, 168));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_216, ui32_1, _countof(ui32_1), CSize(216, 216));
	pCommandBars->GetImageManager()->SetIcons(ID_LARGEICONS_256, ui32_1, _countof(ui32_1), CSize(256, 256));

	UINT nIDs[] = {ID_BUTTON_BITMAP};
	pCommandBars->GetImageManager()->SetIcons(ID_BUTTON_BITMAP, nIDs, 1, CSize(0, 0), xtpImageNormal);
}

int nFonts[] = { 0, 11, 13, 16 };

void CMainFrame::OnOptionsFont(UINT nID)
{
	int nFontHeight = XTP_DPI_Y(nFonts[nID - ID_OPTIONS_FONT_SYSTEM]);

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	pRibbonBar->SetFontHeight(nFontHeight);
}

void CMainFrame::OnUpdateOptionsFont(CCmdUI* pCmdUI)
{
	int nFontHeight = XTP_DPI_Y(nFonts[pCmdUI->m_nID - ID_OPTIONS_FONT_SYSTEM]);

	CXTPRibbonBar* pRibbonBar = (CXTPRibbonBar*)GetCommandBars()->GetAt(0);

	pCmdUI->SetCheck(pRibbonBar->GetFontHeight() == nFontHeight ? TRUE : FALSE);

}

void CMainFrame::OnAutoResizeIcons()
{
	GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons ^= 1;
	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnUpdateAutoResizeIcons(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetCommandBars()->GetPaintManager()->m_bAutoResizeIcons);
}

void CMainFrame::OnDpiIconsScalling()
{
	GetCommandBars()->GetCommandBarsOptions()->SetDPIScallingOptions(TRUE, !GetCommandBars()->GetCommandBarsOptions()->GetToolbarsIconsScalling());
	GetCommandBars()->RedrawCommandBars();
}

void CMainFrame::OnUpdateDpiIconsScalling(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(GetCommandBars()->GetCommandBarsOptions()->GetToolbarsIconsScalling());
}

