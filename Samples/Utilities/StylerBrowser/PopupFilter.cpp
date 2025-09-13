// PopupFilter.cpp
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
#include "styler.h"
#include "PopupFilter.h"
#include "StylerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopupFilter dialog

CStringArray CPopupFilter::m_lstFilter;

CPopupFilter::CPopupFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CPopupFilter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPopupFilter)
	//}}AFX_DATA_INIT
	m_bCheckAll = CStylerView::m_bFilterAll;
	m_bCheckList = CStylerView::m_bFilterList;
}


void CPopupFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPopupFilter)
	DDX_Check(pDX, IDC_CHECK_ALL, m_bCheckAll);
	DDX_Check(pDX, IDC_CHECK_LIST, m_bCheckList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPopupFilter, CDialog)
	//{{AFX_MSG_MAP(CPopupFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopupFilter message handlers

BOOL CPopupFilter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CListBox* pLB = (CListBox*)GetDlgItem(IDC_LIST);
	for (int i = 0; i < m_lstFilter.GetSize(); i++)
	{
		pLB->AddString(m_lstFilter[i]);
	}



/*	VERIFY(m_LBEditor.Initialize(this, IDC_LIST, LBE_AUTOEDIT | LBE_BUTTONS | 
                        LBE_TOOLTIPS | LBE_NEWBUTTON | LBE_DELBUTTON));
	m_LBEditor.SetWindowText(_T(" &Items:"));*/
	m_LBEditor.SubclassDlgItem(IDC_LIST, this);
	m_LBEditor.SetListEditStyle(_T(" &Items:"), LBS_XTP_DEFAULT);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPopupFilter::SaveFilterList()
{
	CString strPath = GetModuleDir();

	CString strUrl;
	if (PathFileExists(strPath + _T("popups.ini")))
		DeleteFile(strPath + _T("popups.ini"));

	for (int i = 0; i < m_lstFilter.GetSize(); i++)
	{
		strUrl.Format(_T("popup%i"), i);
		WritePrivateProfileString(_T("Popups"), strUrl, m_lstFilter[i], strPath + _T("popups.ini"));
	}

}

void CPopupFilter::OnOK() 
{
	CListBox* pLB = (CListBox*)GetDlgItem(IDC_LIST);
	
	m_lstFilter.RemoveAll();
	for (int i = 0; i < pLB->GetCount(); i++)
	{
		CString str;
		pLB->GetText(i, str);
		if (!str.IsEmpty())
		m_lstFilter.Add(str);
	}	

	SaveFilterList();

	UpdateData(TRUE);
	CStylerView::m_bFilterAll = m_bCheckAll;
	CStylerView::m_bFilterList = m_bCheckList;

	
	CDialog::OnOK();
}

void CPopupFilter::LoadFilterList()
{
	CString strPath = GetModuleDir();
			
	TCHAR chReturn[100];
	CString strUrl;
	int nIndex = 0;
	strUrl.Format(_T("popup%i"), nIndex);
	while (GetPrivateProfileString(_T("Popups"), strUrl, _T(""), chReturn, 100, strPath + _T("popups.ini")) > 0)
	{
		CString strReturn(chReturn);
		if (!strReturn.IsEmpty())
		{
			m_lstFilter.Add(strReturn);
		}
		strUrl.Format(_T("popup%i"), ++nIndex);
	}

}
