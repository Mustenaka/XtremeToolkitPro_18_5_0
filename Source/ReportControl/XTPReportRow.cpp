// XTPReportRow.cpp : implementation of the CXTPReportRow class.
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
#include "Common/XTPToolTipContext.h"
#include "Common/XTPMarkupRender.h"
#include "Common/XTPCustomHeap.h"
#include "Common/XTPSmartPtrInternalT.h"
#include "Common/XTPColorManager.h"

#include "ReportControl/XTPReportDefines.h"
#include "ReportControl/XTPReportRecordItemRange.h"
#include "ReportControl/XTPReportRecord.h"
#include "ReportControl/XTPReportControl.h"
#include "ReportControl/XTPReportPaintManager.h"
#include "ReportControl/XTPReportRow.h"
#include "ReportControl/XTPReportRows.h"
#include "ReportControl/XTPReportSelectedRows.h"
#include "ReportControl/XTPReportColumns.h"
#include "ReportControl/XTPReportColumn.h"
#include "ReportControl/XTPReportTip.h"
#include "ReportControl/XTPReportHeader.h"
#include "ReportControl/XTPReportSection.h"
#include "ReportControl/XTPReportRecordItem.h"
#include "ReportControl/Behavior/XTPReportBehavior.h"
#include "ReportControl/ItemTypes/XTPReportRecordItemPreview.h"
#include "ReportControl/ItemTypes/XTPReportRecordItemIcon.h"

#include "ReportControl/XTPReportControlIIDs.h"

#include "Common/Base/Diagnostic/XTPDisableNoisyWarnings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CXTPReportRow, CXTPCmdTarget)
/////////////////////////////////////////////////////////////////////////////
// CXTPReportRow

CXTPReportRow::CXTPReportRow()
	: m_pParentRows(NULL)
	, m_pParentRow (NULL)
	, m_pRecord    (NULL)
	, m_pChilds    (NULL)
	, m_pControl   (NULL)
	, m_pSection   (NULL)

	, m_nIndex     (-1)
	, m_nChildIndex(-1)

	, m_nGroupLevel (0)
	, m_nRowLevel   (0)

	, m_bVisible   (FALSE)
	, m_bExpanded  (TRUE)
	, m_bLockExpand(FALSE)
{


	m_rcRow.SetRectEmpty();
	m_rcCollapse.SetRectEmpty();
	m_bHasSelectedChilds = FALSE;

	m_nPreviewHeight = 0;
	m_nFreeHeight = 0;
	m_nMergeHeight = -1;

	EnableAutomation();
#ifdef _XTP_ACTIVEX
	EnableTypeLib();
#endif
}

void CXTPReportRow::InitRow(
	CXTPReportControl *pControl,
	CXTPReportSection *pSection,
	CXTPReportRecord  *pRecord)
{
	ASSERT(pRecord || IsGroupRow());
	ASSERT(pControl);

	SetControl(pControl);
	m_pSection = pSection;

	if (m_pControl->m_bFreeHeightMode)
		m_nFreeHeight = m_pControl->m_nDefaultRowFreeHeight;

	if (pRecord)
	{
		m_pRecord = pRecord;
		m_bExpanded = pRecord->m_bExpanded;
		m_pRecord->InternalAddRef();
	}
}

void CXTPReportRow::InitRow(CXTPReportRow *pRow)
{
	ASSERT(pRow->m_pRecord);
	ASSERT(pRow->m_pParentRow == NULL);
	ASSERT(pRow->m_pControl);

	SetControl(pRow->m_pControl);
	m_pRecord  = pRow->m_pRecord;
	m_pSection = pRow->m_pSection;

	if (NULL != m_pRecord)
	{
		m_pRecord->InternalAddRef();
	}

	m_rcRow          = pRow->m_rcRow;
	m_rcCollapse     = pRow->m_rcCollapse;
	m_bVisible       = pRow->m_bVisible;
	m_bExpanded      = pRow->m_bExpanded;
	m_nIndex         = pRow->m_nIndex;
	m_nPreviewHeight = pRow->m_nPreviewHeight;
	m_nRowLevel      = pRow->m_nRowLevel;
	m_nGroupLevel    = pRow->m_nGroupLevel;

	if (m_pControl->m_bFreeHeightMode)
		m_nFreeHeight = m_pControl->m_nDefaultRowFreeHeight;
}


CXTPReportRows* CXTPReportRow::GetChilds(BOOL bCreate)
{
	if (!m_pChilds && bCreate)
		m_pChilds = new CXTPReportRows();

	return m_pChilds;
}



CXTPReportRow::~CXTPReportRow()
{
	if (m_pChilds)
		m_pChilds->InternalRelease();

	if (m_pRecord)
		m_pRecord->InternalRelease();
}

int CXTPReportRow::GetHeight(CDC *pDC, int nWidth)
{
	ASSERT(m_pControl);
	if (!m_pControl)
		return 0;

	int nHeight = m_pControl->GetPaintManager()->GetRowHeight(pDC, this, nWidth);

	if (!IsGroupRow() && !IsItemsVisible())
	{
		nHeight = 0;
	}


	m_nPreviewHeight = 0;

	if (IsPreviewVisible())
	{
		CXTPReportRecordItemPreview *pItem = GetRecord()->GetItemPreview();
		int nWidthPreview = m_pControl->GetReportHeader()->GetWidth();

		m_nPreviewHeight = pItem->GetPreviewHeight(pDC, this, nWidthPreview);
		m_nPreviewHeight = m_pControl->GetPaintManager()->GetPreviewItemHeight(pDC, this, nWidthPreview, m_nPreviewHeight);
	}

	return nHeight + m_nPreviewHeight;
}


BOOL CXTPReportRow::IsFocused() const
{
	return m_pSection->GetRows()->GetFocusedRowIndex() == m_nIndex;
}

BOOL CXTPReportRow::IsSelected() const
{
	return m_pControl->GetSelectedRows()->Contains(this);
}

void CXTPReportRow::SetSelected(BOOL bSelected)
{
	if (bSelected == IsSelected())
		return;

	if (bSelected)
	{
		if (!m_pControl->IsMultipleSelection())
			m_pControl->GetSelectedRows()->Clear();

		m_pControl->GetSelectedRows()->Add(this);
	}
	else
	{
		m_pControl->GetSelectedRows()->Remove(this);
	}

	m_pControl->RedrawControl();
}

int CXTPReportRow::GetLastChildRow(CXTPReportRows* pChilds) const
{
	CXTPReportRow* pRow = pChilds->GetAt(pChilds->GetCount() - 1);

	if (!pRow)
		return -1;

	if (pRow->HasChildren() && pRow->IsExpanded())
		return GetLastChildRow(pRow->GetChilds());

	return pRow->GetIndex();
}

void CXTPReportRow::SelectChilds()
{
	BOOL bM = m_pControl->IsMultipleSelection();
	BOOL bC = HasChildren();
	BOOL bE = IsExpanded();
	if (!(bM && bC && bE && m_nIndex != -1))
		return;

	m_pControl->BeginUpdate();

	int nIndexBegin = m_nIndex + 1;
	int nIndexEnd = GetLastChildRow(GetChilds());

	m_pControl->GetSelectedRows()->AddBlock(nIndexBegin, nIndexEnd);

	m_pControl->EndUpdate();
}

BOOL CXTPReportRow::IsItemsVisible() const
{
	return TRUE;
}


BOOL CXTPReportRow::IsPreviewVisible() const
{
	return !IsGroupRow()
		&& m_pRecord
		&& m_pControl->IsPreviewMode()
		&& !m_pControl->IsIconView()
		&& m_pRecord->GetItemPreview();
}


void CXTPReportRow::DrawItemGrid(CDC *pDC, CXTPReportColumn *pColumn, CRect rcItem)
{
	CXTPReportPaintManager *pPaintManager = m_pControl->GetPaintManager();

	const BOOL bGridVisible = pPaintManager->IsGridVisible(FALSE);

	rcItem.DeflateRect(0, 0, 0, XTP_DPI_Y(1));

	// Draw horizontal grid
	if (bGridVisible && !IsPreviewVisible())
	{
		pPaintManager->DrawGrid(pDC, xtpReportOrientationHorizontal, rcItem);
	}

	// Draw vertical grid
	switch(GetType())
	{
		case xtpRowTypeBody:
		{
			pPaintManager->DrawGrid(pDC, xtpReportOrientationVertical, rcItem);
		}
		break;

		case xtpRowTypeHeader:
		{
			if (pColumn->GetDrawHeaderRowsVGrid())
			{
				pPaintManager->DrawGrid(pDC, xtpReportOrientationVertical, rcItem);
			}
		}
		break;

		case xtpRowTypeFooter:
		{
			if (pColumn->GetDrawFooterRowsVGrid())
			{
				pPaintManager->DrawGrid(pDC, xtpReportOrientationVertical, rcItem);
			}
		}
		break;
	} // switch
}


