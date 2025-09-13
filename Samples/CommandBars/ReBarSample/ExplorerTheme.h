// ExplorerTheme.h
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

#if !defined(AFX_EXPLORERTHEME_H__65131115_96C7_4906_BE7F_A489E4FBCAE5__INCLUDED_)
#define AFX_EXPLORERTHEME_H__65131115_96C7_4906_BE7F_A489E4FBCAE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CExplorerTabPaintManager : public CXTPTabPaintManager
{
public:
	CExplorerTabPaintManager();

	void DrawNavigateButton(CDC* pDC, CXTPTabManagerNavigateButton* pButton, CRect& rc);
	
public:
	class CExplorerTabAppearance : public CXTPTabPaintManager::CAppearanceSetPropertyPage
	{
	public:
		void DrawSingleButton(CDC* pDC, CXTPTabManagerItem* pItem);
		CXTPResourceImages m_images;
	};
};

#endif // !defined(AFX_EXPLORERTHEME_H__65131115_96C7_4906_BE7F_A489E4FBCAE5__INCLUDED_)
