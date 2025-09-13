// MySyntaxDlg.cpp : implementation file
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
#include "MDITextEditor.h"
#include "MySyntaxDlg.h"


// CMySyntaxDlg dialog

IMPLEMENT_DYNAMIC(CMySyntaxDlg, CDialog)

CMySyntaxDlg::CMySyntaxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMySyntaxDlg::IDD, pParent)
{

}

CMySyntaxDlg::~CMySyntaxDlg()
{
}

void CMySyntaxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SYNTAX_EDIT, m_edit);
}


BEGIN_MESSAGE_MAP(CMySyntaxDlg, CDialog)
END_MESSAGE_MAP()

void CMySyntaxDlg::OnOK()
{
	 m_edit.GetWindowText(m_Syntax);

	CDialog::OnOK();
}

BOOL CMySyntaxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_edit.SetWindowText(m_Syntax);

	return TRUE;
}