BOOL AdjustClipRect(CDC *pDC, CRect &rcClip)
{
	if (NULL != pDC && pDC->IsKindOf(RUNTIME_CLASS(CPreviewDC)))
	{
		CPreviewDC *pPreviewDC = DYNAMIC_DOWNCAST(CPreviewDC, pDC);

		pPreviewDC->PrinterDPtoScreenDP(&rcClip.TopLeft());
		pPreviewDC->PrinterDPtoScreenDP(&rcClip.BottomRight());

		// Offset the result by the viewport
		// origin of the print preview window
		CPoint ptOrg;

		// Note: pDC->GetViewportOrg() uses the m_hAttributDC
		::GetViewportOrgEx(pDC->m_hDC, &ptOrg);
		rcClip += ptOrg;
	}

	return TRUE;
}


void CXTPReportRow::Draw(CDC *pDC, CRect rcRow, CRect rcClip, int nLeftOffset,
	CXTPReportRecordMergeItems &mergeItems, int nColumnFrom, int nColumnTo)
{
	// Check preconditions
	ASSERT(NULL != m_pControl);

	if (NULL == m_pControl)
	{
		return;
	}

	const BOOL bIsPrinting = pDC->IsPrinting();
	int nFreezeIndex = -1;
	const int nFreezeCount = m_pControl->GetFreezeColumnsCount(nFreezeIndex);
	const int nHeaderIndent = m_pControl->GetHeaderIndent();

	// Paint Manager
	CXTPReportPaintManager *pPaintManager = m_pControl->GetPaintManager();
	const BOOL bGridVisible = pPaintManager->IsGridVisible(xtpReportOrientationHorizontal);

	int nIconColumnIndex = -1;
	CXTPReportColumn* pRecNumCol = m_pControl->GetColumns()->Find(m_pControl->m_iColumnForNum);
	if (pRecNumCol)
		nIconColumnIndex = pRecNumCol->GetIndex();

	m_rcRow        = rcRow;
	m_rcRow.left  -= nLeftOffset;
	m_rcRow.right -= nLeftOffset;

	if (nFreezeCount == 0)
		rcRow = m_rcRow;

	XTP_REPORTRECORDITEM_DRAWARGS drawArgs;
	drawArgs.pDC      = pDC;
	drawArgs.pControl = m_pControl;
	drawArgs.pRow     = this;

	CRect rcIndent(nFreezeCount ? rcRow : m_rcRow);
	rcIndent.right = rcIndent.left + nHeaderIndent;

	BOOL  bPrevItemWasLastFrozen = FALSE;
	BOOL  bDrawFreezeColsDivider = FALSE;
	CXTPReportRecordItem* pLastFrozenItem = NULL;
	CRect rcLastFrozenItem, rcClipFrozenBorder;
	CRect rcItem(m_rcRow);
	rcItem.bottom -= m_nPreviewHeight; // Deduct preview item

	int nFreezeRight = 0;

	if (nFreezeCount > 0)
	{
		CXTPReportColumn *pColumn = m_pControl->GetColumns()->GetAt(nFreezeIndex);
		nFreezeRight = pColumn->GetRect().right;
	}

	if (NULL != m_pRecord) // if drawing record, not group
	{
		if (bIsPrinting)
		{
			rcItem.right = rcRow.left;
		}

		///////////////////////////////////////////////////////////////////////
		// Paint record items
		///////////////////////////////////////////////////////////////////////
		CRect rcClipRow;   // Clipping rectangle for row
		CRect rcClipItem;  // Clipping rectangle for item

		BOOL bFirstColumn = TRUE;

		int nColumnPos = -1;

		for (int nColumn=nColumnFrom; nColumn<nColumnTo; nColumn++)
		{
			CXTPReportColumn *pColumn = m_pControl->GetColumns()->GetAt(nColumn);

			if (NULL != pColumn && pColumn->IsVisible() && IsItemsVisible())
			{
				++nColumnPos;

				/////////////////////////////////////////////////////////////////
				// Determine item position
				/////////////////////////////////////////////////////////////////

				rcItem.bottom  = m_rcRow.bottom;
				rcItem.bottom -= m_nPreviewHeight;

				if (bIsPrinting) // Printing
				{
					if (pPaintManager->IsColumnWidthWYSIWYG())
					{
						rcItem.left  = rcItem.right;
						rcItem.right = rcItem.left + pColumn->GetWidth();
					}
					else
					{
						rcItem.left  = rcItem.right;
						rcItem.right = rcItem.left + pColumn->GetPrintWidth(rcRow.Width());
					}
				}
				else // Drawing
				{
					rcItem.left  = pColumn->GetRect().left;
					rcItem.right = pColumn->GetRect().right;
				}

				// Offset first column by header indentation
				if (bFirstColumn)
				{
					bFirstColumn = FALSE;
					rcItem.left += nHeaderIndent;
				}

				/////////////////////////////////////////////////////////////////
				//
				/////////////////////////////////////////////////////////////////
				BOOL bDrawFreeze = nColumn<=nFreezeIndex;

				if (bDrawFreeze)
				{
					// Frozen column
					rcClipRow.SetRect(rcRow.left, rcRow.top, nFreezeRight, rcRow.bottom);
				}
				else
				{
					// Non-frozen column
					rcClipRow.SetRect(nFreezeRight, rcRow.top, rcRow.right, rcRow.bottom);
				}

				// Determine clipping rectangle
				rcClipItem.IntersectRect(rcItem, rcClip);        // Clip section
				rcClipItem.IntersectRect(rcClipItem, rcClipRow); // Clip row

				// In print preview mode the clipping rectangle needs to be
				// adjusted before creating the clipping region
				//AdjustClipRect(pDC, rcClipItem);


				if (!bDrawFreeze && !bIsPrinting && rcItem.right <= nFreezeRight)
				{
					// Column is entirely under frozen column, do not draw
					continue;
				}

				if (!CRect().IntersectRect(rcClip, rcItem) && !bIsPrinting)
					continue;

				// Create clipping region
				CRgn rgnClipItem;
				if (!bIsPrinting)
				{
					rgnClipItem.CreateRectRgnIndirect(rcClipItem);
					pDC->SelectClipRgn(&rgnClipItem, RGN_COPY);
				}

				CXTPReportRecordItem *pItem = m_pRecord->GetItem(pColumn);

#if 0
				CXTPReportBorder *pBorder = pPaintManager->GetItemBorder(pItem);

				if (NULL != pBorder)
				{
					pBorder->Draw(pDC, rcItem);
					rcItem = CXTPReportBorder::DeflateRect(rcItem, pBorder);
				}
#endif
				// Draw row background
				pPaintManager->FillRow(pDC, this, rcItem);

				// Draw shade background if sorted by this row
				if (pColumn->IsSorted())
				{
					pPaintManager->FillItemShade(pDC, rcItem);
				}

				if (NULL != pItem)
				{
					// draw item
					drawArgs.pColumn    = pColumn;
					drawArgs.rcItem     = rcItem;
					drawArgs.nTextAlign = pColumn->GetAlignment();
					drawArgs.pItem      = pItem;

					if (!pItem->IsMerged())
					{
						if (pColumn->IsAutoNumbering())
						{
							pPaintManager->DrawRowNumber(pDC, rcItem, this);
						}
						else
						{
							int nItemTextWidth = pItem->Draw(&drawArgs);
							pColumn->m_nMaxItemWidth = max(pColumn->m_nMaxItemWidth, nItemTextWidth);
						}
					}
					else
					{
						CXTPReportRecordItem *pMergeItem = pItem->GetMergeItem();
						CXTPReportRecordMergeItemId itemId(nColumnPos, nColumn, GetIndex());
						mergeItems[pMergeItem].AddItem(itemId, rcItem);
					}
				}
				else if (m_pControl->IsIconView() && !m_pControl->IsVirtualMode())
				{
					// IconView - non Virtual Mode!
					pItem = new CXTPReportRecordItemIcon();
					drawArgs.pColumn = pColumn;
					drawArgs.rcItem = rcItem;
					CXTPReportColumn* pDataColumn = m_pControl->GetColumns()->GetAt(m_pControl->m_iIconPropNum);
					CXTPReportRecordItem* pDataItem = GetRecord()->GetItem(m_pControl->m_iIconPropNum);
					if (pDataColumn != NULL && pDataItem != NULL)
					{
						pItem->SetCaption(pDataItem->GetCaption(pDataColumn));
						pItem->SetIconIndex(m_pControl->m_iIconNum);
						pItem->SetRecord(pDataItem->GetRecord());
					}
					drawArgs.pItem = pItem;
					pItem->Draw(&drawArgs);
					delete pItem;
					pItem = NULL;
				}
				else if (nIconColumnIndex > -1
					&& !m_pControl->IsIconView()
					&& !m_pControl->IsVirtualMode()) //no Item! (ghost)
				{
					CRect rcIcon = m_pControl->GetColumns()->GetAt(nIconColumnIndex)->GetRect();
					rcIcon.top = m_rcRow.top;
					rcIcon.bottom = m_rcRow.bottom - m_nPreviewHeight;
					rcIcon.left = 0;
					pPaintManager->DrawRowNumber(pDC, rcIcon, this);
				}
#if 1
				if (pItem && !pItem->IsMerged())
				{
					CRect rcGridItem(rcItem);
					rcGridItem.left--;
					DrawItemGrid(pDC, pColumn, rcGridItem);
				}
#endif

				if (nColumn == nFreezeIndex)
				{
					bPrevItemWasLastFrozen = TRUE;
					pLastFrozenItem = pItem;
					rcLastFrozenItem = rcItem;
				}
				else if (bPrevItemWasLastFrozen)
				{
					if (!(pLastFrozenItem == NULL || pItem == NULL ||
						pLastFrozenItem->IsMerged() && pItem->IsMerged() &&
						pLastFrozenItem->GetMergeItem() == pItem->GetMergeItem()))
					{
						bDrawFreezeColsDivider = TRUE;
						const int nMaxFrozenBorderWidth = XTP_DPI_X(10);
						rcClipFrozenBorder.IntersectRect(rcItem, rcClip);	// Clip section
					// inflate clip rect to allow draw FreezeColsDivider
						rcClipFrozenBorder.left		-= nMaxFrozenBorderWidth;
						rcClipFrozenBorder.right	+= nMaxFrozenBorderWidth;
					}
					
					bPrevItemWasLastFrozen = FALSE;
				}

				if (!bIsPrinting)	// Release clipping
				{
					pDC->SelectClipRgn(NULL, RGN_COPY);
					rgnClipItem.DeleteObject();
				}
			}
		} // for (nColumn)

		if (IsPreviewVisible())
		{
			CRect rcPreviewItem(m_rcRow);
			rcPreviewItem.DeflateRect(nHeaderIndent, rcPreviewItem.Height() - m_nPreviewHeight, 0, 0);

			drawArgs.rcItem     = rcPreviewItem;
			drawArgs.nTextAlign = DT_LEFT;
			drawArgs.pColumn    = NULL;
			drawArgs.pItem      = m_pRecord->GetItemPreview();

			// Determine clipping rectangle
			rcClipItem.IntersectRect(rcPreviewItem, rcClip);	// Clip section
			rcClipItem.IntersectRect(rcClipItem, 	rcRow);		// Clip row

			CRgn rgnClipItem;
			if (!bIsPrinting)
			{
				rgnClipItem.CreateRectRgnIndirect(rcClipItem);
				pDC->SelectClipRgn(&rgnClipItem, RGN_COPY);
			}

			drawArgs.pItem->Draw(&drawArgs);

			// Release clipping
			if (!bIsPrinting)
			{
				pDC->SelectClipRgn(NULL, RGN_COPY);
				rgnClipItem.DeleteObject();
			}
		}

		if (nHeaderIndent > 0) // draw indent column
		{
			rcIndent.IntersectRect(rcIndent, rcClip);
			pPaintManager->FillIndent(pDC, rcIndent);
		}
	} // (NULL != m_pRecord)

	CRgn rgnClip;
	if (!bIsPrinting)
	{
		rgnClip.CreateRectRgnIndirect(&rcClip);
		pDC->SelectClipRgn(&rgnClip, RGN_COPY);
	}

	CRect rcFocus(rcIndent.right, m_rcRow.top, m_rcRow.right, m_rcRow.bottom - (bGridVisible ? XTP_DPI_Y(1) : 0));

	if (!m_pControl->IsIconView() 
		&& IsFocused() 
		&& (m_pControl->HasFocus() || !pPaintManager->m_bHideSelection)
		&& m_pControl->IsRowFocusVisible())
	{
		pPaintManager->DrawFocusedRow(pDC, rcFocus);
	}

	if (nHeaderIndent > 0 && bGridVisible)
	{
		if (m_nIndex < GetSection()->GetRows()->GetCount() - 1)
		{
			CXTPReportRow *pNextRow = GetSection()->GetRows()->GetAt(m_nIndex+1);
			ASSERT(pNextRow);
			rcFocus.left = rcIndent.left + min(nHeaderIndent, pPaintManager->m_nTreeIndent * pNextRow->GetTreeDepth());
		}
		else
		{
			rcFocus.left = m_rcRow.left;
		}
		rcFocus.right = rcIndent.right;

		pPaintManager->DrawGrid(pDC, xtpReportOrientationHorizontal, rcFocus);
	}

	if (IsPreviewVisible())
	{
		pPaintManager->DrawGrid(pDC, xtpReportOrientationHorizontal, rcFocus);
	}
	
	if (bDrawFreezeColsDivider)
	{
		CRgn rgnClipItem;
		if (!bIsPrinting)
		{
			rgnClipItem.CreateRectRgnIndirect(rcClipFrozenBorder);
			pDC->SelectClipRgn(&rgnClipItem, RGN_COPY);
		}
		pPaintManager->DrawFreezeColsDivider(pDC, rcLastFrozenItem, GetControl(), this);
		
		if (!bIsPrinting)
		{
			pDC->SelectClipRgn(NULL, RGN_COPY);
			rgnClipItem.DeleteObject();
		}
	}
	
	if (!bIsPrinting)
	{
		pDC->SelectClipRgn(NULL, RGN_COPY);
		rgnClip.DeleteObject();
	}
}

