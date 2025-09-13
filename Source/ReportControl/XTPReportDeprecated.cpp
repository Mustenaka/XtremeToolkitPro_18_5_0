// XTPReportDeprecated.cpp
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

#include "StdAfx.h"

#include "Common/XTPFramework.h"
#include "Common/XTPSystemHelpers.h"
#include "Common/XTPSynchro.h"
#include "Common/XTPApplication.h"
#include "Common/XTPSingleton.h"
#include "Common/XTPGdiObjects.h"
#include "Common/XTPDrawHelpers.h"
#include "Common/XTPImageManager.h"
#include "Common/XTPXMLHelpers.h"
#include "Common/XTPPropExchange.h"
#include "Common/PropExchange/XTPPropExchangeEnumerator.h"
#include "Common/PropExchange/XTPPropExchangeEnumeratorPtr.h"
#include "Common/PropExchange/XTPPropExchangeSection.h"
#include "Common/PropExchange/XTPPropExchangeArchive.h"
#include "Common/PropExchange/XTPPropExchangeXMLNode.h"
#include "Common/PropExchange/XTPPropExchangeRegistry.h"
#include "Common/PropExchange/XTPPropExchangeIniFile.h"
#include "Common/XTPToolTipContext.h"
#include "Common/XTPResourceManager.h"
#include "Common/XTPMarkupRender.h"
#include "Common/XTPVC80Helpers.h"
#include "Common/XTPCustomHeap.h"
#include "Common/XTPSmartPtrInternalT.h"
#include "Common/XTPColorManager.h"

#include "ReportControl/XTPReportDefines.h"

#if XTP_REPORT_DEPRECATED()

#include "ReportControl/Behavior/XTPReportBehavior.h"
#include "ReportControl/XTPReportRows.h"
#include "ReportControl/XTPReportSelectedRows.h"

#include "ReportControl/XTPReportRecordItem.h"
#include "ReportControl/XTPReportRecord.h"
#include "ReportControl/XTPReportRecords.h"
#include "ReportControl/XTPReportHeader.h"
#include "ReportControl/XTPReportColumn.h"
#include "ReportControl/XTPReportColumns.h"
#include "ReportControl/XTPReportRow.h"
#include "ReportControl/XTPReportControl.h"
#include "ReportControl/XTPReportPaintManager.h"
#include "ReportControl/XTPReportNavigator.h"
#include "ReportControl/XTPReportSubListControl.h"
#include "ReportControl/XTPReportGroupRow.h"
#include "ReportControl/XTPReportInplaceControls.h"
#include "ReportControl/XTPReportRecordItemControls.h"
#include "ReportControl/XTPReportHyperlink.h"
#include "ReportControl/XTPReportRecordItemRange.h"
#include "ReportControl/XTPReportSections.h"
#include "ReportControl/XTPReportSection.h"
#include "ReportControl/XTPReportBorder.h"
#include "ReportControl/XTPReportThickness.h"

#include "ReportControl/XTPReportADO.h"
#include "ReportControl/XTPReportDataManager.h"

#include "Common/Base/Diagnostic/XTPDisableNoisyWarnings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelectionEnable
/////////////////////////////////////////////////////////////////////////////

void CXTPReportControl::SelectionEnable(BOOL bEnable)
{
	m_pSectionBody->SelectionEnable(bEnable);

	if (!bEnable)
	{
		m_bInitialSelectionEnable = FALSE;
		m_bBlockSelection         = FALSE;
		m_bMultiSelectionMode     = FALSE;
		m_pSelectedRows->Clear();
	}
}

BOOL CXTPReportControl::IsSelectionEnabled() const
{
	return m_pSectionBody->IsSelectionEnabled();
}

void CXTPReportControl::HeaderRowsEnableSelection(BOOL bEnable)
{
	m_pSectionHeader->SelectionEnable(bEnable);
}

BOOL CXTPReportControl::IsHeaderRowsSelectionEnabled() const
{
	return m_pSectionHeader->IsSelectionEnabled();
}

