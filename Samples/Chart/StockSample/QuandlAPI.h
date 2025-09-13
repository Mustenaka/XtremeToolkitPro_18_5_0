// QuandlAPI.h: interface for the CQuandlAPI class.
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

#if !defined(__QUANDLAPI_H__)
#define __QUANDLAPI_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//============================================================================
// Summary: CQuandlAPI is a singleton class used to access the Quandl API for
//          stock quotes and financial information for a particular company.
//          See https://www.quandl.com/ for more details.
//============================================================================
class CQuandlAPI  
{
public:

    // ----------------------------------------------------------------------
    // Summary: Destructor, handles cleanup and de-allocation.
    // ----------------------------------------------------------------------
	virtual ~CQuandlAPI();

    // ----------------------------------------------------------------------
    // Summary: Call this method to retreive the financial history for the 
    //          ticker specified by strTicker for a particular time range.
    // Input:   strTicker - Specifies the ticker to retrieve history for.
    //          timeStart - Starting date to retrieve histroy for.
    //            timeEnd - Ending date to retrieve history for.
    // Returns: A CStringArray containing financial information for the ticker
    //          specified by strTicker that occured between the dates specified
    //          by timeStart and timeEnd.
    // ----------------------------------------------------------------------
    CStringArray& GetHistory(CString strTicker, CTime timeStart, CTime timeEnd);

    // ----------------------------------------------------------------------
    // Summary: Call this method to retrieve the latest financial quote for the
    //          ticker specifed by strTicker.
    // Input:   strTicker - Specifies the ticker to retrieve financial quote for.
    // Returns: A comma delimited array of values for the specified ticker.  You 
    //          can use AfxExtractSubString to retrieve each item, can be one of 
    //          the following values:
    //          0 - Date
    //          1 - Open
    //          2 - High
    //          3 - Low
    //          4 - Close
    //          5 - Volume
    // Example: CString strArrQuote = CQuandlAPI::Inst().GetQuote(m_strTicker);
    //          AfxExtractSubString(m_strDate, strArrQuote, 0, ',');
    // ----------------------------------------------------------------------
    CString GetQuote(CString strTicker);

    // ----------------------------------------------------------------------
    // Summary: Call this method to retreive the Company, Sector and Industry
    //          details for the specified strTicker.
    // Input:   strTicker - Specifies the ticker to retrieve details for.
    //             iIndex - Indentifies which value to extract, can be one of
    //                      the following values:
    //                      1 - Retrieve company name.
    //                      2 - Retreive sector name.
    //                      3 - Retreive industry name.
    // Returns: A CString value containing the details identified by iIndex.
    // ----------------------------------------------------------------------
    CString GetTickerInfo(CString strTicker, int iIndex);

    // ----------------------------------------------------------------------
    // Summary: Call this method to extract the date from the specified quote
    //          string array.
    // Input:   arrQuote - String array containing financial information for a 
    //                     particular ticker symbol.
    // Returns: A CString value containing the date from the quote string array.
    // ----------------------------------------------------------------------
	CString GetDate(CString arrQuote);

    // ----------------------------------------------------------------------
    // Summary: Call this method to extract the day's low from the specified 
    //          quote string array.
    // Input:   arrQuote - String array containing financial information for a 
    //                     particular ticker symbol.
    // Returns: A double value containing the low from the quote string array.
    // ----------------------------------------------------------------------
	double GetLow(CString arrQuote);

    // ----------------------------------------------------------------------
    // Summary: Call this method to extract the day's high from the specified 
    //          quote string array.
    // Input:   arrQuote - String array containing financial information for a 
    //                     particular ticker symbol.
    // Returns: A double value containing the high from the quote string array.
    // ----------------------------------------------------------------------
	double GetHigh(CString arrQuote);

    // ----------------------------------------------------------------------
    // Summary: Call this method to extract the day's open from the specified 
    //          quote string array.
    // Input:   arrQuote - String array containing financial information for a 
    //                     particular ticker symbol.
    // Returns: A double value containing the open from the quote string array.
    // ----------------------------------------------------------------------
	double GetOpen(CString arrQuote);

    // ----------------------------------------------------------------------
    // Summary: Call this method to extract the day's close from the specified 
    //          quote string array.
    // Input:   arrQuote - String array containing financial information for a 
    //                     particular ticker symbol.
    // Returns: A double value containing the close from the quote string array.
    // ----------------------------------------------------------------------
	double GetClose(CString arrQuote);

    // ----------------------------------------------------------------------
    // Summary: Call this method to display an alert box containing error
    //          information if IsValid() returns FALSE.
    // ----------------------------------------------------------------------
    void ShowError();

    // ----------------------------------------------------------------------
    // Summary: Call this after a call to GetHistory or GetQuote to determine
    //          if there were any errors retrieving financial information for 
    //          any given ticker.
    // Returns: TRUE if successful, otherwise returns FALSE.
    // ----------------------------------------------------------------------
    BOOL IsValid() const;

    // ----------------------------------------------------------------------
    // Summary: Called to access the CQuandlAPI singleton class.
    // ----------------------------------------------------------------------
    static CQuandlAPI& Inst();

private:
    // ----------------------------------------------------------------------
    // Make the constructor private so the object can only be accessed thru
    // a call to CQuandlAPI::Inst() making this a single instance object.
    // ----------------------------------------------------------------------
	CQuandlAPI();

    // ----------------------------------------------------------------------
    // Override the default copy constructor and assignment operator so 
    // you can not make a copy of this singleton.
    // ----------------------------------------------------------------------
    CQuandlAPI(CQuandlAPI const&);      // Don't Implement.
    void operator=(CQuandlAPI const&);  // Don't Implement.

    // ----------------------------------------------------------------------
    // Initializes ticker array that contains details for each company.
    // ----------------------------------------------------------------------
    void InitTickerArray();

    // ----------------------------------------------------------------------
    // Retrieves the file buffer from the specified URL and converts it to a 
    // CStringArray.
    // ----------------------------------------------------------------------
    BOOL ReadBuffer(LPCTSTR lpszURL, CStringArray& arrString);

    CStringArray m_strArrTickers; // Array of available ticker symbols.
    CStringArray m_strArrQuote;   // Array of available quote data.
    CString      m_strError;      // Error message if any.
};

#endif // !defined(__QUANDLAPI_H__)
