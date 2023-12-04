// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "FFaLib/FFaDynCalls/FFaSwitchBoard.H"
#include "vpmDB/FmModelMemberBase.H"


template<class T, class FmT>
class CaSignalConnector : public FFaSwitchBoardConnector
{
public:
  CaSignalConnector() : myOwner(NULL) {}
  virtual ~CaSignalConnector() {}

  void Connect(T* owner)
  {
    myOwner = owner;
    FFaSwitchBoard::connect(FmModelMemberBase::getSignalConnector(),
			    FmModelMemberBase::MODEL_MEMBER_DISCONNECTED,
			    FFaSlot1M(CaSignalConnector,this,
				      onModelMemberDisconnected,
				      FmModelMemberBase*));
  }

private:
  void onModelMemberDisconnected(FmModelMemberBase* item)
  {
    if (dynamic_cast<FmT*>(item) == myOwner->m_ptr)
      myOwner->m_ptr = NULL; // disconnected
  }

public:
  T* myOwner;
};
