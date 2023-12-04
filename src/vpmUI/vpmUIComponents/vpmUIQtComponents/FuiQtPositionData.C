// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <array>

#include "FFuLib/FFuQtComponents/FFuQtLabelFrame.H"
#include "FFuLib/FFuQtComponents/FFuQtOptionMenu.H"
#include "FFuLib/FFuQtComponents/FFuQtIOField.H"
#include "FFuLib/FFuQtComponents/FFuQtLabel.H"
#include "FFuLib/FFuQtComponents/FFuQtToggleButton.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtQueryInputField.H"
#include "vpmUI/vpmUIComponents/vpmUIQtComponents/FuiQtPositionData.H"


FuiQtPositionData::FuiQtPositionData(QWidget* parent, int xpos, int ypos,
                                     int width, int height, const char* name)
  : FFuQtMultUIComponent(parent,xpos,ypos,width,height,name)
{
  FuiQtQueryInputField* myQtRotRefCSField;
  FuiQtQueryInputField* myQtPosRefCSField;

  FFuQtLabel*  qLabel;
  QGridLayout* gLayout;
  QVBoxLayout* vLayout;

  std::array<FFuQtIOField*,9> lineEdit;
  int i;

  this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  QGridLayout* myLayout = new QGridLayout(this);
  myLayout->setContentsMargins(2,2,2,2);
  myLayout->setSpacing(2);

  // The translation frame
  myTranslationFrame = new QGroupBox(this);
  myTranslationFrame->setTitle("Position");
  myTranslationFrame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  vLayout = new QVBoxLayout();
  vLayout->setContentsMargins(3,3,3,3);
  vLayout->setSpacing(0);
  vLayout->setAlignment(Qt::AlignTop);

  gLayout = new QGridLayout();
  gLayout->addWidget(new QLabel("Reference CS", myTranslationFrame), 0, 0);
  gLayout->addWidget(new QLabel("Coordinate type", myTranslationFrame), 0, 1);

  myQtPosRefCSField = new FuiQtQueryInputField(myTranslationFrame);
  myQtPosRefCSField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  gLayout->addWidget(myQtPosRefCSField, 1, 0);

  FFuQtOptionMenu* myQtPosViewTypeMenu = new FFuQtOptionMenu(myTranslationFrame);
  myQtPosViewTypeMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  gLayout->addWidget(myQtPosViewTypeMenu, 1, 1);

  vLayout->addLayout(gLayout);

  gLayout = new QGridLayout();
  gLayout->setSpacing(2);

  for (i = 0; i < 3; i++) {
    lineEdit[i] = new FFuQtIOField(myTranslationFrame);
    gLayout->addWidget(lineEdit[i], 1, i);
    myLabels.push_back(qLabel = new FFuQtLabel(myTranslationFrame));
    gLayout->addWidget(qLabel, 0, i);
  }
  vLayout->addLayout(gLayout);
  myTranslationFrame->setLayout(vLayout);
  myLayout->addWidget(myTranslationFrame, 0, 0, 2, 1, Qt::AlignTop);

  // The rotation frame
  myRotationFrame = new QGroupBox(this);
  myRotationFrame->setTitle("Orientation");
  myRotationFrame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  vLayout = new QVBoxLayout();
  vLayout->setContentsMargins(3,3,3,3);
  vLayout->setSpacing(0);
  vLayout->setAlignment(Qt::AlignTop);

  gLayout = new QGridLayout();
  gLayout->addWidget(new QLabel("Reference CS", myRotationFrame), 0, 0);
  gLayout->addWidget(new QLabel("Coordinate type", myRotationFrame), 0, 1);

  myQtRotRefCSField = new FuiQtQueryInputField(myRotationFrame);
  myQtRotRefCSField->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  gLayout->addWidget(myQtRotRefCSField, 1, 0);

  FFuQtOptionMenu* myQtRotViewTypeMenu = new FFuQtOptionMenu(myRotationFrame);
  myQtRotViewTypeMenu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  gLayout->addWidget(myQtRotViewTypeMenu, 1, 1);

  vLayout->addLayout(gLayout);

  gLayout = new QGridLayout();
  gLayout->setSpacing(2);

  for (i = 3; i < 9; i++)
    lineEdit[i] = new FFuQtIOField(myRotationFrame);
  for (i = 3; i < 6; i++)
    gLayout->addWidget(lineEdit[i], 1, i-3);
  for (i = 6; i < 9; i++)
    gLayout->addWidget(lineEdit[i], 3, i-6);
  for (i = 3; i < 9; i++) {
    myLabels.push_back(qLabel = new FFuQtLabel(myRotationFrame));
    if (i < 6)
      gLayout->addWidget(qLabel, 0, i-3);
    else
      gLayout->addWidget(qLabel, 2, i-6);
  }
  vLayout->addLayout(gLayout);
  myRotationFrame->setLayout(vLayout);
  myLayout->addWidget(myRotationFrame, 0, 1, Qt::AlignTop);

  // Position follow toggle group:
  FFuQtLabelFrame* followFrame = new FFuQtLabelFrame(this);
  followFrame->setLabel("Relative positioning of Triads");
  followFrame->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
  vLayout = new QVBoxLayout();
  vLayout->setContentsMargins(3,3,3,3);
  vLayout->setSpacing(2);
  vLayout->setAlignment(Qt::AlignTop);

  FFuQtToggleButton* masterToggle = new FFuQtToggleButton();
  masterToggle->setText("Master triad follows joint");
  vLayout->addWidget(masterToggle);

  FFuQtToggleButton* slaveToggle = new FFuQtToggleButton();
  slaveToggle->setText("Slave triad follows joint");
  vLayout->addWidget(slaveToggle);

  followFrame->setLayout(vLayout);
  myLayout->addWidget(followFrame, 1, 1, Qt::AlignTop);

  myQtPosRefCSField->setMinimumHeight(myQtRotViewTypeMenu->getHeightHint());
  myQtRotRefCSField->setMinimumHeight(myQtRotViewTypeMenu->getHeightHint());

  myPosRefCSField = myQtPosRefCSField;
  myRotRefCSField = myQtRotRefCSField;

  myPosViewTypeMenu = myQtPosViewTypeMenu;
  myRotViewTypeMenu = myQtRotViewTypeMenu;

  for (FFuQtIOField* field : lineEdit)
    myFields.push_back(field);

  myTriadPosFollowFrame = followFrame;
  myMasterFollowToggle = masterToggle;
  mySlaveFollowToggle = slaveToggle;

  this->initWidgets();
}


int FuiQtPositionData::getHeightHint()
{
  return this->sizeHint().height();
}

int FuiQtPositionData::getWidthHint()
{
  return this->sizeHint().width();
}


void FuiQtPositionData::setPosLabel(const std::string& text)
{
  myTranslationFrame->setTitle(text.c_str());
}

void FuiQtPositionData::setRotLabel(const std::string& text)
{
  myRotationFrame->setTitle(text.c_str());
}


void FuiQtPositionData::popUpRotUI(bool onOff)
{
  if (onOff)
    myRotationFrame->show();
  else
    myRotationFrame->hide();
}

void FuiQtPositionData::popUpPosUI(bool onOff)
{
  if (onOff)
    myTranslationFrame->show();
  else
    myTranslationFrame->hide();
}
