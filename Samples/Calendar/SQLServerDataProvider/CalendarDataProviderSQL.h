// CalendarDataProviderSQL.h
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

#if !defined(AFX_CALENDARDATAPROVIDERSQL_H__791386E5_71B5_4772_B063_74BF78CCB93F__INCLUDED_)
#define AFX_CALENDARDATAPROVIDERSQL_H__791386E5_71B5_4772_B063_74BF78CCB93F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Calendar/XTPCalendarCustomDataProvider.h"

class CCalendarDataProviderSQL : public CXTPCalendarCustomDataProvider
{
public:
	CCalendarDataProviderSQL();
	virtual ~CCalendarDataProviderSQL();

	virtual BOOL Open();
	virtual void Close();

	// Base functionality. 
	// Must be implemented. 
	virtual CXTPCalendarEventsPtr   DoRetrieveDayEvents(COleDateTime dtDay);

	virtual CXTPCalendarEventPtr                DoRead_Event(DWORD dwEventID);
	
	virtual BOOL DoCreate_Event (CXTPCalendarEvent* pEvent, DWORD& rdwNewEventID);
	virtual BOOL DoUpdate_Event (CXTPCalendarEvent* pEvent);
	virtual BOOL DoDelete_Event (CXTPCalendarEvent* pEvent);

	// Recurrence events support.
	virtual CXTPCalendarRecurrencePatternPtr    DoRead_RPattern(DWORD dwPatternID);

	virtual BOOL DoCreate_RPattern  (CXTPCalendarRecurrencePattern* pPattern, DWORD& rdwNewPatternID);
	virtual BOOL DoUpdate_RPattern  (CXTPCalendarRecurrencePattern* pPattern);
	virtual BOOL DoDelete_RPattern  (CXTPCalendarRecurrencePattern* pPattern);

	// Additional feature handlers. 
	// My be implement only if you need these feature.
	virtual CXTPCalendarEventsPtr DoGetUpcomingEvents(COleDateTime dtFrom, COleDateTimeSpan spPeriod);
	virtual CXTPCalendarEventsPtr DoGetAllEvents_raw();
	virtual void                  DoRemoveAllEvents();

private:
	XTPADODB::_ConnectionPtr m_ptrDBconn;
};

#endif // !defined(AFX_CALENDARDATAPROVIDERSQL_H__791386E5_71B5_4772_B063_74BF78CCB93F__INCLUDED_)
