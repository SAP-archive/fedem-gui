// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_PROPERTIES_H
#define FUI_QT_PROPERTIES_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "vpmUI/vpmUITopLevels/FuiProperties.H"


class FuiQtProperties : public FFuQtMultUIComponent,
			public FuiProperties
{
public:
  FuiQtProperties(QWidget* parent,
		  int xpos =100, int ypos  =100,
		  int width=388, int height=460,
		  const char* name = "FuiQtProperties");
  virtual ~FuiQtProperties() {}

  virtual void setSensitivity(bool isSensitive)
  {
    this->FuiProperties::setSensitivity(isSensitive);
  }

  virtual bool initStartGuide(FedemEdition edition);
};

#endif
