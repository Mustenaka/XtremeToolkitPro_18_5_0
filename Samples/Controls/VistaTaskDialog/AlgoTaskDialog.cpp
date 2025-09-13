// AlgoTaskDialog.cpp
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

#include "AlgoTaskDialog.h"

///////////////// TEST CODE ///////////////////

enum
{
	Button_SendFeedback = 101,
	Button_NoThanks
};

#define MAX_DLU 371

static LPCTSTR SAMPLE_TEXT = _T("Aa Bb Cc");

CAlgoTaskDialog::CAlgoTaskDialog(void)
{
	m_strHeaderText = SAMPLE_TEXT;

	m_sizeClient.SetSizeEmpty();
	m_sizeDlu.SetSizeEmpty();

	SetWindowTitle(_T("Task Dialog Sample"));
	SetMainInstruction(SAMPLE_TEXT);
	SetFooter(SAMPLE_TEXT);
	//SetFooterIcon(TD_INFORMATION_ICON);
	//SetMainIcon(TD_WARNING_ICON);

	AddButton(_T("Increase Text Size\nClick here to dynamically increasing text size."), Button_SendFeedback);

	m_config.dwFlags |= TDF_ALLOW_DIALOG_CANCELLATION | TDF_USE_COMMAND_LINKS;
	m_config.dwCommonButtons = TDCBF_OK_BUTTON;
}

CAlgoTaskDialog::~CAlgoTaskDialog(void)
{
}

void CAlgoTaskDialog::UpdateFooterText()
{
	CXTPClientRect rcClient(CWnd::FromHandle(m_hWnd));
	m_sizeClient = rcClient.Size();

	CWindowDC dc(NULL);
	CXTPFontDC fontDC(&dc, &m_xtpFontLarge);

	CSize sizeExtent = dc.GetTextExtent(m_strHeaderText);
	CSize sizeExtentUnits = XTPPix2Dlu(sizeExtent.cx, sizeExtent.cy);

	CSize sizeClient = m_sizeClient;
	CSize sizeClientUnits = XTPPix2Dlu(sizeClient.cx, sizeClient.cy);

	m_strFooterText.Format(_T("Extent cx: %d (%d), cy: %d (%d)\r\nClient cx: %d (%d), cy: %d (%d)"),
		sizeExtent.cx, sizeExtentUnits.cx, sizeExtent.cy, sizeExtentUnits.cy,
		sizeClient.cx, sizeClientUnits.cx, sizeClient.cy, sizeClientUnits.cy);

	SetFooter(m_strFooterText);
}

void CAlgoTaskDialog::OnDialogConstructed()
{
	UpdateFooterText();
}

BOOL CAlgoTaskDialog::CopyToClipboard(const CString& strText)
{
	if (::OpenClipboard(m_hWnd))
	{
		::EmptyClipboard();

		HGLOBAL hGlobalBuff = ::GlobalAlloc(GMEM_MOVEABLE, strText.GetLength() + 1);

		CHAR* szBuffer = (CHAR*)::GlobalLock(hGlobalBuff);

		WCSTOMBS_S(szBuffer, strText, strText.GetLength() + 1);
		::GlobalUnlock(hGlobalBuff);

		if (::SetClipboardData(CF_TEXT, hGlobalBuff) == NULL)
			return FALSE;

		::CloseClipboard();
		return TRUE;
	}

	return FALSE;
}

void CAlgoTaskDialog::OnButtonClicked(int nButtonID, BOOL& bCloseDialog)
{
	switch (nButtonID)
	{
	case Button_SendFeedback:
		{
			bCloseDialog = FALSE;

			CWnd* pTaskDlg = CWnd::FromHandle(m_hWnd);

			CXTPWindowRect rcWindow(pTaskDlg);
			USES_CONVERSION;
			
			TCHAR chMin   = 'A';
			TCHAR chMax   = 'Z';
			TCHAR chSpace = ' ';

			TCHAR ch;
			int i;

			int cxMax = 550;

			m_avgCharPix = ::GetDialogBaseUnits();

			CString strBuffer;
			strBuffer.Format(_T("Average character width: %d, height: %d\r\n"), m_avgCharPix.cx, m_avgCharPix.cy);
			strBuffer += m_strFooterText + _T("\r\n");

			CXTPClientRect rcClient(CWnd::FromHandle(m_hWnd));
			int cxWidth = rcClient.Width();

			for (ch = chMin, i = 0; i < 500; i += 100, ++ch)
			{
				if (ch > chMax)
					ch = chMin;

				TCHAR chUpper = ch;
				TCHAR chLower = ch + chSpace;

				CString strTemp;
				strTemp.Format(_T("%c%c%c"), chUpper, chLower, chSpace);

				m_strHeaderText += strTemp;
				SetMainInstruction(m_strHeaderText);

				UpdateFooterText();

				if (m_sizeClient.cx > cxWidth)
				{
					cxWidth = m_sizeClient.cx; 
					strBuffer += m_strFooterText + _T("\r\n---------------------------------------------\r\n");
				}

				if (cxMax <= cxWidth)
					break;

				Sleep(100);
			}

			CopyToClipboard(strBuffer);

			break;
		}
	case IDOK:
		{
			bCloseDialog = TRUE;
			break;
		}
	}
}
