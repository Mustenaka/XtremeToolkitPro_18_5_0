// StockQuoteDlg.cpp
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
#include "stocksample.h"
#include "StockSampleDoc.h"
#include "StockSampleView.h"
#include "StockQuoteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStockQuoteDlg dialog


CStockQuoteDlg::CStockQuoteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStockQuoteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStockQuoteDlg)
	m_strCompany = _T("");
	m_strOpen = _T("");
	m_strVolume = _T("");
	m_strDate = _T("");
	m_strClose = _T("");
	m_strHigh = _T("");
	m_strLow = _T("");
	m_strTicker = _T("MSFT");
	m_nStyle = 0;
	m_strSector = _T("");
	m_strIndustry = _T("");
	m_bThickLines = FALSE;
	//}}AFX_DATA_INIT
	
	m_crRed = RGB(204,51,0);
	m_crGreen = RGB(0,153,0);
	m_pChart = NULL;
}


void CStockQuoteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStockQuoteDlg)
    DDX_Control(pDX, IDC_STR_LOW, m_txtLow);
	DDX_Control(pDX, IDC_STR_HIGH, m_txtHigh);
	DDX_Control(pDX, IDC_STR_CLOSE, m_txtClose);
	DDX_Control(pDX, IDC_STR_DATE, m_txtDate);
	DDX_Control(pDX, IDC_STR_VOLUME, m_txtVolume);
	DDX_Control(pDX, IDC_STR_OPEN, m_txtOpen);
	DDX_Control(pDX, IDC_STR_COMPANY, m_txtCompany);
    DDX_Text(pDX, IDC_STR_COMPANY, m_strCompany);
	DDX_Text(pDX, IDC_STR_OPEN, m_strOpen);
	DDX_Text(pDX, IDC_STR_VOLUME, m_strVolume);
	DDX_Text(pDX, IDC_STR_DATE, m_strDate);
	DDX_Text(pDX, IDC_STR_CLOSE, m_strClose);
	DDX_Text(pDX, IDC_STR_HIGH, m_strHigh);
	DDX_Text(pDX, IDC_STR_LOW, m_strLow);
	DDX_Text(pDX, IDC_EDIT_TICKER, m_strTicker);
	DDX_CBIndex(pDX, IDC_COMBO_STYLE, m_nStyle);
	DDX_Text(pDX, IDC_STR_SECTOR, m_strSector);
	DDX_Text(pDX, IDC_STR_INDUSTRY, m_strIndustry);
	DDX_Check(pDX, IDC_CHK_THICKLINES, m_bThickLines);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStockQuoteDlg, CDialog)
	//{{AFX_MSG_MAP(CStockQuoteDlg)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTN_GETQUOTE, OnBtnGetQuote)
	ON_CBN_SELENDOK(IDC_COMBO_STYLE, OnSelendOkComboStyle)
	ON_BN_CLICKED(IDC_CHK_THICKLINES, OnChkThickLines)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStockQuoteDlg message handlers

