// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "CaDOF.h"
#include "CaFunction.h"
#include "CaApplication.h"
#include "CaMacros.h"

#include "vpmDB/FmJointBase.H"
#include "vpmDB/FmDB.H"


//////////////////////////////////////////////////////////////////////
// Constructors and set-up

IMPLEMENT_DYNCREATE(CaDOF, CCmdTarget)

BEGIN_MESSAGE_MAP(CaDOF, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CaDOF, CCmdTarget)
  DISP_PROPERTY_EX_ID(CaDOF, "DOFConstraintType", dispidDOFConstraintType, get_DOFConstraintType, SetNotSupported, VT_I4)
  DISP_PROPERTY_EX_ID(CaDOF, "InitialVelocity", dispidInitialVelocity, get_InitialVelocity, SetNotSupported, VT_R8)
  DISP_PROPERTY_EX_ID(CaDOF, "AddBC", dispidAddBC, get_AddBC, put_AddBC, VT_BOOL)
  DISP_PROPERTY_EX_ID(CaDOF, "LoadMagnitude", dispidLoadMagnitude, get_LoadMagnitude, SetNotSupported, VT_VARIANT)
  DISP_PROPERTY_EX_ID(CaDOF, "PrescribedMotionType", dispidPrescribedMotionType, get_PrescribedMotionType, SetNotSupported, VT_VARIANT)
  DISP_PROPERTY_EX_ID(CaDOF, "PrescribedMotionMagnitude", dispidPrescribedMotionMagnitude, get_PrescribedMotionMagnitude, SetNotSupported, VT_VARIANT)
  DISP_PROPERTY_EX_ID(CaDOF, "SDStressfreeLength", dispidSDStressfreeLength, get_SDStressfreeLength, SetNotSupported, VT_VARIANT)
  DISP_PROPERTY_EX_ID(CaDOF, "SDStiffness", dispidSDStiffness, get_SDStiffness, SetNotSupported, VT_VARIANT)
  DISP_PROPERTY_EX_ID(CaDOF, "SDStiffnessScale", dispidSDStiffnessScale, get_SDStiffnessScale, SetNotSupported, VT_VARIANT)
  DISP_PROPERTY_EX_ID(CaDOF, "SDDamper", dispidSDDamper, get_SDDamper, SetNotSupported, VT_VARIANT)
  DISP_PROPERTY_EX_ID(CaDOF, "SDDamperScale", dispidSDDamperScale, get_SDDamperScale, SetNotSupported, VT_VARIANT)
  DISP_FUNCTION_ID(CaDOF, "SetFree", dispidSetFree, SetFree, VT_EMPTY, VTS_VARIANT VTS_VARIANT)
  DISP_FUNCTION_ID(CaDOF, "SetFixed", dispidSetFixed, SetFixed, VT_EMPTY, VTS_NONE)
  DISP_FUNCTION_ID(CaDOF, "SetPrescribed", dispidSetPrescribed, SetPrescribed, VT_EMPTY, VTS_I4 VTS_VARIANT VTS_VARIANT)
  DISP_FUNCTION_ID(CaDOF, "SetSpringDamper", dispidSetSpringDamper, SetSpringDamper, VT_EMPTY, VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CaDOF, CCmdTarget)
  INTERFACE_PART(CaDOF, IID_IDOF, LocalClass)
END_INTERFACE_MAP()

// {FE8E38C7-69F4-4b38-B887-4C0028301792}
IMPLEMENT_OLECREATE(CaDOF, "FEDEM.DOF",
0xfe8e38c7, 0x69f4, 0x4b38, 0xb8, 0x87, 0x4c, 0x0, 0x28, 0x30, 0x17, 0x92);


CaDOF::CaDOF(void) : m_ptr(m_pDOF)
{
  EnableAutomation();
  ::AfxOleLockApp();
  m_pDOF = NULL;
  m_nDOFIndex = -1;
  signalConnector.Connect(this);
}

