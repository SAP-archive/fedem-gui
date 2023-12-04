/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#include "CaCommonHeaders.h"
#include "CaSignalConnector.h"

class FmBeamProperty;


class CaCrossSection : public CCmdTarget
{
public:
  CaCrossSection(void);
  ~CaCrossSection(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmBeamProperty* m_pCrossSection;

  DECLARE_DYNCREATE(CaCrossSection)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaCrossSection)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidDescription = 1L,
    dispidBaseID = 2L,
    dispidParent = 3L,
    dispidGetCrossSectionType = 100L,
    dispidSetCrossSectionType = 101L,
    dispidGetMaterial = 102L,
    dispidSetMaterial = 103L,
    dispidGetShearCenterOffset = 104L,
    dispidSetShearCenterOffset = 105L,
    dispidGetPipeDiameters = 120L,
    dispidSetPipeDiameters = 121L,
    dispidGetPipeDependentProperties = 122L,
    dispidSetPipeDependentProperties = 123L,
    dispidGetPipeShearReductionFactors = 124L,
    dispidSetPipeShearReductionFactors = 125L,
    dispidGetGenericGeometricProperties = 140L,
    dispidSetGenericGeometricProperties = 141L,
    dispidGetGenericMomentOfInertia = 142L,
    dispidSetGenericMomentOfInertia = 143L,
    dispidGetGenericShearStiffness = 144L,
    dispidSetGenericShearStiffness = 145L,
    dispidGetHydroBuoyancyAndDragDiameters = 700L,
    dispidSetHydroBuoyancyAndDragDiameters = 701L,
    dispidGetHydrodynamicCoefficients = 702L,
    dispidSetHydrodynamicCoefficients = 703L,
    dispidGetHydrodynamicAxialCoefficients = 704L,
    dispidSetHydrodynamicAxialCoefficients = 705L,
    dispidGetHydroSpinDragCoefficient = 706L,
    dispidSetHydroSpinDragCoefficient = 707L,
    dispidGetHydroInternalFluidDiameter = 708L,
    dispidSetHydroInternalFluidDiameter = 709L,
    dispidDelete = 800L
  };

  // Methods
  BSTR   get_Description();
  void   put_Description(LPCTSTR val);
  long   get_BaseID();
  ISubAssembly* get_Parent();
  CrossSectionType GetCrossSectionType();
  void SetCrossSectionType(CrossSectionType CSType);
  IMaterial* GetMaterial();
  void SetMaterial(IMaterial* Material);
  void GetShearCenterOffset(double* sy, double* sz);
  void SetShearCenterOffset(double sy, double sz);
  void GetPipeDiameters(double* OuterDiameter, double* InnerDiameter);
  void SetPipeDiameters(double OuterDiameter, double InnerDiameter);
  void GetPipeDependentProperties(double* A, double* Iy, double* Iz, double* Ip);
  void SetPipeDependentProperties(double A, double Iy, double Iz, double Ip);
  void GetPipeShearReductionFactors(double* ky, double* kz);
  void SetPipeShearReductionFactors(double ky, double kz);
  void GetGenericGeometricProperties(double* EA, double* EIyy, double* EIzz, double* GIt, double* mL, double* rhoIp);
  void SetGenericGeometricProperties(double EA, double EIyy, double EIzz, double GIt, double mL, double rhoIp);
  void GetGenericMomentOfInertia(double* Ix, double* Iy, double* Iz);
  void SetGenericMomentOfInertia(double Ix, double Iy, double Iz);
  void GetGenericShearStiffness(double* GAsy, double* GAsz);
  void SetGenericShearStiffness(double GAsy, double GAsz);
  void GetHydroBuoyancyAndDragDiameters(double* Db, double* Dd);
  void SetHydroBuoyancyAndDragDiameters(double Db, double Dd);
  void GetHydrodynamicCoefficients(double* Cd, double* Ca, double* Cm);
  void SetHydrodynamicCoefficients(double Cd, double Ca, double Cm);
  void GetHydrodynamicAxialCoefficients(double* Cd_axial, double* Ca_axial, double* Cm_axial);
  void SetHydrodynamicAxialCoefficients(double Cd_axial, double Ca_axial, double Cm_axial);
  double GetHydroSpinDragCoefficient();
  void SetHydroSpinDragCoefficient(double Cd_spin);
  double GetHydroInternalFluidDiameter();
  void SetHydroInternalFluidDiameter(double Di);
  void Delete();


  BEGIN_INTERFACE_PART(LocalClass, ICrossSection)
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
    STDMETHOD(get_Parent)(THIS_ ISubAssembly** ppObj);
    STDMETHOD(GetCrossSectionType)(THIS_ CrossSectionType* pRet);
    STDMETHOD(SetCrossSectionType)(THIS_ CrossSectionType CSType);
    STDMETHOD(GetMaterial)(THIS_ IMaterial** ppRet);
    STDMETHOD(SetMaterial)(THIS_ IMaterial* Material);
    STDMETHOD(GetShearCenterOffset)(THIS_ double* sy, double* sz);
    STDMETHOD(SetShearCenterOffset)(THIS_ double sy, double sz);
    STDMETHOD(GetPipeDiameters)(THIS_ double* OuterDiameter, double* InnerDiameter);
    STDMETHOD(SetPipeDiameters)(THIS_ double OuterDiameter, double InnerDiameter);
    STDMETHOD(GetPipeDependentProperties)(THIS_ double* A, double* Iy, double* Iz, double* Ip);
    STDMETHOD(SetPipeDependentProperties)(THIS_ double A, double Iy, double Iz, double Ip);
    STDMETHOD(GetPipeShearReductionFactors)(THIS_ double* ky, double* kz);
    STDMETHOD(SetPipeShearReductionFactors)(THIS_ double ky, double kz);
    STDMETHOD(GetGenericGeometricProperties)(THIS_ double* EA, double* EIyy, double* EIzz, double* GIt, double* mL, double* rhoIp);
    STDMETHOD(SetGenericGeometricProperties)(THIS_ double EA, double EIyy, double EIzz, double GIt, double mL, double rhoIp);
    STDMETHOD(GetGenericMomentOfInertia)(THIS_ double* Ix, double* Iy, double* Iz);
    STDMETHOD(SetGenericMomentOfInertia)(THIS_ double Ix, double Iy, double Iz);
    STDMETHOD(GetGenericShearStiffness)(THIS_ double* GAsy, double* GAsz);
    STDMETHOD(SetGenericShearStiffness)(THIS_ double GAsy, double GAsz);
    STDMETHOD(GetHydroBuoyancyAndDragDiameters)(THIS_ double* Db, double* Dd);
    STDMETHOD(SetHydroBuoyancyAndDragDiameters)(THIS_ double Db, double Dd);
    STDMETHOD(GetHydrodynamicCoefficients)(THIS_ double* Cd, double* Ca, double* Cm);
    STDMETHOD(SetHydrodynamicCoefficients)(THIS_ double Cd, double Ca, double Cm);
    STDMETHOD(GetHydrodynamicAxialCoefficients)(THIS_ double* Cd_axial, double* Ca_axial, double* Cm_axial);
    STDMETHOD(SetHydrodynamicAxialCoefficients)(THIS_ double Cd_axial, double Ca_axial, double Cm_axial);
    STDMETHOD(GetHydroSpinDragCoefficient)(THIS_ double* Cd_spin);
    STDMETHOD(SetHydroSpinDragCoefficient)(THIS_ double Cd_spin);
    STDMETHOD(GetHydroInternalFluidDiameter)(THIS_ double* Di);
    STDMETHOD(SetHydroInternalFluidDiameter)(THIS_ double Di);
    STDMETHOD(Delete)(THIS_);
  END_INTERFACE_PART(LocalClass)

private:
  // Signal Receiver
  CaSignalConnector<CaCrossSection,FmBeamProperty> signalConnector;

public:
  FmBeamProperty*& m_ptr; // TODO: Remove
};
