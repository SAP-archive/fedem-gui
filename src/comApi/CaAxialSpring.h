/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmAxialSpring;


class CaAxialSpring : public CCmdTarget
{
public:
  CaAxialSpring(void);
  ~CaAxialSpring(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmAxialSpring* m_pAxialSpring;

  DECLARE_DYNCREATE(CaAxialSpring)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaAxialSpring)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDescription = 1L,
    dispidBaseID = 2L,
    dispidParent = 3L,
    dispidGetTriad1 = 100L,
    dispidSetTriad1 = 101L,
    dispidGetTriad2 = 102L,
    dispidSetTriad2 = 103L,
    dispidGetStiffnessScale = 104L,
    dispidSetStiffnessScale = 105L,
    dispidGetStiffnessFunction = 106L,
    dispidSetStiffnessFunction = 107L,
    dispidGetStiffnessCoefficient = 108L,
    dispidSetStiffnessCoefficient = 109L,
    dispidGetStressFreeLengthOrDeflection = 110L,
    dispidSetStressFreeLengthOrDeflection = 111L,
    dispidGetStressFreeLengthChange = 112L,
    dispidSetStressFreeLengthChange = 113L,
    dispidDelete = 800L
  };

  // Methods
  BSTR   get_Description();
  void   put_Description(LPCTSTR val);
  long   get_BaseID();
  ISubAssembly* get_Parent();
  ITriad* GetTriad1();
  void SetTriad1(ITriad* Triad);
  ITriad* GetTriad2();
  void SetTriad2(ITriad* Triad);
  IFunction* GetStiffnessScale();
  void SetStiffnessScale(IFunction* Function);
  IFunction* GetStiffnessFunction();
  void SetStiffnessFunction(IFunction* Function);
  double GetStiffnessCoefficient();
  void SetStiffnessCoefficient(double Value);
  double GetStressFreeLengthOrDeflection(BOOL* pIsDeflection);
  void SetStressFreeLengthOrDeflection(BOOL IsDeflection, double Value);
  IFunction* GetStressFreeLengthChange();
  void SetStressFreeLengthChange(IFunction* Function);
  void Delete();

  BEGIN_INTERFACE_PART(LocalClass, IAxialSpring)
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
    STDMETHOD(GetTriad1)(THIS_ ITriad** ppRet);
    STDMETHOD(SetTriad1)(THIS_ ITriad* Triad);
    STDMETHOD(GetTriad2)(THIS_ ITriad** ppRet);
    STDMETHOD(SetTriad2)(THIS_ ITriad* Triad);
    STDMETHOD(GetStiffnessScale)(THIS_ IFunction** ppObj);
    STDMETHOD(SetStiffnessScale)(THIS_ IFunction* Function);
    STDMETHOD(GetStiffnessFunction)(THIS_ IFunction** ppObj);
    STDMETHOD(SetStiffnessFunction)(THIS_ IFunction* Function);
    STDMETHOD(GetStiffnessCoefficient)(THIS_ double* pVal);
    STDMETHOD(SetStiffnessCoefficient)(THIS_ double Val);
    STDMETHOD(GetStressFreeLengthOrDeflection)(THIS_ VARIANT_BOOL* IsDeflection, double* pVal);
    STDMETHOD(SetStressFreeLengthOrDeflection)(THIS_ VARIANT_BOOL IsDeflection, double Value);
    STDMETHOD(GetStressFreeLengthChange)(THIS_ IFunction** ppObj);
    STDMETHOD(SetStressFreeLengthChange)(THIS_ IFunction* Function);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaAxialSpring,FmAxialSpring> signalConnector;

public:
  FmAxialSpring*& m_ptr; // TODO: Remove
};