CaDOF::~CaDOF(void)
{
  ::AfxOleUnlockApp();
  m_pDOF = NULL;
  m_nDOFIndex = -1;
}


//////////////////////////////////////////////////////////////////////
// Methods

void CaDOF::checkMe()
{
  CA_CHECK(m_pDOF);

  if (m_nDOFIndex == -1)
    AfxThrowOleException(CO_E_OBJNOTCONNECTED);
  else if (m_nDOFIndex < 1 || m_nDOFIndex > 6)
    AfxThrowOleException(ERROR_INVALID_INDEX);
}


DOFConstraintType CaDOF::get_DOFConstraintType()
{
  this->checkMe();

  switch (m_pDOF->getStatusOfDOF(m_nDOFIndex-1)) {
  case FmHasDOFsBase::FIXED:
    return DOFConstraintType::Fixed;
  case FmHasDOFsBase::FREE_DYNAMICS:
    return DOFConstraintType::Free;
  case FmHasDOFsBase::FREE:
    return DOFConstraintType::Free;
  case FmHasDOFsBase::PRESCRIBED:
    return DOFConstraintType::Prescribed;
  case FmHasDOFsBase::SPRING_CONSTRAINED:
    return DOFConstraintType::SpringDamper;
  case FmHasDOFsBase::SPRING_DYNAMICS:
    return DOFConstraintType::SpringDamper;
  }
  return DOFConstraintType::Free;
}

void CaDOF::put_DOFConstraintType(DOFConstraintType Val)
{
  this->checkMe();

  switch (Val) {
  case DOFConstraintType::Free:
    m_pDOF->setStatusForDOF(m_nDOFIndex-1, FmHasDOFsBase::FREE);
    break;
  case DOFConstraintType::Fixed:
    m_pDOF->setStatusForDOF(m_nDOFIndex-1, FmHasDOFsBase::FIXED);
    break;
  case DOFConstraintType::Prescribed:
    m_pDOF->setStatusForDOF(m_nDOFIndex-1, FmHasDOFsBase::PRESCRIBED);
    break;
  case DOFConstraintType::SpringDamper:
    m_pDOF->setStatusForDOF(m_nDOFIndex-1, FmHasDOFsBase::SPRING_CONSTRAINED);
    break;
  }
}

double CaDOF::get_InitialVelocity()
{
  this->checkMe();

  return m_pDOF->getInitVel(m_nDOFIndex-1);
}

BOOL CaDOF::get_AddBC()
{
  this->checkMe();

  return m_pDOF->getStatusCode(m_nDOFIndex-1) == 2;
}

void CaDOF::put_AddBC(BOOL Val)
{
  this->checkMe();

  int dof = m_nDOFIndex - 1;

  FmHasDOFsBase::DOFStatus stat = m_pDOF->getStatusOfDOF(dof);

  if (Val) {
    if (stat == FmHasDOFsBase::DOFStatus::FREE)
      m_pDOF->setStatusForDOF(dof, FmHasDOFsBase::DOFStatus::FREE_DYNAMICS);
    else if (stat == FmHasDOFsBase::DOFStatus::SPRING_CONSTRAINED)
      m_pDOF->setStatusForDOF(dof, FmHasDOFsBase::DOFStatus::SPRING_DYNAMICS);
    else
      return;
  }
  else
  {
    if (stat == FmHasDOFsBase::DOFStatus::FREE_DYNAMICS)
      m_pDOF->setStatusForDOF(dof, FmHasDOFsBase::DOFStatus::FREE);
    else if (stat == FmHasDOFsBase::DOFStatus::SPRING_CONSTRAINED)
      m_pDOF->setStatusForDOF(dof, FmHasDOFsBase::DOFStatus::SPRING_DYNAMICS);
    else
      return;
  }

  m_pDOF->onChanged();
}

