// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiGraphDefine.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuSpinBox.H"
#include "FFuLib/FFuOptionMenu.H"
#include "FFuLib/FFuToggleButton.H"
#include "FFuLib/FFuLabelField.H"

//----------------------------------------------------------------------------

FuiGraphDefine::FuiGraphDefine()
{
  this->titleField = 0;
  this->titleLabel = 0;
  this->subtitleField = 0;
  this->subtitleLabel = 0;

  this->xAxisField = 0;
  this->xAxisLabel = 0;
  this->yAxisField = 0;
  this->yAxisLabel = 0;

  for (FFuLabel*& label : this->fontSizeLabel) label = NULL;
  for (FFuSpinBox*& box : this->fontSizeBox)   box = NULL;

  this->gridMenu = 0;
  this->gridLabel = 0;

  this->legendButton = 0;
  this->autoscaleButton = 0;

  this->timeButton = 0;
  this->tminField = 0;
  this->tmaxField = 0;
}
//----------------------------------------------------------------------------

void FuiGraphDefine::initWidgets()
{
  this->titleField->setAcceptedCB(FFaDynCB1M(FuiGraphDefine,this,onFieldValueChanged,char*));
  this->subtitleField->setAcceptedCB(FFaDynCB1M(FuiGraphDefine,this,onFieldValueChanged,char*));
  this->xAxisField->setAcceptedCB(FFaDynCB1M(FuiGraphDefine,this,onFieldValueChanged,char*));
  this->yAxisField->setAcceptedCB(FFaDynCB1M(FuiGraphDefine,this,onFieldValueChanged,char*));

  for (FFuSpinBox* box : this->fontSizeBox) {
    box->setMinMax(5,50);
    box->setIntValue(8);
    box->setValueChangedCB(FFaDynCB1M(FuiGraphDefine,this,onFieldValueChanged,int));
  }

  this->gridMenu->setOptionSelectedCB(FFaDynCB1M(FuiGraphDefine,this,onFieldValueChanged,int));
  this->legendButton->setToggleCB(FFaDynCB1M(FuiGraphDefine,this,onButtonToggled,bool));
  this->autoscaleButton->setToggleCB(FFaDynCB1M(FuiGraphDefine,this,onButtonToggled,bool));

  this->timeButton->setToggleCB(FFaDynCB1M(FuiGraphDefine,this,onButtonToggled,bool));
  this->tminField->setAcceptedCB(FFaDynCB1M(FuiGraphDefine,this,onFieldValueChanged,double));
  this->tmaxField->setAcceptedCB(FFaDynCB1M(FuiGraphDefine,this,onFieldValueChanged,double));

  this->titleLabel->setLabel("Title");
  this->subtitleLabel->setLabel("Sub title");
  this->xAxisLabel->setLabel("X-Axis label");
  this->yAxisLabel->setLabel("Y-Axis label");

  for (FFuLabel* label : this->fontSizeLabel)
    label->setLabel("Font size:");

  this->gridLabel->setLabel("Grid:");
  this->gridMenu->addOption("None");   // 0 refer FFu2DPlotter enum
  this->gridMenu->addOption("Coarse"); // 1
  this->gridMenu->addOption("Fine");   // 2

  this->legendButton->setLabel("Legend");
  this->autoscaleButton->setLabel("Autoscale");

  const char* timeTip =
    "Note: The time interval fields are used only for curves that plot results from the RDB, and\n"
    "are used to limit the amount of data read for a large result database with many time steps.\n"
    "They do NOT affect curves plotting internal functions or imported curves, unless the\n"
    "RDB-curves all have Time as their X-axis defintion. In the latter case, it is assumed that\n"
    "the imported curves also have Time as X-axis definition and are clipped accordingly.";
  this->timeButton->setLabel("Use time interval");
  this->timeButton->setToolTip(timeTip);
  this->tminField->setLabel("Start time");
  this->tminField->setToolTip(timeTip);
  this->tmaxField->setLabel("Stop time");
  this->tmaxField->setToolTip(timeTip);

  // These features are (not yet) supported with Qwt 6.1.2, so hide the widgets in the GUI
  this->subtitleLabel->popDown();
  this->subtitleField->popDown();

  // create ui's UA object
  FFuUAExistenceHandler::invokeCreateUACB(this);
}
//----------------------------------------------------------------------------

