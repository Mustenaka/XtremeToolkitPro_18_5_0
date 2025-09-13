// MessageRecord.h
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

#if !defined(AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_)
#define AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//////////////////////////////////////////////////////////////////////////
// This class is your main custom Record class which you'll manipulate with.
// It contains any kind of specific methods like different types of constructors,
// any additional custom data as class members, any data manipulation methods.
class CMessageRecord : public CXTPReportRecord
{
	DECLARE_SERIAL(CMessageRecord)
public:

	// Construct record object using empty values on each field
	CMessageRecord();

	// Construct record object from detailed values on each field
	CMessageRecord(CString strItem1, CString strItem2, CString strItem3);

	// Construct record object from CMessageRecord object
	CMessageRecord(CMessageRecord* pRecord);

	CMessageRecord& operator= (const CMessageRecord& x);

	// Clean up internal objects
	virtual ~CMessageRecord();

	// Create record fields using empty values
	virtual void CreateItems();

	// Overridden callback method, where we can customize any drawing item metrics.
	virtual void GetItemMetrics(XTP_REPORTRECORDITEM_DRAWARGS* pDrawArgs, XTP_REPORTRECORDITEM_METRICS* pItemMetrics);
};

#endif // !defined(AFX_MESSAGERECORD_H__AFFF918D_1624_41E5_8902_81B1F0C749BA__INCLUDED_)
