// ComponentSliderCtrl.cpp
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
#include "ComponentSliderCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CComponentSliderCtrl dialog

struct CComponentSliderCtrl::ValueInfo
{
	CString strName;
	CString strFormat;
	enum { Integer, Float } nType;
	union
	{
		struct
		{
			int nFrom;
			int nTo;
			int nCurrent;
		} IntegerValue;

		struct
		{
			float fFrom;
			float fTo;
			float fCurrent;
		} FloatValue;
	};
};

CComponentSliderCtrl::CComponentSliderCtrl(
	IComponentSliderCtrlCallback& callback,
	CWnd* pParent /*=NULL*/)
	: CTabCtrlDialog(CComponentSliderCtrl::IDD, pParent)
	, m_callback(callback)
	, m_bBeingDragged(FALSE)
{
	//{{AFX_DATA_INIT(CComponentSliderCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

BOOL CComponentSliderCtrl::Create(CWnd* pParent, CRect rc)
{
	BOOL bSuccess = CTabCtrlDialog::Create(IDD, pParent);
	if (bSuccess)
	{
		MoveWindow(&rc);
		ShowWindow(SW_SHOW);
	}

	return bSuccess;
}

int CComponentSliderCtrl::AddValue(LPCTSTR lpName, int nFrom, int nTo, int nCurrent, LPCTSTR lpFormat /*= NULL*/)
{
	ASSERT(NULL != lpName);
	ASSERT(nFrom <= nTo);
	ASSERT(nFrom <= nCurrent && nCurrent <= nTo);

	int nItem = m_wndValueList.AddString(lpName);
	if (CB_ERR != nItem)
	{
		ValueInfo* pValueInfo = new ValueInfo();
		pValueInfo->strName = lpName;
		pValueInfo->strFormat = (lpFormat != NULL ? lpFormat : _T("%i"));
		pValueInfo->nType = ValueInfo::Integer;
		pValueInfo->IntegerValue.nFrom = nFrom;
		pValueInfo->IntegerValue.nTo = nTo;
		pValueInfo->IntegerValue.nCurrent = nCurrent;
		m_wndValueList.SetItemDataPtr(nItem, pValueInfo);

		if (1 == m_wndValueList.GetCount())
		{
			m_wndValueList.SetCurSel(nItem);
			SetActiveValue(nItem);
		}
	}

	return nItem;
}

int CComponentSliderCtrl::AddValue(LPCTSTR lpName, float fFrom, float fTo, float fCurrent, LPCTSTR lpFormat /*= NULL*/)
{
	ASSERT(NULL != lpName);
	ASSERT(fFrom <= fTo);
	ASSERT(fFrom <= fCurrent && fCurrent <= fTo);

	int nItem = m_wndValueList.AddString(lpName);
	if (CB_ERR != nItem)
	{
		ValueInfo* pValueInfo = new ValueInfo();
		pValueInfo->strName = lpName;
		pValueInfo->strFormat = (lpFormat != NULL ? lpFormat : _T("%f"));
		pValueInfo->nType = ValueInfo::Float;
		pValueInfo->FloatValue.fFrom = fFrom;
		pValueInfo->FloatValue.fTo = fTo;
		pValueInfo->FloatValue.fCurrent = fCurrent;
		m_wndValueList.SetItemDataPtr(nItem, pValueInfo);

		if (1 == m_wndValueList.GetCount())
		{
			m_wndValueList.SetCurSel(nItem);
			SetActiveValue(nItem);
		}
	}

	return nItem;
}

void CComponentSliderCtrl::SetValue(int nItem, int nValue)
{
	int nCount = m_wndValueList.GetCount();
	ASSERT(0 <= nItem && nItem < nCount);

	ValueInfo* pValueInfo = reinterpret_cast<ValueInfo*>(m_wndValueList.GetItemDataPtr(nItem));
	ASSERT(NULL != pValueInfo);
	ASSERT(ValueInfo::Integer == pValueInfo->nType);

	pValueInfo->IntegerValue.nCurrent = nValue;

	if (m_wndValueList.GetCurSel() == nItem)
	{
		m_wndSlider.SetPos(ValueToSliderPos(*pValueInfo));

		CString strValue = GetValueString(*pValueInfo);
		m_wndValue.SetWindowText(strValue);
	}
}

void CComponentSliderCtrl::SetValue(int nItem, float fValue)
{
	int nCount = m_wndValueList.GetCount();
	ASSERT(0 <= nItem && nItem < nCount);

	ValueInfo* pValueInfo = reinterpret_cast<ValueInfo*>(m_wndValueList.GetItemDataPtr(nItem));
	ASSERT(NULL != pValueInfo);
	ASSERT(ValueInfo::Float == pValueInfo->nType);

	pValueInfo->FloatValue.fCurrent = fValue;

	if (m_wndValueList.GetCurSel() == nItem)
	{
		m_wndSlider.SetPos(ValueToSliderPos(*pValueInfo));

		CString strValue = GetValueString(*pValueInfo);
		m_wndValue.SetWindowText(strValue);
	}
}

void CComponentSliderCtrl::DoDataExchange(CDataExchange* pDX)
{
	CTabCtrlDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComponentSliderCtrl)
	DDX_Control(pDX, IDC_COMBO, m_wndValueList);
	DDX_Control(pDX, IDC_SLIDER, m_wndSlider);
	DDX_Control(pDX, IDC_VALUE, m_wndValue);
	//}}AFX_DATA_MAP
}

