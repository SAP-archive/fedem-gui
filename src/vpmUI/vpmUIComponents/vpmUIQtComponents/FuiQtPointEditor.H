// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUIQTPOINTEDITOR_H
#define FUIQTPOINTEDITOR_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUIComponents/FuiPointEditor.H"


class FuiQtPointEditor : public virtual FFuQtMultUIComponent, 
                         public FuiPointEditor
{
  
public:

  FuiQtPointEditor(QWidget* parent = 0,
                   int xpos=100,
                   int ypos=100,
                   int width=40,
                   int height=60,
                   const char* name="PointEditor");
  virtual ~FuiQtPointEditor();

  virtual void setSensitivity(bool sensitive){FuiPointEditor::setSensitivity(sensitive);}

};

#endif
