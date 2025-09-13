// MessageRecord.cpp
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
#include "ReportDialogEx.h"
#include "MessageRecord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// CMessageRecord class

IMPLEMENT_SERIAL(CMessageRecord, CXTPReportRecord, VERSIONABLE_SCHEMA | _XTP_SCHEMA_CURRENT)

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMessageRecord::CMessageRecord()
{
	CreateItems();
}

CMessageRecord::CMessageRecord(CString strItem1, CString strItem2, CString strItem3, CString strItem4)
{
	AddItem(new CXTPReportRecordItemText(strItem1));
	AddItem(new CXTPReportRecordItemText(strItem2));
	AddItem(new CXTPReportRecordItemText(strItem3));
	AddItem(new CXTPReportRecordItemText(strItem4));
}

CMessageRecord::CMessageRecord(CMessageRecord* pRecord)
{
	for(int i = 0; i < 4; i++)
	{
		AddItem(new CXTPReportRecordItemText(((CXTPReportRecordItemText*)pRecord->GetItem(i))->GetValue()));
	}
}

CMessageRecord& CMessageRecord::operator= (const CMessageRecord& x)
{
	for(int i = 0; i < GetItemCount(); i++)
	{
		((CXTPReportRecordItemText*)GetItem(i))->SetValue(((CXTPReportRecordItemText*)x.GetItem(i))->GetValue());
	}

	return *this;
}

void CMessageRecord::CreateItems()
{
	// Initialize record items with empty values
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
	AddItem(new CXTPReportRecordItemText(_T("")));
}

CMessageRecord::~CMessageRecord()
{
}

void CMessageRecord::GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics)
{
	CXTPReportRecord::GetItemMetrics(pDrawArgs, pItemMetrics);
}
