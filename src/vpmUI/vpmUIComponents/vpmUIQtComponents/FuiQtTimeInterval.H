// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTTIMEINTERVAL_H
#define FUIQTTIMEINTERVAL_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiTimeInterval.H"

// Typedefs and fwd declarations

class FuiQtTimeInterval: public FFuQtMultUIComponent,public FuiTimeInterval
{
public:
  FuiQtTimeInterval(QWidget * parent=0,const char* name="FuiQtTimeInterval");
  virtual ~FuiQtTimeInterval();

// Operations
private:
  virtual void setSensitivity(bool isSensitive) {
    FuiTimeInterval::setSensitivity(isSensitive);}

// Attributes 
private: 
 

};
/////////////////////////////////////////////////////////////////////////////

#endif
