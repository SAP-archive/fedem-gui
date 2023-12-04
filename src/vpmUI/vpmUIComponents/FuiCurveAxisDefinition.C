// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiCurveAxisDefinition.H"
#include "FFuLib/FFuPushButton.H"
#include "FFuLib/FFuOptionMenu.H"
#include "FFuLib/FFuLabel.H"


//----------------------------------------------------------------------------

FuiCurveAxisDefinition::FuiCurveAxisDefinition()
{
  this->resultLabel = 0;
  this->editButton = 0;
  this->operMenu = 0;
}
//----------------------------------------------------------------------------

void FuiCurveAxisDefinition::initWidgets()
{
  this->operMenu->setOptionChangedCB(FFaDynCB1M(FuiCurveAxisDefinition,this,
						onOperMenuSelected,std::string));

  this->editButton->setActivateCB(FFaDynCB0M(FuiCurveAxisDefinition,this,
					     onEditButtonClicked));
  this->editButton->setLabel("Edit...");

  FFuUAExistenceHandler::invokeCreateUACB(this);
}
//----------------------------------------------------------------------------

void FuiCurveAxisDefinition::setUIValues(const std::string& result,
					 const std::vector<std::string>& opers,
					 const std::string& selOper)
{
  this->resultLabel->setLabel(result.c_str());

  this->operMenu->clearOptions();
  for (unsigned int i = 0; i < opers.size(); i++)
    this->operMenu->addOption(opers[i].c_str());

  if (!selOper.empty())
    this->operMenu->selectOption(selOper);

  this->operMenu->setSensitivity(!opers.empty());

  this->placeWidgets(this->getWidth(),this->getHeight());
}
//-----------------------------------------------------------------------------

void FuiCurveAxisDefinition::placeWidgets(int width, int height)
{
  int buttonWidth = this->editButton->getWidthHint();
  int textHeight = this->resultLabel->getHeightHint();
  int labelCenterY = height/5;
  int btnHeight = height/2;
  if (btnHeight > 28) btnHeight = 28;

  this->resultLabel->setCenterYGeometry(0, labelCenterY, width, textHeight);
  this->editButton->setEdgeGeometry(0, buttonWidth, height - btnHeight, height);
  this->operMenu->setEdgeGeometry(width - 3*buttonWidth/2, width, height - btnHeight, height);
}
//-----------------------------------------------------------------------------

void FuiCurveAxisDefinition::onOperMenuSelected(std::string oper)
{
  this->operSelectedCB.invoke(oper);
}
//-----------------------------------------------------------------------------

void FuiCurveAxisDefinition::onEditButtonClicked()
{
  this->editResultCB.invoke();
}
//-----------------------------------------------------------------------------
