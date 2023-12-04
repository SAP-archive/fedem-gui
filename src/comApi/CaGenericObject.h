/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmGenericDBObject;


class CaGenericObject : public CCmdTarget
{
public:
  CaGenericObject(void);
  ~CaGenericObject(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmGenericDBObject* m_pGenericObject;

  DECLARE_DYNCREATE(CaGenericObject)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaGenericObject)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDescription = 1L,
    dispidObjectType = 2L,
    dispidObjectDefinition = 3L,
    dispidBaseID = 4L,
    dispidParent = 5L,
    dispidDelete = 800L
  };

  // Methods
  BSTR get_Description();
  void put_Description(LPCTSTR val);
  BSTR get_ObjectType();
  void put_ObjectType(LPCTSTR val);
  BSTR get_ObjectDefinition();
  void put_ObjectDefinition(LPCTSTR val);
  long get_BaseID();
  ISubAssembly* get_Parent();
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, IGenericObject)
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
    STDMETHOD(get_ObjectType)(THIS_ BSTR* pVal);
    STDMETHOD(put_ObjectType)(THIS_ BSTR val);
    STDMETHOD(get_ObjectDefinition)(THIS_ BSTR* pVal);
    STDMETHOD(put_ObjectDefinition)(THIS_ BSTR val);
    STDMETHOD(get_BaseID)(THIS_ long* pVal);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaGenericObject,FmGenericDBObject> signalConnector;

public:
  FmGenericDBObject*& m_ptr; // TODO: Remove
};