VARIANT CaDOF::get_LoadMagnitude()
{
  this->checkMe();

  VARIANT vRet;
  vRet.vt = VT_EMPTY;

  FmDofLoad* pLoad = m_pDOF->getLoadAtDOF(m_nDOFIndex-1);
  if (pLoad == NULL)
    return vRet;

  if (pLoad->getEngine()) {
    // IFunction
    CaFunction* pCaFunction = (CaFunction*)CaFunction::CreateObject();
    if (pCaFunction == NULL)
      return vRet;
    pCaFunction->m_ptr = pLoad->getEngine();
    IFunction* pIFunction = NULL;
    LPDISPATCH pDisp = pCaFunction->GetIDispatch(false);
    pDisp->QueryInterface(IID_IFunction, (void**)&pIFunction);
    pCaFunction->InternalRelease();
    vRet.punkVal = pIFunction;
    vRet.vt = VT_UNKNOWN;
  }
  else {
    // double
    vRet.dblVal = pLoad->getInitLoad();
    vRet.vt = VT_R8;
  }

  return vRet;
}

DOFPrescribedMotionType CaDOF::get_PrescribedMotionType()
{
  this->checkMe();

  FmDofMotion* pMotion = m_pDOF->getMotionAtDOF(m_nDOFIndex-1);
  if (pMotion != NULL)
    switch (pMotion->getMotionType()) {
    case FmDofMotion::DEFLECTION:
      return DOFPrescribedMotionType::Deflection;
    case FmDofMotion::VELOCITY:
      return DOFPrescribedMotionType::Velocity;
    case FmDofMotion::ACCELERATION:
      return DOFPrescribedMotionType::Acceleration;
    }

  return (DOFPrescribedMotionType)0;
}

VARIANT CaDOF::get_PrescribedMotionMagnitude()
{
  this->checkMe();

  VARIANT vRet;
  vRet.vt = VT_EMPTY;

  FmDofMotion* pMotion = m_pDOF->getMotionAtDOF(m_nDOFIndex-1);
  if (pMotion == NULL)
    return vRet;

  if (pMotion->getEngine()) {
    // IFunction
    CaFunction* pCaFunction = (CaFunction*)CaFunction::CreateObject();
    if (pCaFunction == NULL)
      return vRet;
    pCaFunction->m_ptr = pMotion->getEngine();
    IFunction* pIFunction = NULL;
    LPDISPATCH pDisp = pCaFunction->GetIDispatch(false);
    pDisp->QueryInterface(IID_IFunction, (void**)&pIFunction);
    pCaFunction->InternalRelease();
    vRet.punkVal = pIFunction;
    vRet.vt = VT_UNKNOWN;
  }
  else {
    // double
    vRet.dblVal = pMotion->getInitMotion();
    vRet.vt = VT_R8;
  }

  return vRet;
}

VARIANT CaDOF::get_SDStressfreeLength()
{
  // Note: Are SDStressfreeLength and PrescribedMotionMagnitude the same?
  // KMO say: Yes, they are, so this method is not necessary.
  return this->get_PrescribedMotionMagnitude();
}

VARIANT CaDOF::get_SDStiffness()
{
  this->checkMe();

  VARIANT vRet;
  vRet.vt = VT_EMPTY;

  FmJointBase* pJoint = dynamic_cast<FmJointBase*>(m_pDOF);
  if (pJoint == NULL)
    return vRet;
  FmJointSpring* pSpring = pJoint->getSpringAtDOF(m_nDOFIndex-1);
  if (pSpring == NULL)
    return vRet;

  if (pSpring->getSpringCharOrStiffFunction()) {
    // IFunction
    CaFunction* pCaFunction = (CaFunction*)CaFunction::CreateObject();
    if (pCaFunction == NULL)
      return vRet;
    pCaFunction->m_ptr = pSpring->getSpringCharOrStiffFunction();
    IFunction* pIFunction = NULL;
    LPDISPATCH pDisp = pCaFunction->GetIDispatch(false);
    pDisp->QueryInterface(IID_IFunction, (void**)&pIFunction);
    pCaFunction->InternalRelease();
    vRet.punkVal = pIFunction;
    vRet.vt = VT_UNKNOWN;
  }
  else {
    // double
    vRet.dblVal = pSpring->getInitStiff();
    vRet.vt = VT_R8;
  }

  return vRet;
}

