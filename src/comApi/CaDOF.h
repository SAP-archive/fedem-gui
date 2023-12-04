/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmHasDOFsBase;


class CaDOF : public CCmdTarget
{
  void checkMe();

public:
  CaDOF(void);
  ~CaDOF(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmHasDOFsBase* m_pDOF;
  long m_nDOFIndex;

  DECLARE_DYNCREATE(CaDOF)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaDOF)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDOFConstraintType = 1L,
    dispidInitialVelocity = 2L,
    dispidAddBC = 3L,
    dispidLoadMagnitude = 4L,
    dispidPrescribedMotionType = 5L,
    dispidPrescribedMotionMagnitude = 6L,
    dispidSDStressfreeLength = 7L,
    dispidSDStiffness = 8L,
    dispidSDStiffnessScale = 9L,
    dispidSDDamper = 10L,
    dispidSDDamperScale = 11L,
    dispidSetFree = 100L,
    dispidSetFixed = 101L,
    dispidSetPrescribed = 102L,
    dispidSetSpringDamper = 103L
  };

  // Methods
  DOFConstraintType get_DOFConstraintType();
  void put_DOFConstraintType(DOFConstraintType Val);
  double get_InitialVelocity();
  BOOL get_AddBC();
  void put_AddBC(BOOL Val);
  VARIANT get_LoadMagnitude();
  DOFPrescribedMotionType get_PrescribedMotionType();
  VARIANT get_PrescribedMotionMagnitude();
  VARIANT get_SDStressfreeLength();
  VARIANT get_SDStiffness();
  VARIANT get_SDStiffnessScale();
  VARIANT get_SDDamper();
  VARIANT get_SDDamperScale();
  void SetFree(const VARIANT FAR& LoadMagnitude, const VARIANT FAR& InitialVelocity);
  void SetFixed();
  void SetPrescribed(DOFPrescribedMotionType MotionType,
    const VARIANT FAR& MotionMagnitude, const VARIANT FAR& InitialVelocity);
  void SetSpringDamper(const VARIANT FAR& LoadMagnitude,
    const VARIANT FAR& StressfreeLength, const VARIANT FAR& Stiffness,
    const VARIANT FAR& StiffnessScale, const VARIANT FAR& Damper,
    const VARIANT FAR& DamperScale, const VARIANT FAR& InitialVelocity);


  BEGIN_INTERFACE_PART(LocalClass, IDOF)
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
    STDMETHOD(get_DOFConstraintType)(THIS_ DOFConstraintType* pVal);
    STDMETHOD(put_DOFConstraintType)(THIS_ DOFConstraintType Val);
    STDMETHOD(get_InitialVelocity)(THIS_ double* pVal);
    STDMETHOD(get_AddBC)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_AddBC)(THIS_ VARIANT_BOOL Val);
    STDMETHOD(get_LoadMagnitude)(THIS_ VARIANT* pVal);
    STDMETHOD(get_PrescribedMotionType)(THIS_ DOFPrescribedMotionType* pVal);
    STDMETHOD(get_PrescribedMotionMagnitude)(THIS_ VARIANT* pVal);
    STDMETHOD(get_SDStressfreeLength)(THIS_ VARIANT* pVal);
    STDMETHOD(get_SDStiffness)(THIS_ VARIANT* pVal);
    STDMETHOD(get_SDStiffnessScale)(THIS_ VARIANT* pVal);
    STDMETHOD(get_SDDamper)(THIS_ VARIANT* pVal);
    STDMETHOD(get_SDDamperScale)(THIS_ VARIANT* pVal);
    STDMETHOD(SetFree)(THIS_ VARIANT LoadMagnitude, VARIANT InitialVelocity);
    STDMETHOD(SetFixed)(THIS_);
    STDMETHOD(SetPrescribed)(THIS_ DOFPrescribedMotionType MotionType, VARIANT MotionMagnitude, VARIANT InitialVelocity);
    STDMETHOD(SetSpringDamper)(THIS_ VARIANT LoadMagnitude, VARIANT StressfreeLength, VARIANT Stiffness,
      VARIANT StiffnessScale, VARIANT Damper, VARIANT DamperScale, VARIANT InitialVelocity);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaDOF,FmHasDOFsBase> signalConnector;

public:
  FmHasDOFsBase*& m_ptr; // TODO: Remove
};