void CXTPReportControl::FooterRowsEnableSelection(BOOL bEnable)
{
	m_pSectionFooter->SelectionEnable(bEnable);
}

BOOL CXTPReportControl::IsFooterRowsSelectionEnabled() const
{
	return m_pSectionFooter->IsSelectionEnabled();
}


/////////////////////////////////////////////////////////////////////////////
// Visible
/////////////////////////////////////////////////////////////////////////////

BOOL CXTPReportControl::IsHeaderRowsVisible() const
{
	return m_pSectionHeader->IsVisible();
}

BOOL CXTPReportControl::IsFooterRowsVisible() const
{
	return m_pSectionFooter->IsVisible();
}

void CXTPReportControl::ShowHeaderRows(BOOL bShow)
{
	m_pSectionHeader->SetVisible(bShow);

	if (!bShow)
		GetNavigator()->SetCurrentFocusInHeadersRows(FALSE);

	AdjustLayout();
	AdjustScrollBars();
}

void CXTPReportControl::ShowFooterRows(BOOL bShow)
{
	m_pSectionFooter->SetVisible(bShow);

	if (!bShow)
		GetNavigator()->SetCurrentFocusInFootersRows(FALSE);

	AdjustLayout();
	AdjustScrollBars();
}


/////////////////////////////////////////////////////////////////////////////
// AllowAccess
/////////////////////////////////////////////////////////////////////////////

void CXTPReportControl::HeaderRowsAllowAccess(BOOL bAllowAccess)
{
	m_pSectionHeader->AllowAccess(bAllowAccess);
}

BOOL CXTPReportControl::IsHeaderRowsAllowAccess() const
{
	return m_pSectionHeader->IsAllowAccess();
}

void CXTPReportControl::FooterRowsAllowAccess(BOOL bAllowAccess)
{
	m_pSectionFooter->AllowAccess(bAllowAccess);
}

BOOL CXTPReportControl::IsFooterRowsAllowAccess() const
{
	return m_pSectionFooter->IsAllowAccess();
}

/////////////////////////////////////////////////////////////////////////////
// AllowEdit
/////////////////////////////////////////////////////////////////////////////

void CXTPReportControl::AllowEdit(BOOL bAllowEdit)
{
	m_pSectionBody->AllowEdit(bAllowEdit);
}

BOOL CXTPReportControl::IsAllowEdit() const
{
	return m_pSectionBody->IsAllowEdit();
}

void CXTPReportControl::HeaderRowsAllowEdit(BOOL bAllowEdit)
{
	m_pSectionHeader->AllowEdit(bAllowEdit);
}

BOOL CXTPReportControl::IsHeaderRowsAllowEdit() const
{
	return m_pSectionHeader->IsAllowEdit();
}

void CXTPReportControl::FooterRowsAllowEdit(BOOL bAllowEdit)
{
	m_pSectionFooter->AllowEdit(bAllowEdit);
}

BOOL CXTPReportControl::IsFooterRowsAllowEdit() const
{
	return m_pSectionFooter->IsAllowEdit();
}

/////////////////////////////////////////////////////////////////////////////
// Allow Group
/////////////////////////////////////////////////////////////////////////////

void CXTPReportControl::AllowGroup(BOOL bAllowGroup)
{
	m_pSectionBody->AllowGroup(bAllowGroup);
}

BOOL CXTPReportControl::IsAllowGroup() const
{
	return m_pSectionBody->IsAllowGroup();
}

void CXTPReportControl::HeaderRowsAllowGroup(BOOL bAllowGroup)
{
	m_pSectionHeader->AllowGroup(bAllowGroup);
}

BOOL CXTPReportControl::IsHeaderRowsAllowGroup() const
{
	return m_pSectionHeader->IsAllowGroup();
}

void CXTPReportControl::FooterRowsAllowGroup(BOOL bAllowGroup)
{
	m_pSectionFooter->AllowGroup(bAllowGroup);
}

