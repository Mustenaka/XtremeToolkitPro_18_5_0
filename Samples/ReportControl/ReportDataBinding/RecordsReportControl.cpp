// RecordsReportControl.cpp
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
#include "RecordsReportControl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRecordsReportControl::CRecordsReportControl()
{
	m_pFocusedRecord = NULL;
	m_pTopRow = NULL;
}

CRecordsReportControl::~CRecordsReportControl()
{
	if(m_pFocusedRecord)
		m_pFocusedRecord = NULL;
}


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRecordsReportControl, CXTPReportControl)
	//{{AFX_MSG_MAP(CRecordsReportControl)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CRecordsReportControl::AddNewRecord()
{
	CXTPReportRecord* pRecord = NULL;
	if(FAILED(GetDataManager()->CreateEmptyRecord(&pRecord)) || !pRecord)
		return;
	int i;
	for(i = 0; i < pRecord->GetItemCount(); i++)
	{
		VARIANT vtValue = ((CXTPReportRecordItemVariant*)pRecord->GetItem(i))->GetValue();
		if(vtValue.vt == VT_BSTR)
		{
			CString strValue = _T("New Record");
			COleVariant vtBstrValue(strValue);
			((CXTPReportRecordItemVariant*)pRecord->GetItem(i))->SetValue(vtBstrValue);
		}
	}
	AddRecordEx(pRecord);
	Populate();
}

void CRecordsReportControl::DeleteSelectedRows()
{
	CXTPReportSelectedRows* pSelectedRows = GetSelectedRows();
	if(!pSelectedRows)
		return;
	int nRow = pSelectedRows->GetCount() - 1;
	if(nRow < 0)
		return;
	CWaitCursor wc;
	CXTPReportRow* pFocusedRow = pSelectedRows->GetAt(pSelectedRows->GetCount() - 1);
	pFocusedRow = GetRows()->GetAt(pFocusedRow->GetIndex() + 1);
	while(nRow >= 0)
	{
		CXTPReportRecord* pRecord = pSelectedRows->GetAt(nRow--)->GetRecord();
		if (pRecord)
			RemoveRecordEx(pRecord);
		if(nRow >= pSelectedRows->GetCount())
			nRow = pSelectedRows->GetCount() - 1;
	}
	SetFocusedRow(pFocusedRow ? pFocusedRow : GetFocusedRow());
}

void CRecordsReportControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar)
	{
		case VK_DELETE :
			DeleteSelectedRows();
			break;
		case VK_INSERT :
		{
			AddNewRecord();
			break;
		}
		case VK_RETURN :
			CXTPReportRow* pFocusedRow = GetFocusedRow();
			if(pFocusedRow && pFocusedRow->GetType() == xtpRowTypeHeader)
			{
				CXTPReportRecord* pRecord = pFocusedRow->GetRecord();
				if(!pRecord)
					break;
				pRecord->InternalAddRef();
				HRESULT hr;
				if(FAILED(hr = GetDataManager()->AddRecord(pRecord, TRUE)))
				{
					pRecord->InternalRelease();
					break;
				}
				pRecord = NULL;
				if(FAILED(hr = GetDataManager()->CreateEmptyRecord(&pRecord)) || pRecord == NULL)
					break;
				GetHeaderRecords()->RemoveAll();
				GetHeaderRecords()->Add(pRecord);
				PopulateHeaderRows();
			}
			break;
	}

	CXTPReportControl::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CRecordsReportControl::OnFocusChanging(CXTPReportRow* pNewRow, CXTPReportColumn* pNewCol)
{
	CXTPReportControl::OnFocusChanging(pNewRow, pNewCol);

	// add new record
	CXTPReportRow* pFocusedRow = GetFocusedRow();
	if(pFocusedRow && pFocusedRow->GetType() == xtpRowTypeHeader && pNewRow && pNewRow != pFocusedRow && pNewRow->GetType() != xtpRowTypeHeader)
	{
		CXTPReportRecord* pRecord = pFocusedRow->GetRecord();
		if(!pRecord)
			return TRUE;
		pRecord->InternalAddRef();
		HRESULT hr;
		if(FAILED(hr = GetDataManager()->AddRecord(pRecord, TRUE)))
		{
			pRecord->InternalRelease();
			return TRUE;
		}
		pRecord = NULL;
		if(FAILED(hr = GetDataManager()->CreateEmptyRecord(&pRecord)) || pRecord == NULL)
			return TRUE;
		GetHeaderRecords()->RemoveAll();
		GetHeaderRecords()->Add(pRecord);
		PopulateHeaderRows();
	}

	return TRUE;
}
