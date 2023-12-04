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
class FmModelMemberBase;
class FaMat34;
class FaMat33;


class CaApplication : public CCmdTarget
{
public:
  CaApplication(void);
  ~CaApplication(void);

  virtual void OnFinalRelease()
  {
    CCmdTarget::OnFinalRelease();
  }

  // Attributes
  FmAssemblyBase* m_pCurrentSubAssembly;

  DECLARE_DYNCREATE(CaApplication)
  DECLARE_MESSAGE_MAP()
  DECLARE_OLECREATE(CaApplication)
  DECLARE_DISPATCH_MAP()
  DECLARE_INTERFACE_MAP()

  enum
  {
    dispidItem = 0L,
    dispidExePath = 1L,
    dispidModelFileName = 2L,
    dispidCount = 3L,
    dispidSimulationEvents = 10L,
    dispidSelection = 11L,
    dispidSolvers = 12L,
    dispidSeaEnvironment = 20L,
    dispidOpen = 100L,
    dispidSave = 101L,
    dispidSaveAs = 102L,
    dispidClose = 103L,
    dispidExit = 104L,
    dispidShow = 105L,
    dispidCreateTriad = 200L,
    dispidCreateJoint = 201L,
    dispidCreateCamJoint = 202L,
    dispidCreateCylindricJoint = 203L,
    dispidCreatePart = 204L,
    dispidCreateBeam = 205L,
    dispidCreateFunction = 206L,
    dispidCreateStrainRosette = 207L,
    dispidCreateCrossSection = 210L,
    dispidCreateMaterial = 211L,
    dispidCreateFriction = 212L,
    dispidCreateAxialSpring = 220L,
    dispidCreateAxialDamper = 221L,
    dispidCreateResultExtractor = 250L,
    dispidCreateSubAssembly = 300L,
    dispidSetCurrentSubAssembly = 301L,
    dispidCreateUserDefinedElement = 302L,
    dispidCreateGenericObject = 303L,
    dispidCreateVesselMotion = 304L,
    dispidCreateMooringLine = 305L,
    dispidGetCount = 500L,
    dispidGetItem = 501L,
    dispidFindByBaseID = 502L,
    dispidFindByDescription = 503L,
    dispidRemove = 504L,
    dispidAttachToGround = 510L,
    dispidLoadFEPart = 511L,
    dispidGetItemType = 512L,
    dispidGetFmObject = 700L
  };

  // Methods
  IDispatch* get_Item(long Index);
  BSTR get_ExePath();
  BSTR get_ModelFileName();
  long get_Count();
  ISimulationEventManager* get_SimulationEvents();
  ISelectionManager* get_Selection();
  ISolverManager* get_Solvers();
  ISeaEnvironment* get_SeaEnvironment();
  BOOL Open(LPCTSTR pszFileName, BOOL bLoadLinks);
  BOOL Save();
  BOOL SaveAs(LPCTSTR pszFileName, BOOL bSaveResults, BOOL bSaveReducedParts);
  BOOL Close();
  void Exit();
  void Show(BOOL ShowWindow);
  ITriad* CreateTriad(double x, double y, double z, 
    const VARIANT FAR& rx, const VARIANT FAR& ry, const VARIANT FAR& rz, 
    const VARIANT FAR& Desc);
  IJoint* CreateJoint(ITriad* MasterTriad, ITriad* SlaveTriad, 
    const VARIANT FAR& Desc);
  ICamJoint* CreateCamJoint(ITriad* SlaveTriad, const VARIANT FAR& Desc);
  ICylindricJoint* CreateCylindricJoint(ITriad* SlaveTriad, const VARIANT FAR& Desc);
  IPart* CreatePart(double x, double y, double z, 
    const VARIANT FAR& rx, const VARIANT FAR& ry, const VARIANT FAR& rz, 
    const VARIANT FAR& Desc);
  IBeam* CreateBeam(ITriad* Triad1, ITriad* Triad2, const VARIANT FAR& CrossSection,
      const VARIANT FAR& Desc);
  IFunction* CreateFunction(FunctionUsageType Usage, const VARIANT FAR& Desc);
  IStrainRosette* CreateStrainRosette(StrainRosetteType SRType, IPart* Part, long Node1, long Node2, long Node3, long Node4,
      const VARIANT FAR& Desc);
  ICrossSection* CreateCrossSection(CrossSectionType CSType, IMaterial* Material,
      const VARIANT FAR& Desc);
  IMaterial* CreateMaterial(double Rho, double E, double nu, const VARIANT FAR& Desc);
  IFriction* CreateFriction(FrictionType FricType, double PrestressForce, double CoulombCoefficient, 
      double StribeckMagnitude, double CriticalStribeckSpeed,
      const VARIANT FAR& Desc);
  IAxialSpring* CreateAxialSpring(ITriad* Triad1, ITriad* Triad2, 
    const VARIANT FAR& Stiffness, const VARIANT FAR& Desc);
  IAxialDamper* CreateAxialDamper(ITriad* Triad1, ITriad* Triad2, 
    const VARIANT FAR& Damper, const VARIANT FAR& Desc);
  IResultExtractor* CreateResultExtractor(LPCTSTR FRSFileNames);
  ISubAssembly* CreateSubAssembly(SubAssemblyType SAType, const VARIANT FAR& x, const VARIANT FAR& y, const VARIANT FAR& z, 
      const VARIANT FAR& rx, const VARIANT FAR& ry, const VARIANT FAR& rz, const VARIANT FAR& Desc);
  void SetCurrentSubAssembly(const VARIANT FAR& SubAssembly);
  IUserDefinedElement* CreateUserDefinedElement(long ElementType, const VARIANT FAR& Desc);
  IGenericObject* CreateGenericObject(LPCTSTR ObjectType, LPCTSTR ObjectDefinition, const VARIANT FAR& Desc);
  IVesselMotion* CreateVesselMotion(const VARIANT FAR& Desc);
  BOOL CreateMooringLine(ITriad* Triad1, ITriad* Triad2, double Length, double NumSegments, long ElementType);
  long GetCount(BOOL Recursive);
  IDispatch* GetItem(long Index, BOOL Recursive);
  IDispatch* FindByBaseID(long BaseID);
  IDispatch* FindByDescription(LPCTSTR UserDescription);
  void Remove(IDispatch* Child, BOOL Recursive);
  void AttachToGround(ITriad* Triad);
  IPart* LoadFEPart(LPCTSTR FileName, BOOL RelativePath);
  BSTR GetItemType(long Index, BOOL Recursive);
  IFmObject* GetFmObject(IDispatch* Object);

