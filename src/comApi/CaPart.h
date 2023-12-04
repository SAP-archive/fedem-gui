/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmPart;


class CaPart : public CCmdTarget
{
public:
  CaPart(void);
  ~CaPart(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmPart* m_pGenPart;

  DECLARE_DYNCREATE(CaPart)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaPart)
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
    dispidBaseID = 9L,
    dispidParent = 10L,
    dispidIsFEPart = 20L,
    dispidFEComponentModes = 21L,
    dispidGetEulerRotationZYX = 100L,
    dispidSetEulerRotationZYX = 101L,
    dispidGetRotationMatrix = 102L,
    dispidSetRotationMatrix = 103L,
    dispidSetPosition = 104L,
    dispidSetMass = 105L,
    dispidGetCOG = 106L,
    dispidSetCOG = 107L,
    dispidGetPrincipalAxisOfInertia = 108L,
    dispidSetPrincipalAxisOfInertia = 109L,
    dispidGetStructuralDamping = 110L,
    dispidSetStructuralDamping = 111L,
    dispidGetScaling = 112L,
    dispidSetScaling = 113L,
    dispidAddTriad = 114L,
    dispidCalculateCOG = 115L,
    dispidGetBoundingBox = 116L,
    dispidFEGetNodeCount = 120L,
    dispidFEGetNodePosition = 121L,
    dispidFEGetNodeStatus = 122L,
    dispidFEGetNodeAtPoint = 123L,
    dispidFEAttach = 124L,
    dispidFECreateSpider = 125L,
    dispidSetTranslationalStiffness = 130L,
    dispidSetRotationalStiffness = 131L,
    dispidDelete = 800L,
    dispidSetPrincipalAxisOfInertiaExExy = 1000L,
    dispidSetVisualizationFile = 1001L
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
  long   get_BaseID();
  ISubAssembly* get_Parent();
  BOOL   get_IsFEPart();
  long   get_FEComponentModes();
  void   put_FEComponentModes(long val);
  void GetEulerRotationZYX(double* rx, double* ry, double* rz);
  void SetEulerRotationZYX(double rx, double ry, double rz);
  void GetRotationMatrix(VARIANT* Array3x3);
  void SetRotationMatrix(const VARIANT FAR& Array3x3);
  void SetPosition(double x, double y, double z);
  void SetMass(double Mass, double Ix, double Iy, double Iz);
  void GetCOG(double* x, double* y, double* z);
  void SetCOG(double x, double y, double z);
  void GetPrincipalAxisOfInertia(double* rx, double* ry, double* rz);
  void SetPrincipalAxisOfInertia(double rx, double ry, double rz);
  void SetPrincipalAxisOfInertiaExExy(double XAxisX, double XAxisY, double XAxisZ, 
      double XYPlaneX, double XYPlaneY, double XYPlaneZ);
  void GetStructuralDamping(double* MassProp, double* StiffProp);
  void SetStructuralDamping(double MassProp, double StiffProp);
  void GetScaling(double* StiffScale, double* MassScale);
  void SetScaling(double StiffScale, double MassScale);
  void AddTriad(ITriad* Triad);
  void CalculateCOG();
  BOOL GetBoundingBox(double* MaxX, double* MaxY, double* MaxZ,
      double* MinX, double* MinY, double* MinZ);
  long FEGetNodeCount();
  long FEGetNodePosition(long Index, double* X = NULL, double* Y = NULL, double* Z = NULL);
  long FEGetNodeAtPoint(double X, double Y, double Z, double Tolerance);
  BOOL FEAttach(IDispatch* Object);
  void FECreateSpider(long SpiderType, VARIANT NodeIndexList, ITriad* Triad);
  void SetTranslationalStiffness(double TransStiffness);
  void SetRotationalStiffness(double RotStiffness);
  void SetVisualizationFile(LPCTSTR FileName);
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, IPart)
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
    STDMETHOD(get_BaseID)(THIS_ long* pVal);
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(get_IsFEPart)(THIS_ VARIANT_BOOL* pRet);
    STDMETHOD(get_FEComponentModes)(THIS_ long* pVal);
    STDMETHOD(put_FEComponentModes)(THIS_ long val);
    STDMETHOD(GetEulerRotationZYX)(THIS_ double* rx, double* ry, double* rz);
    STDMETHOD(SetEulerRotationZYX)(THIS_ double rx, double ry, double rz);
    STDMETHOD(GetRotationMatrix)(THIS_ VARIANT* Array3x3);
    STDMETHOD(SetRotationMatrix)(THIS_ VARIANT Array3x3);
    STDMETHOD(SetPosition)(THIS_ double x, double y, double z);
    STDMETHOD(SetMass)(THIS_ double Mass, double Ix, double Iy, double Iz);
    STDMETHOD(GetCOG)(THIS_ double* x, double* y, double* z);
    STDMETHOD(SetCOG)(THIS_ double x, double y, double z);
    STDMETHOD(GetPrincipalAxisOfInertia)(THIS_ double* rx, double* ry, double* rz);
    STDMETHOD(SetPrincipalAxisOfInertia)(THIS_ double rx, double ry, double rz);
    STDMETHOD(GetStructuralDamping)(THIS_ double* MassProp, double* StiffProp);
    STDMETHOD(SetStructuralDamping)(THIS_ double MassProp, double StiffProp);
    STDMETHOD(GetScaling)(THIS_ double* StiffScale, double* MassScale);
    STDMETHOD(SetScaling)(THIS_ double StiffScale, double MassScale);
    STDMETHOD(AddTriad)(THIS_ ITriad* Triad);
    STDMETHOD(CalculateCOG)(THIS_);
    STDMETHOD(GetBoundingBox)(THIS_ double* MaxX, double* MaxY, double* MaxZ,
        double* MinX, double* MinY, double* MinZ, VARIANT_BOOL* pVal);
    STDMETHOD(FEGetNodeCount)(THIS_ long* pnVal);
    STDMETHOD(FEGetNodePosition)(THIS_ long Index, double* X, double* Y, double* Z);
    STDMETHOD(FEGetNodeStatus)(THIS_ long Index, long* pnVal);
    STDMETHOD(FEGetNodeAtPoint)(THIS_ double X, double Y, double Z, double Tolerance, long* pnVal);
    STDMETHOD(FEAttach)(THIS_ IDispatch* Object, VARIANT_BOOL* pVal);
    STDMETHOD(FECreateSpider)(THIS_ long SpiderType, VARIANT NodeIndexList, ITriad* Triad);
    STDMETHOD(SetTranslationalStiffness)(THIS_ double TransStiffness);
    STDMETHOD(SetRotationalStiffness)(THIS_ double RotStiffness);
    STDMETHOD(Delete)(THIS_);
    STDMETHOD(SetPrincipalAxisOfInertiaExExy)(THIS_ double XAxisX, double XAxisY, double XAxisZ, 
        double XYPlaneX, double XYPlaneY, double XYPlaneZ);
    STDMETHOD(SetVisualizationFile)(THIS_ BSTR FileName);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaPart,FmPart> signalConnector;

public:
  FmPart*& m_ptr; // TODO: Remove
};
