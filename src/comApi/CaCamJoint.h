/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmCamJoint;


class CaCamJoint : public CCmdTarget
{
public:
  CaCamJoint(void);
  ~CaCamJoint(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmCamJoint* m_pCamJoint;

  DECLARE_DYNCREATE(CaCamJoint)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaCamJoint)
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
    dispidThickness = 7L,
    dispidWidth = 8L,
    dispidUseRadialStiffness = 9L,
    dispidParent = 10L,
    dispidGetEulerRotationZYX = 100L,
    dispidSetEulerRotationZYX = 101L,
    dispidGetRotationMatrix = 102L,
    dispidSetRotationMatrix = 103L,
    dispidSetPosition = 105L,
    dispidGetFriction = 106L,
    dispidSetFriction = 107L,
    dispidAddMasterTriad = 108L,
    dispidSetMasterArcFromJoint = 109L,
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
  double get_Thickness();
  void   put_Thickness(double val);
  double get_Width();
  void   put_Width(double val);
  BOOL   get_UseRadialStiffness();
  void   put_UseRadialStiffness(BOOL val);
  ISubAssembly* get_Parent();
  void GetEulerRotationZYX(double* rx, double* ry, double* rz);
  void SetEulerRotationZYX(double rx, double ry, double rz);
  void GetRotationMatrix(VARIANT* Array3x3);
  void SetRotationMatrix(const VARIANT FAR& Array3x3);
  void SetPosition(double x, double y, double z);
  IFriction* GetFriction(long* nDOFIndex);
  void SetFriction(long nDOFIndex, IFriction* Friction);
  void AddMasterTriad(ITriad* MasterTriad);
  void SetMasterArcFromJoint(ICamJoint* CamJoint);
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, ICamJoint)
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
    STDMETHOD(get_Thickness)(THIS_ double* pVal);
    STDMETHOD(put_Thickness)(THIS_ double val);
    STDMETHOD(get_Width)(THIS_ double* pVal);
    STDMETHOD(put_Width)(THIS_ double val);
    STDMETHOD(get_UseRadialStiffness)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_UseRadialStiffness)(THIS_ VARIANT_BOOL val);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(GetEulerRotationZYX)(THIS_ double* rx, double* ry, double* rz);
    STDMETHOD(SetEulerRotationZYX)(THIS_ double rx, double ry, double rz);
    STDMETHOD(GetRotationMatrix)(THIS_ VARIANT* Array3x3);
    STDMETHOD(SetRotationMatrix)(THIS_ VARIANT Array3x3);
    STDMETHOD(SetPosition)(THIS_ double x, double y, double z);
    STDMETHOD(GetFriction)(THIS_ long* DOFIndex, IFriction** pRet);
    STDMETHOD(SetFriction)(THIS_ long DOFIndex, IFriction* Friction);
    STDMETHOD(AddMasterTriad)(THIS_ ITriad* MasterTriad);
    STDMETHOD(SetMasterArcFromJoint)(THIS_ ICamJoint* CamJoint);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaCamJoint,FmCamJoint> signalConnector;

public:
  FmCamJoint*& m_ptr; // TODO: Remove
};
