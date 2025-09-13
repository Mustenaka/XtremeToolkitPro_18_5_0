// QuandlAPI.cpp: implementation of the CQuandlAPI class.
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
#include "QuandlAPI.h"

#include <afxinet.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQuandlAPI::CQuandlAPI()
{
    InitTickerArray();
}

CQuandlAPI::~CQuandlAPI()
{
}

AFX_INLINE void ExtractSubString(CString& rString, const CString& strRead, int& iStart)
{
    // see if sub-string is wrapped in quotes.
    if (strRead[iStart] == _T('"'))
    {
        int iNext = strRead.Find(_T('"'), iStart + 1);
        rString = strRead.Mid(iStart + 1, iNext - iStart - 1);
        iStart = strRead.Find(_T(','), iNext) + 1;
    }
    else
    {
        int iNext = strRead.Find(_T(','), iStart);
        rString = strRead.Mid(iStart, iNext - iStart);
        iStart = strRead.Find(_T(','), iNext) + 1;
    }
}

BOOL CQuandlAPI::ReadBuffer(LPCTSTR lpszURL, CStringArray& arrString)
{
    arrString.RemoveAll();

	CInternetSession session;
	CInternetFile* pFile = (CInternetFile*)session.OpenURL(lpszURL);
	
	if (pFile)
	{
        // Note: we use CFile::Read instead of a MFC bug with CStdioFile::ReadString 
        // that returns garbled characters with UNICODE builds.  To work around this
        // we retrieve the buffer 128 bytes at a time and terminate the result using
        // the number of bytes read.

        CString strBuffer;
        char szBuffer[256];
        UINT uBytes = pFile->Read(szBuffer, 128);

        while (uBytes != 0)
        {
            szBuffer[uBytes + 1] = 0;
            strBuffer += CString(szBuffer, uBytes);
            uBytes = pFile->Read(szBuffer, 128);
        }

        // Now that we have our entire buffer, we can use _tcstok to for the newline
        // token to retrieve each line and add it to our string array.

		TCHAR* lpszContext = NULL;
		TCHAR* pszBuffer = STRTOK_S((LPTSTR)(LPCTSTR)strBuffer, _T("\n"), &lpszContext);
        while (pszBuffer != NULL)
        {
            arrString.Add(pszBuffer);
            pszBuffer = STRTOK_S(NULL, _T("\n"), &lpszContext);
        }
        
 		pFile->Close();
		delete pFile;
    }

    session.Close();

    if (arrString.GetSize() == 2)
    {
        CString strError;
        AfxExtractSubString(strError, arrString[0], 0, _T(','));

        // check for error.
        if (strError.CompareNoCase(_T("code")) == 0)
        {
            m_strError = arrString[1];
            m_strError.Remove(_T('"'));
	        arrString.RemoveAll();
            return FALSE;
        }
    }

    return (arrString.GetSize() > 0);
}

void CQuandlAPI::InitTickerArray()
{
    m_strArrTickers.RemoveAll();

	// format URL to pass to GetHttpConnection.
	CString strURL = _T("https://s3.amazonaws.com/quandl-static-content/Ticker+CSV%27s/secwiki_tickers.csv");

    CStringArray strArrTickers;
    ReadBuffer(strURL, strArrTickers);

    for (int i = 0; i < strArrTickers.GetSize(); ++i)
    {
        CString strBuffer;
        int iIndex = 0;
        
        CString strTicker;
        ExtractSubString(strTicker, strArrTickers[i], iIndex);
        strBuffer = strTicker + _T(";");
        
        CString strName;
        ExtractSubString(strName, strArrTickers[i], iIndex);
        strBuffer = strBuffer + strName + _T(";");
        
        CString strSector;
        ExtractSubString(strSector, strArrTickers[i], iIndex);
        strBuffer = strBuffer + strSector + _T(";");
        
        CString strIndustry;
        ExtractSubString(strIndustry, strArrTickers[i], iIndex);
        strBuffer = strBuffer + strIndustry;
        
        m_strArrTickers.Add(strBuffer);
    }
}

