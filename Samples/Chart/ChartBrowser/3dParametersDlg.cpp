// 3dParametersDlg.cpp
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
#include "chartbrowser.h"
#include "BaseView.h"
#include "ComponentSliderCtrl.h"
#include "3dParametersDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C3dParametersDlg dialog


C3dParametersDlg::C3dParametersDlg(
	CXTPChartControl& wndChartControl,
	CWnd* pParent /*=NULL*/)
	: CTabCtrlDialog(C3dParametersDlg::IDD, pParent)
	, m_wndChartControl(wndChartControl)
	, m_pwndRotation(NULL)
	, m_pwndLightPosition(NULL)
	, m_pwndLightModelAmbientColor(NULL)
	, m_pwndLightAmbientColor(NULL)
	, m_pwndLightDiffuseColor(NULL)
	, m_pwndLightSpecularColor(NULL)
	, m_pwndMaterialEmissionColor(NULL)
	, m_pwndMaterialDiffuseColor(NULL)
	, m_pwndMaterialSpecularColor(NULL)
	, m_pwndMaterialShininess(NULL)
{
	//{{AFX_DATA_INIT(C3dParametersDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_xRotationCallback.pThis = this;
	m_xLightPositionCallback.pThis = this;
	m_xLightModelAmbientColor.pThis = this;
	m_xLightAmbientColor.pThis = this;
	m_xLightDiffuseColor.pThis = this;
	m_xLightSpecularColor.pThis = this;
	m_xMaterialEmissionColor.pThis = this;
	m_xMaterialDiffuseColor.pThis = this;
	m_xMaterialSpecularColor.pThis = this;
	m_xMaterialShininess.pThis = this;
}

C3dParametersDlg::~C3dParametersDlg()
{
	SAFE_DELETE(m_pwndRotation);
	SAFE_DELETE(m_pwndLightPosition);
	SAFE_DELETE(m_pwndLightModelAmbientColor);
	SAFE_DELETE(m_pwndLightAmbientColor);
	SAFE_DELETE(m_pwndLightDiffuseColor);
	SAFE_DELETE(m_pwndLightSpecularColor);
	SAFE_DELETE(m_pwndMaterialEmissionColor);
	SAFE_DELETE(m_pwndMaterialDiffuseColor);
	SAFE_DELETE(m_pwndMaterialSpecularColor);
	SAFE_DELETE(m_pwndMaterialShininess);
}

void C3dParametersDlg::SetRotation(const CXTPChart3dRotation& rotation)
{
	ASSERT(NULL != m_pwndRotation && ::IsWindow(*m_pwndRotation));
	m_pwndRotation->SetValue(0, static_cast<int>(rotation.m_dYaw));
	m_pwndRotation->SetValue(1, static_cast<int>(rotation.m_dPitch));
	m_pwndRotation->SetValue(2, static_cast<int>(rotation.m_dRoll));
}

void C3dParametersDlg::SetLightPosition(const CXTPPoint3f& position)
{
	ASSERT(NULL != m_pwndLightPosition && ::IsWindow(*m_pwndLightPosition));
	m_pwndLightPosition->SetValue(0, position.X);
	m_pwndLightPosition->SetValue(1, position.Y);
	m_pwndLightPosition->SetValue(2, position.Z);
}

void C3dParametersDlg::SetLightModelAmbientColor(const CXTPChartColor& color)
{
	ASSERT(NULL != m_pwndLightModelAmbientColor && ::IsWindow(*m_pwndLightModelAmbientColor));
	m_pwndLightModelAmbientColor->SetValue(0, color.GetR());
	m_pwndLightModelAmbientColor->SetValue(1, color.GetG());
	m_pwndLightModelAmbientColor->SetValue(2, color.GetB());
}