VARIANT CaDOF::get_SDStiffnessScale()
{
  this->checkMe();

  VARIANT vRet;
  vRet.vt = VT_EMPTY;

  FmJointBase* pJoint = dynamic_cast<FmJointBase*>(m_pDOF);
  if (pJoint == NULL)
    return vRet;
  FmJointSpring* pSpring = pJoint->getSpringAtDOF(m_nDOFIndex-1);
  if (pSpring == NULL)
    return vRet;
  FmEngine* pScaleEng = pSpring->getScaleEngine();
  if (pScaleEng == NULL)
    return vRet;

  // IFunction
  CaFunction* pCaFunction = (CaFunction*)CaFunction::CreateObject();
  if (pCaFunction == NULL)
    return vRet;

  pCaFunction->m_ptr = pScaleEng;
  IFunction* pIFunction = NULL;
  LPDISPATCH pDisp = pCaFunction->GetIDispatch(false);
  pDisp->QueryInterface(IID_IFunction, (void**)&pIFunction);
  pCaFunction->InternalRelease();
  vRet.punkVal = pIFunction;
  vRet.vt = VT_UNKNOWN;
  return vRet;
}

VARIANT CaDOF::get_SDDamper()
{
  this->checkMe();

  VARIANT vRet;
  vRet.vt = VT_EMPTY;

  FmJointBase* pJoint = dynamic_cast<FmJointBase*>(m_pDOF);
  if (pJoint == NULL)
    return vRet;
  FmJointDamper* pDamper = pJoint->getDamperAtDOF(m_nDOFIndex-1);
  if (pDamper == NULL)
    return vRet;

  if (pDamper->getFunction()) {
    // IFunction
    CaFunction* pCaFunction = (CaFunction*)CaFunction::CreateObject();
    if (pCaFunction == NULL)
      return vRet;
    pCaFunction->m_ptr = pDamper->getFunction();
    IFunction* pIFunction = NULL;
    LPDISPATCH pDisp = pCaFunction->GetIDispatch(false);
    pDisp->QueryInterface(IID_IFunction, (void**)&pIFunction);
    pCaFunction->InternalRelease();
    vRet.punkVal = pIFunction;
    vRet.vt = VT_UNKNOWN;
  }
  else {
    // double
    vRet.dblVal = pDamper->getInitDamp();
    vRet.vt = VT_R8;
  }

  return vRet;
}

VARIANT CaDOF::get_SDDamperScale()
{
  this->checkMe();

  VARIANT vRet;
  vRet.vt = VT_EMPTY;

  FmJointBase* pJoint = dynamic_cast<FmJointBase*>(m_pDOF);
  if (pJoint == NULL)
    return vRet;
  FmJointDamper* pDamper = pJoint->getDamperAtDOF(m_nDOFIndex-1);
  if (pDamper == NULL)
    return vRet;
  FmEngine* pScaleEng = pDamper->getDampEngine();
  if (pScaleEng == NULL)
    return vRet;

  // IFunction
  CaFunction* pCaFunction = (CaFunction*)CaFunction::CreateObject();
  if (pCaFunction == NULL)
    return vRet;

  pCaFunction->m_ptr = pScaleEng;
  IFunction* pIFunction = NULL;
  LPDISPATCH pDisp = pCaFunction->GetIDispatch(false);
  pDisp->QueryInterface(IID_IFunction, (void**)&pIFunction);
  pCaFunction->InternalRelease();
  vRet.punkVal = pIFunction;
  vRet.vt = VT_UNKNOWN;
  return vRet;
}

