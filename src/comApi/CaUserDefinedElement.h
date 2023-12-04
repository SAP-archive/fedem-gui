/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmUserDefinedElement;


class CaUserDefinedElement : public CCmdTarget
{
public:
  CaUserDefinedElement(void);
  ~CaUserDefinedElement(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmUserDefinedElement* m_ptr;
  long m_numElementNodes;

  DECLARE_DYNCREATE(CaUserDefinedElement)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaUserDefinedElement)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDescription = 1L,
    dispidBaseID = 2L,
    dispidParent = 3L,
    dispidNumElementNodes = 4L,
    dispidGetTriad = 100L,
    dispidSetTriad = 101L,
    dispidGetStructuralDamping = 102L,
    dispidSetStructuralDamping = 103L,
    dispidGetScaling = 104L,
    dispidSetScaling = 105L,
    dispidDelete = 800L
  };

  // Methods
  BSTR   get_Description();
  void   put_Description(LPCTSTR val);
  long   get_BaseID();
  long   get_NumElementNodes();
  ISubAssembly* get_Parent();
  ITriad* GetTriad(int pos);
  void SetTriad(int pos, ITriad* Triad);
  void GetStructuralDamping(double* MassProp, double* StiffProp);
  void SetStructuralDamping(double MassProp, double StiffProp);
  void GetScaling(double* StiffScale, double* MassScale);
  void SetScaling(double StiffScale, double MassScale);
  void Delete();

  BEGIN_INTERFACE_PART(LocalClass, IUserDefinedElement)
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
    STDMETHOD(get_NumElementNodes)(THIS_ long* pVal);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(GetTriad)(THIS_ long pos, ITriad** Triad);
    STDMETHOD(SetTriad)(THIS_ long pos, ITriad* Triad);
    STDMETHOD(GetStructuralDamping)(THIS_ double* MassProp, double* StiffProp);
    STDMETHOD(SetStructuralDamping)(THIS_ double MassProp, double StiffProp);
    STDMETHOD(GetScaling)(THIS_ double* StiffScale, double* MassScale);
    STDMETHOD(SetScaling)(THIS_ double StiffScale, double MassScale);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaUserDefinedElement,FmUserDefinedElement> signalConnector;
};