BOOL CComponentSliderCtrl::OnInitDialog()
{
	CTabCtrlDialog::OnInitDialog();
	return TRUE;
}

void CComponentSliderCtrl::SetActiveValue(int nItem)
{
	ASSERT(nItem < m_wndValueList.GetCount());

	ValueInfo* pValueInfo = reinterpret_cast<ValueInfo*>(m_wndValueList.GetItemDataPtr(nItem));
	ASSERT(NULL != pValueInfo);

	if (NULL != pValueInfo)
	{
		switch (pValueInfo->nType)
		{
		case ValueInfo::Integer:
			m_wndSlider.SetRange(pValueInfo->IntegerValue.nFrom, pValueInfo->IntegerValue.nTo);
			break;
		case ValueInfo::Float:
			m_wndSlider.SetRange(0, 100);
			break;
		}

		m_wndSlider.SetPos(ValueToSliderPos(*pValueInfo));

		CString strValue = GetValueString(*pValueInfo);
		m_wndValue.SetWindowText(strValue);
	}
}

int CComponentSliderCtrl::ValueToSliderPos(const ValueInfo& value)
{
	int nPos = 0;

	switch (value.nType)
	{
	case ValueInfo::Integer:
		nPos = value.IntegerValue.nCurrent;
		break;
	case ValueInfo::Float:
		nPos = static_cast<int>((value.FloatValue.fCurrent * 100) / (value.FloatValue.fTo - value.FloatValue.fFrom));
		break;
	default:
		ASSERT(!"Unexpected");
	}

	return nPos;
}

void CComponentSliderCtrl::SliderPosToValue(int nPos, ValueInfo& value)
{
	switch (value.nType)
	{
	case ValueInfo::Integer:
		value.IntegerValue.nCurrent = nPos;
		break;
	case ValueInfo::Float:
		value.FloatValue.fCurrent = (static_cast<float>(nPos) * (value.FloatValue.fTo - value.FloatValue.fFrom)) / 100.f;
		break;
	default:
		ASSERT(!"Unexpected");
	}
}

CString CComponentSliderCtrl::GetValueString(const ValueInfo& value) const
{
	CString strValue;

	switch (value.nType)
	{
	case ValueInfo::Integer:
		strValue.Format(value.strFormat, value.IntegerValue.nCurrent);
		break;
	case ValueInfo::Float:
		strValue.Format(value.strFormat, value.FloatValue.fCurrent);
		break;
	default:
		ASSERT(!"Unexpected");
	}

	return strValue;
}

BEGIN_MESSAGE_MAP(CComponentSliderCtrl, CTabCtrlDialog)
	//{{AFX_MSG_MAP(CComponentSliderCtrl)
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_CBN_SELENDOK(IDC_COMBO, OnValueSelected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComponentSliderCtrl message handlers

void CComponentSliderCtrl::OnDestroy()
{
	int nItems = m_wndValueList.GetCount();
	for (int i = 0; i < nItems; ++i)
	{
		ValueInfo* pValueInfo = reinterpret_cast<ValueInfo*>(m_wndValueList.GetItemDataPtr(i));
		ASSERT(NULL != pValueInfo);
		delete pValueInfo;
	}
}

void CComponentSliderCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	ASSERT_VALID(pScrollBar);

	if (TB_LINEUP <= nSBCode && nSBCode < TB_ENDTRACK)
	{
		int nItem = m_wndValueList.GetCurSel();
		if (CB_ERR != nItem)
		{
			if (!m_bBeingDragged)
			{
				m_callback.OnBeforeValueChanged(nItem);
				m_bBeingDragged = TRUE;
			}

			nPos = m_wndSlider.GetPos();

			ValueInfo* pValueInfo = reinterpret_cast<ValueInfo*>(m_wndValueList.GetItemDataPtr(nItem));
			ASSERT(NULL != pValueInfo);

			SliderPosToValue(nPos, *pValueInfo);

			switch (pValueInfo->nType)
			{
			case ValueInfo::Integer:
				m_callback.OnValueChanged(nItem, pValueInfo->IntegerValue.nCurrent);
				break;
			case ValueInfo::Float:
				m_callback.OnValueChanged(nItem, pValueInfo->FloatValue.fCurrent);
				break;
			default:
				ASSERT(!"Unexpected");
			}

			CString strValue = GetValueString(*pValueInfo);
			m_wndValue.SetWindowText(strValue);
		}
	}
	else if (TB_ENDTRACK == nSBCode && m_bBeingDragged)
	{
		m_bBeingDragged = FALSE;

		int nItem = m_wndValueList.GetCurSel();
		if (CB_ERR != nItem)
		{
			m_callback.OnAfterValueChanged(nItem);
		}
	}
}

void CComponentSliderCtrl::OnValueSelected()
{
	int nItem = m_wndValueList.GetCurSel();
	if (CB_ERR != nItem)
	{
		SetActiveValue(nItem);
	}
}