void CaDOF::SetFree(const VARIANT FAR& LoadMagnitude, const VARIANT FAR& InitialVelocity)
{
  this->checkMe();

  // Get load magnitude parameter.
  // Note: LoadMagnitude can be a double, a function name or an IFunction.
  double fLoadMagnitude = 0.0;
  FmModelMemberBase* pLoadMagnitudeFunction = NULL;
  CaApplication::GetFunctionParameter(LoadMagnitude, &fLoadMagnitude, &pLoadMagnitudeFunction);
  // Convert to double
  VARIANT varR8;
  VariantInit(&varR8);
  VariantChangeType(&varR8, &InitialVelocity, 0, VT_R8);
  double fInitialVelocity = varR8.vt == VT_R8 ? varR8.dblVal : 0.0;

  int dof = m_nDOFIndex - 1;

  // Set status
  m_pDOF->setStatusForDOF(dof, FmHasDOFsBase::DOFStatus::FREE);
  // Set initial velocity
  m_pDOF->setInitVel(dof, fInitialVelocity);
  // Set load magnitude
  FmDofLoad* pLoad = m_pDOF->getLoadAtDOF(dof,true);
  pLoad->setInitLoad(fLoadMagnitude);
  pLoad->setEngine(dynamic_cast<FmEngine*>(pLoadMagnitudeFunction));

  m_pDOF->onChanged();
}

void CaDOF::SetFixed()
{
  this->checkMe();

  if (m_pDOF->setStatusForDOF(m_nDOFIndex-1,FmHasDOFsBase::DOFStatus::FIXED))
    m_pDOF->onChanged();
}

void CaDOF::SetPrescribed(DOFPrescribedMotionType MotionType,
  const VARIANT FAR& MotionMagnitude, const VARIANT FAR& InitialVelocity)
{
  this->checkMe();

  // Get motion magnitude parameter.
  // Note: MotionMagnitude can be a double, a function name or an IFunction.
  double fMotionMagnitude = 0.0;
  FmModelMemberBase* pMotionMagnitudeFunction = NULL;
  CaApplication::GetFunctionParameter(MotionMagnitude, &fMotionMagnitude, &pMotionMagnitudeFunction);
  // Convert to double
  VARIANT varR8;
  VariantInit(&varR8);
  VariantChangeType(&varR8, &InitialVelocity, 0, VT_R8);
  double fInitialVelocity = varR8.vt == VT_R8 ? varR8.dblVal : 0.0;

  int dof = m_nDOFIndex - 1;

  // Set status
  m_pDOF->setStatusForDOF(dof, FmHasDOFsBase::DOFStatus::PRESCRIBED);
  // Set initial velocity
  m_pDOF->setInitVel(dof, fInitialVelocity);
  // Set motion type and magnitude
  FmDofMotion* pMotion = m_pDOF->getMotionAtDOF(dof,true);
  pMotion->setMotionType((FmDofMotion::MotionType)(int)MotionType);
  pMotion->setInitMotion(fMotionMagnitude);
  pMotion->setEngine(dynamic_cast<FmEngine*>(pMotionMagnitudeFunction));

  m_pDOF->onChanged();
}

