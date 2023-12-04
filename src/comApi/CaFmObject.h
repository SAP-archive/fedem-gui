/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmModelMemberBase;


class CaFmObject : public CCmdTarget
{
public:
  CaFmObject(void);
  ~CaFmObject(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmModelMemberBase* m_ptr;

  DECLARE_DYNCREATE(CaFmObject)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaFmObject)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDescription = 1L,
    dispidBaseID = 2L,
    dispidParent = 3L,
    dispidGetValue = 100L,
    dispidSetValue = 101L,
    dispidDelete = 800L
  };

  // Methods
  BSTR get_Description();
  void put_Description(LPCTSTR val);
  long get_BaseID();
  ISubAssembly* get_Parent();
  BSTR GetValue(LPCTSTR FieldName);
  void SetValue(LPCTSTR FieldName, LPCTSTR Value);
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, IFmObject)
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
    STDMETHOD(GetValue)(THIS_ BSTR FieldName, BSTR* Value);
    STDMETHOD(SetValue)(THIS_ BSTR FieldName, BSTR Value);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaFmObject,FmModelMemberBase> signalConnector;
};