int CXTPReportRow::GetTreeDepth() const
{
	return m_nRowLevel;
}

INT_PTR CXTPReportRow::OnToolHitTest(CPoint point, TOOLINFO* pTI)
{
	CRect rcItem;
	CXTPReportRecordItem* pItem = HitTest(point, &rcItem);

	if (!pItem)
		return -1;


	INT_PTR nHit = pItem->OnToolHitTest(point, pTI);
	if (nHit != -1)
		return nHit;

	nHit = (INT_PTR) pItem;
	CString strTip = pItem->GetTooltip();

	m_pControl->OnGetToolTipInfo(this, pItem, strTip);

	if (strTip.IsEmpty() || strTip == _T(" "))
		return -1;

	if (m_pControl->GetPaintManager()->m_bCleanTooltip)
	{
		//Clean markup
		CString s(strTip), u, v;
		int j = s.Find(_T("<"));
		int k = s.Find(_T(">"));
		while (j > -1 && k > -1)
		{
			u = s.Left(j);
			v = s.Mid(k + 1);
			s = u + v;
			strTip = s;
			j = s.Find(_T("<"));
			k = s.Find(_T(">"));
		}
	}

	CXTPToolTipContext::FillInToolInfo(pTI, m_pControl->m_hWnd, rcItem, nHit, strTip);

	return nHit;
}

BOOL CXTPReportRow::OnLButtonDown(XTP_REPORTRECORDITEM_CLICKARGS *pClickArgs)
{
	if (m_pControl->m_bFreeHeightMode)
	{
		XTPReportMouseMode mouseMode = m_pControl->GetMouseMode();
		if (mouseMode == xtpReportMouseOverRowDivide)
		{
			m_pControl->SetCapture();
			m_pControl->SetMouseMode(xtpReportMouseNothing);
			CPoint point = pClickArgs->ptClient;
			m_pControl->ClientToScreen(&point);
			CRect rcControl = m_pControl->GetReportRectangle();
			CRect rcRow(GetRect());
			rcRow.right = rcControl.right;
			m_pControl->ClientToScreen(&rcRow);
			m_pControl->ClientToScreen(&rcControl);

			CXTPSplitterTracker tracker(TRUE, m_pControl->m_bDesktopTrackerMode);

			CRect rcBound(rcRow.left, rcRow.top + m_pControl->m_nDefaultRowFreeHeight, rcRow.right, point.y);
			CRect rcTracker(rcRow.left, point.y - XTP_DPI_Y(2), rcRow.right, point.y - XTP_DPI_Y(1));
			CRect rcAvail(rcRow.left, rcRow.top + m_pControl->m_nDefaultRowFreeHeight, rcRow.right, rcControl.bottom);

			if (tracker.Track(m_pControl, rcAvail, rcTracker, point, FALSE))
			{
				m_nFreeHeight = rcTracker.bottom - rcRow.top;

				if (GetRecord())
					GetRecord()->m_nFreeHeight = m_nFreeHeight;

				m_pControl->AdjustScrollBars();
				m_pControl->RedrawControl();
			}
			return TRUE;
		}
	}

	if (pClickArgs->pItem && pClickArgs->pItem->OnLButtonDown(pClickArgs))
	{
		return TRUE;
	}

	return (BOOL) m_pControl->SendMessageToParent(this, pClickArgs->pItem, pClickArgs->pColumn, XTP_NM_REPORT_LBUTTONDOWN, &pClickArgs->ptClient);
}

