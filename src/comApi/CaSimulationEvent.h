/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmSimulationEvent;


class CaSimulationEvent : public CCmdTarget
{
public:
  CaSimulationEvent(void);
  ~CaSimulationEvent(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmSimulationEvent* m_pSimulationEvent;

  DECLARE_DYNCREATE(CaSimulationEvent)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaSimulationEvent)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidID = 1L,
    dispidProbability = 2L,
    dispidDescription = 3L,
    dispidGetFRSFileNames = 100L,
    dispidActivate = 101L,
    dispidAddPropertyValue = 102L,
    dispidDelete = 800L
  };

  // Methods
  long get_ID();
  void put_ID(long val);
  double get_Probability();
  void put_Probability(double val);
  BSTR get_Description();
  void put_Description(LPCTSTR val);
  BSTR GetFRSFileNames();
  void Activate(BOOL Activate, BOOL Notify);
  void AddPropertyValue(IDispatch* ModelObject, LPCTSTR PropertyName, LPCTSTR Value);
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, ISimulationEvent)
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
    STDMETHOD(get_ID)(THIS_ long* pVal);
    STDMETHOD(put_ID)(THIS_ long val);
    STDMETHOD(get_Probability)(THIS_ double* pVal);
    STDMETHOD(put_Probability)(THIS_ double val);
    STDMETHOD(get_Description)(THIS_ BSTR* pVal);
    STDMETHOD(put_Description)(THIS_ BSTR val);
    STDMETHOD(GetFRSFileNames)(THIS_ BSTR* pVal);
    STDMETHOD(Activate)(VARIANT_BOOL Activate, VARIANT_BOOL Notify);
    STDMETHOD(AddPropertyValue)(IDispatch* ModelObject, BSTR PropertyName, BSTR Value);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaSimulationEvent,FmSimulationEvent> signalConnector;

public:
  FmSimulationEvent*& m_ptr; // TODO: Remove
};
