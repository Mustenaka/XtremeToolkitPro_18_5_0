// BatchSearch.h
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

#if !defined(AFX_BATCHSEARCH_H__1A4C7EB0_C93E_4319_AF3E_C64729AC4E66__INCLUDED_)
#define AFX_BATCHSEARCH_H__1A4C7EB0_C93E_4319_AF3E_C64729AC4E66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSearchOptions;

BOOL CheckMatchWholeWords(const CString& str, int nIndex, int nLength);


class CBatchSearch  
{
	struct CMatch
	{
		CString strFindString;
		CString strReplaceString;
	};

	struct CNode
	{
		CNode();		
		~CNode();

		CMap<TCHAR, TCHAR, CNode*, CNode*> nextMap;
		int nMatch;
		CNode* parentNode;
		TCHAR pch;
		CNode* linkNode;
	};

public:
	CBatchSearch();
	virtual ~CBatchSearch();

	BOOL LoadMatches(CString strBatchFile, CSearchOptions* pOptions);
	void BuildTree();

	CArray<CMatch, CMatch&> m_arrMatches;

	int FindNext(const CString& strBuffer, int nIndex, CSearchOptions* pOptions, CString& strFindString, CString& strReplaceString);
	CNode* GetLink(CNode* v);
	CNode* GoNextChar(CNode* v, TCHAR c);

protected:
	CNode* m_pRootNode;
};

#endif // !defined(AFX_BATCHSEARCH_H__1A4C7EB0_C93E_4319_AF3E_C64729AC4E66__INCLUDED_)
