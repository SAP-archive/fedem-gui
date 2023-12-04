/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"


class CaSimulationEventManager : public CCmdTarget
{
public:
  CaSimulationEventManager(void);
  ~CaSimulationEventManager(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  DECLARE_DYNCREATE(CaSimulationEventManager)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaSimulationEventManager)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidItem = 0L,
    dispidCount = 1L,
    dispidAdd = 100L,
    dispidRemove = 101L,
    dispidClear = 102L,
	dispidSetActiveEvent = 103L
  };

  // Methods
  ISimulationEvent* get_Item(long Index);
  long get_Count();
  ISimulationEvent* Add(long ID, const VARIANT FAR& Probability, const VARIANT FAR& Desc);
  void Remove(ISimulationEvent* Item);
  void Clear();
  void SetActiveEvent(const VARIANT FAR& SimEvent);


  BEGIN_INTERFACE_PART(LocalClass, ISimulationEventManager)
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
    STDMETHOD(get_Item)(THIS_ long Index, ISimulationEvent** ppObj);
    STDMETHOD(get_Count)(THIS_ long* pnVal);
    STDMETHOD(Add)(THIS_ long ID, VARIANT Probability, VARIANT Desc, ISimulationEvent** ppObj);
    STDMETHOD(Remove)(THIS_ ISimulationEvent* Item);
    STDMETHOD(Clear)(THIS_);
	STDMETHOD(SetActiveEvent)(THIS_ VARIANT SimEvent);
  END_INTERFACE_PART(LocalClass)
};
