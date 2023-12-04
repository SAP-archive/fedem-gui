// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "CaSimulationEventManager.h"
#include "CaSimulationEvent.h"

#include "vpmApp/vpmAppProcess/FapSimEventHandler.H"

#include "vpmPM/FpModelRDBHandler.H"

#include "vpmDB/FmSimulationEvent.H"
#include "vpmDB/FmDB.H"


//////////////////////////////////////////////////////////////////////
// Constructors and set-up

IMPLEMENT_DYNCREATE(CaSimulationEventManager, CCmdTarget)

BEGIN_MESSAGE_MAP(CaSimulationEventManager, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CaSimulationEventManager, CCmdTarget)
  DISP_PROPERTY_PARAM_ID(CaSimulationEventManager, "Item", dispidItem, get_Item, SetNotSupported, VT_UNKNOWN, VTS_I4)
  DISP_PROPERTY_EX_ID(CaSimulationEventManager, "Count", dispidCount, get_Count, SetNotSupported, VT_I4)
  DISP_FUNCTION_ID(CaSimulationEventManager, "Add", dispidAdd, Add, VT_UNKNOWN, VTS_I4 VTS_VARIANT VTS_VARIANT)
  DISP_FUNCTION_ID(CaSimulationEventManager, "Remove", dispidRemove, Remove, VT_EMPTY, VTS_UNKNOWN)
  DISP_FUNCTION_ID(CaSimulationEventManager, "Clear", dispidClear, Clear, VT_EMPTY, VTS_NONE)
  DISP_FUNCTION_ID(CaSimulationEventManager, "SetActiveEvent", dispidSetActiveEvent, SetActiveEvent, VT_EMPTY, VTS_VARIANT)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CaSimulationEventManager, CCmdTarget)
  INTERFACE_PART(CaSimulationEventManager, IID_ISimulationEventManager, LocalClass)
END_INTERFACE_MAP()

// {E3416206-C929-44f4-967C-18AE4B2B33DA}
IMPLEMENT_OLECREATE(CaSimulationEventManager, "FEDEM.SimulationEventManager",
0xe3416206, 0xc929, 0x44f4, 0x96, 0x7c, 0x18, 0xae, 0x4b, 0x2b, 0x33, 0xda);


CaSimulationEventManager::CaSimulationEventManager(void)
{
  EnableAutomation();
  ::AfxOleLockApp();
}

CaSimulationEventManager::~CaSimulationEventManager(void)
{
  ::AfxOleUnlockApp();
}


//////////////////////////////////////////////////////////////////////
// Methods

ISimulationEvent* CaSimulationEventManager::get_Item(long Index)
{
  // Get simulation events
  std::vector<FmSimulationEvent*> simulationEvents;
  FmDB::getAllSimulationEvents(simulationEvents);

  // Check
  if ((Index < 0) || (Index >= simulationEvents.size()))
    AfxThrowOleException(E_INVALIDARG);

  // Get simulation event
  FmSimulationEvent* pSimulationEvent = simulationEvents[Index];
  if (pSimulationEvent == NULL)
    AfxThrowOleException(E_POINTER);

  // Create COM wrapper
  CaSimulationEvent* pCaSimulationEvent = (CaSimulationEvent*)CaSimulationEvent::CreateObject();
  if (pCaSimulationEvent == NULL)
    AfxThrowOleException(E_OUTOFMEMORY);
  pCaSimulationEvent->m_pSimulationEvent = pSimulationEvent;
  ISimulationEvent* pISimulationEvent = NULL;
  LPDISPATCH pDisp = pCaSimulationEvent->GetIDispatch(false);
  pDisp->QueryInterface(IID_ISimulationEvent, (void**)&pISimulationEvent);
  pCaSimulationEvent->InternalRelease();
  return pISimulationEvent;
}

long CaSimulationEventManager::get_Count()
{
  // Get simulation events
  std::vector<FmSimulationEvent*> simulationEvents;
  FmDB::getAllSimulationEvents(simulationEvents);
  return simulationEvents.size();
}

ISimulationEvent* CaSimulationEventManager::Add(long ID, const VARIANT FAR& Probability, const VARIANT FAR& Desc)
{
  // Get ID argument
  /*VARIANT varI4;
  VariantInit(&varI4);
  VariantChangeType(&varI4, &ID, 0, VT_I4);
  LONG nID = -1;
  if (varI4.vt == VT_I4)
    nID = varI4.lVal;*/
  LONG nID = ID;

  // Get Probability argument
  VARIANT varR8;
  VariantInit(&varR8);
  VariantChangeType(&varR8, &Probability, 0, VT_R8);
  double fProbability = 1.0;
  if (varR8.vt == VT_R8)
    fProbability = varR8.dblVal;

  // New simulation event
  FmSimulationEvent* pSimulationEvent = new FmSimulationEvent();
  if (pSimulationEvent == NULL)
    AfxThrowOleException(E_OUTOFMEMORY);
  if (nID != -1)
    pSimulationEvent->setID(nID);
  pSimulationEvent->setProbability(fProbability);

  // Set user description
  if (Desc.vt == VT_BSTR)
    pSimulationEvent->setUserDescription(std::string(CW2A(Desc.bstrVal)));

  pSimulationEvent->connect();

  // Create COM wrapper
  CaSimulationEvent* pCaSimulationEvent = (CaSimulationEvent*)CaSimulationEvent::CreateObject();
  if (pCaSimulationEvent == NULL)
    AfxThrowOleException(E_OUTOFMEMORY);
  pCaSimulationEvent->m_pSimulationEvent = pSimulationEvent;
  ISimulationEvent* pISimulationEvent = NULL;
  LPDISPATCH pDisp = pCaSimulationEvent->GetIDispatch(false);
  pDisp->QueryInterface(IID_ISimulationEvent, (void**)&pISimulationEvent);
  pCaSimulationEvent->InternalRelease();
  return pISimulationEvent;
}