void CaDOF::SetSpringDamper(const VARIANT FAR& LoadMagnitude,
  const VARIANT FAR& StressfreeLength, const VARIANT FAR& Stiffness,
  const VARIANT FAR& StiffnessScale, const VARIANT FAR& Damper,
  const VARIANT FAR& DamperScale, const VARIANT FAR& InitialVelocity)
{
  this->checkMe();

  // Get function parameters.
  // Note: Function parameters can be a double, a function name or an IFunction.
  // Load magnitude
  double fLoadMagnitude = 0.0;
  FmModelMemberBase* pLoadMagnitudeFunction = NULL;
  CaApplication::GetFunctionParameter(LoadMagnitude, &fLoadMagnitude, &pLoadMagnitudeFunction);
  // Stressfree length
  double fStressfreeLength = 0.0;
  FmModelMemberBase* pStressfreeLengthFunction = NULL;
  CaApplication::GetFunctionParameter(StressfreeLength, &fStressfreeLength, &pStressfreeLengthFunction);

  // Stiffness
  double fStiffness = 0.0;
  FmModelMemberBase* pStiffnessFunction = NULL;
  CaApplication::GetFunctionParameter(Stiffness, &fStiffness, &pStiffnessFunction);
  // StiffnessScale
  double fStiffnessScale = 0.0;
  FmModelMemberBase* pStiffnessScaleFunction = NULL;
  CaApplication::GetFunctionParameter(StiffnessScale, &fStiffnessScale, &pStiffnessScaleFunction);
  // Damper
  double fDamper = 0.0;
  FmModelMemberBase* pDamperFunction = NULL;
  CaApplication::GetFunctionParameter(Damper, &fDamper, &pDamperFunction);
  // DamperScale
  double fDamperScale = 0.0;
  FmModelMemberBase* pDamperScaleFunction = NULL;
  CaApplication::GetFunctionParameter(DamperScale, &fDamperScale, &pDamperScaleFunction);
  // Convert to double
  VARIANT varR8;
  VariantInit(&varR8);
  VariantChangeType(&varR8, &InitialVelocity, 0, VT_R8);
  double fInitialVelocity = varR8.vt == VT_R8 ? varR8.dblVal : 0.0;

  // Note: I have not added checking/searching for sd-only functions.

  int dof = m_nDOFIndex - 1;

  // Set status
  m_pDOF->setStatusForDOF(dof, FmHasDOFsBase::DOFStatus::SPRING_CONSTRAINED);
  // Set initial velocity
  m_pDOF->setInitVel(dof, fInitialVelocity);
  // Set load magnitude
  FmDofLoad* pLoad = m_pDOF->getLoadAtDOF(dof,true);
  pLoad->setInitLoad(fLoadMagnitude);
  pLoad->setEngine(dynamic_cast<FmEngine*>(pLoadMagnitudeFunction));

  FmJointBase* pJoint = dynamic_cast<FmJointBase*>(m_pDOF);
  if (pJoint != NULL)
  {
    // Set stiffness & stressfree length
    FmJointSpring* pSpring = pJoint->getSpringAtDOF(dof,true);
    pSpring->setInitStiff(fStiffness);
    pSpring->setSpringCharOrStiffFunction(pStiffnessFunction);
    pSpring->setInitLengthOrDefl(fStressfreeLength);
    pSpring->setLengthEngine(dynamic_cast<FmEngine*>(pStressfreeLengthFunction));
    pSpring->setScaleEngine(dynamic_cast<FmEngine*>(pStiffnessScaleFunction));
    // Set damper
    FmJointDamper* pDamper = pJoint->getDamperAtDOF(dof,true);
    pDamper->setInitDamp(fDamper);
    pDamper->setFunction(dynamic_cast<FmMathFuncBase*>(pDamperFunction));
    pDamper->setDampEngine(dynamic_cast<FmEngine*>(pDamperScaleFunction));
  }

  m_pDOF->onChanged();
}


//////////////////////////////////////////////////////////////////////
// Implementation

