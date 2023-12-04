/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmCylJoint;


class CaCylindricJoint : public CCmdTarget
{
public:
  CaCylindricJoint(void);
  ~CaCylindricJoint(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmCylJoint* m_pCylJoint;

  DECLARE_DYNCREATE(CaCylindricJoint)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaCylindricJoint)
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
    dispidScrewRatio = 7L,
    dispidScrewTransmission = 8L,
    dispidParent = 9L,
    dispidGetEulerRotationZYX = 100L,
    dispidSetEulerRotationZYX = 101L,
    dispidGetRotationMatrix = 102L,
    dispidSetRotationMatrix = 103L,
    dispidSetPosition = 105L,
    dispidAddMasterTriad = 106L,
    dispidSetMasterArcFromJoint = 107L,
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
  double get_ScrewRatio();
  void   put_ScrewRatio(double val);
  BOOL   get_ScrewTransmission();
  void   put_ScrewTransmission(BOOL val);
  ISubAssembly* get_Parent();
  void GetEulerRotationZYX(double* rx, double* ry, double* rz);
  void SetEulerRotationZYX(double rx, double ry, double rz);
  void GetRotationMatrix(VARIANT* Array3x3);
  void SetRotationMatrix(const VARIANT FAR& Array3x3);
  void SetPosition(double x, double y, double z);
  void AddMasterTriad(ITriad* MasterTriad);
  void SetMasterArcFromJoint(ICylindricJoint* CylJoint);
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, ICylindricJoint)
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
    STDMETHOD(get_ScrewRatio)(THIS_ double* pVal);
    STDMETHOD(put_ScrewRatio)(THIS_ double val);
    STDMETHOD(get_ScrewTransmission)(THIS_ VARIANT_BOOL* pVal);
    STDMETHOD(put_ScrewTransmission)(THIS_ VARIANT_BOOL val);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(GetEulerRotationZYX)(THIS_ double* rx, double* ry, double* rz);
    STDMETHOD(SetEulerRotationZYX)(THIS_ double rx, double ry, double rz);
    STDMETHOD(GetRotationMatrix)(THIS_ VARIANT* Array3x3);
    STDMETHOD(SetRotationMatrix)(THIS_ VARIANT Array3x3);
    STDMETHOD(SetPosition)(THIS_ double x, double y, double z);
    STDMETHOD(AddMasterTriad)(THIS_ ITriad* MasterTriad);
    STDMETHOD(SetMasterArcFromJoint)(THIS_ ICylindricJoint* CylJoint);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaCylindricJoint,FmCylJoint> signalConnector;

public:
  FmCylJoint*& m_ptr; // TODO: Remove
};