void CaSimulationEventManager::Remove(ISimulationEvent* Item)
{
  // Check
  if (Item == NULL)
    AfxThrowOleException(E_INVALIDARG);

  // Get simulation event
  IDispatch* pDisp1 = NULL;
  Item->QueryInterface(IID_IDispatch, (void**)&pDisp1);
  if (pDisp1 == NULL)
    return;
  CaSimulationEvent* pCaSimulationEvent = 
    dynamic_cast<CaSimulationEvent*>(CaSimulationEvent::FromIDispatch(pDisp1));
  pDisp1->Release();
  if (pCaSimulationEvent == NULL)
    return;

  // Check
  if (pCaSimulationEvent->m_pSimulationEvent != NULL)
    pCaSimulationEvent->m_pSimulationEvent->erase();
}

void CaSimulationEventManager::Clear()
{
  std::vector<FmSimulationEvent*> simulationEvents;
  FmDB::getAllSimulationEvents(simulationEvents);
  for (FmSimulationEvent* pEvent : simulationEvents)
    pEvent->erase();
}

void CaSimulationEventManager::SetActiveEvent(const VARIANT FAR& SimEvent)
{
  // Empty, null or error
  if (SimEvent.vt == VT_EMPTY || SimEvent.vt == VT_NULL || SimEvent.vt == VT_ERROR)
    FapSimEventHandler::activate(NULL);
  // IDispatch or IUnknown pointer
  else if (SimEvent.vt == VT_DISPATCH || SimEvent.vt == VT_UNKNOWN) {
    IUnknown* pUnk = SimEvent.vt == VT_DISPATCH ? SimEvent.pdispVal : SimEvent.punkVal;
    IDispatch* pDisp1 = NULL;
    pUnk->QueryInterface(IID_IDispatch, (void**)&pDisp1);
    if (pDisp1 == NULL)
      return;

    CaSimulationEvent* pEvent = dynamic_cast<CaSimulationEvent*>(CaSimulationEvent::FromIDispatch(pDisp1));
    pDisp1->Release();
    if (pEvent == NULL)
      return;

    FapSimEventHandler::activate(pEvent->m_ptr);
  }
}


//////////////////////////////////////////////////////////////////////
// Implementation

STDMETHODIMP_(ULONG) CaSimulationEventManager::XLocalClass::AddRef()
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass)
          return pThis->ExternalAddRef();
}
STDMETHODIMP_(ULONG) CaSimulationEventManager::XLocalClass::Release()
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass)
          return pThis->ExternalRelease();
}
STDMETHODIMP CaSimulationEventManager::XLocalClass::QueryInterface(
  REFIID iid, LPVOID* ppvObj)
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass)
          return pThis->ExternalQueryInterface(&iid, ppvObj);
}
STDMETHODIMP CaSimulationEventManager::XLocalClass::GetTypeInfoCount(
  UINT FAR* pctinfo)
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass)
          LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
  ASSERT(lpDispatch != NULL);
  return lpDispatch->GetTypeInfoCount(pctinfo);
}
STDMETHODIMP CaSimulationEventManager::XLocalClass::GetTypeInfo(
  UINT itinfo, LCID lcid, ITypeInfo FAR* FAR* pptinfo)
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass)
          LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
  ASSERT(lpDispatch != NULL);
  return lpDispatch->GetTypeInfo(itinfo, lcid, pptinfo);
}
STDMETHODIMP CaSimulationEventManager::XLocalClass::GetIDsOfNames(
  REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames,
  LCID lcid, DISPID FAR* rgdispid) 
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass)
          LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
  ASSERT(lpDispatch != NULL);
  return lpDispatch->GetIDsOfNames(riid, rgszNames, cNames, 
          lcid, rgdispid);
}
STDMETHODIMP CaSimulationEventManager::XLocalClass::Invoke(
  DISPID dispidMember, REFIID riid, LCID lcid, WORD wFlags,
  DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult,
  EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr)
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass)
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

STDMETHODIMP CaSimulationEventManager::XLocalClass::get_Item(long Index, ISimulationEvent** ppObj)
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass);
  TRY
  {
    *ppObj = pThis->get_Item(Index);
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaSimulationEventManager::XLocalClass::get_Count(long* pnVal)
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass);
  TRY
  {
    *pnVal = pThis->get_Count();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaSimulationEventManager::XLocalClass::Add(long ID, VARIANT Probability, VARIANT Desc, ISimulationEvent** ppObj)
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass);
  TRY
  {
    *ppObj = pThis->Add(ID, Probability, Desc);
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaSimulationEventManager::XLocalClass::Remove(ISimulationEvent* Item)
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass);
  TRY
  {
    pThis->Remove(Item);
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaSimulationEventManager::XLocalClass::Clear()
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass);
  TRY
  {
    pThis->Clear();
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}

STDMETHODIMP CaSimulationEventManager::XLocalClass::SetActiveEvent(VARIANT SimEvent)
{
  METHOD_PROLOGUE(CaSimulationEventManager, LocalClass);
  TRY
  {
    pThis->SetActiveEvent(SimEvent);
  }
  CATCH_ALL(e)
  {
    return ResultFromScode(COleException::Process(e));
  }
  END_CATCH_ALL
  return S_OK;
}
