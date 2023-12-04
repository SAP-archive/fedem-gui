/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmGraph;


class CaGraph : public CCmdTarget
{
public:
  CaGraph(void);
  ~CaGraph(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmGraph* m_ptr;

  DECLARE_DYNCREATE(CaGraph)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaGraph)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidItem = 0L,
    dispidDescription = 1L,
    dispidBaseID = 2L,
    dispidTitle = 3L,
    dispidSubTitle = 4L,
    dispidXAxisLabel = 5L,
    dispidYAxisLabel = 6L,
    dispidGridType = 7L,
    dispidShowLegend = 8L,
    dispidAutoScaleFlag= 9L,
    dispidUseTimeRange = 10L,
    dispidTimeRangeMin = 11L,
    dispidTimeRangeMax = 12L,
    dispidXAxisScaleMin = 13L,
    dispidXAxisScaleMax = 14L,
    dispidYAxisScaleMin = 15L,
    dispidYAxisScaleMax = 16L,
    dispidIsFunctionPreview = 17L,
    dispidIsBeamDiagram = 18L,
    dispidCreateCurve = 100L,
    dispidGetItem = 101L,
    dispidGetCount = 102L,
    dispidDelete = 800L
  };

  // Methods
  ICurve* get_Item(long Index);
  BSTR get_Description();
  void put_Description(LPCTSTR val);
  long get_BaseID();
  BSTR get_Title();
  void put_Title(LPCTSTR val);
  BSTR get_SubTitle();
  void put_SubTitle(LPCTSTR val);
  BSTR get_XAxisLabel();
  void put_XAxisLabel(LPCTSTR val);
  BSTR get_YAxisLabel();
  void put_YAxisLabel(LPCTSTR val);
  long get_GridType();
  void put_GridType(long val);
  BOOL get_ShowLegend();
  void put_ShowLegend(BOOL val);
  BOOL get_AutoScaleFlag();
  void put_AutoScaleFlag(BOOL val);
  BOOL get_UseTimeRange();
  void put_UseTimeRange(BOOL val);
  double get_TimeRangeMin();
  void put_TimeRangeMin(double val);
  double get_TimeRangeMax();
  void put_TimeRangeMax(double val);
  double get_XAxisScaleMin();
  void put_XAxisScaleMin(double val);
  double get_XAxisScaleMax();
  void put_XAxisScaleMax(double val);
  double get_YAxisScaleMin();
  void put_YAxisScaleMin(double val);
  double get_YAxisScaleMax();
  void put_YAxisScaleMax(double val);
  BOOL get_IsFunctionPreview();
  BOOL get_IsBeamDiagram();
  ICurve* CreateCurve();
  ICurve* GetItem(long Index);
  long GetCount();
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, IGraph)
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
    STDMETHOD(get_Item)(THIS_ long Index, ICurve** ppObj);
    STDMETHOD(get_Description)(THIS_ BSTR* pVal);
    STDMETHOD(put_Description)(THIS_ BSTR val);
    STDMETHOD(get_BaseID)(THIS_ long* pVal);
    STDMETHOD(get_Title)(THIS_ BSTR* pVal);
    STDMETHOD(put_Title)(THIS_ BSTR val);
    STDMETHOD(get_SubTitle)(THIS_ BSTR* pVal);
    STDMETHOD(put_SubTitle)(THIS_ BSTR val);
    STDMETHOD(get_XAxisLabel)(THIS_ BSTR* pVal);
    STDMETHOD(put_XAxisLabel)(THIS_ BSTR val);
    STDMETHOD(get_YAxisLabel)(THIS_ BSTR* pVal);
    STDMETHOD(put_YAxisLabel)(THIS_ BSTR val);
    STDMETHOD(get_GridType)(THIS_ long* pVal);
    STDMETHOD(put_GridType)(THIS_ long val);
    STDMETHOD(get_ShowLegend)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_ShowLegend)(THIS_ VARIANT_BOOL val);
    STDMETHOD(get_AutoScaleFlag)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_AutoScaleFlag)(THIS_ VARIANT_BOOL val);
    STDMETHOD(get_UseTimeRange)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_UseTimeRange)(THIS_ VARIANT_BOOL val);
    STDMETHOD(get_TimeRangeMin)(THIS_ double* pVal);
    STDMETHOD(put_TimeRangeMin)(THIS_ double val);
    STDMETHOD(get_TimeRangeMax)(THIS_ double* pVal);
    STDMETHOD(put_TimeRangeMax)(THIS_ double val);
    STDMETHOD(get_XAxisScaleMin)(THIS_ double* pVal);
    STDMETHOD(put_XAxisScaleMin)(THIS_ double val);
    STDMETHOD(get_XAxisScaleMax)(THIS_ double* pVal);
    STDMETHOD(put_XAxisScaleMax)(THIS_ double val);
    STDMETHOD(get_YAxisScaleMin)(THIS_ double* pVal);
    STDMETHOD(put_YAxisScaleMin)(THIS_ double val);
    STDMETHOD(get_YAxisScaleMax)(THIS_ double* pVal);
    STDMETHOD(put_YAxisScaleMax)(THIS_ double val);
    STDMETHOD(get_IsFunctionPreview)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(get_IsBeamDiagram)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(CreateCurve)(THIS_ ICurve** ppObj);
    STDMETHOD(GetItem)(THIS_ long Index, ICurve** ppObj);
    STDMETHOD(GetCount)(THIS_ long* pVal);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaGraph,FmGraph> signalConnector;
};
