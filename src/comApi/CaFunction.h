/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"


class CaFunction : public CCmdTarget
{
public:
  CaFunction(void);
  ~CaFunction(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes.
  FmModelMemberBase* m_ptr;
  FunctionUsageType m_nUsage;

  DECLARE_DYNCREATE(CaFunction)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaFunction)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidFunctionType = 1L,
    dispidParameters = 2L,
    dispidArgumentObject = 3L,
    dispidArgumentDOF = 4L,
    dispidArgumentVariable = 5L,
    dispidUsage = 6L,
    dispidDescription = 7L,
    dispidBaseID = 8L,
    dispidParent = 9L,
    dispidChannelID = 10L,
    dispidSetConstant = 90L,
    dispidSetLinear = 91L,
    dispidSetSin = 100L,
    dispidSetCombinedSin = 101L,
    dispidSetPolyline = 120L,
    dispidSetPolylineFromFile = 121L,
    dispidSetMathExpression = 130L,
    dispidSetExternal = 140L,
    dispidSetJonswap = 420L,
    dispidSetArgumentSingle = 2000L,
    dispidSetArgumentRelative = 2001L,
    dispidSetArgumentScalar = 2002L,
    dispidDelete = 8000L
  };

  // Methods
  FunctionType get_FunctionType();
  BSTR get_Parameters();
  void put_Parameters(LPCTSTR val);
  VARIANT get_ArgumentObject();
  FunctionArgSingleDOFType get_ArgumentDOF();
  FunctionArgVariableType get_ArgumentVariable();
  FunctionUsageType get_Usage();
  BSTR get_Description();
  void put_Description(LPCTSTR val);
  long get_BaseID();
  ISubAssembly* get_Parent();
  long get_ChannelID();
  void SetConstant(double Value);
  void SetLinear(double Slope);
  void SetSin(double Period, double MeanValue, double Amplitude, const VARIANT FAR& MaxTime);
  void SetCombinedSin(double Period1, double Amplitude1, double Period2,
    double Amplitude2, double MeanValue, const VARIANT FAR& MaxTime);
  void SetPolyline(const VARIANT FAR& ArrayNx2, FunctionExtrapolationType Extrapolation);
  void SetPolylineFromFile(LPCTSTR FileName, const VARIANT FAR& ChannelName,
    const VARIANT FAR& ScaleFactor, const VARIANT FAR& ZeroAdjust, const VARIANT FAR& VerticalShift);
  void SetMathExpression(LPCTSTR Expression);
  void SetExternal();
  void SetJonswap(double Hs, double Tp, const VARIANT FAR& Gamma, const VARIANT FAR& N,
    const VARIANT FAR& RndSeed, const VARIANT FAR& TRangeMin, const VARIANT FAR& TRangeMax);
  void SetArgumentSingle(const FunctionArgSingleDOFType DOF, FunctionArgVariableType Val,
    const VARIANT FAR& ArgObject1, const VARIANT FAR& ArgNumber);
  void SetArgumentRelative(const FunctionArgRelativeDOFType DOF, FunctionArgVariableType Val,
    const VARIANT FAR& ArgObject1, const VARIANT FAR& ArgObject2, const VARIANT FAR& ArgNumber);
  void SetArgumentScalar(const VARIANT FAR& ArgObject1, const VARIANT FAR& ArgNumber);
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, IFunction)
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
    STDMETHOD(get_FunctionType)(THIS_ FunctionType* pVal);
    STDMETHOD(get_Parameters)(THIS_ BSTR* pVal);
    STDMETHOD(put_Parameters)(THIS_ BSTR val);
    STDMETHOD(get_ArgumentObject)(THIS_ VARIANT* pVal);
    STDMETHOD(get_ArgumentDOF)(THIS_ FunctionArgSingleDOFType* pVal);
    STDMETHOD(get_ArgumentVariable)(THIS_ FunctionArgVariableType* pVal);
    STDMETHOD(get_Usage)(THIS_ FunctionUsageType* pVal);
    STDMETHOD(get_Description)(THIS_ BSTR* pVal);
    STDMETHOD(put_Description)(THIS_ BSTR val);
    STDMETHOD(get_BaseID)(THIS_ long* pVal);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(get_ChannelID)(THIS_ long* pVal);
    STDMETHOD(SetConstant)(THIS_ double Value);
    STDMETHOD(SetLinear)(THIS_ double Slope);
    STDMETHOD(SetSin)(THIS_ double Period, double MeanValue, double Amplitude, VARIANT MaxTime);
    STDMETHOD(SetCombinedSin)(THIS_ double Period1, double Amplitude1, double Period2,
      double Amplitude2, double MeanValue, VARIANT MaxTime);
    STDMETHOD(SetPolyline)(THIS_ VARIANT ArrayNx2, FunctionExtrapolationType Extrapolation);
    STDMETHOD(SetPolylineFromFile)(THIS_ BSTR FileName, VARIANT ChannelName, VARIANT ScaleFactor,
      VARIANT ZeroAdjust, VARIANT VerticalShift);
    STDMETHOD(SetMathExpression)(THIS_ BSTR Expression);
    STDMETHOD(SetExternal)(THIS_);
    STDMETHOD(SetJonswap)(THIS_ double Hs, double Tp, VARIANT Gamma, VARIANT N,
      VARIANT RndSeed, VARIANT TRangeMin, VARIANT TRangeMax);
    STDMETHOD(SetArgumentSingle)(THIS_ FunctionArgSingleDOFType DOF, FunctionArgVariableType Val,
      VARIANT ArgObject1, VARIANT ArgNumber);
    STDMETHOD(SetArgumentRelative)(THIS_ FunctionArgRelativeDOFType DOF, FunctionArgVariableType Val,
      VARIANT ArgObject1, VARIANT ArgObject2, VARIANT ArgNumber);
    STDMETHOD(SetArgumentScalar)(THIS_ VARIANT ArgObject1, VARIANT ArgNumber);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaFunction,FmModelMemberBase> signalConnector;
};
