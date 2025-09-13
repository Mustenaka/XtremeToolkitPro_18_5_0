// MainFrm.h
//

#ifndef _XTP_INCLUDE_COMMANDBARS
#define CXTPFrameWnd CFrameWnd
#define CXTPStatusBar   CStatusBar
#endif

class CMainFrame : public CXTPFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	virtual ~CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	//{{AFX_VIRTUAL(CMainFrame)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CXTPStatusBar  m_wndStatusBar;
	CToolBar       m_wndToolBar;

protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnThemeNone();
	afx_msg void OnThemeOffice2007();
	afx_msg void OnThemeOffice2010();
	afx_msg void OnThemeVista();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

	void OnThemeChanged(int nSchema);
	static CString GetStylesPath();

	int m_nTheme;
};

/////////////////////////////////////////////////////////////////////////////
