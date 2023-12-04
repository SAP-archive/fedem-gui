/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmStrainRosette;


class CaStrainRosette : public CCmdTarget
{
public:
  CaStrainRosette(void);
  ~CaStrainRosette(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmStrainRosette* m_pStrainRosette;

  DECLARE_DYNCREATE(CaStrainRosette)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaStrainRosette)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDescription = 1L,
    dispidBaseID = 2L,
    dispidElasticModulus = 4L,
    dispidPoissonRatio= 5L,
    dispidUseFEThickness = 6L,
    dispidUseFEMaterial = 7L,
    dispidStrainRosetteType = 8L,
    dispidAngleOffset = 9L,
    dispidLayerHeight = 10L,
    dispidNode1 = 11L,
    dispidNode2 = 12L,
    dispidNode3 = 13L,
    dispidNode4 = 14L,
    dispidPart = 15L,
    dispidParent = 16L,
    dispidGetReferenceDirection = 100L,
	dispidSetReferenceDirection = 101L,
    dispidStartStrainsToZero = 102L,
    dispidDelete = 800L
  };

  // Methods
  BSTR   get_Description();
  void   put_Description(LPCTSTR val);
  long   get_BaseID();
  double get_ElasticModulus();
  void   put_ElasticModulus(double val);
  double get_PoissonRatio();
  void   put_PoissonRatio(double val);
  BOOL   get_UseFEThickness();
  void   put_UseFEThickness(BOOL val);
  BOOL   get_UseFEMaterial();
  void   put_UseFEMaterial(BOOL val);
  BOOL   get_StartStrainsToZero();
  void   put_StartStrainsToZero(BOOL val);
  StrainRosetteType get_StrainRosetteType();
  void   put_StrainRosetteType(StrainRosetteType val);
  double get_AngleOffset();
  void   put_AngleOffset(double val);
  double get_LayerHeight();
  void   put_LayerHeight(double val);
  long   get_Node1();
  void   put_Node1(long val);
  long   get_Node2();
  void   put_Node2(long val);
  long   get_Node3();
  void   put_Node3(long val);
  long   get_Node4();
  void   put_Node4(long val);
  IPart* get_Part();
  ISubAssembly* get_Parent();
  void GetReferenceDirection(double* X, double* Y, double* Z);
  void SetReferenceDirection(double X, double Y, double Z);
  void Delete();

  BEGIN_INTERFACE_PART(LocalClass, IStrainRosette)
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
    STDMETHOD(get_ElasticModulus)(THIS_ double* pVal);
    STDMETHOD(put_ElasticModulus)(THIS_ double val);
    STDMETHOD(get_PoissonRatio)(THIS_ double* pVal);
    STDMETHOD(put_PoissonRatio)(THIS_ double val);
    STDMETHOD(get_UseFEThickness)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_UseFEThickness)(THIS_ VARIANT_BOOL val);
    STDMETHOD(get_UseFEMaterial)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_UseFEMaterial)(THIS_ VARIANT_BOOL val);
	STDMETHOD(get_StartStrainsToZero)(THIS_ VARIANT_BOOL* pVal);
	STDMETHOD(put_StartStrainsToZero)(THIS_ VARIANT_BOOL val);
    STDMETHOD(get_StrainRosetteType)(THIS_ StrainRosetteType* pVal);
    STDMETHOD(put_StrainRosetteType)(THIS_ StrainRosetteType val);
    STDMETHOD(get_AngleOffset)(THIS_ double* pVal);
    STDMETHOD(put_AngleOffset)(THIS_ double val);
    STDMETHOD(get_LayerHeight)(THIS_ double* pVal);
    STDMETHOD(put_LayerHeight)(THIS_ double val);
    STDMETHOD(get_Node1)(THIS_ long* pVal);
    STDMETHOD(put_Node1)(THIS_ long val);
    STDMETHOD(get_Node2)(THIS_ long* pVal);
    STDMETHOD(put_Node2)(THIS_ long val);
    STDMETHOD(get_Node3)(THIS_ long* pVal);
    STDMETHOD(put_Node3)(THIS_ long val);
    STDMETHOD(get_Node4)(THIS_ long* pVal);
    STDMETHOD(put_Node4)(THIS_ long val);
    STDMETHOD(get_Part)(THIS_ IPart** pVal);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(GetReferenceDirection)(THIS_ double* X, double* Y, double* Z);
	STDMETHOD(SetReferenceDirection)(THIS_ double X, double Y, double Z);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaStrainRosette,FmStrainRosette> signalConnector;

public:
  FmStrainRosette*& m_ptr; // TODO: Remove
};
