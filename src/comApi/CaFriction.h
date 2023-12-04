/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmFrictionBase;


class CaFriction : public CCmdTarget
{
public:
  CaFriction(void);
  ~CaFriction(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmFrictionBase* m_pFriction;

  DECLARE_DYNCREATE(CaFriction)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaFriction)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidPrestressForce = 1L,
    dispidCoulombCoefficient = 2L,
    dispidStribeckMagnitude = 3L,
    dispidCriticalStribeckSpeed = 4L,
    dispidRadius = 5L,
    dispidBendingCapacityDistance = 6L,
    dispidBearingConstant = 7L,
    dispidDescription = 8L,
    dispidParent = 9L
  };

  // Methods
  double get_PrestressForce();
  void put_PrestressForce(double val);
  double get_CoulombCoefficient();
  void put_CoulombCoefficient(double val);
  double get_StribeckMagnitude();
  void put_StribeckMagnitude(double val);
  double get_CriticalStribeckSpeed();
  void put_CriticalStribeckSpeed(double val);
  double get_Radius();
  void put_Radius(double val);
  double get_BendingCapacityDistance();
  void put_BendingCapacityDistance(double val);
  double get_BearingConstant();
  void put_BearingConstant(double val);
  BSTR get_Description();
  void put_Description(LPCTSTR val);
  ISubAssembly* get_Parent();


  BEGIN_INTERFACE_PART(LocalClass, IFriction)
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
    STDMETHOD(get_PrestressForce)(THIS_ double* pVal);
    STDMETHOD(put_PrestressForce)(THIS_ double val);
    STDMETHOD(get_CoulombCoefficient)(THIS_ double* pVal);
    STDMETHOD(put_CoulombCoefficient)(THIS_ double val);
    STDMETHOD(get_StribeckMagnitude)(THIS_ double* pVal);
    STDMETHOD(put_StribeckMagnitude)(THIS_ double val);
    STDMETHOD(get_CriticalStribeckSpeed)(THIS_ double* pVal);
    STDMETHOD(put_CriticalStribeckSpeed)(THIS_ double val);
    STDMETHOD(get_Radius)(THIS_ double* pVal);
    STDMETHOD(put_Radius)(THIS_ double val);
    STDMETHOD(get_BendingCapacityDistance)(THIS_ double* pVal);
    STDMETHOD(put_BendingCapacityDistance)(THIS_ double val);
    STDMETHOD(get_BearingConstant)(THIS_ double* pVal);
    STDMETHOD(put_BearingConstant)(THIS_ double val);
    STDMETHOD(get_Description)(THIS_ BSTR* pVal);
    STDMETHOD(put_Description)(THIS_ BSTR val);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaFriction,FmFrictionBase> signalConnector;

public:
  FmFrictionBase*& m_ptr; // TODO: Remove
};
