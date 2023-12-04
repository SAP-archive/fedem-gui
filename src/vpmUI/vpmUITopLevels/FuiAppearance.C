// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmUI/vpmUITopLevels/FuiAppearance.H"
#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuLabelFrame.H"
#include "FFuLib/FFuFrame.H"
#include "FFuLib/FFuScale.H"
#include "FFuLib/FFuDialogButtons.H"
#include "FFuLib/FFuColorSelector.H"
#include "FFuLib/FFuOptionMenu.H"


Fmd_SOURCE_INIT(FUI_APPEARANCE, FuiAppearance, FFuTopLevelShell);


FuiAppearance::FuiAppearance()
{
  Fmd_CONSTRUCTOR_INIT(FuiAppearance);

  isShininessChanged    = false;
  isTransparencyChanged = false;
  isColorChanged        = false;
  isPolygonsChanged     = false;
  isLinesChanged        = false;
}


void FuiAppearance::setUIValues(const FFuaUIValues* values)
{
  if (!values) return;
  
  FuaAppearanceValues* gsValues = (FuaAppearanceValues*) values;
    
  myShininessScale->setValue(gsValues->myShininess);
  myTransparencyScale->setValue(gsValues->myTransparency);
  myColorSelector->setColor(gsValues->myColor, false);
  myPolygonOptions->selectOption(gsValues->myPolygonsValue);
  myLinesOptions->selectOption(gsValues->myLinesValue);
}


bool FuiAppearance::getValues(FuaAppearanceValues* values) const
{
  if (!values) return false;
  
  values->isShininessChanged    = this->isShininessChanged;
  values->isTransparencyChanged = this->isTransparencyChanged;
  values->isColorChanged        = this->isColorChanged;
  values->isPolygonsChanged     = this->isPolygonsChanged;
  values->isLinesChanged        = this->isLinesChanged;
  values->myShininess = myShininessScale->getValue();
  values->myTransparency = myTransparencyScale->getValue();
  values->myColor = myColorSelector->getColor();
  values->myPolygonsValue = myPolygonOptions->getSelectedOption();
  values->myLinesValue = myLinesOptions->getSelectedOption();
  return true;
}


void FuiAppearance::setPolygonLODText(const std::vector<std::string>& options)
{
  myPolygonOptions->setOptions(options);
}

void FuiAppearance::setLinesLODText(const std::vector<std::string>& options)
{
  myLinesOptions->setOptions(options);
}


void FuiAppearance::initWidgets(void)
{
  // Frame labels
  myDetailsFrame->setLabel("Level Of Detail");
  myColorFrame->setLabel("Color");
  myMaterialFrame->setLabel("Material");
  
  myDialogButtons->setButtonClickedCB(FFaDynCB1M(FuiAppearance,this,
						 onDialogButtonClicked,int));
  myDialogButtons->setButtonLabel(FFuDialogButtons::LEFTBUTTON,"Close");

  // Symbols
  myShininessLabel->setLabel("Shininess");
  myTransparencyLabel->setLabel("Transparency");
  myPolygonsLabel->setLabel("Polygons");
  myLinesLabel->setLabel("Lines");

  myTransparencyScale->setMinMax(0,100);
  myShininessScale->setMinMax(0,100);

  myTransparencyScale->setDragCB(FFaDynCB1M(FuiAppearance,this,
					    onTranspSliderChanged,int));
  myShininessScale->setDragCB(FFaDynCB1M(FuiAppearance,this,
					 onShininessSliderChanged,int));
  myColorSelector->setColorChangedCB(FFaDynCB1M(FuiAppearance,this,
						colorValueChanged,FFuColor));

  myPolygonOptions->setOptionSelectedCB(FFaDynCB1M(FuiAppearance,this, 
						   onPolygonOptionChanged,int));
  myLinesOptions->setOptionSelectedCB(FFaDynCB1M(FuiAppearance,this,
						 onLinesOptionChanged,int));
  
  FFuUAExistenceHandler::invokeCreateUACB(this);
}