void C3dParametersDlg::SetLightAmbientColor(const CXTPChartColor& color)
{
	ASSERT(NULL != m_pwndLightAmbientColor && ::IsWindow(*m_pwndLightAmbientColor));
	m_pwndLightAmbientColor->SetValue(0, color.GetR());
	m_pwndLightAmbientColor->SetValue(1, color.GetG());
	m_pwndLightAmbientColor->SetValue(2, color.GetB());
}

void C3dParametersDlg::SetLightDiffuseColor(const CXTPChartColor& color)
{
	ASSERT(NULL != m_pwndLightDiffuseColor && ::IsWindow(*m_pwndLightDiffuseColor));
	m_pwndLightDiffuseColor->SetValue(0, color.GetR());
	m_pwndLightDiffuseColor->SetValue(1, color.GetG());
	m_pwndLightDiffuseColor->SetValue(2, color.GetB());
}

void C3dParametersDlg::SetLightSpecularColor(const CXTPChartColor& color)
{
	ASSERT(NULL != m_pwndLightSpecularColor && ::IsWindow(*m_pwndLightSpecularColor));
	m_pwndLightSpecularColor->SetValue(0, color.GetR());
	m_pwndLightSpecularColor->SetValue(1, color.GetG());
	m_pwndLightSpecularColor->SetValue(2, color.GetB());
}

void C3dParametersDlg::SetMaterialEmissionColor(const CXTPChartColor& color)
{
	ASSERT(NULL != m_pwndMaterialEmissionColor && ::IsWindow(*m_pwndMaterialEmissionColor));
	m_pwndMaterialEmissionColor->SetValue(0, color.GetR());
	m_pwndMaterialEmissionColor->SetValue(1, color.GetG());
	m_pwndMaterialEmissionColor->SetValue(2, color.GetB());
}

void C3dParametersDlg::SetMaterialDiffuseColor(const CXTPChartColor& color)
{
	ASSERT(NULL != m_pwndMaterialDiffuseColor && ::IsWindow(*m_pwndMaterialDiffuseColor));
	m_pwndMaterialDiffuseColor->SetValue(0, color.GetR());
	m_pwndMaterialDiffuseColor->SetValue(1, color.GetG());
	m_pwndMaterialDiffuseColor->SetValue(2, color.GetB());
}

void C3dParametersDlg::SetMaterialSpecularColor(const CXTPChartColor& color)
{
	ASSERT(NULL != m_pwndMaterialSpecularColor && ::IsWindow(*m_pwndMaterialSpecularColor));
	m_pwndMaterialSpecularColor->SetValue(0, color.GetR());
	m_pwndMaterialSpecularColor->SetValue(1, color.GetG());
	m_pwndMaterialSpecularColor->SetValue(2, color.GetB());
}

void C3dParametersDlg::SetMaterialShininess(float fShininess)
{
	ASSERT(NULL != m_pwndMaterialShininess && ::IsWindow(*m_pwndMaterialShininess));
	m_pwndMaterialShininess->SetValue(0, fShininess);
}

void C3dParametersDlg::DoDataExchange(CDataExchange* pDX)
{
	CTabCtrlDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(C3dParametersDlg)
	//}}AFX_DATA_MAP
}

