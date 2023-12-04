/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"


class CaSolverManager : public CCmdTarget
{
public:
  CaSolverManager(void);
  ~CaSolverManager(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  DECLARE_DYNCREATE(CaSolverManager)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaSolverManager)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidStartTime = 0L,
    dispidStopTime = 1L,
    dispidTimeIncrement = 2L,
    dispidQuasiStatic = 3L,
    dispidInitEquil = 4L,
    dispidGetFRSFileNames = 10L,
    dispidSolveDynamics = 100L,
    dispidSolveAll = 101L,
    dispidSolveEvents = 102L,
    dispidEraseSimulationResults = 103L,
    dispidEraseEventResults = 104L,
    dispidWriteSolverInputFile = 105L
  };

  double get_StartTime();
  void   put_StartTime(double val);
  double get_StopTime();
  void   put_StopTime(double val);
  double get_TimeIncrement();
  void   put_TimeIncrement(double val);
  BOOL   get_QuasiStatic();
  void   put_QuasiStatic(BOOL val);
  BOOL   get_InitEquil();
  void   put_InitEquil(BOOL val);

  BSTR GetFRSFileNames();
  void SolveDynamics();
  void SolveAll();
  void SolveEvents();
  void EraseSimulationResults();
  void EraseEventResults();
  BOOL WriteSolverInputFile(LPCTSTR FileName);

  BEGIN_INTERFACE_PART(LocalClass, ISolverManager)
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
        STDMETHOD(get_StartTime)(THIS_ double* pVal);
        STDMETHOD(put_StartTime)(THIS_ double Val);
        STDMETHOD(get_StopTime)(THIS_ double* pVal);
        STDMETHOD(put_StopTime)(THIS_ double Val);
        STDMETHOD(get_TimeIncrement)(THIS_ double* pVal);
        STDMETHOD(put_TimeIncrement)(THIS_ double Val);
        STDMETHOD(get_QuasiStatic)(THIS_ VARIANT_BOOL* pVal);
        STDMETHOD(put_QuasiStatic)(THIS_ VARIANT_BOOL Val);
        STDMETHOD(get_InitEquil)(THIS_ VARIANT_BOOL* pVal);
        STDMETHOD(put_InitEquil)(THIS_ VARIANT_BOOL Val);
	STDMETHOD(GetFRSFileNames)(THIS_ BSTR* pVal);
	STDMETHOD(SolveDynamics)(THIS_);
	STDMETHOD(SolveAll)(THIS_);
	STDMETHOD(SolveEvents)(THIS_);
	STDMETHOD(EraseSimulationResults)(THIS_);
	STDMETHOD(EraseEventResults)(THIS_);
	STDMETHOD(WriteSolverInputFile)(THIS_ BSTR FileName, VARIANT_BOOL* pVal);
  END_INTERFACE_PART(LocalClass)
};
