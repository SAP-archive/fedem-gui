/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmCurveSet;


class CaCurve : public CCmdTarget
{
public:
  CaCurve(void);
  ~CaCurve(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmCurveSet* m_ptr;

  DECLARE_DYNCREATE(CaCurve)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaCurve)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDescription = 1L,
    dispidBaseID = 2L,
    dispidParent = 3L,
    dispidMode = 4L,
    dispidLegend = 5L,
    dispidColor = 6L,
    dispidTimeRangeMin = 7L,
    dispidTimeRangeMax = 8L,
    dispidXAxisScale = 9L,
    dispidYAxisScale = 10L,
    dispidXAxisOffset = 11L,
    dispidYAxisOffset = 12L,
    dispidXAxisZeroAdjust = 13L,
    dispidYAxisZeroAdjust = 14L,
    dispidSymbolType = 15L,
    dispidSetResult = 100L,
    dispidGetResult = 101L,
    dispidSetResultOper = 102L,
    dispidGetResultOper = 103L,
    dispidSetCombinedCurve = 200L,
    dispidDelete = 800L
  };

  // Methods
  BSTR get_Description();
  void put_Description(LPCTSTR val);
  long get_BaseID();
  IGraph* get_Parent();
  long get_Mode();
  BSTR get_Legend();
  void put_Legend(LPCTSTR val);
  OLE_COLOR get_Color();
  void put_Color(OLE_COLOR val);
  double get_TimeRangeMin();
  void put_TimeRangeMin(double val);
  double get_TimeRangeMax();
  void put_TimeRangeMax(double val);
  double get_XAxisScale();
  void put_XAxisScale(double val);
  double get_YAxisScale();
  void put_YAxisScale(double val);
  double get_XAxisOffset();
  void put_XAxisOffset(double val);
  double get_YAxisOffset();
  void put_YAxisOffset(double val);
  BOOL get_XAxisZeroAdjust();
  void put_XAxisZeroAdjust(BOOL val);
  BOOL get_YAxisZeroAdjust();
  void put_YAxisZeroAdjust(BOOL val);
  long get_SymbolType();
  void put_SymbolType(long val);
  void SetResult(int Axis, LPCTSTR OGType, long BaseID, long UserID,
    LPCTSTR RefType, LPCTSTR DescPath);
  void GetResult(int Axis, BSTR* OGType, long* BaseID, long* UserID,
    BSTR* RefType, BSTR* DescPath);
  void SetResultOper(int Axis, LPCTSTR Oper);
  BSTR GetResultOper(int Axis);
  void SetCombinedCurve(LPCTSTR Expression, ICurve* A, ICurve* B,
    const VARIANT FAR& C, const VARIANT FAR& D, const VARIANT FAR& E);
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, ICurve)
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
    STDMETHOD(get_Parent)(THIS_ IGraph** ppObj);
    STDMETHOD(get_Mode)(THIS_ long* pVal);
    STDMETHOD(get_Legend)(THIS_ BSTR* pVal);
    STDMETHOD(put_Legend)(THIS_ BSTR val);
    STDMETHOD(get_Color)(THIS_ OLE_COLOR* pVal);
    STDMETHOD(put_Color)(THIS_ OLE_COLOR val);
    STDMETHOD(get_TimeRangeMin)(THIS_ double* pVal);
    STDMETHOD(put_TimeRangeMin)(THIS_ double val);
    STDMETHOD(get_TimeRangeMax)(THIS_ double* pVal);
    STDMETHOD(put_TimeRangeMax)(THIS_ double val);
    STDMETHOD(get_XAxisScale)(THIS_ double* pVal);
    STDMETHOD(put_XAxisScale)(THIS_ double val);
    STDMETHOD(get_YAxisScale)(THIS_ double* pVal);
    STDMETHOD(put_YAxisScale)(THIS_ double val);
    STDMETHOD(get_XAxisOffset)(THIS_ double* pVal);
    STDMETHOD(put_XAxisOffset)(THIS_ double val);
    STDMETHOD(get_YAxisOffset)(THIS_ double* pVal);
    STDMETHOD(put_YAxisOffset)(THIS_ double val);
    STDMETHOD(get_XAxisZeroAdjust)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_XAxisZeroAdjust)(THIS_ VARIANT_BOOL val);
    STDMETHOD(get_YAxisZeroAdjust)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_YAxisZeroAdjust)(THIS_ VARIANT_BOOL val);
    STDMETHOD(get_SymbolType)(THIS_ long* pVal);
    STDMETHOD(put_SymbolType)(THIS_ long val);
    STDMETHOD(SetResult)(THIS_ int Axis, BSTR OGType, long BaseID, long UserID,
      BSTR RefType, BSTR DescPath);
    STDMETHOD(GetResult)(THIS_ int Axis, BSTR* OGType, long* BaseID, long* UserID,
      BSTR* RefType, BSTR* DescPath);
    STDMETHOD(SetResultOper)(THIS_ int Axis, BSTR Oper);
    STDMETHOD(GetResultOper)(THIS_ int Axis, BSTR* pVal);
    STDMETHOD(SetCombinedCurve)(THIS_ BSTR Expression, ICurve* A, ICurve* B,
      VARIANT C, VARIANT D, VARIANT E);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaCurve,FmCurveSet> signalConnector;
};
