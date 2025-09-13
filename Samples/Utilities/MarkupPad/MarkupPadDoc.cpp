// MarkupPadDoc.cpp
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
#include "MarkupPad.h"

#include "MarkupPadDoc.h"
#include "MarkupPadView.h"
#include "MarkupPadEdit.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadDoc

IMPLEMENT_DYNCREATE(CMarkupPadDoc, CDocument)

BEGIN_MESSAGE_MAP(CMarkupPadDoc, CDocument)
	//{{AFX_MSG_MAP(CMarkupPadDoc)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadDoc construction/destruction

CMarkupPadDoc::CMarkupPadDoc()
	: m_bProcessingInstructionsFound(FALSE)
{
}

CMarkupPadDoc::~CMarkupPadDoc()
{
}

void CMarkupPadDoc::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle(lpszTitle);

}

BOOL CMarkupPadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	POSITION pos = GetFirstViewPosition();
	while (pos)
	{
		CView* pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CEditView)))
		{
			pView->SetWindowText(NULL);
		}
		else if (pView->IsKindOf(RUNTIME_CLASS(CMarkupPadView)))
		{
			MARKUP_RELEASE(((CMarkupPadView*)pView)->m_pUIElement);
		}
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMarkupPadDoc serialization

void WriteByte(CArchive& ar, int nByte)
{
	BYTE n = (BYTE)nByte;
	ar.Write(&n, 1);
}

CEditView* CMarkupPadDoc::GetView() const
{
	// find the first view - if there are no views
	// we must return NULL

	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
		return NULL;

	// find the first view that is a CRichEditView

	CView* pView;
	while (pos != NULL)
	{
		pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CEditView)))
			return (CEditView*) pView;
	}

	// can't find one--return NULL

	return NULL;
}

CMarkupPadView* CMarkupPadDoc::GetMarkupView() const
{
	POSITION pos = GetFirstViewPosition();
	if (pos == NULL)
		return NULL;

	CView* pView;
	while (pos != NULL)
	{
		pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CMarkupPadView)))
			return (CMarkupPadView*) pView;
	}

	return NULL;
}

