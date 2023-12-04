/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmAssemblyBase;


class CaSubAssembly : public CCmdTarget
{
public:
  CaSubAssembly(void);
  ~CaSubAssembly(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmAssemblyBase* m_pSubAssembly;

  DECLARE_DYNCREATE(CaSubAssembly)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaSubAssembly)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidItem = 0L,
    dispidX = 1L,
    dispidY = 2L,
    dispidZ = 3L,
    dispidDescription = 4L,
    dispidBaseID = 5L,
    dispidTotalMass = 6L,
    dispidTotalLength = 7L,
    dispidMovable = 8L,
    dispidModelFileName = 9L,
    dispidCount = 10L,
    dispidTag = 11L,
    dispidParent = 12L,
    dispidGetEulerRotationZYX = 100L,
    dispidSetEulerRotationZYX = 101L,
    dispidGetRotationMatrix = 102L,
    dispidSetRotationMatrix = 103L,
    dispidGetPosition = 104L,
    dispidSetPosition = 105L,
    dispidGetItem = 200L,
    dispidRemove = 201L,
    dispidRemoveAt = 202L,
    dispidClear = 203L,
    dispidGetItemType = 204L,
    dispidDelete = 800L
  };

  // Methods
  IDispatch* get_Item(long Index);
  double get_X();
  void   put_X(double val);
  double get_Y();
  void   put_Y(double val);
  double get_Z();
  void   put_Z(double val);
  BSTR   get_Description();
  void   put_Description(LPCTSTR val);
  long   get_BaseID();
  double get_TotalMass();
  double get_TotalLength();
  BOOL   get_Movable();
  BSTR   get_ModelFileName();
  void   put_ModelFileName(LPCTSTR val);
  long   get_Count();
  BSTR   get_Tag();
  void   put_Tag(LPCTSTR val);
  ISubAssembly* get_Parent();
  void GetEulerRotationZYX(double* rx, double* ry, double* rz, BOOL Global);
  void SetEulerRotationZYX(double rx, double ry, double rz, BOOL Global);
  void GetRotationMatrix(VARIANT* Array3x3, BOOL Global);
  void SetRotationMatrix(const VARIANT FAR& Array3x3, BOOL Global);
  void GetPosition(double* x, double* y, double* z, BOOL Global);
  void SetPosition(double x, double y, double z, BOOL Global);
  IDispatch* GetItem(long Index);
  BSTR GetItemType(long Index);
  void Remove(IDispatch* Child);
  void RemoveAt(long Index);
  void Clear();
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, ISubAssembly)
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
    STDMETHOD(get_Item)(THIS_ long Index, IDispatch** ppObj);
    STDMETHOD(get_X)(THIS_ double* pVal);
    STDMETHOD(put_X)(THIS_ double val);
    STDMETHOD(get_Y)(THIS_ double* pVal);
    STDMETHOD(put_Y)(THIS_ double val);
    STDMETHOD(get_Z)(THIS_ double* pVal);
    STDMETHOD(put_Z)(THIS_ double val);
    STDMETHOD(get_Description)(THIS_ BSTR* pVal);
    STDMETHOD(put_Description)(THIS_ BSTR val);
    STDMETHOD(get_BaseID)(THIS_ long* pVal);
    STDMETHOD(get_TotalMass)(THIS_ double* pVal);
    STDMETHOD(get_TotalLength)(THIS_ double* pVal);
    STDMETHOD(get_Movable)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(get_ModelFileName)(THIS_ BSTR* pVal);
    STDMETHOD(put_ModelFileName)(THIS_ BSTR val);
    STDMETHOD(get_Count)(THIS_ long* pVal);
    STDMETHOD(get_Tag)(THIS_ BSTR* pVal);
    STDMETHOD(put_Tag)(THIS_ BSTR val);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(GetEulerRotationZYX)(THIS_ double* rx, double* ry, double* rz, VARIANT_BOOL Global);
    STDMETHOD(SetEulerRotationZYX)(THIS_ double rx, double ry, double rz, VARIANT_BOOL Global);
    STDMETHOD(GetRotationMatrix)(THIS_ VARIANT* Array3x3, VARIANT_BOOL Global);
    STDMETHOD(SetRotationMatrix)(THIS_ VARIANT Array3x3, VARIANT_BOOL Global);
    STDMETHOD(GetPosition)(THIS_ double* x, double* y, double* z, VARIANT_BOOL Global);
    STDMETHOD(SetPosition)(THIS_ double x, double y, double z, VARIANT_BOOL Global);
    STDMETHOD(GetItem)(THIS_ long Index, IDispatch** ppObj);
    STDMETHOD(GetItemType)(THIS_ long Index, BSTR* pVal);
    STDMETHOD(Remove)(THIS_ IDispatch* Child);
    STDMETHOD(RemoveAt)(THIS_ long Index);
    STDMETHOD(Clear)(THIS_);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaSubAssembly,FmAssemblyBase> signalConnector;

public:
  FmAssemblyBase*& m_ptr; // TODO: Remove
};