BOOL CXTPReportControl::IsFooterRowsAllowGroup() const
{
	return m_pSectionFooter->IsAllowGroup();
}

/////////////////////////////////////////////////////////////////////////////
// Allow Sort
/////////////////////////////////////////////////////////////////////////////

void CXTPReportControl::AllowSort(BOOL bAllowSort)
{
	m_pSectionBody->AllowSort(bAllowSort);
}

BOOL CXTPReportControl::IsAllowSort() const
{
	return m_pSectionBody->IsAllowSort();
}

void CXTPReportControl::HeaderRowsAllowSort(BOOL bAllowSort)
{
	m_pSectionHeader->AllowSort(bAllowSort);
}

BOOL CXTPReportControl::IsHeaderRowsAllowSort() const
{
	return m_pSectionHeader->IsAllowSort();
}

void CXTPReportControl::FooterRowsAllowSort(BOOL bAllowSort)
{
	m_pSectionFooter->AllowSort(bAllowSort);
}

BOOL CXTPReportControl::IsFooterRowsAllowSort() const
{
	return m_pSectionFooter->IsAllowSort();
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////

int CXTPReportControl::GetTopRowIndex() const
{
	return m_pSectionScroll->GetScrollIndexV();
}


/////////////////////////////////////////////////////////////////////////////
// GetRows / GetRecords
/////////////////////////////////////////////////////////////////////////////

CXTPReportRecords* CXTPReportControl::GetRecords() const
{
	return m_pSectionBody->GetRecords();
}

CXTPReportRows* CXTPReportControl::GetRows() const
{
	return m_pSectionBody->GetRows();
}

CXTPReportRecords* CXTPReportControl::GetHeaderRecords() const
{
	return m_pSectionHeader->GetRecords();
}

CXTPReportRecords* CXTPReportControl::GetFooterRecords() const
{
	return m_pSectionFooter->GetRecords();
}

CXTPReportRows* CXTPReportControl::GetHeaderRows() const
{
	return m_pSectionHeader->GetRows();
}

CXTPReportRows* CXTPReportControl::GetFooterRows() const
{
	return m_pSectionFooter->GetRows();
}

/////////////////////////////////////////////////////////////////////////////
// Areas
/////////////////////////////////////////////////////////////////////////////

CRect CXTPReportControl::GetReportRectangle() const
{
	return m_pSectionBody->m_rcSection;
}


CRect CXTPReportControl::GetHeaderRowsRect() const
{
	return m_pSectionHeader->m_rcSection;
}

CRect CXTPReportControl::GetFooterRowsRect() const
{
	return m_pSectionFooter->m_rcSection;
}

/////////////////////////////////////////////////////////////////////////////
// Populate
/////////////////////////////////////////////////////////////////////////////

void CXTPReportControl::PopulateHeaderRows()
{
	m_pSectionHeader->Populate(TRUE);
}

void CXTPReportControl::PopulateFooterRows()
{
	m_pSectionFooter->Populate(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// Pin footer
/////////////////////////////////////////////////////////////////////////////

void CXTPReportControl::PinFooterRows(BOOL bPin)
{
	if (bPin)
	{
		m_pSectionBody  ->SetHeightMode(xtpReportSectionHeightModeAutoShrink);
		m_pSectionFooter->SetHeightMode(xtpReportSectionHeightModeAutoExpand);
		//m_pSectionFooter->GetBorder()->GetBorderThickness()->SetTop(0);
	}
	else
	{
		m_pSectionBody  ->SetHeightMode(xtpReportSectionHeightModeExpand);
		m_pSectionFooter->SetHeightMode(xtpReportSectionHeightModeAuto);
		//m_pSectionFooter->GetBorder()->GetBorderThickness()->SetTop(1);
	}

	m_bPinFooterRows = bPin;
	AdjustLayout();
	AdjustScrollBars();
}

////////////////////////////////////////////////////////////////////////////
// Divider style
/////////////////////////////////////////////////////////////////////////////

XTPReportFixedRowsDividerStyle CXTPReportPaintManager::GetHeaderRowsDividerStyle() const
{
	if (m_pControl)
	{
		return m_pControl->m_pSectionHeader->GetDividerStyle();
	}
	else
	{
		return xtpReportFixedRowsDividerNone;
	}
}

void CXTPReportPaintManager::SetHeaderRowsDividerStyle(XTPReportFixedRowsDividerStyle style)
{
	if (m_pControl)
	{
		m_pControl->m_pSectionHeader->SetDividerStyle(style);
	}
}

XTPReportFixedRowsDividerStyle CXTPReportPaintManager::GetFooterRowsDividerStyle() const
{
	if (m_pControl)
	{
		return m_pControl->m_pSectionFooter->GetDividerStyle();
	}
	else
	{
		return xtpReportFixedRowsDividerNone;
	}
}

void CXTPReportPaintManager::SetFooterRowsDividerStyle(XTPReportFixedRowsDividerStyle style)
{
	if (m_pControl)
	{
		m_pControl->m_pSectionFooter->SetDividerStyle(style);
	}
}

#if defined(_XTP_ACTIVEX)

int CXTPReportPaintManager::OleGetHeaderRowsDividerStyle()
{
	return GetHeaderRowsDividerStyle();
}

void CXTPReportPaintManager::OleSetHeaderRowsDividerStyle(int style)
{
	SetHeaderRowsDividerStyle(XTPReportFixedRowsDividerStyle(style));
}

int CXTPReportPaintManager::OleGetFooterRowsDividerStyle()
{
	return GetFooterRowsDividerStyle();
}

void CXTPReportPaintManager::OleSetFooterRowsDividerStyle(int style)
{
	SetFooterRowsDividerStyle(XTPReportFixedRowsDividerStyle(style));
}

#endif // defined(_XTP_ACTIVEX)


/////////////////////////////////////////////////////////////////////////////
// Divider color
/////////////////////////////////////////////////////////////////////////////

CXTPPaintManagerColor CXTPReportPaintManager::GetHeaderRowsDividerColor() const
{
	if (m_pControl)
	{
		return m_pControl->m_pSectionHeader->GetDividerColor();
	}
	else
	{
		return CXTPPaintManagerColor(COLOR_BTNFACE);
	}
}

void CXTPReportPaintManager::SetHeaderRowsDividerColor(CXTPPaintManagerColor clrDivider)
{
	if (m_pControl)
	{
		m_pControl->m_pSectionHeader->SetDividerColor(clrDivider);
	}
}

CXTPPaintManagerColor CXTPReportPaintManager::GetFooterRowsDividerColor() const
{
	if (m_pControl)
	{
		return m_pControl->m_pSectionFooter->GetDividerColor();
	}
	else
	{
		return CXTPPaintManagerColor(COLOR_BTNFACE);
	}
}

void CXTPReportPaintManager::SetFooterRowsDividerColor(CXTPPaintManagerColor clrDivider)
{
	if (m_pControl)
	{
		m_pControl->m_pSectionFooter->SetDividerColor(clrDivider);
	}
}

/////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////

void CXTPReportControl::SetFullColumnScrolling(BOOL bSet)
{
	if (bSet)
	{
		m_scrollModeH = xtpReportScrollModeBlock;
	}
	else
	{
		m_scrollModeH = xtpReportScrollModeSmooth;
	}

	if (m_hWnd)
	{
		CXTPReportControl::OnHScroll(SB_TOP, 0, NULL);

		RedrawControl();
		UpdateWindow();

		AdjustScrollBars();
	}
}

void CXTPReportControl::GetColumnTotalSize(int &nTotalCount, int &nTotalWidth) const
{
	nTotalCount = 0;
	nTotalWidth = 0;
	int nColumn = 0;
	
	GetFreezeColumnsCount(nColumn);
	nColumn = (nColumn == -1) ? 0 : nColumn + 1;	// next column's index after last frozen column
	
	for (; nColumn<GetColumns()->GetCount(); nColumn++)
	{
		const CXTPReportColumn *pColumn = GetColumns()->GetAt(nColumn);

		if (pColumn->IsVisible())
		{
			nTotalCount += 1;
			nTotalWidth += pColumn->GetWidth();
		}
	}
}

void CXTPReportControl::GetColumnOutOfViewSize(int &nOutOfViewCount, int &nOutOfViewWidth) const
{
	int nLeft  = 0;
	int nRight = 0;
	int nColumn = 0;
	int nLastFreezeColumnIndex = -1; 
	
	GetFreezeColumnsCount(nLastFreezeColumnIndex);
	
	if (nLastFreezeColumnIndex > -1)
	{
		for (; nColumn <= nLastFreezeColumnIndex; nColumn++)
		{
			const CXTPReportColumn *pColumn = GetColumns()->GetAt(nColumn);
			if (pColumn->IsVisible())
				nLeft += pColumn->GetWidth();
		}
	}
	
	nOutOfViewCount = 0;
	nOutOfViewWidth = 0;

	for (; nColumn<GetColumns()->GetCount(); nColumn++)
	{
		const CXTPReportColumn *pColumn = GetColumns()->GetAt(nColumn);

		if (pColumn->IsVisible())
		{
			nRight = nLeft + pColumn->GetWidth();

			if (nRight > GetReportRectangle().right)
			{
				nOutOfViewCount += 1;
				nOutOfViewWidth += pColumn->GetWidth() - max(0, GetReportRectangle().right-nLeft);
			}

			nLeft = nRight;
		}
	}
}

void CXTPReportControl::GetColumnScrollSize(int nOutOfViewWidth, int &nScrollCount, int &nScrollWidth) const
{
	nScrollCount = 0;
	nScrollWidth = 0;

	if (nOutOfViewWidth <= nScrollWidth)
		return;
	
	int nColumn = 0;
	GetFreezeColumnsCount(nColumn);
	nColumn = (nColumn == -1) ? 0 : nColumn + 1;	// next column index after last frozen column

	for (; nColumn<GetColumns()->GetCount(); nColumn++)
	{
		const CXTPReportColumn *pColumn = GetColumns()->GetAt(nColumn);
		if (pColumn->IsVisible())
		{
			nScrollCount += 1;
			nScrollWidth += pColumn->GetWidth();
			
			if (nOutOfViewWidth <= nScrollWidth)
				break;
		}
	}
}

int CXTPReportControl::InsertRow(int nIndex, CXTPReportRow *pRow)
{
	return m_pSectionBody->InsertRow(nIndex, pRow);
}

CXTPReportRecord* CXTPReportControl::AddRecord(CXTPReportRecord *pRecord)
{
	return m_pSectionBody->AddRecord(pRecord);
}

void CXTPReportControl::AddRecordEx(
	CXTPReportRecord *pRecord, CXTPReportRecord *pParentRecord,
	int nRowChildIndex, int nRecordChildIndex)
{
	m_pSectionBody->AddRecordEx(pRecord, pParentRecord, nRowChildIndex, nRecordChildIndex);
}

void CXTPReportControl::UpdateRecord(CXTPReportRecord* pRecord, BOOL bUpdateChildren)
{
	m_pSectionBody->UpdateRecord(pRecord, bUpdateChildren);
}

BOOL CXTPReportControl::RemoveRecordEx(CXTPReportRecord *pRecord, BOOL bAdjustLayout, BOOL bRemoveFromParent)
{
	return m_pSectionBody->RemoveRecordEx(pRecord, bAdjustLayout, bRemoveFromParent);
}

BOOL CXTPReportControl::RemoveRowEx(CXTPReportRow *pRow, BOOL bAdjustLayout)
{
	return m_pSectionBody->RemoveRowEx(pRow, bAdjustLayout);
}

void CXTPReportControl::ReSortRows()
{
	m_pSections->ReSortRows();
}


#endif // XTP_REPORT_DEPRECATED()