BOOL C3dParametersDlg::OnInitDialog()
{
	CTabCtrlDialog::OnInitDialog();

	const int nHorzGap = XTP_DPI_X(6);
	CRect rcInitial(XTP_DPI_X(2), XTP_DPI_Y(2), XTP_DPI_X(291), XTP_DPI_Y(28));
	CRect rcCtrl = rcInitial;

	m_pwndRotation = new CComponentSliderCtrl(m_xRotationCallback);
	if (m_pwndRotation->Create(this, rcCtrl))
	{
		m_pwndRotation->AddValue(_T("Rotation.Yaw"), 0, 360, 0);
		m_pwndRotation->AddValue(_T("Rotation.Pitch"), 0, 360, 0);
		m_pwndRotation->AddValue(_T("Rotation.Roll"), 0, 360, 0);
	}
	else
	{
		TRACE(_T("Unable to create rotation controls\n"));
	}

	rcCtrl.OffsetRect(0, rcInitial.Height());
	m_pwndLightPosition = new CComponentSliderCtrl(m_xLightPositionCallback);
	if (m_pwndLightPosition->Create(this, rcCtrl))
	{
		m_pwndLightPosition->AddValue(_T("LightPosition.X"), 0.f, 1.f, 0.f);
		m_pwndLightPosition->AddValue(_T("LightPosition.Y"), 0.f, 1.f, 0.f);
		m_pwndLightPosition->AddValue(_T("LightPosition.Z"), 0.f, 1.f, 0.f);
	}
	else
	{
		TRACE(_T("Unable to create light position controls\n"));
	}

	rcCtrl = rcInitial;
	rcCtrl.OffsetRect(rcInitial.Width() + nHorzGap, 0);
	m_pwndLightModelAmbientColor = new CComponentSliderCtrl(m_xLightModelAmbientColor);
	if (m_pwndLightModelAmbientColor->Create(this, rcCtrl))
	{
		m_pwndLightModelAmbientColor->AddValue(_T("LightModelAmbient.R"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndLightModelAmbientColor->AddValue(_T("LightModelAmbient.G"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndLightModelAmbientColor->AddValue(_T("LightModelAmbient.B"), 0, 0xff, 0, _T("0x%02X"));
	}
	else
	{
		TRACE(_T("Unable to create light model ambient color controls\n"));
	}
	
	rcCtrl.OffsetRect(0, rcInitial.Height());
	m_pwndLightAmbientColor = new CComponentSliderCtrl(m_xLightAmbientColor);
	if (m_pwndLightAmbientColor->Create(this, rcCtrl))
	{
		m_pwndLightAmbientColor->AddValue(_T("LightAmbient.R"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndLightAmbientColor->AddValue(_T("LightAmbient.G"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndLightAmbientColor->AddValue(_T("LightAmbient.B"), 0, 0xff, 0, _T("0x%02X"));
	}
	else
	{
		TRACE(_T("Unable to create light ambient color controls\n"));
	}

	rcCtrl.OffsetRect(0, rcInitial.Height());
	m_pwndLightDiffuseColor = new CComponentSliderCtrl(m_xLightDiffuseColor);
	if (m_pwndLightDiffuseColor->Create(this, rcCtrl))
	{
		m_pwndLightDiffuseColor->AddValue(_T("LightDiffuse.R"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndLightDiffuseColor->AddValue(_T("LightDiffuse.G"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndLightDiffuseColor->AddValue(_T("LightDiffuse.B"), 0, 0xff, 0, _T("0x%02X"));
	}
	else
	{
		TRACE(_T("Unable to create light diffuse color controls\n"));
	}

	rcCtrl.OffsetRect(0, rcInitial.Height());
	m_pwndLightSpecularColor = new CComponentSliderCtrl(m_xLightSpecularColor);
	if (m_pwndLightSpecularColor->Create(this, rcCtrl))
	{
		m_pwndLightSpecularColor->AddValue(_T("LightSpecular.R"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndLightSpecularColor->AddValue(_T("LightSpecular.G"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndLightSpecularColor->AddValue(_T("LightSpecular.B"), 0, 0xff, 0, _T("0x%02X"));
	}
	else
	{
		TRACE(_T("Unable to create light specular color controls\n"));
	}

	rcCtrl = rcInitial;
	rcCtrl.OffsetRect((rcInitial.Width() + nHorzGap) * 2, 0);
	m_pwndMaterialEmissionColor = new CComponentSliderCtrl(m_xMaterialEmissionColor);
	if (m_pwndMaterialEmissionColor->Create(this, rcCtrl))
	{
		m_pwndMaterialEmissionColor->AddValue(_T("MaterialEmission.R"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndMaterialEmissionColor->AddValue(_T("MaterialEmission.G"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndMaterialEmissionColor->AddValue(_T("MaterialEmission.B"), 0, 0xff, 0, _T("0x%02X"));
	}
	else
	{
		TRACE(_T("Unable to create material emission color controls\n"));
	}


	rcCtrl.OffsetRect(0, rcInitial.Height());
	m_pwndMaterialDiffuseColor = new CComponentSliderCtrl(m_xMaterialDiffuseColor);
	if (m_pwndMaterialDiffuseColor->Create(this, rcCtrl))
	{
		m_pwndMaterialDiffuseColor->AddValue(_T("MaterialDiffuse.R"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndMaterialDiffuseColor->AddValue(_T("MaterialDiffuse.G"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndMaterialDiffuseColor->AddValue(_T("MaterialDiffuse.B"), 0, 0xff, 0, _T("0x%02X"));
	}
	else
	{
		TRACE(_T("Unable to create material diffuse color controls\n"));
	}

	rcCtrl.OffsetRect(0, rcInitial.Height());
	m_pwndMaterialSpecularColor = new CComponentSliderCtrl(m_xMaterialSpecularColor);
	if (m_pwndMaterialSpecularColor->Create(this, rcCtrl))
	{
		m_pwndMaterialSpecularColor->AddValue(_T("MaterialSpecular.R"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndMaterialSpecularColor->AddValue(_T("MaterialSpecular.G"), 0, 0xff, 0, _T("0x%02X"));
		m_pwndMaterialSpecularColor->AddValue(_T("MaterialSpecular.B"), 0, 0xff, 0, _T("0x%02X"));
	}
	else
	{
		TRACE(_T("Unable to create material specular color controls\n"));
	}

	rcCtrl.OffsetRect(0, rcInitial.Height());
	m_pwndMaterialShininess = new CComponentSliderCtrl(m_xMaterialShininess);
	if (m_pwndMaterialShininess->Create(this, rcCtrl))
	{
		m_pwndMaterialShininess->AddValue(_T("MaterialShininess"), 0.f, 1.f, 0.f);
	}
	else
	{
		TRACE(_T("Unable to create material shininess controls\n"));
	}

	return TRUE;
}

void C3dParametersDlg::OnRotationChanged(const float* pfYaw, const float* pfPitch, const float* pfRoll)
{
	CXTPChartSeriesCollection* pSeriesCollection = m_wndChartControl.GetContent()->GetSeries();
	ASSERT(NULL != pSeriesCollection);

	CXTPChart3dPieSeriesStyle* pStyle = DYNAMIC_DOWNCAST(CXTPChart3dPieSeriesStyle, pSeriesCollection->GetAt(0)->GetStyle());
	ASSERT(NULL != pStyle);

	CXTPChart3dRotation rotation = pStyle->Get3dRotation();
	pStyle->Set3dRotation(
		NULL != pfYaw ? *pfYaw : rotation.m_dYaw,
		NULL != pfPitch ? *pfPitch : rotation.m_dPitch,
		NULL != pfRoll ? *pfRoll : rotation.m_dRoll);
}

void C3dParametersDlg::OnLightPositionChanged(const float* pX, const float* pY, const float* pZ)
{
	CXTPChartDiagram3DAppearance* p3dAppearance = m_wndChartControl.GetContent()->GetAppearance()->GetDiagram3DAppearance();
	ASSERT(NULL != p3dAppearance);

	if (NULL != pX) p3dAppearance->LightPosition.X = *pX;
	if (NULL != pY) p3dAppearance->LightPosition.Y = *pY;
	if (NULL != pZ) p3dAppearance->LightPosition.Z = *pZ;

	m_wndChartControl.OnChartChanged();
}

void C3dParametersDlg::OnLightModelAmbientColorChanged(const int* pR, const int* pG, const int* pB)
{
	CXTPChartDiagram3DAppearance* p3dAppearance = m_wndChartControl.GetContent()->GetAppearance()->GetDiagram3DAppearance();
	ASSERT(NULL != p3dAppearance);

	DWORD argb = CXTPChartColor::MakeARGB(
		p3dAppearance->LightModelAmbientColor.GetA(),
		(NULL != pR ? *pR : p3dAppearance->LightModelAmbientColor.GetR()),
		(NULL != pG ? *pG : p3dAppearance->LightModelAmbientColor.GetG()),
		(NULL != pB ? *pB : p3dAppearance->LightModelAmbientColor.GetB()));
	p3dAppearance->LightModelAmbientColor.SetValue(argb);

	m_wndChartControl.OnChartChanged();
}

void C3dParametersDlg::OnLightAmbientColorChanged(const int* pR, const int* pG, const int* pB)
{
	CXTPChartDiagram3DAppearance* p3dAppearance = m_wndChartControl.GetContent()->GetAppearance()->GetDiagram3DAppearance();
	ASSERT(NULL != p3dAppearance);

	DWORD argb = CXTPChartColor::MakeARGB(
		p3dAppearance->LightAmbientColor.GetA(),
		(NULL != pR ? *pR : p3dAppearance->LightAmbientColor.GetR()),
		(NULL != pG ? *pG : p3dAppearance->LightAmbientColor.GetG()),
		(NULL != pB ? *pB : p3dAppearance->LightAmbientColor.GetB()));
	p3dAppearance->LightAmbientColor.SetValue(argb);

	m_wndChartControl.OnChartChanged();
}

void C3dParametersDlg::OnLightDiffuseColorChanged(const int* pR, const int* pG, const int* pB)
{
	CXTPChartDiagram3DAppearance* p3dAppearance = m_wndChartControl.GetContent()->GetAppearance()->GetDiagram3DAppearance();
	ASSERT(NULL != p3dAppearance);

	DWORD argb = CXTPChartColor::MakeARGB(
		p3dAppearance->LightDiffuseColor.GetA(),
		(NULL != pR ? *pR : p3dAppearance->LightDiffuseColor.GetR()),
		(NULL != pG ? *pG : p3dAppearance->LightDiffuseColor.GetG()),
		(NULL != pB ? *pB : p3dAppearance->LightDiffuseColor.GetB()));
	p3dAppearance->LightDiffuseColor.SetValue(argb);

	m_wndChartControl.OnChartChanged();
}

void C3dParametersDlg::OnLightSpecularColorChanged(const int* pR, const int* pG, const int* pB)
{
	CXTPChartDiagram3DAppearance* p3dAppearance = m_wndChartControl.GetContent()->GetAppearance()->GetDiagram3DAppearance();
	ASSERT(NULL != p3dAppearance);

	DWORD argb = CXTPChartColor::MakeARGB(
		p3dAppearance->LightSpecularColor.GetA(),
		(NULL != pR ? *pR : p3dAppearance->LightSpecularColor.GetR()),
		(NULL != pG ? *pG : p3dAppearance->LightSpecularColor.GetG()),
		(NULL != pB ? *pB : p3dAppearance->LightSpecularColor.GetB()));
	p3dAppearance->LightSpecularColor.SetValue(argb);

	m_wndChartControl.OnChartChanged();
}

void C3dParametersDlg::OnMaterialEmissionColorChanged(const int* pR, const int* pG, const int* pB)
{
	CXTPChartDiagram3DAppearance* p3dAppearance = m_wndChartControl.GetContent()->GetAppearance()->GetDiagram3DAppearance();
	ASSERT(NULL != p3dAppearance);

	DWORD argb = CXTPChartColor::MakeARGB(
		p3dAppearance->MaterialEmissionColor.GetA(),
		(NULL != pR ? *pR : p3dAppearance->MaterialEmissionColor.GetR()),
		(NULL != pG ? *pG : p3dAppearance->MaterialEmissionColor.GetG()),
		(NULL != pB ? *pB : p3dAppearance->MaterialEmissionColor.GetB()));
	p3dAppearance->MaterialEmissionColor.SetValue(argb);

	m_wndChartControl.OnChartChanged();
}

void C3dParametersDlg::OnMaterialDiffuseColorChanged(const int* pR, const int* pG, const int* pB)
{
	CXTPChartDiagram3DAppearance* p3dAppearance = m_wndChartControl.GetContent()->GetAppearance()->GetDiagram3DAppearance();
	ASSERT(NULL != p3dAppearance);

	DWORD argb = CXTPChartColor::MakeARGB(
		p3dAppearance->MaterialDiffuseColor.GetA(),
		(NULL != pR ? *pR : p3dAppearance->MaterialDiffuseColor.GetR()),
		(NULL != pG ? *pG : p3dAppearance->MaterialDiffuseColor.GetG()),
		(NULL != pB ? *pB : p3dAppearance->MaterialDiffuseColor.GetB()));
	p3dAppearance->MaterialDiffuseColor.SetValue(argb);

	m_wndChartControl.OnChartChanged();
}

void C3dParametersDlg::OnMaterialSpecularColorChanged(const int* pR, const int* pG, const int* pB)
{
	CXTPChartDiagram3DAppearance* p3dAppearance = m_wndChartControl.GetContent()->GetAppearance()->GetDiagram3DAppearance();
	ASSERT(NULL != p3dAppearance);

	DWORD argb = CXTPChartColor::MakeARGB(
		p3dAppearance->MaterialSpecularColor.GetA(),
		(NULL != pR ? *pR : p3dAppearance->MaterialSpecularColor.GetR()),
		(NULL != pG ? *pG : p3dAppearance->MaterialSpecularColor.GetG()),
		(NULL != pB ? *pB : p3dAppearance->MaterialSpecularColor.GetB()));
	p3dAppearance->MaterialSpecularColor.SetValue(argb);

	m_wndChartControl.OnChartChanged();
}

void C3dParametersDlg::OnMaterialShininessChanged(float fShininess)
{
	CXTPChartDiagram3DAppearance* p3dAppearance = m_wndChartControl.GetContent()->GetAppearance()->GetDiagram3DAppearance();
	ASSERT(NULL != p3dAppearance);

	p3dAppearance->MaterialShininess = fShininess;

	m_wndChartControl.OnChartChanged();
}

void C3dParametersDlg::ComponentSliderCtrlCallback::OnBeforeValueChanged(int nItem)
{
	pThis->m_wndChartControl.BeginFrequentUpdates();

	UNREFERENCED_PARAMETER(nItem);
}

void C3dParametersDlg::ComponentSliderCtrlCallback::OnAfterValueChanged(int nItem)
{
	pThis->m_wndChartControl.EndFrequentUpdates();

	UNREFERENCED_PARAMETER(nItem);
}

void C3dParametersDlg::XRotationCallback::OnValueChanged(int nItem, int nValue)
{
	float fValue = static_cast<float>(nValue);
	switch (nItem)
	{
	case 0: // yaw
		pThis->OnRotationChanged(&fValue, NULL, NULL);
		break;
	case 1: // pitch
		pThis->OnRotationChanged(NULL, &fValue, NULL);
		break;
	case 2: // roll
		pThis->OnRotationChanged(NULL, NULL, &fValue);
		break;
	default:
		ASSERT(!"Unexpected");
	}
}

void C3dParametersDlg::XLightPositionCallback::OnValueChanged(int nItem, float fValue)
{
	switch (nItem)
	{
	case 0: // Z
		pThis->OnLightPositionChanged(&fValue, NULL, NULL);
		break;
	case 1: // Y
		pThis->OnLightPositionChanged(NULL, &fValue, NULL);
		break;
	case 2: // Z
		pThis->OnLightPositionChanged(NULL, NULL, &fValue);
		break;
	default:
		ASSERT(!"Unexpected");
	}
}

void C3dParametersDlg::XLightModelAmbientColor::OnValueChanged(int nItem, int nValue)
{
	switch (nItem)
	{
	case 0: // R
		pThis->OnLightModelAmbientColorChanged(&nValue, NULL, NULL);
		break;
	case 1: // G
		pThis->OnLightModelAmbientColorChanged(NULL, &nValue, NULL);
		break;
	case 2: // B
		pThis->OnLightModelAmbientColorChanged(NULL, NULL, &nValue);
		break;
	default:
		ASSERT(!"Unexpected");
	}
}

void C3dParametersDlg::XLightAmbientColor::OnValueChanged(int nItem, int nValue)
{
	switch (nItem)
	{
	case 0: // R
		pThis->OnLightAmbientColorChanged(&nValue, NULL, NULL);
		break;
	case 1: // G
		pThis->OnLightAmbientColorChanged(NULL, &nValue, NULL);
		break;
	case 2: // B
		pThis->OnLightAmbientColorChanged(NULL, NULL, &nValue);
		break;
	default:
		ASSERT(!"Unexpected");
	}
}

void C3dParametersDlg::XLightDiffuseColor::OnValueChanged(int nItem, int nValue)
{
	switch (nItem)
	{
	case 0: // R
		pThis->OnLightDiffuseColorChanged(&nValue, NULL, NULL);
		break;
	case 1: // G
		pThis->OnLightDiffuseColorChanged(NULL, &nValue, NULL);
		break;
	case 2: // B
		pThis->OnLightDiffuseColorChanged(NULL, NULL, &nValue);
		break;
	default:
		ASSERT(!"Unexpected");
	}
}

void C3dParametersDlg::XLightSpecularColor::OnValueChanged(int nItem, int nValue)
{
	switch (nItem)
	{
	case 0: // R
		pThis->OnLightSpecularColorChanged(&nValue, NULL, NULL);
		break;
	case 1: // G
		pThis->OnLightSpecularColorChanged(NULL, &nValue, NULL);
		break;
	case 2: // B
		pThis->OnLightSpecularColorChanged(NULL, NULL, &nValue);
		break;
	default:
		ASSERT(!"Unexpected");
	}
}

void C3dParametersDlg::XMaterialEmissionColor::OnValueChanged(int nItem, int nValue)
{
	switch (nItem)
	{
	case 0: // R
		pThis->OnMaterialEmissionColorChanged(&nValue, NULL, NULL);
		break;
	case 1: // G
		pThis->OnMaterialEmissionColorChanged(NULL, &nValue, NULL);
		break;
	case 2: // B
		pThis->OnMaterialEmissionColorChanged(NULL, NULL, &nValue);
		break;
	default:
		ASSERT(!"Unexpected");
	}
}

void C3dParametersDlg::XMaterialDiffuseColor::OnValueChanged(int nItem, int nValue)
{
	switch (nItem)
	{
	case 0: // R
		pThis->OnMaterialDiffuseColorChanged(&nValue, NULL, NULL);
		break;
	case 1: // G
		pThis->OnMaterialDiffuseColorChanged(NULL, &nValue, NULL);
		break;
	case 2: // B
		pThis->OnMaterialDiffuseColorChanged(NULL, NULL, &nValue);
		break;
	default:
		ASSERT(!"Unexpected");
	}
}

void C3dParametersDlg::XMaterialSpecularColor::OnValueChanged(int nItem, int nValue)
{
	switch (nItem)
	{
	case 0: // R
		pThis->OnMaterialSpecularColorChanged(&nValue, NULL, NULL);
		break;
	case 1: // G
		pThis->OnMaterialSpecularColorChanged(NULL, &nValue, NULL);
		break;
	case 2: // B
		pThis->OnMaterialSpecularColorChanged(NULL, NULL, &nValue);
		break;
	default:
		ASSERT(!"Unexpected");
	}
}

void C3dParametersDlg::XMaterialShininess::OnValueChanged(int nItem, float fValue)
{
	pThis->OnMaterialShininessChanged(fValue);
}

BEGIN_MESSAGE_MAP(C3dParametersDlg, CTabCtrlDialog)
	//{{AFX_MSG_MAP(C3dParametersDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// C3dParametersDlg message handlers