BOOL CStockQuoteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	NONCLIENTMETRICS ncm;
	::ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
	ncm.cbSize = sizeof(NONCLIENTMETRICS);
	
	VERIFY(::SystemParametersInfo(SPI_GETNONCLIENTMETRICS,
		sizeof(NONCLIENTMETRICS), &ncm, 0));
	
	ncm.lfMenuFont.lfWeight = FW_BOLD;
	m_fontBold.CreateFontIndirect(&ncm.lfMenuFont);
	
	OnBtnGetQuote();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CStockQuoteDlg::OnBtnGetQuote() 
{
    CString strSymbol = m_strTicker;
	UpdateData();
	
	m_txtDate.SetFont(&m_fontBold);
	m_txtOpen.SetFont(&m_fontBold);
	m_txtClose.SetFont(&m_fontBold);
	m_txtHigh.SetFont(&m_fontBold);
	m_txtLow.SetFont(&m_fontBold);
	m_txtVolume.SetFont(&m_fontBold);
	m_txtCompany.SetFont(&m_fontBold);

	CString strArrQuote = CQuandlAPI::Inst().GetQuote(m_strTicker);

    if (CQuandlAPI::Inst().IsValid())
    {
        m_strCompany = CQuandlAPI::Inst().GetTickerInfo(m_strTicker, 1);
        m_strSector = CQuandlAPI::Inst().GetTickerInfo(m_strTicker, 2);
        m_strIndustry = CQuandlAPI::Inst().GetTickerInfo(m_strTicker, 3);

	    AfxExtractSubString(m_strDate, strArrQuote, 0, ',');
	    AfxExtractSubString(m_strOpen, strArrQuote, 1, ',');
	    AfxExtractSubString(m_strHigh, strArrQuote, 2, ',');
	    AfxExtractSubString(m_strLow, strArrQuote, 3, ',');
	    AfxExtractSubString(m_strClose, strArrQuote, 4, ',');
	    AfxExtractSubString(m_strVolume, strArrQuote, 5, ',');
	    
	    m_strVolume = FormatNumber(_ttoi(m_strVolume));
	    
	    if (m_pChart)
	    {
            m_pChart->UpdateHistory(m_strTicker, (m_nStyle == 0));
	    }
    }
    else
    {
        m_strTicker = strSymbol;
        CQuandlAPI::Inst().ShowError();
    }

    m_strTicker.MakeUpper();
    m_strCompany.MakeUpper();
    
    UpdateData(FALSE);
}

CString CStockQuoteDlg::FormatNumber(LONGLONG ulNumber)
{
	TCHAR szLeadingZero[30];
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT,
		LOCALE_ILZERO, szLeadingZero, 2) == 0)
	{
		TRACE0("Error obtaining leading zero locale information.\n");
		return _T("");
	}
	
	TCHAR szDecimalSep[5];
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT,
		LOCALE_SDECIMAL, szDecimalSep, 4) == 0)
	{
		TRACE0("Error obtaining decimal separator locale information.\n");
		return _T("");
	}
	
	TCHAR szThousandSep[5];
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT,
		LOCALE_STHOUSAND, szThousandSep, 4) == 0)
	{
		TRACE0("Error obtaining thousand separator locale information.\n");
		return _T("");
	}
	
	TCHAR szNegativeOrder[30];
	if (::GetLocaleInfo(LOCALE_USER_DEFAULT,
		LOCALE_INEGNUMBER, szNegativeOrder, 2) == 0)
	{
		TRACE0("Error obtaining negative order locale information.\n");
		return _T("");
	}
	
	NUMBERFMT fmt;
	fmt.NumDigits     = 0;
	fmt.LeadingZero   = _ttoi(szLeadingZero);
	fmt.Grouping      = 3;
	fmt.lpDecimalSep  = szDecimalSep;
	fmt.lpThousandSep = szThousandSep;
	fmt.NegativeOrder = _ttoi(szNegativeOrder);
	
	CString strValue;
	strValue.Format(_T("%I64d"), ulNumber);
	
	TCHAR szBuffer[256];
	if (::GetNumberFormat(LOCALE_USER_DEFAULT, 0, strValue, &fmt, szBuffer, 256) == 0)
	{
		TRACE0("Error obtaining number format for default locale.\n");
		return _T("");
	}
	
	return szBuffer;
}

HBRUSH CStockQuoteDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (pWnd->GetDlgCtrlID() == IDC_STR_CLOSE)
	{
        TCHAR* szStopString;
        
		if (_tcstod(m_strClose, &szStopString) > _tcstod(m_strOpen, &szStopString))
		{
			pDC->SetTextColor(m_crGreen);
		}
		else
		{
			pDC->SetTextColor(m_crRed);
		}
	}
	
	return hbr;
}

BOOL CStockQuoteDlg::Create(UINT nIDTemplate, CStockSampleView* pParentWnd)
{
	m_pChart = pParentWnd;
	return CDialog::Create(nIDTemplate, pParentWnd);
}

void CStockQuoteDlg::OnSelendOkComboStyle() 
{
	UpdateData();
	
    if (m_pChart)
    {
        m_pChart->UpdateHistory(m_strTicker, (m_nStyle == 0));
    }
}

void CStockQuoteDlg::OnChkThickLines() 
{
	UpdateData();
	
    if (m_pChart)
    {
        m_pChart->SetThickStyle(m_bThickLines);
    }
}