BOOL CXTPReportRow::OnLButtonUp(XTP_REPORTRECORDITEM_CLICKARGS *pClickArgs)
{
	if (m_pControl->m_bFreeHeightMode)
	{
		m_pControl->SetMouseMode(xtpReportMouseNothing);
		ReleaseCapture();
	}

	if (pClickArgs->pItem && pClickArgs->pItem->OnLButtonUp(pClickArgs))
	{
		return TRUE;
	}

	return (BOOL) m_pControl->SendMessageToParent(this, pClickArgs->pItem, pClickArgs->pColumn, XTP_NM_REPORT_LBUTTONUP, &pClickArgs->ptClient);
}



BOOL CXTPReportRow::IsLockExpand() const
{
	BOOL bLockExpand = FALSE;

	// Locking on control level
	if (m_pControl)
	{
		bLockExpand = bLockExpand || m_pControl->IsLockExpand();
	}

	// Locking on rows level (not supported)
	if (m_pParentRows)
	{
		//bLockExpand = bLockExpand || m_pParentRows;
	}

	// Locking on row level
	bLockExpand = bLockExpand || m_bLockExpand;

	// Locking on record level (not supported)
	if (m_pRecord)
	{
		//bLockExpand = bLockExpand || m_pRecord;
	}

	return bLockExpand;
}

void CXTPReportRow::OnClick(CPoint ptClicked)
{
	XTP_REPORTRECORDITEM_CLICKARGS clickArgs;
	clickArgs.pControl = m_pControl;
	clickArgs.pRow     = this;
	clickArgs.pColumn  = NULL;
	clickArgs.ptClient = ptClicked;

	// find clicked item
	clickArgs.pItem = HitTest(ptClicked, &clickArgs.rcItem, &clickArgs.pColumn);

	if (m_pControl->IsVirtualMode())
	{
		if (m_rcCollapse.PtInRect(ptClicked)
			&& clickArgs.pColumn && clickArgs.pColumn->IsTreeColumn()
			&& m_rcCollapse.PtInRect(m_pControl->m_mouseDownState.ptMouse))
		{
			m_pControl->SendMessageToParent(this, NULL, clickArgs.pColumn, XTP_NM_REPORT_ROWEXPANDED, NULL);
			return;
		}
	}
	if (HasChildren() && m_rcCollapse.PtInRect(ptClicked)
		&& clickArgs.pColumn && clickArgs.pColumn->IsTreeColumn()
		&& m_rcCollapse.PtInRect(m_pControl->m_mouseDownState.ptMouse)
		&& !IsLockExpand())
	{
		SetExpanded(!IsExpanded());
		return;
	}

	// notify item if found
	if (!clickArgs.pItem)
		return;

	clickArgs.pItem->OnClick(&clickArgs);
}

void CXTPReportRow::OnDblClick(CPoint ptClicked)
{
	XTP_REPORTRECORDITEM_CLICKARGS clickArgs;
	clickArgs.pControl = m_pControl;
	clickArgs.pRow = this;
	clickArgs.ptClient = ptClicked;
	clickArgs.pColumn = NULL;

	// find clicked item
	clickArgs.pItem = HitTest(ptClicked, &clickArgs.rcItem, &clickArgs.pColumn);

	// notify item if found
	if (clickArgs.pItem != NULL)
	{
		clickArgs.pItem->OnDblClick(&clickArgs);
	}
	else
	{
		// just notify parent
		m_pControl->SendMessageToParent(this, NULL, clickArgs.pColumn, NM_DBLCLK, &ptClicked, -1);
	}
}

CRect CXTPReportRow::GetItemRect(CXTPReportRecordItem* pItem)
{
	return GetItemRect(pItem, FALSE);
}

CRect CXTPReportRow::GetItemRect(CXTPReportRecordItem* pItem, BOOL bAsMerged)
{
	if (!IsItemsVisible() || !pItem || !m_pRecord)
		return CRect(0, 0, 0, 0);

	if (IsPreviewVisible() && pItem == GetRecord()->GetItemPreview())
	{
		return CRect(m_rcRow.left + m_pControl->GetHeaderIndent(),
			m_rcRow.bottom - m_nPreviewHeight, m_rcRow.right, m_rcRow.bottom);
	}

	CXTPReportColumns* pColumns = m_pControl->GetColumns();
	int nColumnCount = pColumns->GetCount();

	CRect rcItem(0, m_rcRow.top, 0, m_rcRow.bottom - m_nPreviewHeight);

	int nLastFreezeColumnIndex = -1;
	int nFreezeColCount = m_pControl->GetFreezeColumnsCount(nLastFreezeColumnIndex);
	if (nFreezeColCount > m_pControl->GetColumns()->GetCount() - 1)
	{
		m_pControl->SetFreezeColumnsCount(0);
		nFreezeColCount = 0;
	}

	int nLeft = nFreezeColCount ? pColumns->GetAt(nLastFreezeColumnIndex)->GetRect().right : 0;

	for (int nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CXTPReportColumn* pColumn = pColumns->GetAt(nColumn);
		if (pColumn && pColumn->IsVisible())
		{
			if (pItem->IsMerged()
				? m_pRecord->GetItem(pColumn)->GetMergeItem() != pItem 
				: m_pRecord->GetItem(pColumn) != pItem)
			{
				continue;
			}

			if (bAsMerged && pItem->IsMerged() && GetSection())
			{
				CXTPReportRows* pRows = GetSection()->GetRows();

				// Find the leftmost merged item column.
				int nLeftmostColumn = nColumn;
				while (0 <= nLeftmostColumn)
				{
					CXTPReportColumn* pLeftColumn = pColumns->GetAt(nLeftmostColumn - 1);
					if (pLeftColumn && pLeftColumn->IsVisible())
					{
						if (m_pRecord->GetItem(pLeftColumn)->GetMergeItem() == pItem)
						{
							--nLeftmostColumn;
							continue;
						}
					}

					break;
				}

				// Find the rightmost merged item column.
				int nRightmostColumn = nColumn;
				while ((nRightmostColumn + 1) < nColumnCount)
				{
					CXTPReportColumn* pRightColumn = pColumns->GetAt(nRightmostColumn + 1);
					if (pRightColumn && pRightColumn->IsVisible())
					{
						if (m_pRecord->GetItem(pRightColumn)->GetMergeItem() == pItem)
						{
							++nRightmostColumn;
							continue;
						}
					}

					break;
				}

				// Find the topmost merged item row.
				CXTPReportColumn* pLeftmostColumn = pColumns->GetAt(nLeftmostColumn);
				CXTPReportColumn* pRightmostColumn = pColumns->GetAt(nRightmostColumn); 
				ASSERT(NULL != pLeftmostColumn);
				ASSERT(NULL != pRightmostColumn);

				int nTopmostRow = GetIndex();
				while (0 <= nTopmostRow)
				{
					CXTPReportRow* pTopRow = pRows->GetAt(nTopmostRow - 1);
					if (NULL != pTopRow && pTopRow->IsVisible() && pTopRow->GetRecord())
					{
						if (pTopRow->GetRecord()->GetItem(pLeftmostColumn)->GetMergeItem() == pItem
							&& pTopRow->GetRecord()->GetItem(pRightmostColumn)->GetMergeItem() == pItem)
						{
							--nTopmostRow;
							continue;
						}
					}

					break;
				}

				// Find the bottommost merged item row.
				int nBottommostRow = GetIndex();
				int nRowCount = pRows->GetCount();
				
				ASSERT(NULL != pLeftmostColumn);
				while (nBottommostRow < nRowCount)
				{
					CXTPReportRow* pBottomRow = pRows->GetAt(nBottommostRow + 1);
					if (NULL != pBottomRow && pBottomRow->IsVisible() && pBottomRow->GetRecord())
					{
						if (pBottomRow->GetRecord()->GetItem(pLeftmostColumn)->GetMergeItem() == pItem
							&& pBottomRow->GetRecord()->GetItem(pRightmostColumn)->GetMergeItem() == pItem)
						{
							++nBottommostRow;
							continue;
						}
					}

					break;
				}

				// Obtain corner item rectangles.
				CRect rcLeftTopRow = pRows->GetAt(nTopmostRow)->GetRect();
				CRect rcLeftTopColumn = pColumns->GetAt(nLeftmostColumn)->GetRect();
				CRect rcLeftTopItem(
					rcLeftTopColumn.left, rcLeftTopRow.top,
					rcLeftTopColumn.right, rcLeftTopRow.bottom);

				CRect rcRightBottomRow = pRows->GetAt(nBottommostRow)->GetRect();
				CRect rcRightBottomColumn = pColumns->GetAt(nRightmostColumn)->GetRect();
				CRect rcRightBottomItem(
					rcRightBottomColumn.left, rcRightBottomRow.top,
					rcRightBottomColumn.right, rcRightBottomRow.bottom);

				rcItem.SetRect(rcLeftTopItem.TopLeft(), rcRightBottomItem.BottomRight());
				
				if (pRightmostColumn->GetIndex() > nLastFreezeColumnIndex)
				{
					rcItem.left = max(rcItem.left, nLeft);
					rcItem.right = max(rcItem.right, nLeft);
				}
				if (rcItem.Width() <= 0)
					return CRect(0, 0, 0, 0);
			}
			else
			{
				rcItem.left = pColumn->GetRect().left;
				rcItem.right = pColumn->GetRect().right;
				if (pColumn->GetIndex() > nLastFreezeColumnIndex)
				{
					rcItem.left = max(rcItem.left, nLeft);
					rcItem.right = max(rcItem.right, nLeft);
				}
				if (rcItem.Width() <= 0)
					return CRect(0, 0, 0, 0);
				
				ShiftTreeIndent(rcItem, pColumn);
			}

			return rcItem;
		}
	}

	return CRect(0, 0, 0, 0);
}

