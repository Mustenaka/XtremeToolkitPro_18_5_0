// Pie3dOptionsDlg.cpp
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
#include "chartbrowser.h"
#include "BaseView.h"
#include "Pie3dOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPie3dOptionsDlg dialog


CPie3dOptionsDlg::CPie3dOptionsDlg(IPie3dOptionsDlgCallback& callback, CWnd* pParent /*=NULL*/)
	: CTabCtrlDialog(CPie3dOptionsDlg::IDD, pParent)
	, m_callback(callback)
{
	//{{AFX_DATA_INIT(CPie3dOptionsDlg)
	m_bShowLabels = TRUE;
	m_nPosition = 0;
	m_nExplodedPoints = 2;
	m_nDepth = 20;
	m_nHoleRadius = 60;
	//}}AFX_DATA_INIT
}

void CPie3dOptionsDlg::ShowTorusControls()
{
	CWnd* pCtrl = GetDlgItem(IDC_EDIT_TORUS_DEPTH);
	if (NULL != pCtrl)
	{
		pCtrl->ShowWindow(SW_SHOW);
	}

	pCtrl = GetDlgItem(IDC_TORUS_DEPTH_LABEL);
	if (NULL != pCtrl)
	{
		pCtrl->ShowWindow(SW_SHOW);
	}
}

void CPie3dOptionsDlg::ShowDoughnutControls()
{
	CWnd* pCtrl = GetDlgItem(IDC_EDIT_HOLE_RADIUS);
	if (NULL != pCtrl)
	{
		pCtrl->ShowWindow(SW_SHOW);
	}

	pCtrl = GetDlgItem(IDC_HOLE_RADIUS_TITLE);
	if (NULL != pCtrl)
	{
		pCtrl->ShowWindow(SW_SHOW);
	}
}

void CPie3dOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CTabCtrlDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CPie3dOptionsDlg)
	DDX_Check(pDX, IDC_CHECK_SHOWLABELS, m_bShowLabels);
	DDX_CBIndex(pDX, IDC_COMBO_LABEL_POSITION, m_nPosition);
	DDX_CBIndex(pDX, IDC_COMBO_EXPLODED_POINTS, m_nExplodedPoints);
	DDX_Text(pDX, IDC_EDIT_TORUS_DEPTH, m_nDepth);
	DDX_Text(pDX, IDC_EDIT_HOLE_RADIUS, m_nHoleRadius);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPie3dOptionsDlg, CTabCtrlDialog)
	//{{AFX_MSG_MAP(CPie3dOptionsDlg)
	ON_BN_CLICKED(IDC_CHECK_SHOWLABELS, OnBnClickedCheckShowLabels)
	ON_CBN_SELCHANGE(IDC_COMBO_LABEL_POSITION, OnCbnSelChangeComboLabelPosition)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPLODED_POINTS, OnCbnSelChangeComboExplodedPoints)
	ON_EN_CHANGE(IDC_EDIT_TORUS_DEPTH, OnEnChangeEditDepth)
	ON_EN_CHANGE(IDC_EDIT_HOLE_RADIUS, OnEnChangeEditHoleRadius)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPie3dOptionsDlg message handlers

void CPie3dOptionsDlg::OnBnClickedCheckShowLabels()
{
	UpdateData();
	m_callback.OnBnClickedCheckShowLabels();
}

void CPie3dOptionsDlg::OnCbnSelChangeComboLabelPosition()
{
	UpdateData();
	m_callback.OnCbnSelChangeComboLabelPosition();
}

void CPie3dOptionsDlg::OnCbnSelChangeComboExplodedPoints()
{
	UpdateData();
	m_callback.OnCbnSelChangeComboExplodedPoints();
}

void CPie3dOptionsDlg::OnEnChangeEditDepth()
{
	UpdateData();
	m_callback.OnEnChangeEditDepth();
}

void CPie3dOptionsDlg::OnEnChangeEditHoleRadius()
{
	UpdateData();
	m_callback.OnEnChangeEditHoleRadius();
}
