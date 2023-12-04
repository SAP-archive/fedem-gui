/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"


class CaSelectionManager : public CCmdTarget
{
public:
  CaSelectionManager(void);
  ~CaSelectionManager(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  DECLARE_DYNCREATE(CaSelectionManager)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaSelectionManager)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidItem = 0L,
    dispidLastItem = 1L,
    dispidCount = 2L,
    dispidAdd = 100L,
    dispidInsert = 101L,
    dispidRemove = 102L,
    dispidRemoveAt = 103L,
    dispidClear = 104L,
    dispidFEGetPickedPoint = 120L,
    dispidFESetPickPointMode = 121L
  };

  // Methods
  IDispatch*  get_Item(long Index);
  void        put_Item(long Index, IDispatch* pObj);
  IDispatch*  get_LastItem();
  void        put_LastItem(IDispatch* pObj);
  long        get_Count();
  void Add(IDispatch* Item);
  void Insert(long Index, IDispatch* Item);
  void Remove(IDispatch* Item);
  void RemoveAt(long Index);
  void Clear();
  BOOL FEGetPickedPoint(double* x, double* y, double* z, BOOL Global);
  void FESetPickPointMode(BOOL On, const VARIANT FAR& Desc);
  BOOL FEGetPickPointMode(long* State);


  BEGIN_INTERFACE_PART(LocalClass, ISelectionManager)
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
    STDMETHOD(get_Item)(THIS_ long Index, IDispatch** ppObj);
    STDMETHOD(put_Item)(THIS_ long Index, IDispatch* pObj);
    STDMETHOD(get_LastItem)(THIS_ IDispatch** ppObj);
    STDMETHOD(put_LastItem)(THIS_ IDispatch* pObj);
    STDMETHOD(get_Count)(THIS_ long* pnVal);
    STDMETHOD(Add)(THIS_ IDispatch* Item);
    STDMETHOD(Insert)(THIS_ long Index, IDispatch* Item);
    STDMETHOD(Remove)(THIS_ IDispatch* Item);
    STDMETHOD(RemoveAt)(THIS_ long Index);
    STDMETHOD(Clear)(THIS_);
    STDMETHOD(FEGetPickedPoint)(THIS_ double* x, double* y, double* z, VARIANT_BOOL Global, VARIANT_BOOL* pRet);
    STDMETHOD(FESetPickPointMode)(THIS_ VARIANT_BOOL On, VARIANT Desc);
    STDMETHOD(FEGetPickPointMode)(THIS_ long* State, VARIANT_BOOL* pRet);
  END_INTERFACE_PART(LocalClass)
};