void CXTPReportRow::ShiftTreeIndent(CRect& rcItem, CXTPReportColumn* pColumn) const
{
	if (pColumn->IsTreeColumn())
	{
		CXTPReportPaintManager* pPaintManager = m_pControl->GetPaintManager();
		ASSERT(pPaintManager);

		if (pPaintManager == NULL)
			return;

		int nTreeTextIndent = HasChildren() ? 
							  pPaintManager->m_nTreeTextIndentRowParent : 
							  pPaintManager->m_nTreeTextIndentRowChildren;

		int nTreeDepth = GetTreeDepth() - m_nGroupLevel;
		if (nTreeDepth > 0)
			nTreeDepth++;
		rcItem.left += m_pControl->GetIndent(nTreeDepth);

		CRect rcBitmap(rcItem);
		int nIndent = pPaintManager->DrawCollapsedBitmap(NULL, this, rcBitmap).cx;
		rcItem.left += nIndent + nTreeTextIndent;
	}
}

CXTPReportRecordItem* CXTPReportRow::HitTest(CPoint ptPoint, CRect* pRectItem, CXTPReportColumn** ppColumn) const
{
	if (!m_pRecord)
		return NULL;

	// find record item
	int x = m_rcRow.left + m_pControl->GetHeaderIndent();

	CXTPReportColumns* pColumns = m_pControl->GetColumns();
	int nColumnCount = pColumns->GetCount();

	// if hittest for Preview item
	if (IsPreviewVisible())
	{
		CXTPReportRecordItemPreview* pPreviewItem = GetRecord()->GetItemPreview();
		if (pPreviewItem)
		{
			CRect rcItem(x, m_rcRow.bottom - m_nPreviewHeight, m_rcRow.right, m_rcRow.bottom);
			if (rcItem.PtInRect(ptPoint))
			{
				if (pRectItem)
				{
					*pRectItem = rcItem;
				}
				return pPreviewItem;
			}
		}
	}

	CRect rcItem(0, m_rcRow.top, 0, m_rcRow.bottom - m_nPreviewHeight);

	if (!IsItemsVisible())
		return NULL;
		
	int nLastFreezeColumnIndex = -1;
	int nFreezeColCount = m_pControl->GetFreezeColumnsCount(nLastFreezeColumnIndex);
	if (nFreezeColCount > m_pControl->GetColumns()->GetCount() - 1)
	{
		m_pControl->SetFreezeColumnsCount(0);
		nFreezeColCount = 0;
	}

	int nLeft = nFreezeColCount > 0 ? pColumns->GetAt(nLastFreezeColumnIndex)->GetRect().right : 0;

	for (int nColumn = 0; nColumn < nColumnCount; nColumn++)
	{
		CXTPReportColumn* pColumn = pColumns->GetAt(nColumn);
		if (pColumn && pColumn->IsVisible())
		{
			rcItem.left = pColumn->GetRect().left;
			rcItem.right = pColumn->GetRect().right;
			if (nFreezeColCount > 0 && pColumn->GetIndex() > nLastFreezeColumnIndex)
			{
				rcItem.left = max(rcItem.left, nLeft);
				rcItem.right = max(rcItem.right, nLeft);
			}
			if (!rcItem.Width())
				continue;

			if (rcItem.PtInRect(ptPoint) && ppColumn)
			{
				*ppColumn = pColumn;
			}
			// make tooltip shift if tree view (see also Draw function)
			ShiftTreeIndent(rcItem, pColumn);

			// check point
			if (rcItem.PtInRect(ptPoint))
			{
				if (pRectItem)
				{
					*pRectItem = rcItem;
				}

				CXTPReportRecordItem *pItem = m_pRecord->GetItem(pColumn);

				if (pItem && pItem->IsMerged())
				{
					pItem = pItem->GetMergeItem();
					if (ppColumn)
					{
						*ppColumn = pColumns->Find(pItem->GetIndex());
					}
				}

				return pItem;
			}
		}
	}

	return NULL;
}

void CXTPReportRow::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_pControl->m_bFreeHeightMode)
	{
		XTPReportMouseMode mouseMode = m_pControl->GetMouseMode();
		if (mouseMode == xtpReportMouseNothing || mouseMode == xtpReportMouseOverRowDivide)
		{
			CRect rc = GetRect();
			if (rc.bottom - point.y > XTP_DPI_Y(-2) && rc.bottom - point.y < XTP_DPI_Y(4))
			{
				if (mouseMode == xtpReportMouseNothing)
					SetCursor(m_pControl->GetReportHeader()->GetResizeVCursor());

				m_pControl->SetMouseMode(xtpReportMouseOverRowDivide);
				return;
			}
		}
	}

	CRect rcItem;
	CXTPReportRecordItem* pItem = HitTest(point, &rcItem);
	if (pItem != NULL)
		pItem->OnMouseMove(nFlags, point, m_pControl);
}

void CXTPReportRow::FillMetrics(CXTPReportColumn* pColumn, CXTPReportRecordItem* pItem, XTP_REPORTRECORDITEM_METRICS* pMetrics)
{
	m_pControl->m_nLockUpdateCount++;
	XTP_REPORTRECORDITEM_DRAWARGS drawArgs;
	drawArgs.pDC = NULL;
	drawArgs.pColumn = pColumn;
	drawArgs.pControl = m_pControl;
	drawArgs.pRow = this;
	drawArgs.rcItem.SetRectEmpty();
	drawArgs.pItem = pItem;
	drawArgs.nTextAlign = pColumn ? pColumn->GetAlignment() : DT_LEFT;
	GetItemMetrics(&drawArgs, pMetrics);
	m_pControl->m_nLockUpdateCount--;
}

