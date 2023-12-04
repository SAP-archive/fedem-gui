// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUIComponents/FuiCtrlElemProperties.H"
#include "FFuLib/FFuIOField.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuLabelField.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuTableView.H"


void FuiCtrlElemProperties::initWidgets()
{
  myParameterFrame->setLabel("Parameters");
  myParameterView->stretchContentsWidth(true);

  FFuUAExistenceHandler::invokeCreateUACB(this);
}


void FuiCtrlElemProperties::placeWidgets(int width, int height)
{
  int glh1 = getGridLinePos(height, 3, FROM_START);
  int glh2 = myParameterFrame->getFontHeigth();
  int glh3 = getGridLinePos(height, 3, FROM_END);

  int glv1 = getGridLinePos(width, 3, FROM_START);
  int glv2 = getGridLinePos(width, 300);
  int glv3 = glv2 + 3;

  myElemPixmap->setEdgeGeometry(glv1,glv2,glh1,glh3);
  myParameterFrame->setEdgeGeometry(glv3,width,0,height);
  myParameterView->setEdgeGeometry(glv3+5,width-5,glh2,glh3);
}


void FuiCtrlElemProperties::setSensitivity(bool isSensitive)
{
  FFuLabelField* field;
  for (int i = 0; i < myParameterView->getRowCount(); i++)
    if ((field = dynamic_cast<FFuLabelField*>(myParameterView->getCell(i,0))))
      field->setSensitivity(isSensitive);
}


void FuiCtrlElemProperties::setUIValues(const FFuaUIValues* values)
{
  const FuaCtrlElemPropertiesValues* data = dynamic_cast<const FuaCtrlElemPropertiesValues*>(values);
  if (!data) return;

  FFuLabelField* field;
  for (size_t i = 0; i < data->parameters.size(); i++)
    if ((field = dynamic_cast<FFuLabelField*>(myParameterView->getCell(i,0))))
      field->setValue(data->parameters[i].value);

  myElemPixmap->setPixMap(data->pixmap);
}


void FuiCtrlElemProperties::buildDynamicWidgets(const FFuaUIValues* values)
{
  const FuaCtrlElemPropertiesValues* data = dynamic_cast<const FuaCtrlElemPropertiesValues*>(values);
  if (!data) return;

  if (data->parameters.empty())
    {
      myParameterFrame->popDown();
      myParameterView->popDown();
    }
  else
    {
      myParameterFrame->popUp();
      myParameterView->popUp();

      int maxLabelWidth = 0;
      std::vector<FFuLabelField*> fields;
      fields.reserve(data->parameters.size());

      for (const FuaCtrlElemPropertiesValues::CtrlParameter& param : data->parameters)
	{
	  FFuLabelField* field = this->makeALabelField();
	  field->myField->setInputCheckMode(FFuIOField::DOUBLECHECK);
	  field->myField->setDoubleDisplayMode(FFuIOField::AUTO,12,1);
	  field->setLabel(param.description.c_str());
	  field->myField->setAcceptedCB(FFaDynCB1M(FuiCtrlElemProperties,this,onValueChanged,char*));
	  if (field->myLabel->getWidthHint() > maxLabelWidth)
	    maxLabelWidth = field->myLabel->getWidthHint();

	  fields.push_back(field);
	  myParameterView->addRow({field});
	}

      for (FFuLabelField* field : fields)
      {
        field->setLabelMargin(3);
        field->setLabelWidth(maxLabelWidth);
      }
    }

  this->placeWidgets(this->getWidth(), this->getHeight());
}


void FuiCtrlElemProperties::eraseDynamicWidgets()
{
  myParameterView->deleteRow(-1);
}


void FuiCtrlElemProperties::onValueChanged(char*)
{
  FuaCtrlElemPropertiesValues values;

  FFuLabelField* field;
  for (int i = 0; i < myParameterView->getRowCount(); i++)
    if ((field = dynamic_cast<FFuLabelField*>(myParameterView->getCell(i,0))))
      values.parameters.push_back(FuaCtrlElemPropertiesValues::CtrlParameter(field->getValue()));

  this->invokeSetAndGetDBValuesCB(&values);
  this->setUIValues(&values);
}
