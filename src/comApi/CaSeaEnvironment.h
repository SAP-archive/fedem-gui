/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"


class CaSeaEnvironment : public CCmdTarget
{
public:
  CaSeaEnvironment(void);
  ~CaSeaEnvironment(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  DECLARE_DYNCREATE(CaSeaEnvironment)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaSeaEnvironment)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidWaterDensity = 1L,
    dispidMeanSeaLevel = 2L,
    dispidWaterDepth = 3L,
    dispidMarineGrowthDensity = 4L,
    dispidMarineGrowthThickness = 5L,
    dispidMarineGrowthUpperLimit = 6L,
    dispidMarineGrowthLowerLimit = 7L,
    dispidGetGravitation = 100L,
    dispidSetGravitation = 101L,
    dispidGetWaveDirection = 102L,
    dispidSetWaveDirection = 103L,
    dispidGetWaveFunction = 104L,
    dispidSetWaveFunction = 105L,
    dispidGetCurrentFunction = 106L,
    dispidSetCurrentFunction = 107L
  };

  // Methods
  double  get_WaterDensity();
  void    put_WaterDensity(double Val);
  double  get_MeanSeaLevel();
  void    put_MeanSeaLevel(double Val);
  double  get_WaterDepth();
  void    put_WaterDepth(double Val);
  double  get_MarineGrowthDensity();
  void    put_MarineGrowthDensity(double Val);
  double  get_MarineGrowthThickness();
  void    put_MarineGrowthThickness(double Val);
  double  get_MarineGrowthUpperLimit();
  void    put_MarineGrowthUpperLimit(double Val);
  double  get_MarineGrowthLowerLimit();
  void    put_MarineGrowthLowerLimit(double Val);
  void GetGravitation(double* x, double* y, double* z);
  void SetGravitation(double x, double y, double z);
  void GetWaveDirection(double* x, double* y, double* z);
  void SetWaveDirection(double x, double y, double z);
  IFunction* GetWaveFunction();
  void SetWaveFunction(IFunction* Function);
  IFunction* GetCurrentFunction();
  void SetCurrentFunction(IFunction* Function);


  BEGIN_INTERFACE_PART(LocalClass, ISeaEnvironment)
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
    STDMETHOD(get_WaterDensity)(THIS_ double* pVal);
    STDMETHOD(put_WaterDensity)(THIS_ double val);
    STDMETHOD(get_MeanSeaLevel)(THIS_ double* pVal);
    STDMETHOD(put_MeanSeaLevel)(THIS_ double val);
    STDMETHOD(get_WaterDepth)(THIS_ double* pVal);
    STDMETHOD(put_WaterDepth)(THIS_ double val);
    STDMETHOD(get_MarineGrowthDensity)(THIS_ double* pVal);
    STDMETHOD(put_MarineGrowthDensity)(THIS_ double val);
    STDMETHOD(get_MarineGrowthThickness)(THIS_ double* pVal);
    STDMETHOD(put_MarineGrowthThickness)(THIS_ double val);
    STDMETHOD(get_MarineGrowthUpperLimit)(THIS_ double* pVal);
    STDMETHOD(put_MarineGrowthUpperLimit)(THIS_ double val);
    STDMETHOD(get_MarineGrowthLowerLimit)(THIS_ double* pVal);
    STDMETHOD(put_MarineGrowthLowerLimit)(THIS_ double val);
    STDMETHOD(GetGravitation)(THIS_ double* x, double* y, double* z);
    STDMETHOD(SetGravitation)(THIS_ double x, double y, double z);
    STDMETHOD(GetWaveDirection)(THIS_ double* x, double* y, double* z);
    STDMETHOD(SetWaveDirection)(THIS_ double x, double y, double z);
    STDMETHOD(GetWaveFunction)(THIS_ IFunction** ppRet);
    STDMETHOD(SetWaveFunction)(THIS_ IFunction* Function);
    STDMETHOD(GetCurrentFunction)(THIS_ IFunction** ppRet);
    STDMETHOD(SetCurrentFunction)(THIS_ IFunction* Function);
  END_INTERFACE_PART(LocalClass)
};
