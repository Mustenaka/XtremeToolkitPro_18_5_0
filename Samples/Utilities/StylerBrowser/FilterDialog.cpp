// FilterDialog.cpp
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
#include "Styler.h"
#include "FilterDialog.h"
#include "Shlwapi.h"

CStringArray CFilterDialog::m_lstFilter;

// CFilterDialog dialog

IMPLEMENT_DYNAMIC(CFilterDialog, CDialog)
CFilterDialog::CFilterDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFilterDialog::IDD, pParent)
{
}

CFilterDialog::~CFilterDialog()
{
}

void CFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CFilterDialog, CDialog)
END_MESSAGE_MAP()


// CFilterDialog message handlers

BOOL CFilterDialog::OnInitDialog()
{
	CDialog::OnInitDialog();


	CListBox* pLB = (CListBox*)GetDlgItem(IDC_LIST);
	for (int i = 0; i < m_lstFilter.GetSize(); i++)
	{
		pLB->AddString(m_lstFilter[i]);
	}

	m_LBEditor.SubclassDlgItem(IDC_LIST, this);
	m_LBEditor.SetListEditStyle(_T(" &Items:"), LBS_XTP_DEFAULT);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CFilterDialog::LoadFilterList(void)
{
	CString strPath = GetModuleDir();
			
	TCHAR chReturn[100];
	CString strUrl;
	int nIndex = 0;
	strUrl.Format(_T("url%i"), nIndex);
	while (GetPrivateProfileString(_T("Filter"), strUrl, _T(""), chReturn, 100, strPath + _T("urlfilter.ini")) > 0)
	{
		CString strReturn(chReturn);
		if (!strReturn.IsEmpty())
		{
			m_lstFilter.Add(strReturn);
		}
		strUrl.Format(_T("url%i"), ++nIndex);
	}

}
void CFilterDialog::OnOK()
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

	CDialog::OnOK();
}

void CFilterDialog::SaveFilterList(void)
{
	CString strPath = GetModuleDir();

	CString strUrl;
	if (PathFileExists(strPath + _T("urlfilter.ini")))
		DeleteFile(strPath + _T("urlfilter.ini"));

	for (int i = 0; i < m_lstFilter.GetSize(); i++)
	{
		strUrl.Format(_T("url%i"), i);
		WritePrivateProfileString(_T("Filter"), strUrl, m_lstFilter[i], strPath + _T("urlfilter.ini"));
	}
}