void CMarkupPadDoc::Serialize(CArchive& ar)
{
	//CDocument::m_bRTF = FALSE;
	//CDocument::Serialize(ar);

	CEditView* pView = GetView();
	if (pView != NULL)
	{
		if (ar.IsStoring())
		{
			// Write UTF-8 BOM
			WriteByte(ar, 0xef);
			WriteByte(ar, 0xbb);
			WriteByte(ar, 0xbf);

			// Write processing instruction
			if (m_bProcessingInstructionsFound)
			{
				static const char XmlHeader[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n";
				for (int i = 0; i < _countof(XmlHeader) - 1; ++i)
				{
					WriteByte(ar, XmlHeader[i]);
				}
			}

			// Write content
			LPWSTR lpBuffer = ((CMarkupPadEdit*)pView)->GetUnicodeText();
			
			if (lpBuffer)
			{
				int nLen = (int)wcslen(lpBuffer);
				for (int i = 0; i < nLen; i++)
				{
					int c = (int)lpBuffer[i];

					if (c == '\r' && lpBuffer[i + 1] != '\n')
					{
						WriteByte(ar, '\r');
						WriteByte(ar, '\n');
					}
					else if (c < (1 << 7))
					{
						WriteByte(ar, c);
					} 
					else if (c < (1 << 11))
					{
						WriteByte(ar, (c >> 6) | 0xc0);
						WriteByte(ar, (c & 0x3f) | 0x80);
					} 
					else if (c < (1 << 16))
					{
						WriteByte(ar, (c >> 12) | 0xe0);
						WriteByte(ar, ((c >> 6) & 0x3f) | 0x80);
						WriteByte(ar, (c & 0x3f) | 0x80);
					} 
					else if (c < (1 << 21))
					{
						WriteByte(ar, (c >> 18) | 0xe0);
						WriteByte(ar, ((c >> 12) & 0x3f) | 0x80);
						WriteByte(ar, ((c >> 6) & 0x3f) | 0x80);
						WriteByte(ar, (c & 0x3f) | 0x80);
					}
				}

				delete[] lpBuffer;
			}
		}
		else
		{
			CMemFile mf;

			char b;
			WCHAR ch;
			INT_PTR pos = 0;
			BOOL bBomComplete = FALSE;
			CArray<BYTE, const BYTE&> bom;
			while (ar.Read(&b, 1) == 1)
			{
				// Store and strip BOM
				if (!bBomComplete && IsValidBomByte(b, pos, 
					0 < bom.GetSize() ? bom.GetData() : NULL, bBomComplete))
				{
					bom.Add(b);
				}
				else
				{
					// Convert characters to UTF-16

					if (0 == (b & '\x80'))
					{
						ch = b;
					}
					else if ('\xF0' == (b & '\xF0')) // 1111 - error, more than 16-bit char
					{
						// do nothign, use as-is
					}
					else if ('\xE0' == (b & '\xF0')) // 1110xxxx 10xxxxxx 10xxxxxx
					{
						BYTE b2;
						BYTE b3;
						ar.Read(&b2, 1);
						ar.Read(&b3, 1);

						ch = (WCHAR)((WCHAR(b & '\x0F') << 12) | (WCHAR(b2 & '\x3F') << 6) | WCHAR(b3 & '\x3F'));
					}
					else if ('\xC0' == (b & '\xE0')) // 110xxxxx 10xxxxxx 
					{
						BYTE b2;
						ar.Read(&b2, 1);

						ch = (WCHAR)((WCHAR(b & '\x1F') << 6) | (b2 & '\x3F'));
					}

					mf.Write(&ch, sizeof(WCHAR));
				}

				++pos;
			}

			ch = L'\0';
			mf.Write(&ch, sizeof(WCHAR));

			mf.SeekToBegin();

			CArray<BYTE, const BYTE&> buffer;
			buffer.SetSize(static_cast<INT_PTR>(mf.GetLength()));
			mf.Read(buffer.GetData(), static_cast<UINT>(buffer.GetSize()));

			LPCWSTR lpXml = SkipXmlProcessingInstructions(reinterpret_cast<LPCWSTR>(buffer.GetData()));
			if (NULL != lpXml)
			{
				m_bProcessingInstructionsFound = reinterpret_cast<LPCWSTR>(buffer.GetData()) < lpXml;

				BLOB dataBlob;
				dataBlob.cbSize = static_cast<LONG>((wcslen(lpXml) + 1) * sizeof(WCHAR));
				dataBlob.pBlobData = reinterpret_cast<LPBYTE>(const_cast<LPWSTR>(lpXml));

				EDITSTREAM es = { 0, 0, &CMarkupPadDoc::RichTextCtrlCallbackIn };
				es.dwCookie = reinterpret_cast<DWORD_PTR>(&dataBlob);

				pView->SendMessage(EM_STREAMIN, SF_TEXT | SF_UNICODE, reinterpret_cast<LPARAM>(&es));
			}
		}
	}
}

BOOL CMarkupPadDoc::IsValidBomByte(BYTE b, INT_PTR pos, BYTE* pBom, BOOL& bBomComplete)
{
	ASSERT(0 < pos ? NULL != pBom : TRUE);

	// EF BB BF - UTF-8
	// FE FF - UTF-16 (BE)
	// FF FE - UTF-16 (LE)
	// 00 00 FE FF - UTF-32 (BE)
	// FF FE 00 00 - UTF-32 (LE)
	// 2B 2F 76 38 - UTF-7
	// 2B 2F 76 39 - 
	// 2B 2F 76 2B - 
	// 2B 2F 76 2F - 
	// 2B 2F 76 38 2D - 
	// F7 64 4C - UTF-1
	// DD 73 66 73 - UTF-EBCDIC
	// 0E FE FF - SCSU
	// FB EE 28 - BOCU-1
	// 84 31 95 33 - GB-18030

	BOOL bValid = FALSE;

	switch (pos)
	{
	case 0:
		bValid = (0xef == b || 0xfe == b || 0xff == b || 0x00 == b
			|| 0x2b == b || 0xf7 == b || 0xdd == b || 0x0e == b
			|| 0xfb == b || 0x84 == b);
		break;
	case 1:
		bValid = (0xbb == b && 0xef == pBom[0])
			|| (0xff == b && 0xfe == pBom[0])
			|| (0xfe == b && 0xff == pBom[0])
			|| (0x00 == b && 0x00 == pBom[0])
			|| (0x2f == b && 0x2b == pBom[0])
			|| (0x64 == b && 0xf7 == pBom[0])
			|| (0x73 == b && 0xdd == pBom[0])
			|| (0xfe == b && 0x0e == pBom[0])
			|| (0xee == b && 0xfb == pBom[0])
			|| (0x31 == b && 0x84 == pBom[0]);
		break;
	case 2:
		bValid = (0xbf == b && 0xbb == pBom[1] && 0xef == pBom[0])
			|| (0xfe == b && 0x00 == pBom[1] && 0x00 == pBom[0])
			|| (0x00 == b && 0xfe == pBom[1] && 0xff == pBom[0])
			|| (0x76 == b && 0x2f == pBom[1] && 0x2b == pBom[0])
			|| (0x4C == b && 0x64 == pBom[1] && 0xf7 == pBom[0])
			|| (0x66 == b && 0x73 == pBom[1] && 0xdd == pBom[0])
			|| (0xFF == b && 0xfe == pBom[1] && 0x0e == pBom[0])
			|| (0x28 == b && 0xee == pBom[1] && 0xfb == pBom[0])
			|| (0x95 == b && 0x31 == pBom[1] && 0x84 == pBom[0]);
		break;
	case 3:
		bValid = (0xff == b && 0xfe == pBom[2] && 0x00 == pBom[1] && 0x00 == pBom[0])
			|| (0x00 == b && 0x00 == pBom[2] && 0xfe == pBom[1] && 0xff == pBom[0])
			|| (0x38 == b && 0x76 == pBom[2] && 0x2f == pBom[1] && 0x2b == pBom[0])
			|| (0x39 == b && 0x76 == pBom[2] && 0x2f == pBom[1] && 0x2b == pBom[0])
			|| (0x2B == b && 0x76 == pBom[2] && 0x2f == pBom[1] && 0x2b == pBom[0])
			|| (0x2F == b && 0x76 == pBom[2] && 0x2f == pBom[1] && 0x2b == pBom[0])
			|| (0x73 == b && 0x66 == pBom[2] && 0x73 == pBom[1] && 0xdd == pBom[0])
			|| (0x33 == b && 0x95 == pBom[2] && 0x31 == pBom[1] && 0x84 == pBom[0]);
		break;
	case 4:
		bValid = (0x2d == b && 0x38 == pBom[3] && 0x76 == pBom[2] && 0x2f == pBom[1] && 0x2b == pBom[0]);
		break;
	case 5:
		// invalid
		break;
	default:
		ASSERT(!"BOM overflow");
	}

	if (!bValid)
	{
		bBomComplete = TRUE;
	}

	return bValid;
}

LPCWSTR CMarkupPadDoc::SkipXmlProcessingInstructions(LPCWSTR lpXml)
{
	ASSERT(NULL != lpXml);

	LPCWSTR lp = lpXml;
	while ((lp = wcsstr(lp, L"<?")) != NULL)
	{
		lpXml = lp;
		lp = wcsstr(lp + _countof(L"<?"), L"?>");
		if (NULL != lp)
		{
			lp += _countof(L"?>");
			lpXml = wcschr(lp, L'<');
		}
		else
		{
			lpXml += _countof(L"?>");
			break;
		}
	}

	return lpXml;
}

DWORD CALLBACK CMarkupPadDoc::RichTextCtrlCallbackIn(DWORD_PTR dwCookie, LPBYTE pbBuff, LONG cb, LONG* pcb)
{
	LPBLOB pBlob = reinterpret_cast<LPBLOB>(dwCookie);
	ASSERT(NULL != pBlob);

	*pcb = __min(static_cast<ULONG>(cb), pBlob->cbSize);
	memcpy(pbBuff, pBlob->pBlobData, *pcb);

	pBlob->cbSize -= *pcb;
	pBlob->pBlobData += *pcb;

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMarkupPadDoc diagnostics

#ifdef _DEBUG
void CMarkupPadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMarkupPadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMarkupPadDoc commands
