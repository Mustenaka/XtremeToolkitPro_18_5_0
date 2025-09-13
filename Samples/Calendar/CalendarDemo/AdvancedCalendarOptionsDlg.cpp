// AdvancedCalendarOptionsDlg.cpp 
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
#include "calendardemo.h"
#include "AdvancedCalendarOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvancedCalendarOptionsDlg dialog


CAdvancedCalendarOptionsDlg::CAdvancedCalendarOptionsDlg(CXTPCalendarControl* pCalendar, CWnd* pParent /*=NULL*/)
	: CDialog(CAdvancedCalendarOptionsDlg::IDD, pParent)
{
	ASSERT(pCalendar);
	m_pCalendar = pCalendar;

	//{{AFX_DATA_INIT(CAdvancedCalendarOptionsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAdvancedCalendarOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvancedCalendarOptionsDlg)
	DDX_Control(pDX, IDC_COMBO_THEME_DEFAULT_COLOR, m_ctrlThemeColor);
	DDX_Control(pDX, IDC_STATIC_THEME_DEFAULT_COLOR, m_ctrlThemeColorLable);
	DDX_Control(pDX, IDC_CHECK_MARKUP, m_ctrlEnableMarkup);
	DDX_Control(pDX, IDC_CHECK_GETTEXT, m_ctrlEnableGetText);
	DDX_Control(pDX, IDC_CHECK_EDIT_SUBJECT_BY_TAB, m_ctrlEditSubject_ByTAB);
	DDX_Control(pDX, IDC_CHECK_EDIT_SUBJECT_BY_MOUSE_CLICK, m_ctrlEditSubject_ByMouseClick);
	DDX_Control(pDX, IDC_CHECK_EDIT_SUBJECT_BY_F2, m_ctrlEditSubject_ByF2);
	DDX_Control(pDX, IDC_CHECK_EDIT_SUBJECT_AFTER_RESIZE, m_ctrlEditSubject_AfterResize);
	DDX_Control(pDX, IDC_CHECK_CREATE_EVENT, m_ctrlInPlaceCreateEvent);
	DDX_Control(pDX, IDC_CHECK_OUTLOOKFONTGLYPHS, m_ctrlUseOutlookFontGlyphs);
	DDX_Control(pDX, IDC_CHECK_SHOW_TSMINUTES, m_ctrlShowTSMinutes);
	DDX_Control(pDX, IDC_CHECK_REMINDERS, m_ctrlReminders);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdvancedCalendarOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CAdvancedCalendarOptionsDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedCalendarOptionsDlg message handlers

void CAdvancedCalendarOptionsDlg::OnOK() 
{
	CXTPCalendarOptions* pOptions = m_pCalendar ? m_pCalendar->GetCalendarOptions() : NULL;
	if (!m_pCalendar || !pOptions) 
	{
		ASSERT(FALSE);
		return;
	}

	pOptions->bUseOutlookFontGlyphs = m_ctrlUseOutlookFontGlyphs.GetCheck() ? TRUE : FALSE;
	pOptions->bDayView_TimeScaleShowMinutes = m_ctrlShowTSMinutes.GetCheck() ? TRUE : FALSE;

	pOptions->bEnableInPlaceCreateEvent = m_ctrlInPlaceCreateEvent.GetCheck() ? TRUE : FALSE;

	pOptions->bEnableInPlaceEditEventSubject_ByF2 = m_ctrlEditSubject_ByF2.GetCheck() ? TRUE : FALSE;
	pOptions->bEnableInPlaceEditEventSubject_ByMouseClick = m_ctrlEditSubject_ByMouseClick.GetCheck() ? TRUE : FALSE;
	pOptions->bEnableInPlaceEditEventSubject_ByTab = m_ctrlEditSubject_ByTAB.GetCheck() ? TRUE : FALSE;
	pOptions->bEnableInPlaceEditEventSubject_AfterEventResize = m_ctrlEditSubject_AfterResize.GetCheck() ? TRUE : FALSE;

	pOptions->OnOptionsChanged();

	m_pCalendar->EnableReminders(m_ctrlReminders.GetCheck() ? TRUE : FALSE);
	m_pCalendar->EnableMarkup(m_ctrlEnableMarkup.GetCheck() ? TRUE : FALSE);
			
	CXTPCalendarTheme* pTheme = m_pCalendar->GetTheme();
	if (pTheme)
	{
		pTheme->SetAskItemTextFlags(m_ctrlEnableGetText.GetCheck() ? -1 : 0);
		pTheme->m_clrBaseColor = m_ctrlThemeColor.GetSelectedColor();
	}
			
	//---------------------------
	m_pCalendar->Populate();
	
	CDialog::OnOK();
}

BOOL CAdvancedCalendarOptionsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CXTPCalendarOptions* pOptions = m_pCalendar ? m_pCalendar->GetCalendarOptions() : NULL;
	if (!m_pCalendar || !pOptions) 
	{
		ASSERT(FALSE);
		return FALSE;
	}

	m_ctrlReminders					.SetCheck(m_pCalendar->IsRemindersEnabled() ? 1:0);
	m_ctrlEnableMarkup				.SetCheck(m_pCalendar->IsMarkupEnabled() ? 1:0);
	m_ctrlUseOutlookFontGlyphs		.SetCheck(pOptions->bUseOutlookFontGlyphs ? 1:0);
	m_ctrlShowTSMinutes				.SetCheck(pOptions->bDayView_TimeScaleShowMinutes ? 1:0);

	m_ctrlInPlaceCreateEvent		.SetCheck(pOptions->bEnableInPlaceCreateEvent?1:0);

	m_ctrlEditSubject_ByF2			.SetCheck(pOptions->bEnableInPlaceEditEventSubject_ByF2?1:0);
	m_ctrlEditSubject_ByMouseClick	.SetCheck(pOptions->bEnableInPlaceEditEventSubject_ByMouseClick?1:0);
	m_ctrlEditSubject_ByTAB			.SetCheck(pOptions->bEnableInPlaceEditEventSubject_ByTab?1:0);
	m_ctrlEditSubject_AfterResize	.SetCheck(pOptions->bEnableInPlaceEditEventSubject_AfterEventResize?1:0);

	// Themes 
	CXTPCalendarTheme* pTheme = m_pCalendar->GetTheme();
	
	InitThemeColors();
	
	if (pTheme)
	{
		m_ctrlThemeColor.EnableWindow(TRUE);
		m_ctrlThemeColor.SelectColor(pTheme->m_clrBaseColor);

		m_ctrlThemeColorLable.EnableWindow(TRUE);

		m_ctrlEnableGetText.EnableWindow(TRUE);
		m_ctrlEnableGetText.SetCheck(pTheme->GetAskItemTextFlags() ? 1:0);
	}
	else
	{
		m_ctrlThemeColor.EnableWindow(FALSE);
		m_ctrlThemeColorLable.EnableWindow(FALSE);
		m_ctrlEnableGetText.EnableWindow(FALSE);
	}

	m_ctrlEnableMarkup.EnableWindow(TRUE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAdvancedCalendarOptionsDlg::InitThemeColors() 
{
	for (int i = 0; i < 15; i++) 
	{
		m_ctrlThemeColor.AddString(_T(""));
	}
	
	m_ctrlThemeColor.SetItemData(0, RGB(93, 140, 201));
	m_ctrlThemeColor.SetItemData(1, RGB(114, 164, 90));
	m_ctrlThemeColor.SetItemData(2, RGB(190, 104, 134));
	m_ctrlThemeColor.SetItemData(3, RGB(90, 164, 164));
	m_ctrlThemeColor.SetItemData(4, RGB(113, 113, 205));
	m_ctrlThemeColor.SetItemData(5, RGB(92, 166, 116));
	m_ctrlThemeColor.SetItemData(6, RGB(93, 105, 105));
	m_ctrlThemeColor.SetItemData(7, RGB(157, 157, 87));
	m_ctrlThemeColor.SetItemData(8, RGB(140, 110, 200));
	m_ctrlThemeColor.SetItemData(9, RGB(169, 143, 93));
	m_ctrlThemeColor.SetItemData(10, RGB(90, 164, 140));
	m_ctrlThemeColor.SetItemData(11, RGB(97, 151, 177));
	m_ctrlThemeColor.SetItemData(12, RGB(139, 139, 139));
	m_ctrlThemeColor.SetItemData(13, RGB(255, 209, 81));
	//m_ctrlThemeColor.SetItemData(14, RGB(105, 133, 189));	
	m_ctrlThemeColor.SetItemData(14, RGB(145, 153, 164));

	m_ctrlThemeColor.SetCurSel(0);
}

void CComboBoxColors::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct->CtlType == ODT_COMBOBOX);
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);

	COLORREF clrBk = (COLORREF)lpDrawItemStruct->itemData;
	dc.FillSolidRect(&lpDrawItemStruct->rcItem, clrBk);

	if ((lpDrawItemStruct->itemAction | ODA_SELECT) &&
	  (lpDrawItemStruct->itemState  & ODS_SELECTED))
	{
		CBrush brFrame(RGB(0,0,0));
		dc.FrameRect(&lpDrawItemStruct->rcItem, &brFrame);
	}

	dc.Detach();
}

void CComboBoxColors::SelectColor(COLORREF clrColor)
{
	for (int i = 0; i < GetCount(); i++)
	{
		if (clrColor == (COLORREF)GetItemData(i)) 
		{
			SetCurSel(i);
			return;
		}
	}
}

COLORREF CComboBoxColors::GetSelectedColor(int nDefaultColorIndex)
{
	COLORREF clrColor = (COLORREF)-1;

	int nSel = GetCurSel();
	if (nSel == CB_ERR) 
	{
		nSel = nDefaultColorIndex;		
	}
	if (nSel >= 0 && nSel < GetCount()) 
	{
		clrColor = (COLORREF)GetItemData(nSel);
	}

	return clrColor;
}
