/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmAxialDamper;


class CaAxialDamper : public CCmdTarget
{
public:
  CaAxialDamper(void);
  ~CaAxialDamper(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmAxialDamper* m_pAxialDamper;

  DECLARE_DYNCREATE(CaAxialDamper)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaAxialDamper)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDescription = 1L,
    dispidBaseID = 2L,
    dispidParent = 3L,
    dispidIsDefDamper = 4L,
    dispidGetTriad1 = 100L,
    dispidSetTriad1 = 101L,
    dispidGetTriad2 = 102L,
    dispidSetTriad2 = 103L,
    dispidGetDampingScale = 104L,
    dispidSetDampingScale = 105L,
    dispidGetDampingFunction = 106L,
    dispidSetDampingFunction = 107L,
    dispidGetDampingCoefficient = 108L,
    dispidSetDampingCoefficient = 109L,
    dispidDelete = 800L
  };

  // Methods
  BSTR   get_Description();
  void   put_Description(LPCTSTR val);
  long   get_BaseID();
  ISubAssembly* get_Parent();
  BOOL get_IsDefDamper();
  void   put_IsDefDamper(BOOL val);
  ITriad* GetTriad1();
  void SetTriad1(ITriad* Triad);
  ITriad* GetTriad2();
  void SetTriad2(ITriad* Triad);
  IFunction* GetDampingScale();
  void SetDampingScale(IFunction* Function);
  IFunction* GetDampingFunction();
  void SetDampingFunction(IFunction* Function);
  double GetDampingCoefficient();
  void SetDampingCoefficient(double Value);
  void Delete();

  BEGIN_INTERFACE_PART(LocalClass, IAxialDamper)
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
    STDMETHOD(get_Description)(THIS_ BSTR* pVal);
    STDMETHOD(put_Description)(THIS_ BSTR val);
    STDMETHOD(get_BaseID)(THIS_ long* pVal);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(get_IsDefDamper)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_IsDefDamper)(THIS_ VARIANT_BOOL val);
    STDMETHOD(GetTriad1)(THIS_ ITriad** ppRet);
    STDMETHOD(SetTriad1)(THIS_ ITriad* Triad);
    STDMETHOD(GetTriad2)(THIS_ ITriad** ppRet);
    STDMETHOD(SetTriad2)(THIS_ ITriad* Triad);
    STDMETHOD(GetDampingScale)(THIS_ IFunction** ppObj);
    STDMETHOD(SetDampingScale)(THIS_ IFunction* Function);
    STDMETHOD(GetDampingFunction)(THIS_ IFunction** ppObj);
    STDMETHOD(SetDampingFunction)(THIS_ IFunction* Function);
    STDMETHOD(GetDampingCoefficient)(THIS_ double* pVal);
    STDMETHOD(SetDampingCoefficient)(THIS_ double Value);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaAxialDamper,FmAxialDamper> signalConnector;

public:
  FmAxialDamper*& m_ptr; // TODO: Remove
};