  BEGIN_INTERFACE_PART(LocalClass, IApplication)
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
    STDMETHOD(get_ExePath)(THIS_ BSTR* pVal);
    STDMETHOD(get_ModelFileName)(THIS_ BSTR* pVal);
    STDMETHOD(get_Count)(THIS_ long* pVal);
    STDMETHOD(get_SimulationEvents)(THIS_ ISimulationEventManager** ppRet);
    STDMETHOD(get_Selection)(THIS_ ISelectionManager** ppRet);
    STDMETHOD(get_Solvers)(THIS_ ISolverManager** ppRet);
    STDMETHOD(get_SeaEnvironment)(THIS_ ISeaEnvironment** ppRet);
    STDMETHOD(Open)(THIS_ BSTR FileName, VARIANT_BOOL LoadLinks, VARIANT_BOOL* pbRet);
    STDMETHOD(Save)(THIS_ VARIANT_BOOL* pbRet);
    STDMETHOD(SaveAs)(THIS_ BSTR FileName, VARIANT_BOOL SaveResults, VARIANT_BOOL SaveReducedParts, VARIANT_BOOL* pbRet);
    STDMETHOD(Close)(THIS_ VARIANT_BOOL* pbRet);
    STDMETHOD(Exit)(THIS);
    STDMETHOD(Show)(THIS_ VARIANT_BOOL ShowWindow);
    STDMETHOD(CreateTriad)(THIS_ double x, double y, double z, 
      VARIANT rx, VARIANT ry, VARIANT rz, VARIANT Desc, ITriad** ppTriad);
    STDMETHOD(CreateJoint)(THIS_ ITriad* MasterTriad, ITriad* SlaveTriad,
      VARIANT Desc, IJoint** ppJoint);
    STDMETHOD(CreateCamJoint)(THIS_ ITriad* SlaveTriad, VARIANT Desc,
      ICamJoint** ppCamJoint);
    STDMETHOD(CreateCylindricJoint)(THIS_ ITriad* SlaveTriad, VARIANT Desc, 
      ICylindricJoint** ppCylindricJoint);
    STDMETHOD(CreatePart)(THIS_ double x, double y, double z, 
      VARIANT rx, VARIANT ry, VARIANT rz, VARIANT Desc, IPart** ppPart);
    STDMETHOD(CreateBeam)(THIS_ ITriad* Triad1, ITriad* Triad2, VARIANT CrossSection,
      VARIANT Desc, IBeam** ppBeam);
    STDMETHOD(CreateFunction)(THIS_ FunctionUsageType Usage, VARIANT Desc, IFunction** ppFunction);
    STDMETHOD(CreateStrainRosette)(THIS_ StrainRosetteType SRType, IPart* Part, long Node1, long Node2, long Node3, long Node4,
      VARIANT Desc, IStrainRosette** ppStrainRosette);
    STDMETHOD(CreateCrossSection)(THIS_ CrossSectionType CSType, IMaterial* Material,
      VARIANT Desc, ICrossSection** ppCrossSection);
    STDMETHOD(CreateMaterial)(THIS_ double Rho, double E, double nu,
      VARIANT Desc, IMaterial** ppMaterial);
    STDMETHOD(CreateFriction)(THIS_ FrictionType FricType, double PrestressForce, double CoulombCoefficient, 
          double StribeckMagnitude, double CriticalStribeckSpeed, VARIANT Desc, IFriction** ppFriction);
    STDMETHOD(CreateAxialSpring)(THIS_ ITriad* Triad1, ITriad* Triad2, VARIANT Stiffness,
          VARIANT Desc, IAxialSpring** ppAxialSpring);
    STDMETHOD(CreateAxialDamper)(THIS_ ITriad* Triad1, ITriad* Triad2, VARIANT Damper,
          VARIANT Desc, IAxialDamper** ppAxialDamper);
	  STDMETHOD(CreateResultExtractor)(THIS_ BSTR FRSFileNames, IResultExtractor** ppResultExtractor);
    STDMETHOD(CreateSubAssembly)(THIS_ SubAssemblyType SAType, VARIANT x, VARIANT y, VARIANT z, 
          VARIANT rx, VARIANT ry, VARIANT rz, VARIANT Desc, ISubAssembly** ppSubAssembly);
    STDMETHOD(SetCurrentSubAssembly)(THIS_ VARIANT SubAssembly);
    STDMETHOD(CreateUserDefinedElement)(THIS_ long ElementType, VARIANT Desc, IUserDefinedElement** ppUserDefinedElement);
    STDMETHOD(CreateGenericObject)(THIS_ BSTR ObjectType, BSTR ObjectDefinition, 
          VARIANT Desc, IGenericObject** ppGenericObject);
    STDMETHOD(CreateVesselMotion)(VARIANT Desc, IVesselMotion** ppVesselMotion);
    STDMETHOD(CreateMooringLine)(THIS_ ITriad* Triad1, ITriad* Triad2, double Length, double NumSegments, long ElementType, VARIANT_BOOL* pbRet);
    STDMETHOD(GetCount)(THIS_ VARIANT_BOOL Recursive, long* pnVal);
    STDMETHOD(GetItem)(THIS_ long Index, VARIANT_BOOL Recursive, IDispatch** ppObj);
    STDMETHOD(GetItemType)(THIS_ long Index, VARIANT_BOOL Recursive, BSTR* pVal);
    STDMETHOD(FindByBaseID)(THIS_ long BaseID, IDispatch** ppRet);
    STDMETHOD(FindByDescription)(THIS_ BSTR UserDescription, IDispatch** ppRet);
    STDMETHOD(Remove)(THIS_ IDispatch* Child, VARIANT_BOOL Recursive);
    STDMETHOD(AttachToGround)(THIS_ ITriad* Triad);
    STDMETHOD(LoadFEPart)(THIS_ BSTR FileName, VARIANT_BOOL RelativePath, IPart** ppRet);
    STDMETHOD(GetFmObject)(THIS_ IDispatch* Object, IFmObject** ppRet);
  END_INTERFACE_PART(LocalClass)


