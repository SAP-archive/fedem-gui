/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmFreeJoint;


class CaJoint : public CCmdTarget
{
public:
  CaJoint(void);
  ~CaJoint(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmFreeJoint* m_pJoint;

  DECLARE_DYNCREATE(CaJoint)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaJoint)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidX = 1L,
    dispidY = 2L,
    dispidZ = 3L,
    dispidDescription = 4L,
    dispidDOF = 5L,
    dispidBaseID = 6L,
    dispidMasterMovedAlong = 7L,
    dispidSlaveMovedAlong = 8L,
    dispidTranslationalCoupling = 9L,
    dispidParent = 10L,
    dispidGetEulerRotationZYX = 100L,
    dispidSetEulerRotationZYX = 101L,
    dispidGetRotationMatrix = 102L,
    dispidSetRotationMatrix = 103L,
    dispidSetPosition = 105L,
    dispidGetFriction = 106L,
    dispidSetFriction = 107L,
    dispidGetMasterTriad = 108L,
    dispidSetMasterTriad = 109L,
    dispidGetSlaveTriad = 110L,
    dispidSetSlaveTriad = 111L,
    dispidGetGlobalCS = 112L,
    dispidSetGlobalCS = 113L,
    dispidDelete = 800L
  };

  // Methods
  double get_X();
  void   put_X(double val);
  double get_Y();
  void   put_Y(double val);
  double get_Z();
  void   put_Z(double val);
  BSTR   get_Description();
  void   put_Description(LPCTSTR val);
  IDOF*  get_DOF(long nDOFIndex);
  long   get_BaseID();
  BOOL   get_MasterMovedAlong();
  void   put_MasterMovedAlong(BOOL val);
  BOOL   get_SlaveMovedAlong();
  void   put_SlaveMovedAlong(BOOL val);
  SpringCouplingType get_TranslationalCoupling();
  void   put_TranslationalCoupling(SpringCouplingType val);
  ISubAssembly* get_Parent();
  void GetEulerRotationZYX(double* rx, double* ry, double* rz);
  void SetEulerRotationZYX(double rx, double ry, double rz);
  void GetRotationMatrix(VARIANT* Array3x3);
  void SetRotationMatrix(const VARIANT FAR& Array3x3);
  void SetPosition(double x, double y, double z);
  IFriction* GetFriction(long* nDOFIndex);
  void SetFriction(long nDOFIndex, IFriction* Friction);
  ITriad* GetMasterTriad();
  void SetMasterTriad(ITriad* Triad);
  ITriad* GetSlaveTriad();
  void SetSlaveTriad(ITriad* Triad);
  void GetGlobalCS(VARIANT* Array4x3);
  void SetGlobalCS(VARIANT Array4x3);
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, IJoint)
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
    STDMETHOD(get_Description)(THIS_ BSTR* pVal);
    STDMETHOD(put_Description)(THIS_ BSTR val);
    STDMETHOD(get_DOF)(THIS_ long DOFIndex, IDOF** ppRet);
    STDMETHOD(get_BaseID)(THIS_ long* pVal);
    STDMETHOD(get_MasterMovedAlong)(VARIANT_BOOL* pVal);
    STDMETHOD(put_MasterMovedAlong)(VARIANT_BOOL val);
    STDMETHOD(get_SlaveMovedAlong)(VARIANT_BOOL* pVal);
    STDMETHOD(put_SlaveMovedAlong)(VARIANT_BOOL val);
    STDMETHOD(get_TranslationalCoupling)(SpringCouplingType* pVal);
    STDMETHOD(put_TranslationalCoupling)(SpringCouplingType val);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(GetEulerRotationZYX)(THIS_ double* rx, double* ry, double* rz);
    STDMETHOD(SetEulerRotationZYX)(THIS_ double rx, double ry, double rz);
    STDMETHOD(GetRotationMatrix)(THIS_ VARIANT* Array3x3);
    STDMETHOD(SetRotationMatrix)(THIS_ VARIANT Array3x3);
    STDMETHOD(SetPosition)(THIS_ double x, double y, double z);
    STDMETHOD(GetFriction)(THIS_ long* DOFIndex, IFriction** pRet);
    STDMETHOD(SetFriction)(THIS_ long DOFIndex, IFriction* Friction);
    STDMETHOD(GetMasterTriad)(THIS_ ITriad** ppRet);
    STDMETHOD(SetMasterTriad)(THIS_ ITriad* Triad);
    STDMETHOD(GetSlaveTriad)(THIS_ ITriad** ppRet);
    STDMETHOD(SetSlaveTriad)(THIS_ ITriad* Triad);
    STDMETHOD(GetGlobalCS)(VARIANT* Array4x3);
    STDMETHOD(SetGlobalCS)(VARIANT Array4x3);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaJoint,FmFreeJoint> signalConnector;

public:
  FmFreeJoint*& m_ptr; // TODO: Remove
};
