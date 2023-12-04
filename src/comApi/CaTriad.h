/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmTriad;


class CaTriad : public CCmdTarget
{
public:
  CaTriad(void);
  ~CaTriad(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmTriad* m_pTriad;

  DECLARE_DYNCREATE(CaTriad)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaTriad)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidX = 1L,
    dispidY = 2L,
    dispidZ = 3L,
    dispidMass = 4L,
    dispidIx = 5L,
    dispidIy = 6L,
    dispidIz = 7L,
    dispidDescription = 8L,
    dispidDOF = 9L,
    dispidReferenceCS = 10L,
    dispidBaseID = 11L,
    dispidTag = 12L,
    dispidParent = 13L,
    dispidGetEulerRotationZYX = 100L,
    dispidSetEulerRotationZYX = 101L,
    dispidGetRotationMatrix = 102L,
    dispidSetRotationMatrix = 103L,
    dispidSetMass = 104L,
    dispidSetPosition = 105L,
    dispidGetAttachedObjects = 106L,
    dispidDelete = 800L
  };

  // Methods
  double get_X();
  void   put_X(double val);
  double get_Y();
  void   put_Y(double val);
  double get_Z();
  void   put_Z(double val);
  double get_Mass();
  void   put_Mass(double val);
  double get_Ix();
  void   put_Ix(double val);
  double get_Iy();
  void   put_Iy(double val);
  double get_Iz();
  void   put_Iz(double val);
  BSTR   get_Description();
  void   put_Description(LPCTSTR val);
  IDOF*  get_DOF(long nDOFIndex);
  ReferenceCSType get_ReferenceCS();
  void   put_ReferenceCS(ReferenceCSType val);
  long   get_BaseID();
  BSTR   get_Tag();
  void   put_Tag(LPCTSTR val);
  ISubAssembly* get_Parent();
  void GetEulerRotationZYX(double* rx, double* ry, double* rz);
  void SetEulerRotationZYX(double rx, double ry, double rz);
  void GetRotationMatrix(VARIANT* Array3x3);
  void SetRotationMatrix(const VARIANT FAR& Array3x3);
  void SetMass(double Mass, double Ix, double Iy, double Iz);
  void SetPosition(double x, double y, double z);
  VARIANT GetAttachedObjects(ObjectType ObjectTypeFlags);
  void Delete();

  BEGIN_INTERFACE_PART(LocalClass, ITriad)
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
    STDMETHOD(get_X)(THIS_ double* pVal);
    STDMETHOD(put_X)(THIS_ double val);
    STDMETHOD(get_Y)(THIS_ double* pVal);
    STDMETHOD(put_Y)(THIS_ double val);
    STDMETHOD(get_Z)(THIS_ double* pVal);
    STDMETHOD(put_Z)(THIS_ double val);
    STDMETHOD(get_Mass)(THIS_ double* pVal);
    STDMETHOD(put_Mass)(THIS_ double val);
    STDMETHOD(get_Ix)(THIS_ double* pVal);
    STDMETHOD(put_Ix)(THIS_ double val);
    STDMETHOD(get_Iy)(THIS_ double* pVal);
    STDMETHOD(put_Iy)(THIS_ double val);
    STDMETHOD(get_Iz)(THIS_ double* pVal);
    STDMETHOD(put_Iz)(THIS_ double val);
    STDMETHOD(get_Description)(THIS_ BSTR* pVal);
    STDMETHOD(put_Description)(THIS_ BSTR val);
    STDMETHOD(get_DOF)(THIS_ long DOFIndex, IDOF** ppRet);
    STDMETHOD(get_ReferenceCS)(THIS_ ReferenceCSType* pVal);
    STDMETHOD(put_ReferenceCS)(THIS_ ReferenceCSType val);
    STDMETHOD(get_BaseID)(THIS_ long* pVal);
    STDMETHOD(get_Tag)(THIS_ BSTR* pVal);
    STDMETHOD(put_Tag)(THIS_ BSTR val);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(GetEulerRotationZYX)(THIS_ double* rx, double* ry, double* rz);
    STDMETHOD(SetEulerRotationZYX)(THIS_ double rx, double ry, double rz);
    STDMETHOD(GetRotationMatrix)(THIS_ VARIANT* Array3x3);
    STDMETHOD(SetRotationMatrix)(THIS_ VARIANT Array3x3);
    STDMETHOD(SetMass)(THIS_ double Mass, double Ix, double Iy, double Iz);
    STDMETHOD(SetPosition)(THIS_ double x, double y, double z);
    STDMETHOD(GetAttachedObjects)(THIS_ ObjectType ObjectTypeFlags, VARIANT* pVal);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaTriad,FmTriad> signalConnector;

public:
  FmTriad*& m_ptr; // TODO: Remove
};