CStringArray& CQuandlAPI::GetHistory(CString strTicker, CTime timeStart, CTime timeEnd)
{
	m_strArrQuote.RemoveAll();
    strTicker.MakeUpper();
    m_strError.Empty();

    CString strEnd = timeEnd.Format(_T("%Y-%m-%d"));
    CString strStart = timeStart.Format(_T("%Y-%m-%d"));

	// format URL to pass to GetHttpConnection.
	CString strURL;	
	strURL.Format(_T("https://www.quandl.com/api/v3/datasets/WIKI/%s.csv?trim_start=%s&trim_end=%s"),
		strTicker.operator LPCTSTR(), strStart.operator LPCTSTR(), strEnd.operator LPCTSTR());

    ReadBuffer(strURL, m_strArrQuote);

    // remove first line which is column name list.
    m_strArrQuote.RemoveAt(0);
    
	return m_strArrQuote;
}

CString CQuandlAPI::GetQuote(CString strTicker)
{
	m_strArrQuote.RemoveAll();
    strTicker.MakeUpper();
    m_strError.Empty();

	// format URL to pass to GetHttpConnection.
	CString strURL;
	strURL.Format(_T("https://www.quandl.com/api/v3/datasets/WIKI/%s.csv?rows=1"),
        strTicker.operator LPCTSTR());

    ReadBuffer(strURL, m_strArrQuote);

    if (m_strArrQuote.GetSize() >= 2)
    {
        return m_strArrQuote[1];
    }

    return _T("");
}

CString CQuandlAPI::GetTickerInfo(CString strTicker, int iIndex)
{
    CString strInfo = strTicker;

    for (int i = 0; i < m_strArrTickers.GetSize(); ++i)
    {
        CString strBuffer;
        AfxExtractSubString(strBuffer, m_strArrTickers[i], 0, ';');

        if (strBuffer.CompareNoCase(strTicker) == 0)
        {
            AfxExtractSubString(strInfo, m_strArrTickers[i], iIndex, ';');
            break;
        }
    }

    return strInfo;
}

AFX_INLINE double StringToDouble(LPCTSTR lpszStr)
{
	USES_CONVERSION;
	return atof(T2A((LPTSTR)lpszStr));
}

CString CQuandlAPI::GetDate(CString arrQuote)
{
	CString strDate;
	AfxExtractSubString(strDate, arrQuote, 0, ',');
	return strDate;
}

double CQuandlAPI::GetLow(CString arrQuote)
{
	CString strLow;
	AfxExtractSubString(strLow, arrQuote, 3, ',');
	return StringToDouble(strLow);
}

double CQuandlAPI::GetHigh(CString arrQuote)
{
	CString strHigh;
	AfxExtractSubString(strHigh, arrQuote, 2, ',');
	return StringToDouble(strHigh);
}

double CQuandlAPI::GetOpen(CString arrQuote)
{
	CString strOpen;
	AfxExtractSubString(strOpen, arrQuote, 1, ',');
	return StringToDouble(strOpen);
}

double CQuandlAPI::GetClose(CString arrQuote)
{
	CString strClose;
	AfxExtractSubString(strClose, arrQuote, 4, ',');
	return StringToDouble(strClose);
}

void CQuandlAPI::ShowError()
{
    int nIndex = m_strError.Find(_T(','));

    if (nIndex == -1)
    {
        AfxMessageBox(m_strError, MB_OK | MB_ICONWARNING);
    }
    else
    {
        CString strMessage = m_strError.Right(m_strError.GetLength()-(nIndex+1));
        CString strCode = m_strError.Left(nIndex);
        CString strBuffer;
        strBuffer.Format(_T("%s\n\nCode: %s"), strMessage.operator LPCTSTR(), strCode.operator LPCTSTR());
        AfxMessageBox(strBuffer, MB_OK | MB_ICONWARNING);
    }
}

BOOL CQuandlAPI::IsValid() const
{
    return m_strError.IsEmpty();
}

CQuandlAPI& CQuandlAPI::Inst()
{
    static CQuandlAPI sInst;
    return sInst;
}
