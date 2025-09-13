// 3dParametersDlg.h
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

#if !defined(AFX_3DPARAMETERSDLG_H__2F232CF4_BD1C_427D_8217_910BB61799AF__INCLUDED_)
#define AFX_3DPARAMETERSDLG_H__2F232CF4_BD1C_427D_8217_910BB61799AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComponentSliderCtrl;

/////////////////////////////////////////////////////////////////////////////
// C3dParametersDlg dialog

class C3dParametersDlg : public CTabCtrlDialog
{
// Construction
public:
	C3dParametersDlg(CXTPChartControl& wndChartControl, CWnd* pParent = NULL);   // standard constructor
	~C3dParametersDlg();

// Dialog Data
	//{{AFX_DATA(C3dParametersDlg)
	enum { IDD = IDD_VIEW_3D_PARAMETERS_TAB };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	void SetRotation(const CXTPChart3dRotation& rotation);
	void SetLightPosition(const CXTPPoint3f& position);
	void SetLightModelAmbientColor(const CXTPChartColor& color);
	void SetLightAmbientColor(const CXTPChartColor& color);
	void SetLightDiffuseColor(const CXTPChartColor& color);
	void SetLightSpecularColor(const CXTPChartColor& color);
	void SetMaterialEmissionColor(const CXTPChartColor& color);
	void SetMaterialDiffuseColor(const CXTPChartColor& color);
	void SetMaterialSpecularColor(const CXTPChartColor& color);
	void SetMaterialShininess(float fShininess);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C3dParametersDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

	void OnRotationChanged(const float* pfYaw, const float* pfPitch, const float* pfRoll);
	void OnLightPositionChanged(const float* pX, const float* pY, const float* pZ);
	void OnLightModelAmbientColorChanged(const int* pR, const int* pG, const int* pB);
	void OnLightAmbientColorChanged(const int* pR, const int* pG, const int* pB);
	void OnLightDiffuseColorChanged(const int* pR, const int* pG, const int* pB);
	void OnLightSpecularColorChanged(const int* pR, const int* pG, const int* pB);
	void OnMaterialEmissionColorChanged(const int* pR, const int* pG, const int* pB);
	void OnMaterialDiffuseColorChanged(const int* pR, const int* pG, const int* pB);
	void OnMaterialSpecularColorChanged(const int* pR, const int* pG, const int* pB);
	void OnMaterialShininessChanged(float fShininess);

	struct ComponentSliderCtrlCallback : IComponentSliderCtrlCallback
	{
		C3dParametersDlg* pThis;

		virtual void OnBeforeValueChanged(int nItem);
		virtual void OnAfterValueChanged(int nItem);
	};

	struct XRotationCallback : ComponentSliderCtrlCallback {
		virtual void OnValueChanged(int nItem, int nValue);
	} m_xRotationCallback;

	struct XLightPositionCallback : ComponentSliderCtrlCallback {
		virtual void OnValueChanged(int nItem, float fValue);
	} m_xLightPositionCallback;

	struct XLightModelAmbientColor : ComponentSliderCtrlCallback {
		virtual void OnValueChanged(int nItem, int nValue);
	} m_xLightModelAmbientColor;

	struct XLightAmbientColor : ComponentSliderCtrlCallback {
		virtual void OnValueChanged(int nItem, int nValue);
	} m_xLightAmbientColor;

	struct XLightDiffuseColor : ComponentSliderCtrlCallback {
		virtual void OnValueChanged(int nItem, int nValue);
	} m_xLightDiffuseColor;

	struct XLightSpecularColor : ComponentSliderCtrlCallback {
		virtual void OnValueChanged(int nItem, int nValue);
	} m_xLightSpecularColor;

	struct XMaterialEmissionColor : ComponentSliderCtrlCallback {
		virtual void OnValueChanged(int nItem, int nValue);
	} m_xMaterialEmissionColor;

	struct XMaterialDiffuseColor : ComponentSliderCtrlCallback {
		virtual void OnValueChanged(int nItem, int nValue);
	} m_xMaterialDiffuseColor;

	struct XMaterialSpecularColor : ComponentSliderCtrlCallback {
		virtual void OnValueChanged(int nItem, int nValue);
	} m_xMaterialSpecularColor;

	struct XMaterialShininess : ComponentSliderCtrlCallback {
		virtual void OnValueChanged(int nItem, float fValue);
	} m_xMaterialShininess;

	friend struct ComponentSliderCtrlCallback;
	friend struct XRotationCallback;
	friend struct XLightPositionCallback;
	friend struct XLightModelAmbientColor;
	friend struct XLightAmbientColor;
	friend struct XLightDiffuseColor;
	friend struct XLightSpecularColor;
	friend struct XMaterialEmissionColor;
	friend struct XMaterialDiffuseColor;
	friend struct XMaterialSpecularColor;
	friend struct XMaterialShininess;

	// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(C3dParametersDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CXTPChartControl& m_wndChartControl;

	CComponentSliderCtrl* m_pwndRotation;
	CComponentSliderCtrl* m_pwndLightPosition;

	CComponentSliderCtrl* m_pwndLightModelAmbientColor;
	CComponentSliderCtrl* m_pwndLightAmbientColor;
	CComponentSliderCtrl* m_pwndLightDiffuseColor;
	CComponentSliderCtrl* m_pwndLightSpecularColor;

	CComponentSliderCtrl* m_pwndMaterialEmissionColor;
	CComponentSliderCtrl* m_pwndMaterialDiffuseColor;
	CComponentSliderCtrl* m_pwndMaterialSpecularColor;
	CComponentSliderCtrl* m_pwndMaterialShininess;
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_3DPARAMETERSDLG_H__2F232CF4_BD1C_427D_8217_910BB61799AF__INCLUDED_)
