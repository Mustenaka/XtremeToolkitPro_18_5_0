// DialogSettings.cpp
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
#include "grep.h"
#include "DialogSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CApplicationSettings::CApplicationSettings()
{
	m_bUseEditor = TRUE;
	m_strEditor = _T("notepad.exe");

}

void CApplicationSettings::SaveSettings()
{
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("UseEditor"), m_bUseEditor);
	AfxGetApp()->WriteProfileString(_T("Settings"), _T("Editor"), m_strEditor);
}

void CApplicationSettings::LoadSettings()
{
	m_bUseEditor = AfxGetApp()->GetProfileInt(_T("Settings"), _T("UseEditor"), TRUE);
	m_strEditor = AfxGetApp()->GetProfileString(_T("Settings"), _T("Editor"), m_strEditor);	
}

CApplicationSettings g_settings;

/////////////////////////////////////////////////////////////////////////////
// CDialogSettings dialog


CDialogSettings::CDialogSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogSettings)
	m_bUseEditor = g_settings.m_bUseEditor;
	m_strEditor = g_settings.m_strEditor;
	//}}AFX_DATA_INIT
}


void CDialogSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSettings)
	DDX_Radio(pDX, IDC_RADIO_ASSOCIATED, m_bUseEditor);
	DDX_Text(pDX, IDC_EDIT_EDITOR, m_strEditor);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogSettings, CDialog)
	//{{AFX_MSG_MAP(CDialogSettings)
	ON_BN_CLICKED(IDC_RADIO_ASSOCIATED, OnRadioEditorChanged)
	ON_BN_CLICKED(IDC_RADIO_EDITOR, OnRadioEditorChanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogSettings message handlers

void CDialogSettings::OnOK() 
{
	UpdateData();

	g_settings.m_bUseEditor = m_bUseEditor;
	g_settings.m_strEditor = m_strEditor;

	g_settings.SaveSettings();
	
	CDialog::OnOK();
}

void CDialogSettings::OnRadioEditorChanged() 
{
	UpdateData();

	GetDlgItem(IDC_EDIT_EDITOR)->EnableWindow(m_bUseEditor);
	
}

BOOL CDialogSettings::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	OnRadioEditorChanged();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
