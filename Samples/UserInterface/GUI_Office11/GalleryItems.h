// GalleryItems.h
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

#if !defined(AFX_GALLERYITEMS_H__04E890F7_BFE8_48DF_9E4A_AE16DBA3BD6A__INCLUDED_)
#define AFX_GALLERYITEMS_H__04E890F7_BFE8_48DF_9E4A_AE16DBA3BD6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGalleryItemStyleSet : public CXTPControlGalleryItem
{
public:
	CGalleryItemStyleSet(int nId, LPCTSTR lpszCaption);
	virtual ~CGalleryItemStyleSet();

	virtual void Draw(CDC* pDC, CXTPControlGallery* pGallery, CRect rcItem, BOOL bEnabled, BOOL bSelected, BOOL bPressed, BOOL bChecked);
};

class CGalleryItemThemeColors : public CXTPControlGalleryItem
{
public:
	CGalleryItemThemeColors(int nId, LPCTSTR lpszCaption);

	virtual void Draw(CDC* pDC, CXTPControlGallery* pGallery, CRect rcItem, BOOL bEnabled, BOOL bSelected, BOOL bPressed, BOOL bChecked);
};

class CGalleryItemThemeFonts : public CXTPControlGalleryItem
{
public:
	CGalleryItemThemeFonts(int nId, LPCTSTR lpszCaption);

	virtual void Draw(CDC* pDC, CXTPControlGallery* pGallery, CRect rcItem, BOOL bEnabled, BOOL bSelected, BOOL bPressed, BOOL bChecked);
};

class CGalleryItemTable : public CXTPControlGalleryItem
{
public:
	CGalleryItemTable(int nId);

	virtual void Draw(CDC* pDC, CXTPControlGallery* pGallery, CRect rcItem, BOOL bEnabled, BOOL bSelected, BOOL bPressed, BOOL bChecked);
};

class CGalleryItemTableLabel : public CXTPControlGalleryItem
{
public:
	CGalleryItemTableLabel();

	virtual void Draw(CDC* pDC, CXTPControlGallery* pGallery, CRect rcItem, BOOL bEnabled, BOOL bSelected, BOOL bPressed, BOOL bChecked);
};

class CGalleryItemFontColor : public CXTPControlGalleryItem
{
public:
	CGalleryItemFontColor(COLORREF clr, LPCTSTR lpszCaption, BOOL bTopMargin = TRUE, BOOL bBotttomMargin = TRUE);
	CGalleryItemFontColor(COLORREF clr, int nToolTip);

public:
	static void AddStandardColors(CXTPControlGalleryItems* pItems);
	static void AddStandardBackColors(CXTPControlGalleryItems* pItems);
	static void AddThemeColors(CXTPControlGalleryItems* pItems, int nTheme);

	virtual void Draw(CDC* pDC, CXTPControlGallery* pGallery, CRect rcItem, BOOL bEnabled, BOOL bSelected, BOOL bPressed, BOOL bChecked);

protected:
	BOOL m_bTopMargin;
	BOOL m_bBottomMargin;

};

class CGalleryItemFontFace : public CXTPControlGalleryItem
{
public:
	CGalleryItemFontFace(LPCTSTR lpszCaption);

public:
	static void AddFontItems(CXTPControlGalleryItems* pItems);

public:
	virtual void Draw(CDC* pDC, CXTPControlGallery* pGallery, CRect rcItem, BOOL bEnabled, BOOL bSelected, BOOL bPressed, BOOL bChecked);
};




class CGalleryItemUndo : public CXTPControlGalleryItem
{
public:
	CGalleryItemUndo(LPCTSTR lpszCaption);

public:
	virtual void Draw(CDC* pDC, CXTPControlGallery* pGallery, CRect rcItem, BOOL bEnabled, BOOL bSelected, BOOL bPressed, BOOL bChecked);
};


class CControlGalleryUndo : public CXTPControlGallery
{
	DECLARE_XTP_CONTROL(CControlGalleryUndo);

public:
	CControlGalleryUndo();

	CXTPControlStatic* FindInfoControl();
	void OnSelectedItemChanged();
};


#endif // !defined(AFX_GALLERYITEMS_H__04E890F7_BFE8_48DF_9E4A_AE16DBA3BD6A__INCLUDED_)
