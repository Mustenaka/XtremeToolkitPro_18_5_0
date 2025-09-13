// ExplorerBar.h
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

#pragma once

#include "CWebBrowser2.h"

class CExplorerBar : public CWnd
{
public:
	CExplorerBar(void);
	~CExplorerBar(void);

	CWebBrowserCtrl* m_pSearch;
	
	void OnNewWindow2(LPDISPATCH* ppDisp, BOOL* bCancel);
	int OnViewSearch();

	BOOL PreTranslateMessage(MSG* pMsg);
public:
//	afx_msg void OnSize(UINT nType, int cx, int cy);

public:

BEGIN_INTERFACE_PART(DocHostUIHandler, IDocHostUIHandler)
	 STDMETHOD(GetOverrideKeyPath)(
			/* [out] */ LPOLESTR __RPC_FAR *pchKey,
            /* [in] */ DWORD dw);
	STDMETHOD(ShowContextMenu)(/* [in] */ DWORD dwID,
            /* [in] */ POINT __RPC_FAR *ppt,
            /* [in] */ IUnknown __RPC_FAR *pcmdtReserved,
            /* [in] */ IDispatch __RPC_FAR *pdispReserved);
	STDMETHOD(GetHostInfo)( 
            /* [out][in] */ DOCHOSTUIINFO __RPC_FAR *pInfo);
	STDMETHOD(ShowUI)( 
            /* [in] */ DWORD dwID,
            /* [in] */ IOleInPlaceActiveObject __RPC_FAR *pActiveObject,
            /* [in] */ IOleCommandTarget __RPC_FAR *pCommandTarget,
            /* [in] */ IOleInPlaceFrame __RPC_FAR *pFrame,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pDoc);
	STDMETHOD(HideUI)(void);
	STDMETHOD(UpdateUI)(void);
	STDMETHOD(EnableModeless)(/* [in] */ BOOL fEnable);
	STDMETHOD(OnDocWindowActivate)(/* [in] */ BOOL fEnable);
	STDMETHOD(OnFrameWindowActivate)(/* [in] */ BOOL fEnable);
	STDMETHOD(ResizeBorder)( 
            /* [in] */ LPCRECT prcBorder,
            /* [in] */ IOleInPlaceUIWindow __RPC_FAR *pUIWindow,
            /* [in] */ BOOL fRameWindow);
	STDMETHOD(TranslateAccelerator)( 
            /* [in] */ LPMSG lpMsg,
            /* [in] */ const GUID __RPC_FAR *pguidCmdGroup,
            /* [in] */ DWORD nCmdID);
	STDMETHOD(GetOptionKeyPath)( 
            /* [out] */ LPOLESTR __RPC_FAR *pchKey,
            /* [in] */ DWORD dw);
	STDMETHOD(GetDropTarget)(
            /* [in] */ IDropTarget __RPC_FAR *pDropTarget,
            /* [out] */ IDropTarget __RPC_FAR *__RPC_FAR *ppDropTarget);
        STDMETHOD(GetExternal)( 
            /* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDispatch);
        STDMETHOD(TranslateUrl)( 
            /* [in] */ DWORD dwTranslate,
            /* [in] */ OLECHAR __RPC_FAR *pchURLIn,
            /* [out] */ OLECHAR __RPC_FAR *__RPC_FAR *ppchURLOut);
        STDMETHOD(FilterDataObject)( 
            /* [in] */ IDataObject __RPC_FAR *pDO,
            /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDORet);
END_INTERFACE_PART(DocHostUIHandler) 	

BEGIN_INTERFACE_PART(OleClientSite, IOleClientSite)
	STDMETHOD(SaveObject)( void) { return E_NOTIMPL;}
		
        
        STDMETHOD (GetMoniker)( 
            /* [in] */ DWORD /*dwAssign*/,
            /* [in] */ DWORD /*dwWhichMoniker*/,
            /* [out] */ IMoniker ** /*ppmk*/) { return E_NOTIMPL;}
        
        STDMETHOD(GetContainer)( 
            /* [out] */ IOleContainer** /*ppContainer*/) { return E_NOTIMPL;}
        
        STDMETHOD(ShowObject)( void) { return E_NOTIMPL;}
        
        STDMETHOD(OnShowWindow)( 
            /* [in] */ BOOL /*fShow*/) { return E_NOTIMPL;}
        
        STDMETHOD(RequestNewObjectLayout)( void) { return E_NOTIMPL;}        

END_INTERFACE_PART(OleClientSite) 	

DECLARE_INTERFACE_MAP()


//	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()

	DECLARE_MESSAGE_MAP()
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
