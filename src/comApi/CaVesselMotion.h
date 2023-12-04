/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmVesselMotion;


class CaVesselMotion : public CCmdTarget
{
public:
  CaVesselMotion(void);
  ~CaVesselMotion(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmVesselMotion* m_ptr;

  DECLARE_DYNCREATE(CaVesselMotion)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaVesselMotion)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDescription = 1L,
    dispidBaseID = 2L,
    dispidParent = 3L,
    dispidRAOFilePath = 4L,
    dispidGetWaveFunction = 5L,
    dispidSetWaveFunction = 6L,
    dispidWaveDir = 7,
    dispidGetMotionScaleFunction = 8,
    dispidSetMotionScaleFunction = 9,
    dispidDelete = 800L
  };

  // Methods
  BSTR get_Description();
  void put_Description(LPCTSTR val);
  BSTR get_RAOFilePath();
  void put_RAOFilePath(LPCTSTR val);
  IFunction* GetWaveFunction();
  void SetWaveFunction(IFunction* Function);
  long get_WaveDir();
  void put_WaveDir(long val);
  IFunction* GetMotionScaleFunction();
  void SetMotionScaleFunction(IFunction* Function);
  long get_BaseID();
  ISubAssembly* get_Parent();
  void Delete();

  BEGIN_INTERFACE_PART(LocalClass, IVesselMotion)
    STDMETHOD(GetTypeInfoCount)(UINT FAR* pctinfo);
    STDMETHOD(GetTypeInfo)(UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo);
    STDMETHOD(GetIDsOfNames)(REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid);
    STDMETHOD(Invoke)(DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr);
    STDMETHOD(get_Description)(THIS_ BSTR* pVal);
    STDMETHOD(put_Description)(THIS_ BSTR val);
    STDMETHOD(get_RAOFilePath)(THIS_ BSTR* pVal);
    STDMETHOD(put_RAOFilePath)(THIS_ BSTR val);
    STDMETHOD(GetWaveFunction)(THIS_ IFunction** ppRet);
    STDMETHOD(SetWaveFunction)(THIS_ IFunction* Function);
    STDMETHOD(get_WaveDir)(THIS_ long* pVal);
    STDMETHOD(put_WaveDir)(THIS_ long val);
    STDMETHOD(GetMotionScaleFunction)(THIS_ IFunction** ppRet);
    STDMETHOD(SetMotionScaleFunction)(THIS_ IFunction* Function);
    STDMETHOD(get_BaseID)(THIS_ long* pVal);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaVesselMotion,FmVesselMotion> signalConnector;
};
