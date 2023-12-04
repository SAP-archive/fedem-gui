/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmMaterialProperty;


class CaMaterial : public CCmdTarget
{
public:
  CaMaterial(void);
  ~CaMaterial(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmMaterialProperty* m_ptr;

  DECLARE_DYNCREATE(CaMaterial)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaMaterial)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDescription = 1L,
    dispidBaseID = 2L,
    dispidParent = 3L,
    dispidGetMaterialProperties = 100L,
    dispidSetMaterialProperties = 101L,
    dispidDelete = 800L
  };

  // Methods
  BSTR get_Description();
  void put_Description(LPCTSTR val);
  long get_BaseID();
  ISubAssembly* get_Parent();
  void GetMaterialProperties(double* Rho, double* E, double* nu, double* G);
  void SetMaterialProperties(double Rho, double E, double nu);
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, IMaterial)
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
    STDMETHOD(GetMaterialProperties)(THIS_ double* Rho, double* E, double* nu, double* G);
    STDMETHOD(SetMaterialProperties)(THIS_ double Rho, double E, double nu);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaMaterial,FmMaterialProperty> signalConnector;
};