void FuiGraphDefine::placeWidgets(int width, int)
{
  int border = this->getBorder();
  int fieldh = this->titleField->getHeightHint();
  int labh = this->titleLabel->getHeightHint();
  int labw = this->xAxisLabel->getWidthHint();

  //GridLines
  //vertical borders
  int glbl = 0;
  int glbr = width > border ? width-border : 0;
  //horisontal borders
  int glbt = border/2;

  //vertical
  int glv0 = glbl+labw+border;
  int glv1 = glbl+4*(glbr-glbl)/5+border;
  int glv2 = glv1+border+this->fontSizeLabel[0]->getWidthHint();
  int glv3 = glv1-(glbr-glbl)/5;
  int glv4 = glv3+border+this->fontSizeLabel[1]->getWidthHint();
  int fieldw = glv1-glv0-border;

  //horisontal
  int glh[5];
  for (int i = 0; i < 5; i++)
    glh[i] = glbt + fieldh/2 + i*(fieldh+glbt);

  //place widgets
  this->titleLabel->setCenterYGeometry(glbl,glh[0],labw,labh);
  this->titleField->setCenterYGeometry(glv0,glh[0],fieldw,fieldh);
  this->fontSizeLabel[0]->setCenterYGeometryWidthHint(glv1,glh[0],labh);
  this->fontSizeBox[0]->setCenterYGeometry(glv2,glh[0],glbr-glv2,fieldh);

  this->subtitleLabel->setCenterYGeometry(glbl,glh[1],labw,labh);
  this->subtitleField->setCenterYGeometry(glv0,glh[1],fieldw,fieldh);

  fieldw -= (glbr-glbl)/5;
  this->xAxisLabel->setCenterYGeometry(glbl,glh[2],labw,labh);
  this->xAxisField->setCenterYGeometry(glv0,glh[2],fieldw,fieldh);
  this->yAxisLabel->setCenterYGeometry(glbl,glh[3],labw,labh);
  this->yAxisField->setCenterYGeometry(glv0,glh[3],fieldw,fieldh);

  for (int l = 1; l < 3; l++) {
    this->fontSizeLabel[l]->setCenterYGeometryWidthHint(glv3,glh[l+1],labh);
    this->fontSizeBox[l]->setCenterYGeometry(glv4,glh[l+1],glv1-glv4-border,fieldh);
  }

  this->gridLabel->setCenterYGeometrySizeHint(glv1,glh[1]);
  this->gridMenu->setCenterYGeometrySizeHint(glv1+this->gridLabel->getWidthHint()+border,glh[1]);
  this->legendButton->setCenterYGeometrySizeHint(glv1,glh[2]);
  this->autoscaleButton->setCenterYGeometrySizeHint(glv1,glh[3]);

  fieldw = (glv1-glbl)/2 - border;
  glv2 = glbl + fieldw + border;
  this->tminField->setLabelWidth(labw+1);
  this->tminField->setCenterYGeometry(glbl,glh[4],fieldw,fieldh);
  int deltaLabel = this->tminField->getLabelWidth() - this->tmaxField->getLabelWidth();
  fieldw -= deltaLabel;
  this->tmaxField->setCenterYGeometry(glv2+deltaLabel,glh[4],fieldw,fieldh);
  this->timeButton->setCenterYGeometrySizeHint(glv1,glh[4]);
}
//-----------------------------------------------------------------------------

void FuiGraphDefine::onFieldValueChanged(char*)
{
  this->updateDBValues();
}
//-----------------------------------------------------------------------------

void FuiGraphDefine::onFieldValueChanged(double)
{
  this->updateDBValues();
}
//-----------------------------------------------------------------------------

void FuiGraphDefine::onFieldValueChanged(int)
{
  this->updateDBValues();
}
//-----------------------------------------------------------------------------

void FuiGraphDefine::onButtonToggled(bool)
{
  this->updateDBValues();
}
//-----------------------------------------------------------------------------

FFuaUIValues* FuiGraphDefine::createValuesObject()
{
  return new FuaGraphDefineValues();
}
//----------------------------------------------------------------------------

void FuiGraphDefine::setUIValues(const FFuaUIValues* values)
{
  FuaGraphDefineValues* graphValues = (FuaGraphDefineValues*) values;

  this->titleField->setValue(graphValues->title);
  this->subtitleField->setValue(graphValues->subtitle);
  this->xAxisField->setValue(graphValues->xAxisLabel);
  this->yAxisField->setValue(graphValues->yAxisLabel);

  for (size_t i = 0; i < this->fontSizeBox.size() && i < graphValues->fontSize.size(); i++)
    this->fontSizeBox[i]->setIntValue(graphValues->fontSize[i]);

  this->gridMenu->selectOption(graphValues->gridType);
  this->legendButton->setValue(graphValues->showLegend);
  this->autoscaleButton->setValue(graphValues->autoScaleOnLoadCurve);

  if (graphValues->useTimeInterval < -1) {
    this->timeButton->popDown();
    this->tminField->popDown();
    this->tmaxField->popDown();
  }
  else {
    this->timeButton->popUp();
    this->tminField->popUp();
    this->tmaxField->popUp();

    this->timeButton->setValue(graphValues->useTimeInterval > 0);
    this->tminField->setValue(graphValues->tmin);
    this->tmaxField->setValue(graphValues->tmax);

    this->timeButton->setSensitivity(graphValues->useTimeInterval >= 0);
    this->tminField->setSensitivity(graphValues->useTimeInterval > 0);
    this->tmaxField->setSensitivity(graphValues->useTimeInterval > 0);
  }
}
//----------------------------------------------------------------------------

void FuiGraphDefine::getUIValues(FFuaUIValues* values)
{
  FuaGraphDefineValues* graphValues = (FuaGraphDefineValues*) values;

  graphValues->title = this->titleField->getValue();
  graphValues->subtitle = this->subtitleField->getValue();
  graphValues->xAxisLabel = this->xAxisField->getValue();
  graphValues->yAxisLabel = this->yAxisField->getValue();

  for (size_t i = 0; i < this->fontSizeBox.size() && i < graphValues->fontSize.size(); i++)
    graphValues->fontSize[i] = this->fontSizeBox[i]->getIntValue();

  graphValues->gridType = this->gridMenu->getSelectedOption();
  graphValues->showLegend = this->legendButton->getValue();
  graphValues->autoScaleOnLoadCurve = this->autoscaleButton->getValue();

  graphValues->useTimeInterval = this->timeButton->getValue();
  graphValues->tmin = this->tminField->getValue();
  graphValues->tmax = this->tmaxField->getValue();
}
//----------------------------------------------------------------------------
