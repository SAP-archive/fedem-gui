// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUMDIWINDOW_H
#define FFUMDIWINDOW_H

#include "FFuLib/FFuBase/FFuTopLevelShell.H"
#include <vector>
#include <string>


class FFuMDIWindow: virtual public  FFuTopLevelShell
{
  Fmd_HEADER_INIT();
public:
  FFuMDIWindow();
  virtual ~FFuMDIWindow();

  // Re-impl if you want something to happen when window gets active
  virtual void onWindowActivated() {}

// Operations  
public:

protected:
  
private:
  
// Attributes
protected:
 

private:
 
};

/////////////////////////////////////////////////////////////////////////////

#endif