void FuiAppearance::placeWidgets(int width,int height)
{
  // Grid lines for main frames and frame text

  // vertical
  int glV1  = FFuMultUIComponent::getGridLinePos(width, 10, FFuMultUIComponent::FROM_START);
  int glV3  = FFuMultUIComponent::getGridLinePos(width, 10, FFuMultUIComponent::FROM_END);
 
  // horizontal for LOD
  int glH1  = FFuMultUIComponent::getGridLinePos(height,  10, FFuMultUIComponent::FROM_START);
  int glH2  = FFuMultUIComponent::getGridLinePos(height, 280);

  // Horizontal for Color
  int glH3  = FFuMultUIComponent::getGridLinePos(height, glH2 + 10, FFuMultUIComponent::FROM_START );
  int glH4  = FFuMultUIComponent::getGridLinePos(height, 600);

  // Horizontal for Material
  int glH5  = FFuMultUIComponent::getGridLinePos(height, glH4 + 10, FFuMultUIComponent::FROM_START );
  int glH6  = FFuMultUIComponent::getGridLinePos(height, myDialogButtons->getHeightHint(),
						 FFuMultUIComponent::FROM_END );

  // Frame geometry
  myDetailsFrame->setEdgeGeometry  (glV1, glV3 ,glH1 ,glH2 ); 
  this->placeDetails(myDetailsFrame);

  myColorFrame->setEdgeGeometry  (glV1, glV3 ,glH3 ,glH4 );  
  this->placeColor(myColorFrame);

  myMaterialFrame-> setEdgeGeometry  (glV1, glV3 ,glH5 ,glH6 );  
  this->placeMaterial(myMaterialFrame);

  myDialogButtons->setEdgeGeometry(0 , width, height - myDialogButtons->getHeightHint(), height);
}

  
void FuiAppearance::placeDetails(FFuComponentBase *parent)
{
  int width = parent->getWidth();
  int height = parent->getHeight();
  
  int textHeight = myPolygonsLabel->getHeightHint();
  
  int glH1 =  textHeight + FFuMultUIComponent::getGridLinePos(height- textHeight, 333);
  int glH2 =  textHeight + FFuMultUIComponent::getGridLinePos(height- textHeight, 666);
    
 int glV1 = FFuMultUIComponent::getGridLinePos(width, 10, FFuMultUIComponent::FROM_START);
 int glV2 = FFuMultUIComponent::getGridLinePos(width, glV1 + 10+  myPolygonsLabel->getWidthHint() , 
					       FFuMultUIComponent::FROM_START);
 
  int glV3 = FFuMultUIComponent::getGridLinePos(width, 10, FFuMultUIComponent::FROM_END);
 
  myPolygonsLabel->setEdgeGeometry  (glV1,  glV1 + myPolygonsLabel->getWidthHint() ,
				      glH1-(myPolygonsLabel->getHeightHint()/2) ,
				      glH1+(myPolygonsLabel->getHeightHint()/2)+1 ); 

  myLinesLabel->setEdgeGeometry  (glV1,  glV1 + myLinesLabel->getWidthHint() ,
				  glH2-(myLinesLabel->getHeightHint()/2) ,
				  glH2+(myLinesLabel->getHeightHint()/2)+1 ); 
  

  myPolygonOptions->setEdgeGeometry  (glV2, glV3 ,
				      glH1-(myPolygonOptions->getHeightHint()/2) ,
				      glH1+(myPolygonOptions->getHeightHint()/2)+1 ); 

  myLinesOptions ->setEdgeGeometry  (glV2, glV3 ,
				     glH2-(myLinesOptions->getHeightHint()/2) ,
				     glH2+(myLinesOptions->getHeightHint()/2)+1 ); 
}


void FuiAppearance::placeColor(FFuComponentBase *parent)
{
  int width = parent->getWidth();
  int height = parent->getHeight();

  myColorSelector->setEdgeGeometry(10, width-10, 20, height-10);
}


void FuiAppearance::placeMaterial(FFuComponentBase *parent)
{
  int width = parent->getWidth();
  int height = parent->getHeight();
  
  int glV1 = FFuMultUIComponent::getGridLinePos(width, 10, FFuMultUIComponent::FROM_START);
  int glV2 = FFuMultUIComponent::getGridLinePos(width, 
						glV1 + 10+  myTransparencyLabel->getWidthHint() , 
						FFuMultUIComponent::FROM_START);
  
  int glV3 = FFuMultUIComponent::getGridLinePos(width, 10, FFuMultUIComponent::FROM_END);

  int textHeight = myTransparencyLabel->getHeightHint();

  int glH1 =  textHeight + FFuMultUIComponent::getGridLinePos(height- textHeight, 333);
  int glH2 =  textHeight + FFuMultUIComponent::getGridLinePos(height- textHeight, 666);

  myShininessLabel->setEdgeGeometry  (glV1,  glV1 + myShininessLabel->getWidthHint() ,
				      glH1-(myShininessLabel->getHeightHint()/2) ,
				      glH1+(myShininessLabel->getHeightHint()/2)+1 ); 

  myTransparencyLabel->setEdgeGeometry  (glV1,  glV1 + myTransparencyLabel->getWidthHint() ,
					 glH2-(myTransparencyLabel->getHeightHint()/2) ,
					 glH2+(myTransparencyLabel->getHeightHint()/2)+1 ); 
 
  myShininessScale ->setEdgeGeometry  (glV2, glV3 ,
				       glH1-(myShininessLabel->getHeightHint()/2) ,
				       glH1+(myShininessLabel->getHeightHint()/2)+1 ); 

  myTransparencyScale->setEdgeGeometry  (glV2, glV3 ,
					 glH2-(myTransparencyLabel->getHeightHint()/2) ,
					 glH2+(myTransparencyLabel->getHeightHint()/2)+1 ); 
}


void FuiAppearance::disableAdvancedOptions(bool disable)
{
  if (disable)
    {
      myShininessLabel->setSensitivity(false);
      myShininessScale->setSensitivity(false);
      myPolygonOptions->setSensitivity(false);
      myLinesOptions->setSensitivity(false);
      myPolygonsLabel->setSensitivity(false);
      myLinesLabel->setSensitivity(false);
    }
  else
   {
      myShininessLabel->setSensitivity(true);
      myShininessScale->setSensitivity(true);
      myPolygonOptions->setSensitivity(true);
      myLinesOptions->setSensitivity(true);
      myPolygonsLabel->setSensitivity(true);
      myLinesLabel->setSensitivity(true);
    }    
}


bool FuiAppearance::onClose()
{
  this->onDialogButtonClicked(FFuDialogButtons::LEFTBUTTON);
  return true;
}


void FuiAppearance::onDialogButtonClicked(int button)
{
  if (button==FFuDialogButtons::LEFTBUTTON) 
    this->invokeFinishedCB();
}


bool FuiAppearance::updateDBValues(bool)
{
  // optain values from UI
  FuaAppearanceValues values; 
  this->getValues(&values);
  
  // do something elsewhere...
  this->invokeSetAndGetDBValuesCB(&values);
  
  //Re-set values to ensure value correspondance between ui and db
  this->setUIValues(&values);
  return true;
} 