void CXTPReportRow::ShowToolTip(CPoint ptTip, CXTPReportTip* pTipWnd)
{
	if (pTipWnd == NULL)
		return;
	
	CRect rcItem(0, 0, 0, 0);
	CXTPReportColumn* pColumn = NULL;
	CXTPReportRecordItem* pItem = HitTest(ptTip, &rcItem, &pColumn);
	// show tooltip
	if (!(pItem &&
		(pItem->IsPreviewItem() || pColumn)))
	{
		pTipWnd->m_pItem = NULL;
		pTipWnd->m_nRowIndex = -1;
		return;
	}
	
	if (!m_pControl->IsIconView() &&
		!CXTPDrawHelpers::IsTopParentActive(m_pControl->GetSafeHwnd())
		|| m_pControl->GetActiveItem())
		return;

	if ((pItem != pTipWnd->m_pItem)
		|| (m_nIndex != pTipWnd->m_nRowIndex))
	{
		rcItem = GetItemRect(pItem, TRUE);
		pTipWnd->m_pItem = pItem;
		pTipWnd->m_nRowIndex = m_nIndex;

		CString strTip = pItem->GetTooltip();
		m_pControl->OnGetToolTipInfo(this, pItem, strTip);

		if (!strTip.IsEmpty()
			|| strTip == _T(" ")
			|| pColumn
			   &&
			  (pColumn->GetAlignment() & DT_WORDBREAK)
			  && !m_pControl->GetPaintManager()->m_bForceShowTooltip)
			return;

		if (pItem->GetMarkupUIElement() != NULL)
			return;

		XTP_REPORTRECORDITEM_METRICS* pMetrics = new XTP_REPORTRECORDITEM_METRICS();
		pMetrics->strText = pItem->GetCaption(pColumn);
		FillMetrics(pColumn, pItem, pMetrics);

		CString strText(pMetrics->strText);

		strText.TrimRight();

		if (strText.IsEmpty())
		{
			pMetrics->InternalRelease();
			return;
		}

		if (m_pControl->GetMarkupContext() && strText[0] == '<' && strText[strText.GetLength() - 1] == '>') // Markup check
		{
			CXTPMarkupUIElement* pElement = XTPMarkupParseText(m_pControl->GetMarkupContext(), strText);

			if (pElement)
			{
				XTPMarkupReleaseElement(pElement);

				pMetrics->InternalRelease();
				return;
			}
		}


		if (!pItem->GetFormula().IsEmpty())
			strText = pItem->GetFormula();

		XTP_REPORTRECORDITEM_ARGS itemArgs;
		itemArgs.pControl = m_pControl;
		itemArgs.pRow = this;

		pItem->GetCaptionRect(&itemArgs, rcItem);

		m_pControl->ClientToScreen(&rcItem);

		if (!pTipWnd->GetSafeHwnd())
		{
			pTipWnd->Create(m_pControl);
		}

		CWindowDC dc(m_pControl);
		CXTPFontDC font(&dc, pMetrics->pFont);
		CRect rcTooltip(rcItem);
		BOOL bActivate = FALSE;
		pTipWnd->SetTooltipText(strText);
		if (pItem->IsPreviewItem())
		{
			CRect rcCalc(rcTooltip.left, 0, rcTooltip.right, 0);
			dc.DrawText(strText, &rcCalc, DT_WORDBREAK | DT_CALCRECT | DT_NOPREFIX);
			bActivate = (rcCalc.Height() / dc.GetTextExtent(_T(" "), 1).cy) > m_pControl->GetPaintManager()->GetMaxPreviewLines();
			rcTooltip.bottom = rcTooltip.top + rcCalc.Height();
			rcTooltip.right++;
		}
		else if (m_pControl->IsIconView())
		{
			CRect rcCalc;
			rcCalc = m_pControl->GetPaintManager()->CalculateMaxTextRect(&dc,
				pMetrics->strText, &rcItem, TRUE, FALSE, DT_NOPREFIX | DT_WORDBREAK);
			bActivate = ((rcCalc.Width() >= rcItem.Width() - XTP_DPI_X(3))
				|| (rcCalc.Height() >= rcItem.Height() - XTP_DPI_Y(3)));

			rcTooltip.bottom = rcTooltip.top + rcCalc.Height() + XTP_DPI_Y(5);
			rcTooltip.right = rcTooltip.left + rcCalc.Width() + XTP_DPI_X(5);
		}
		else
		{
			// Calculate tooltip fine rect
			if (pTipWnd->IsMultilineForce())
			{
				CRect rcCalc;
				rcCalc = m_pControl->GetPaintManager()->CalculateMaxTextRect(&dc,
				pMetrics->strText, &rcItem, TRUE, FALSE, DT_NOPREFIX | DT_WORDBREAK);
				bActivate = ((rcCalc.Width() >= rcItem.Width() - XTP_DPI_X(3))
					|| (rcCalc.Height() >= rcItem.Height() - XTP_DPI_Y(3)));

				// with small tuning
				rcTooltip.bottom = rcTooltip.top + rcCalc.Height();
				rcTooltip.right = rcTooltip.left + rcCalc.Width() + XTP_DPI_X(15);
			}
			else
			{
				CSize sz = dc.GetTextExtent(strText);
				bActivate = sz.cx > (rcTooltip.Width() - XTP_DPI_X(4));
			}
		}
		if (bActivate ||  m_pControl->GetPaintManager()->m_bForceShowTooltip)
		{
			rcTooltip.InflateRect(XTP_DPI_X(1), XTP_DPI_Y(1), 0, 0);

			if (!m_pControl->GetPaintManager()->IsGridVisible(FALSE))
				rcTooltip.top++;

			CRect rcHover(m_rcRow);
			m_pControl->ClientToScreen(&rcHover);
			pTipWnd->SetFont(pMetrics->pFont);
			//pTipWnd->SetTooltipText(strText);
			pTipWnd->SetHoverRect(m_pControl->IsIconView() ? rcHover : rcTooltip);
			pTipWnd->SetTooltipRect(rcTooltip);
			pTipWnd->Activate(TRUE, pTipWnd->IsMultilineForce() || pItem->IsPreviewItem() || m_pControl->IsIconView());

			TRACKMOUSEEVENT tme =
			{
				sizeof(TRACKMOUSEEVENT), TME_LEAVE, m_pControl->GetSafeHwnd(), 0
			};
			_TrackMouseEvent (&tme);
		}

		pMetrics->InternalRelease();
	}
}

BOOL CXTPReportRow::HasParent(CXTPReportRow* pRow)
{
	if (m_pParentRow == NULL)
		return FALSE;
	if (pRow == m_pParentRow)
		return TRUE;
	return m_pParentRow->HasParent(pRow);
}

void CXTPReportRow::SetFullExpanded(BOOL bExpanded)
{
	SetExpanded(bExpanded, TRUE);
}


void CXTPReportRow::SetExpanded(BOOL bExpanded, BOOL bRecursive)
{
	if (bExpanded != m_bExpanded)
	{
		if (HasChildren())
		{
			BOOL bNotify = m_pControl->GetBehavior()->Notifications->Row->bRowExpanded;
			_SetExpanded(bExpanded, bRecursive, bNotify);

			if (!bNotify)
			{
				m_pSection->RefreshIndexes(0); // Refresh all indexes after expand
			}

			m_pControl->AdjustLayout();
			m_pControl->AdjustScrollBars();
			m_pControl->RedrawControl();
		}
		else
		{
			m_bExpanded = bExpanded;
		}
	}
}

void CXTPReportRow::_SetExpanded(BOOL bExpanded, BOOL bRecursive, BOOL bNotify)
{
	if (bExpanded != m_bExpanded && HasChildren())
	{
		// Store state in row
		m_bExpanded = bExpanded;

		// Store state in record
		if (m_pRecord)
		{
			m_pRecord->SetExpanded(bExpanded);
		}

		if (bExpanded)
		{
			m_pSection->_DoExpand(GetIndex(), this);
		}
		else
		{
			m_pSection->_DoCollapse(this);
		}

		if (bNotify)
		{
			m_pSection->RefreshIndexes(GetIndex());
			m_pControl->SendMessageToParent(this, NULL, NULL, XTP_NM_REPORT_ROWEXPANDED, NULL);
		}

		// Expand children
		if (bRecursive)
		{
			CXTPReportRows *pChildren = GetChilds();

			if (!bNotify && pChildren->GetCount() > 0)
			{
				m_pSection->RefreshIndexes(GetIndex());
			}

			for (int nChild=0; nChild<pChildren->GetCount(); nChild++)
			{
				CXTPReportRow *pChild = pChildren->GetAt(nChild);
				if ((NULL != pChild) && pChild->HasChildren())
				{
					pChild->_SetExpanded(bExpanded, bRecursive, bNotify);

					if (bNotify)
					{
						m_pSection->RefreshIndexes(pChild->GetIndex());
						m_pControl->SendMessageToParent(pChild, NULL, NULL, XTP_NM_REPORT_ROWEXPANDED, NULL);
					}
				}
			}
		}
	}
}

void CXTPReportRow::LockExpand(BOOL bLock)
{
	m_bLockExpand = bLock;
}