  // Utilities
public:
  static void CreateSafeArray(VARIANT* Array3x3, const FaMat33& m);
  static void CreateSafeArray(VARIANT* Array4x3, const FaMat34& m);
  static void GetFromSafeArray(const VARIANT& Array3x3, FaMat33& m);
  static void GetFromSafeArray(const VARIANT& Array4x3, FaMat34& m);
  static void GetFromSafeArray(const VARIANT& ArrayNxM, int N, int M, double* pData);
  static void GetFromSafeArray(const VARIANT& ArrayNxM, int N, int M, long* pData);
  static void GetFromSafeArrayDims(const VARIANT& ArrayNxM, int* pDims, int* pN, int* pM);
  static IDispatch* CreateCOMObjectWrapper(FmModelMemberBase* item);
  static FmModelMemberBase* GetFromCOMObjectWrapper(IDispatch* pDisp);
  static void GetFunctionParameter(const VARIANT FAR& FunctionParam, double* pVal, FmModelMemberBase** ppFunction);

private:
  // Signal Receiver
  CaSignalConnector<CaApplication,FmAssemblyBase> signalConnector;

  friend class CaSignalConnector<CaApplication,FmAssemblyBase>;

  FmAssemblyBase*& m_ptr; // == m_pCurrentAssembly (used by signalConnector)
};