STDMETHODIMP_(ULONG) CaDOF::XLocalClass::AddRef()
{
  METHOD_PROLOGUE(CaDOF, LocalClass)
  return pThis->ExternalAddRef();
}
STDMETHODIMP_(ULONG) CaDOF::XLocalClass::Release()
{
  METHOD_PROLOGUE(CaDOF, LocalClass)
  return pThis->ExternalRelease();
}
STDMETHODIMP CaDOF::XLocalClass::QueryInterface(
  REFIID iid, LPVOID* ppvObj)
{
  METHOD_PROLOGUE(CaDOF, LocalClass)
  return pThis->ExternalQueryInterface(&iid, ppvObj);
}
STDMETHODIMP CaDOF::XLocalClass::GetTypeInfoCount(
  UINT FAR* pctinfo)
{
  METHOD_PROLOGUE(CaDOF, LocalClass)
  LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
  ASSERT(lpDispatch != NULL);
  return lpDispatch->GetTypeInfoCount(pctinfo);
}
STDMETHODIMP CaDOF::XLocalClass::GetTypeInfo(
  UINT itinfo, LCID lcid, ITypeInfo FAR* FAR* pptinfo)
{
  METHOD_PROLOGUE(CaDOF, LocalClass)
  LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
  ASSERT(lpDispatch != NULL);
  return lpDispatch->GetTypeInfo(itinfo, lcid, pptinfo);
}
STDMETHODIMP CaDOF::XLocalClass::GetIDsOfNames(
  REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames,
  LCID lcid, DISPID FAR* rgdispid)
{
  METHOD_PROLOGUE(CaDOF, LocalClass)
  LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
  ASSERT(lpDispatch != NULL);
  return lpDispatch->GetIDsOfNames(riid, rgszNames, cNames,
          lcid, rgdispid);
}
STDMETHODIMP CaDOF::XLocalClass::Invoke(
  DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
  DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult,
  EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr)
{
  METHOD_PROLOGUE(CaDOF, LocalClass)
  LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
  ASSERT(lpDispatch != NULL);
  return lpDispatch->Invoke(dispidMember, riid, lcid,
          wFlags, pdispparams, pvarResult,
          pexcepinfo, puArgErr);
}


// Note: The following wrapper code will only be called by TLB
// interface calls, and not by IDispatch calls. So, you should
// only forward this call to the code in the methods part here
// (see further up in this file).

STDMETHODIMP CaDOF::XLocalClass::get_DOFConstraintType(DOFConstraintType* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_DOFConstraintType();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::put_DOFConstraintType(DOFConstraintType Val)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    pThis->put_DOFConstraintType(Val);
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::get_InitialVelocity(double* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_InitialVelocity();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::get_AddBC(VARIANT_BOOL* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_AddBC();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::put_AddBC(VARIANT_BOOL Val)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    pThis->put_AddBC(Val);
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::get_LoadMagnitude(VARIANT* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_LoadMagnitude();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::get_PrescribedMotionType(DOFPrescribedMotionType* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_PrescribedMotionType();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::get_PrescribedMotionMagnitude(VARIANT* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_PrescribedMotionMagnitude();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::get_SDStressfreeLength(VARIANT* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_SDStressfreeLength();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::get_SDStiffness(VARIANT* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_SDStiffness();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::get_SDStiffnessScale(VARIANT* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_SDStiffnessScale();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::get_SDDamper(VARIANT* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_SDDamper();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::get_SDDamperScale(VARIANT* pVal)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    *pVal = pThis->get_SDDamperScale();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::SetFree(VARIANT LoadMagnitude, VARIANT InitialVelocity)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    pThis->SetFree(LoadMagnitude, InitialVelocity);
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::SetFixed()
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    pThis->SetFixed();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::SetPrescribed(DOFPrescribedMotionType MotionType,
  VARIANT MotionMagnitude, VARIANT InitialVelocity)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    pThis->SetPrescribed(MotionType, MotionMagnitude, InitialVelocity);
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaDOF::XLocalClass::SetSpringDamper(VARIANT LoadMagnitude,
  VARIANT StressfreeLength, VARIANT Stiffness, VARIANT StiffnessScale,
  VARIANT Damper, VARIANT DamperScale, VARIANT InitialVelocity)
{
  METHOD_PROLOGUE(CaDOF, LocalClass);
  TRY
  {
    pThis->SetSpringDamper(LoadMagnitude, StressfreeLength, Stiffness, StiffnessScale,
                           Damper, DamperScale, InitialVelocity);
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}
