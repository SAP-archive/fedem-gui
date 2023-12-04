/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmBeam;


class CaBeam : public CCmdTarget
{
public:
  CaBeam(void);
  ~CaBeam(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmBeam* m_pBeam;

  DECLARE_DYNCREATE(CaBeam)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaBeam)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidMass = 1L,
    dispidDescription = 2L,
    dispidBaseID = 3L,
    dispidVisualize3D = 4L,
    dispidVisualize3DStartAngle = 5L,
    dispidVisualize3DStopAngle = 6L,
    dispidParent = 7L,
    dispidGetEulerRotationZYX = 10L,
    dispidGetTriad1 = 100L,
    dispidSetTriad1 = 101L,
    dispidGetTriad2 = 102L,
    dispidSetTriad2 = 103L,
    dispidGetCrossSection = 104L,
    dispidSetCrossSection = 105L,
    dispidSetLocalZaxis = 106L,
    dispidGetGlobalCS = 107L,
    dispidGetLocalCS = 108L,
    dispidGetStructuralDamping = 109L,
    dispidSetStructuralDamping = 110L,
    dispidGetScaling = 111L,
    dispidSetScaling = 112L,
    dispidGetLength = 113L,
    dispidDelete = 800L
  };

  // Methods
  double get_Mass();
  BSTR   get_Description();
  void   put_Description(LPCTSTR val);
  long   get_BaseID();
  BOOL   get_Visualize3D();
  void   put_Visualize3D(BOOL val);
  double get_Visualize3DStartAngle();
  void   put_Visualize3DStartAngle(double val);
  double get_Visualize3DStopAngle();
  void   put_Visualize3DStopAngle(double val);
  ISubAssembly* get_Parent();
  void GetEulerRotationZYX(double* rx, double* ry, double* rz);
  ITriad* GetTriad1();
  void SetTriad1(ITriad* Triad);
  ITriad* GetTriad2();
  void SetTriad2(ITriad* Triad);
  ICrossSection* GetCrossSection();
  void SetCrossSection(ICrossSection* CrossSection);
  void SetLocalZaxis(double x, double y, double z);
  void GetGlobalCS(VARIANT* Array4x3);
  void GetLocalCS(VARIANT* Array4x3);
  void GetStructuralDamping(double* MassProp, double* StiffProp);
  void SetStructuralDamping(double MassProp, double StiffProp);
  void GetScaling(double* StiffScale, double* MassScale);
  void SetScaling(double StiffScale, double MassScale);
  double GetLength();
  void Delete();

  BEGIN_INTERFACE_PART(LocalClass, IBeam)
    STDMETHOD(GetTypeInfoCount)(UINT FAR* pctinfo);
    STDMETHOD(GetTypeInfo)(
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);
    STDMETHOD(GetIDsOfNames)(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);
    STDMETHOD(Invoke)(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);
    STDMETHOD(get_Mass)(THIS_ double* pVal);
    STDMETHOD(get_Description)(THIS_ BSTR* pVal);
    STDMETHOD(put_Description)(THIS_ BSTR val);
	STDMETHOD(get_BaseID)(THIS_ long* pVal);
	STDMETHOD(get_Visualize3D)(THIS_ VARIANT_BOOL* pVal);
	STDMETHOD(put_Visualize3D)(THIS_ VARIANT_BOOL val);
	STDMETHOD(get_Visualize3DStartAngle)(THIS_ double* pVal);
	STDMETHOD(put_Visualize3DStartAngle)(THIS_ double val);
	STDMETHOD(get_Visualize3DStopAngle)(THIS_ double* pVal);
	STDMETHOD(put_Visualize3DStopAngle)(THIS_ double val);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(GetEulerRotationZYX)(THIS_ double* rx, double* ry, double* rz);
    STDMETHOD(GetTriad1)(THIS_ ITriad** ppRet);
    STDMETHOD(SetTriad1)(THIS_ ITriad* Triad);
    STDMETHOD(GetTriad2)(THIS_ ITriad** ppRet);
    STDMETHOD(SetTriad2)(THIS_ ITriad* Triad);
    STDMETHOD(GetCrossSection)(THIS_ ICrossSection** ppRet);
    STDMETHOD(SetCrossSection)(THIS_ ICrossSection* CrossSection);
	STDMETHOD(SetLocalZaxis)(THIS_ double x, double y, double z);
	STDMETHOD(GetGlobalCS)(THIS_ VARIANT* Array4x3);
    STDMETHOD(GetLocalCS)(THIS_ VARIANT* Array4x3);
    STDMETHOD(GetStructuralDamping)(THIS_ double* MassProp, double* StiffProp);
    STDMETHOD(SetStructuralDamping)(THIS_ double MassProp, double StiffProp);
    STDMETHOD(GetScaling)(THIS_ double* StiffScale, double* MassScale);
    STDMETHOD(SetScaling)(THIS_ double StiffScale, double MassScale);
    STDMETHOD(GetLength)(THIS_ double* pRet);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaBeam,FmBeam> signalConnector;

public:
  FmBeam*& m_ptr; // TODO: Remove
};
