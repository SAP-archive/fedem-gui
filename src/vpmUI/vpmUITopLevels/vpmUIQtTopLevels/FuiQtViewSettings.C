// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtScale.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtColorDialog.H"
#include "FFuLib/FFuQtComponents/FFuQtPushButton.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "FuiQtViewSettings.H"


//////////////////////////////////////////////////////////////////////
//
//  Qt implementation of static create method in FuiViewSettings
//  Used instead of constructor :
//

FuiViewSettings* FuiViewSettings::create(int xpos, int ypos,
					 int width,int height,
					 const char* title,
					 const char* name)
{
  return new FuiQtViewSettings(xpos,ypos,width,height,title,name);
}


//////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor :
//

FuiQtViewSettings::FuiQtViewSettings(int xpos, int ypos,
				     int width,int height,
				     const char* title,
				     const char* name)
  : FFuQtTopLevelShell(NULL,xpos,ypos,width,height,title,name,Qt::WindowStaysOnTopHint)
{
  FFuQtLabelFrame * qtSymbolsFrame;
  FFuQtLabelFrame * qtDefaultColorFrame;
  FFuQtLabelFrame * qtViewerOptionsFrame;
  mySymbolsFrame = qtSymbolsFrame = new FFuQtLabelFrame(this);
  myDefaultColorFrame = qtDefaultColorFrame = new FFuQtLabelFrame(this);
  myViewerOptionsFrame = qtViewerOptionsFrame = new FFuQtLabelFrame(this);

  myCloseButton = new FFuQtPushButton(this);

  // Symbols
  FFuQtFrame *qtSymbolColFrames[FuiViewSettings::NSYMBOLS];

  myOnOffLabel = new FFuQtLabel(qtSymbolsFrame);
  myColorLabel = new FFuQtLabel(qtSymbolsFrame);
  mySymbolSizeLabel = new FFuQtLabel(qtSymbolsFrame);
  myLineWidthLabel = new FFuQtLabel(qtSymbolsFrame);

  for (int i = 0; i < FuiViewSettings::NSYMBOLS; i++)
    {
      mySymbolToggles[i]                               = new FFuQtToggleButton(qtSymbolsFrame);
      mySymbolColFrames[i]      = qtSymbolColFrames[i] = new FFuQtFrame(qtSymbolsFrame);
      mySymbolColEditButtons[i]                        = new FFuQtPushButton(qtSymbolsFrame);
      mySymbolColDialog[i]                             = new FFuQtColorDialog(xpos-345,ypos+40);

      qtSymbolColFrames[i]->setFrameStyle(QFrame::Panel | QFrame::Sunken);
      qtSymbolColFrames[i]->setLineWidth( 2 );
    }

  myRevoluteJointToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myBallJointToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myRigidJointToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myFreeJointToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myPrismaticJointToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myCylindricJointToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myCamJointToggle = new FFuQtToggleButton(qtSymbolsFrame);

  myBeamTriadsToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myBeamsToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myBeamCSToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myPartsToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myPartCSToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myInternalPartCSsToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myPartCoGCSToggle = new FFuQtToggleButton(qtSymbolsFrame);

  myRefPlaneToggle = new FFuQtToggleButton(qtSymbolsFrame);
  mySeaStateToggle = new FFuQtToggleButton(qtSymbolsFrame);
  myWavesToggle = new FFuQtToggleButton(qtSymbolsFrame);

  FFuQtScale* qtLineWidthScale;
  mySymbolSizeField = new FFuQtIOField(qtSymbolsFrame);
  myLineWidthScale = qtLineWidthScale = new FFuQtScale(qtSymbolsFrame);
  qtLineWidthScale->setOrientation(Qt::Horizontal);

  // Default colors
  FFuQtScale* qtFogScale;
  FFuQtFrame* qtGroundedColFrame;
  FFuQtFrame* qtUnattachedColFrame;
  FFuQtFrame* qtBackgroundColFrame;

  myGroundedColLabel = new FFuQtLabel(qtDefaultColorFrame);
  myUnattacedColLabel = new FFuQtLabel(qtDefaultColorFrame);
  myBackgroundColLabel = new FFuQtLabel(qtDefaultColorFrame);

  myGroundedColEditButton = new FFuQtPushButton(qtDefaultColorFrame);
  myUnattachedColEditButton = new FFuQtPushButton(qtDefaultColorFrame);
  myBackgroundColEditButton = new FFuQtPushButton(qtDefaultColorFrame);

  myGroundedColFrame = qtGroundedColFrame = new FFuQtFrame(qtDefaultColorFrame);
  myUnattachedColFrame = qtUnattachedColFrame = new FFuQtFrame(qtDefaultColorFrame);
  myBackgroundColFrame = qtBackgroundColFrame = new FFuQtFrame(qtDefaultColorFrame);

  qtUnattachedColFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  qtBackgroundColFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  qtGroundedColFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  qtUnattachedColFrame->setLineWidth( 2 );
  qtGroundedColFrame->setLineWidth( 2 );
  qtBackgroundColFrame->setLineWidth( 2 );

  // viewer options
  myFogToggle = new FFuQtToggleButton(qtViewerOptionsFrame);
  myFogVisibilityLabel = new FFuQtLabel(qtViewerOptionsFrame);
  mySimpleTransparencyToggle = new FFuQtToggleButton(qtViewerOptionsFrame);
  myAntialiazingToggle = new FFuQtToggleButton(qtViewerOptionsFrame);

  myFogScale = qtFogScale = new FFuQtScale(qtViewerOptionsFrame);
  qtFogScale->setOrientation(Qt::Horizontal);

  // color editors
  myGroundedColDialog   = new FFuQtColorDialog();
  myUnattachedColDialog = new FFuQtColorDialog();
  myBackgroundColDialog = new FFuQtColorDialog();

  // call to the UI independent widget manipulation
  this->initWidgets();
}