CXTPReportRow* CXTPReportRow::AddChild(CXTPReportRow* pRow)
{
	GetChilds()->Add(pRow);
	pRow->m_pParentRow = this;

	return pRow;
}

void CXTPReportRow::OnContextMenu(CPoint ptClick)
{
	CXTPReportColumn     *pColumn = NULL;
	CXTPReportRecordItem *pItem   = HitTest(ptClick, NULL, &pColumn);

	m_pControl->ClientToScreen(&ptClick);

	// send process notification to the user and wait for the reaction
	m_pControl->SendMessageToParent(this, pItem, pColumn, NM_RCLICK, &ptClick);
}

void CXTPReportRow::GetItemMetrics(
	XTP_REPORTRECORDITEM_DRAWARGS *pDrawArgs,
	XTP_REPORTRECORDITEM_METRICS  *pItemMetrics)
{
	ASSERT(m_pRecord);
	ASSERT(pDrawArgs->pRow  == this);
	ASSERT(pDrawArgs->pItem != NULL);

	if (!m_pRecord || !pDrawArgs->pItem)
		return;

	CXTPReportPaintManager *pPaintManager = pDrawArgs->pControl->GetPaintManager();

	pItemMetrics->pFont            = &pPaintManager->m_xtpFontText;
	pItemMetrics->clrForeground    = pPaintManager->m_clrWindowText;
	pItemMetrics->clrBackground    = XTP_REPORT_COLOR_DEFAULT;
	pItemMetrics->nColumnAlignment = pDrawArgs->nTextAlign;
	pItemMetrics->nItemIcon        = XTP_REPORT_NOICON;

	m_pRecord->GetItemMetrics(pDrawArgs, pItemMetrics);
	pDrawArgs->pItem->GetItemMetrics(pDrawArgs, pItemMetrics);

	LOGFONT lf;
	pItemMetrics->pFont->GetLogFont(&lf);
	if (lf.lfWeight == FW_BOLD && !pPaintManager->m_clrBoldText.IsDefaultValue())
	{
		pItemMetrics->clrForeground = pPaintManager->m_clrBoldText;
	}

	m_pControl->GetItemMetrics(pDrawArgs, pItemMetrics);
	pDrawArgs->nTextAlign = pItemMetrics->nColumnAlignment;


	BOOL isSelected	= IsSelected();
	BOOL isFocused	= IsFocused();
	BOOL hasFocus	= GetControl()->HasFocus();
	
	//select merged cells if any row from merge group is selected
	if (pDrawArgs->pItem->IsMerged() && GetSection())
	{
		CXTPReportRows *pRows = GetSection()->GetRows();
		
		for(int i=GetIndex()+1; i < pRows->GetCount(); ++i)
		{
			CXTPReportRow  *pRow = pRows->GetAt(i);
			CXTPReportRecordItem *pItem = pRow->GetRecord()->GetItem(pDrawArgs->pColumn);
			
			if (pItem && pItem->IsMerged() && pItem->GetMergeItem() == pDrawArgs->pItem)
			{
				isSelected	|= pRow->IsSelected();
				isFocused	|= pRow->IsFocused();
				hasFocus	|= pRow->GetControl()->HasFocus();
			}
			else
				break;
		}
	}
	
	if (isSelected
		&& (pDrawArgs->pDC
		&& !pDrawArgs->pDC->IsPrinting())
		&& !pDrawArgs->pControl->IsIconView())
	{
		if (pDrawArgs->pColumn
			&& isFocused
			&& m_pControl->m_pFocusedColumn == pDrawArgs->pColumn)
			return;

		if (hasFocus)
		{
			pItemMetrics->clrForeground = (lf.lfWeight == FW_BOLD && !pPaintManager->m_clrBoldTextHighlight.IsDefaultValue() 
				? pPaintManager->m_clrBoldTextHighlight 
				: pPaintManager->m_clrHighlightText);
			pItemMetrics->clrBackground = pPaintManager->m_clrHighlight;
		}
		else if (!pPaintManager->m_bHideSelection)
		{
			pItemMetrics->clrForeground = pPaintManager->m_clrSelectedRowText;
			pItemMetrics->clrBackground = pPaintManager->m_clrSelectedRow;
		}
	}
}

BOOL CXTPReportRow::HasChildren() const
{
	return m_pChilds && m_pChilds->GetCount() > 0;
}

int CXTPReportRow::GetIndex() const
{
	return m_nIndex;
}

BOOL CXTPReportRow::IsGroupRow() const
{
	return FALSE;
}

BOOL CXTPReportRow::IsExpanded() const
{
	return m_bExpanded;
}

BOOL CXTPReportRow::IsVisible() const
{
	return m_bVisible;
}

void CXTPReportRow::SetVisible(BOOL bVisible)
{
	m_bVisible = bVisible;
}

BOOL CXTPReportRow::IsLastTreeRow() const
{
	if (!m_pParentRow)
		return FALSE;

	CXTPReportRows* pRows = m_pParentRow->GetChilds();

	return pRows->GetCount() > 0 && pRows->GetAt(pRows->GetCount() - 1) == this;
}

void CXTPReportRow::EnsureVisible()
{
	m_pControl->EnsureVisible(this);
}

CXTPReportRow* CXTPReportRow::GetNextSiblingRow() const
{
	if (!m_pParentRows)
		return 0;

	if (m_nChildIndex == -1)
		return 0;

	ASSERT(m_pParentRows->GetAt(m_nChildIndex) == this);

	if (m_nChildIndex < m_pParentRows->GetCount() - 1)
		return m_pParentRows->GetAt(m_nChildIndex + 1);

	return 0;
}


BOOL CXTPReportRow::HasMergedItems() const
{
	BOOL bMerged = FALSE;

	CXTPReportRecord *pRecord = GetRecord();

	if (pRecord)
	{
		for (int iItem=0; iItem<pRecord->GetItemCount(); iItem++)
		{
			CXTPReportRecordItem *pItem = pRecord->GetItem(iItem);

			if (pItem->IsMerged())
			{
				bMerged = TRUE;
				break;
			}
		}
	}

	return bMerged;
}

XTPReportRowType CXTPReportRow::GetType() const
{
	XTPReportRowType rowType = xtpRowTypeInvalid;

	if (NULL != m_pSection)
	{
		rowType = m_pSection->GetRowType();
	}

	return rowType;
}


/////////////////////////////////////////////////////////////////////////////
// IAccessible
/////////////////////////////////////////////////////////////////////////////

CCmdTarget* CXTPReportRow::GetAccessible()
{
	return this;
}

HRESULT CXTPReportRow::GetAccessibleParent(IDispatch* FAR* ppdispParent)
{
	SAFE_MANAGE_STATE(m_pModuleState);

	*ppdispParent = m_pControl->GetIDispatch(TRUE);
	return S_OK;
}

HRESULT CXTPReportRow::GetAccessibleChildCount(long FAR* pChildCount)
{
	if (pChildCount == 0)
	{
		return E_INVALIDARG;
	}
	*pChildCount = 0;

	if (m_pRecord)
	{
		*pChildCount = m_pRecord->GetItemCount();

	}

	return S_OK;
}

HRESULT CXTPReportRow::GetAccessibleChild(VARIANT varChild, IDispatch* FAR* ppdispChild)
{
	*ppdispChild = NULL;
	int nChild = GetChildIndex(&varChild);

	if (nChild <= 0)
	{
		return E_INVALIDARG;
	}

	*ppdispChild = NULL;
	return S_FALSE;
}

HRESULT CXTPReportRow::GetAccessibleName(VARIANT varChild, BSTR* pszName)
{
	int nIndex = GetChildIndex(&varChild);

	if (nIndex == CHILDID_SELF)
	{
		CString strCaption = _T("Report Row");
		*pszName = strCaption.AllocSysString();
		return S_OK;
	}

	CXTPReportRecordItem* pItem = m_pRecord->GetItem(nIndex - 1);
	if (!pItem)
		return E_INVALIDARG;

	CString strCaption = pItem->GetCaption(m_pControl->GetColumns()->Find(pItem->GetIndex()));
	*pszName = strCaption.AllocSysString();
	return S_OK;

}

HRESULT CXTPReportRow::GetAccessibleRole(VARIANT varChild, VARIANT* pvarRole)
{
	int nIndex = GetChildIndex(&varChild);

	if (nIndex == CHILDID_SELF)
	{
		pvarRole->vt = VT_I4;
		pvarRole->lVal = ROLE_SYSTEM_ROW;

	}
	else
	{
		pvarRole->vt = VT_I4;
		pvarRole->lVal = ROLE_SYSTEM_CELL;
	}
	return S_OK;
}

HRESULT CXTPReportRow::GetAccessibleState(VARIANT varChild, VARIANT* pvarState)
{
	pvarState->vt = VT_I4;
	pvarState->lVal = 0;
	int nChild = GetChildIndex(&varChild);

	if (nChild == CHILDID_SELF)
	{
		pvarState->lVal = 0;

		if (IsSelected())
			pvarState->lVal = STATE_SYSTEM_SELECTED;
	}
	else
	{
		CXTPReportRecordItem* pItem = m_pRecord->GetItem(nChild - 1);
		if (pItem)
		{
			CXTPReportColumn* pColumn = m_pControl->GetColumns()->Find(pItem->GetIndex());
			if (pColumn && !pColumn->IsVisible())
			{
				pvarState->lVal = STATE_SYSTEM_INVISIBLE;
			}
		}
	}

	return S_OK;
}


HRESULT CXTPReportRow::AccessibleLocation(long* pxLeft, long* pyTop, long* pcxWidth, long* pcyHeight, VARIANT varChild)
{
	*pxLeft = *pyTop = *pcxWidth = *pcyHeight = 0;

	CRect rc(0, 0, 0, 0);

	int nChild = GetChildIndex(&varChild);

	if (nChild == CHILDID_SELF)
	{
		rc = GetRect();
		m_pControl->ClientToScreen(&rc);
	}
	else
	{
		CXTPReportRecordItem* pItem = m_pRecord->GetItem(nChild - 1);
		if (pItem)
		{
			rc = GetItemRect(pItem);
			m_pControl->ClientToScreen(&rc);
		}

	}

	*pxLeft = rc.left;
	*pyTop = rc.top;
	*pcxWidth = rc.Width();
	*pcyHeight = rc.Height();

	return S_OK;
}

HRESULT CXTPReportRow::AccessibleHitTest(long xLeft, long yTop, VARIANT* pvarID)
{
	if (pvarID == NULL)
		return E_INVALIDARG;

	pvarID->vt = VT_I4;
	pvarID->lVal = CHILDID_SELF;

	CPoint pt(xLeft, yTop);
	m_pControl->ScreenToClient(&pt);

	if (!GetRect().PtInRect(pt))
		return S_FALSE;


	CXTPReportRecordItem* pItem = HitTest(pt);
	if (pItem)
	{
		pvarID->lVal = pItem->GetIndex() + 1;
		return S_OK;
	}

	return S_OK;
}

#ifdef _XTP_ACTIVEX

BEGIN_DISPATCH_MAP(CXTPReportRow, CXTPCmdTarget)
	DISP_FUNCTION_ID   (CXTPReportRow, "Record",    1, OleGetRecord, VT_DISPATCH, VTS_NONE)
	DISP_PROPERTY_EX_ID(CXTPReportRow, "Index",     2, GetIndex,        SetNotSupported, VT_I4)
	DISP_PROPERTY_EX_ID(CXTPReportRow, "GroupRow",  3, IsGroupRow,      SetNotSupported, VT_BOOL)
	DISP_PROPERTY_EX_ID(CXTPReportRow, "Childs",    4, OleGetChilds,    SetNotSupported, VT_DISPATCH)
	DISP_PROPERTY_EX_ID(CXTPReportRow, "ParentRow", 5, OleGetParentRow, SetNotSupported, VT_DISPATCH)
	DISP_PROPERTY_EX_ID(CXTPReportRow, "Section",  12, OleGetSection,   SetNotSupported, VT_DISPATCH)
	DISP_PROPERTY_EX_ID(CXTPReportRow, "Expanded",  6, IsExpanded,      SetFullExpanded, VT_BOOL)
	DISP_PROPERTY_EX_ID(CXTPReportRow, "Selected",  7, IsSelected,     SetSelected,      VT_BOOL)
	DISP_FUNCTION_ID   (CXTPReportRow, "EnsureVisible",  8, EnsureVisible, VT_EMPTY, VTS_NONE)
	DISP_PROPERTY_EX_ID(CXTPReportRow, "NextSiblingRow", 9, OleGetNextSiblingRow, SetNotSupported, VT_DISPATCH)
	DISP_PROPERTY_ID   (CXTPReportRow, "RowTreeLevel",  10, m_nRowLevel, VT_I4)

	DISP_FUNCTION_ID(CXTPReportRow, "GetRect", 101, OleGetRect, VT_EMPTY, VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4)
	DISP_FUNCTION_ID(CXTPReportRow, "GetItemRect", 11, OleGetItemRect, VT_EMPTY, VTS_DISPATCH VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4)
	DISP_FUNCTION_ID(CXTPReportRow, "GetItemRectAsMerged", 13, OleGetItemRectAsMerged, VT_EMPTY, VTS_DISPATCH VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_BOOL)
END_DISPATCH_MAP()

IMPLEMENT_OLETYPELIB_EX(CXTPReportRow, XTPDIID_IReportRow)

CXTPReportRow* AFX_CDECL CXTPReportRow::FromDispatch(LPDISPATCH pDisp)
{
	CXTPReportRow* pInst = NULL;
	if (NULL != pDisp)
	{
		pInst = XTP_DYNAMIC_DOWNCAST_REMOTE_(CXTPReportRow, CXTPReportRow::FromIDispatchSafe(pDisp));
		if (NULL == pInst)
		{
			AfxThrowOleException(E_INVALIDARG);
		}
	}

	return pInst;
}

LPDISPATCH CXTPReportRow::OleGetRecord()
{
	return m_pRecord ? m_pRecord->GetIDispatch(TRUE) : NULL;
}

LPDISPATCH CXTPReportRow::OleGetChilds()
{
	return GetChilds()->GetIDispatch(TRUE);
}

LPDISPATCH CXTPReportRow::OleGetParentRow()
{
	return m_pParentRow ? m_pParentRow->GetIDispatch(TRUE) : NULL;
}

LPDISPATCH CXTPReportRow::OleGetSection()
{
	LPDISPATCH lpDispatch = NULL;

	if (NULL != m_pSection)
	{
		lpDispatch = m_pSection->GetIDispatch(TRUE);
	}

	return lpDispatch;
}

LPDISPATCH CXTPReportRow::OleGetNextSiblingRow()
{
	CXTPReportRow* pRow = GetNextSiblingRow();
	return pRow ? pRow->GetIDispatch(TRUE) : NULL;
}

void CXTPReportRow::OleGetRect(long* Left, long* Top, long* Right, long* Bottom)
{
	CRect rc = CRect(0);

	CXTPReportScreenRows *pScreenRows = GetSection()->GetRows()->GetScreenRows();

	if (m_pControl && m_pControl->IsVirtualMode())
	{
		for (int i = 0; i < pScreenRows->GetSize(); i++)
		{
			if (pScreenRows->GetAt(i)->m_nIndex == m_nIndex)
			{
				rc = pScreenRows->GetAt(i)->m_rcRow;
				break;
			}
		}
	}
	else
		rc = GetRect();
	if (Left) *Left = rc.left;
	if (Top) *Top = rc.top;
	if (Right) *Right = rc.right;
	if (Bottom) *Bottom = rc.bottom;
}

void CXTPReportRow::OleGetItemRect(LPDISPATCH lpDispatch, long* Left, long* Top, long* Right, long* Bottom)
{
	OleGetItemRectAsMerged(lpDispatch, Left, Top, Right, Bottom, VARIANT_FALSE);
}

void CXTPReportRow::OleGetItemRectAsMerged(LPDISPATCH lpDispatch, long* Left, long* Top, long* Right, long* Bottom, VARIANT_BOOL fAsMerged)
{
	CXTPReportRecordItem* pItem = DYNAMIC_DOWNCAST(CXTPReportRecordItem, 
		CXTPReportRecordItem::FromIDispatchSafe(lpDispatch));
	if (pItem)
	{
		CRect rc = GetItemRect(pItem, VARIANT_TRUE == fAsMerged);
		if (Left) *Left = rc.left;
		if (Top) *Top = rc.top;
		if (Right) *Right = rc.right;
		if (Bottom) *Bottom = rc.bottom;
	}
}

#endif

BEGIN_INTERFACE_MAP(CXTPReportRow, CXTPCmdTarget)
#ifdef _XTP_ACTIVEX
	INTERFACE_PART(CXTPReportRow, XTPDIID_IReportRow, Dispatch)
#endif
	INTERFACE_PART(CXTPReportRow, IID_IAccessible, ExternalAccessible)
END_INTERFACE_MAP()
