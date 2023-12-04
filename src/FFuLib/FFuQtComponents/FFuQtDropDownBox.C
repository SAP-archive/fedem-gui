// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuQtDropDownBox.H"

#include <QLabel>
#include <QFrame>
#include <QToolButton>
#include <QGridLayout>
#include <QIcon>
#include <QLinearGradient>
#include <QBrush>
#include <QPalette>

#include "FFuLib/Icons/ExpandDown.xpm"
#include "FFuLib/Icons/ExpandUp.xpm"


FFuQtDropDownBox::FFuQtDropDownBox(QWidget*)
{
  myContentsFrame   = new QFrame;
  myHeadingLabel    = new QLabel("Heading");
  myExpandIconButton = new QToolButton;
  myLayout           = new QGridLayout;

  // Setup label for heading 

  QPalette headingPal(myHeadingLabel->palette());
  QColor lightColor = headingPal.color(QPalette::Window);
  QColor darkColor = headingPal.color(QPalette::Dark);

  QLinearGradient headingGrad;
  headingGrad.setCoordinateMode(QGradient::StretchToDeviceMode);
  headingGrad.setStart(0, 0.5);
  headingGrad.setStart(1, 0.5);
  headingGrad.setColorAt(0, lightColor);
  headingGrad.setColorAt(1, darkColor);

  QBrush headingBrush(headingGrad);
  headingPal.setBrush (QPalette::Window, headingBrush);

  myHeadingLabel->setPalette(headingPal);
  myHeadingLabel->setFrameShadow(QFrame::Raised);
  myHeadingLabel->setFrameShape(QFrame::WinPanel);
  myHeadingLabel->setAutoFillBackground(true);
  QFont boldFont = myHeadingLabel->font();
  boldFont.setBold(true);
  myHeadingLabel->setFont(boldFont);

  int headingHeight = myHeadingLabel->fontMetrics().height()*2;
  myHeadingLabel->setMinimumHeight(headingHeight);
  myHeadingLabel->setMaximumHeight(headingHeight);

  // Set up button that expands and minimizes the box contents

  QIcon upDownIcon;
  upDownIcon.addPixmap(QPixmap(ExpandDown_xpm), QIcon::Normal, QIcon::Off);
  upDownIcon.addPixmap(QPixmap(ExpandUp_xpm), QIcon::Normal, QIcon::On);
  myExpandIconButton->setIcon(upDownIcon);
  myExpandIconButton->setCheckable(true);
  myExpandIconButton->setChecked(true);
  myExpandIconButton->setAutoRaise(true);

  int buttonSize = headingHeight - 2*2 - 2*2;
  myExpandIconButton->setMinimumHeight(buttonSize+1);
  myExpandIconButton->setMinimumWidth(buttonSize);
  myExpandIconButton->setMaximumHeight(buttonSize+1);
  myExpandIconButton->setMaximumWidth(buttonSize);

  // Setup contents frame

  myContentsFrame->setFrameShadow(QFrame::Plain);
  myContentsFrame->setFrameShape(QFrame::StyledPanel);
  myContentsFrame->setMinimumSize(100, 100  );

  // Setup layout and add all the widgets

  myLayout->setContentsMargins(0,0,0,0);
  myLayout->setSpacing(0);

  myLayout->addWidget(myHeadingLabel, 1, 1,1,-1); 
  myLayout->addWidget(myExpandIconButton,1,2,Qt::AlignHCenter);
  myLayout->addWidget(myContentsFrame, 2,1,1,2);
  myLayout->setColumnMinimumWidth(2,headingHeight+2);
  myLayout->setColumnStretch(1,100);
  myLayout->setColumnStretch(2,1);

  this->setLayout(myLayout);

  // Make the expand button work
  connect(myExpandIconButton, SIGNAL(toggled(bool)),
          myContentsFrame, SLOT(setVisible(bool)));
}

void FFuQtDropDownBox::setHeading(const QString& text)
{
  myHeadingLabel->setText(text);
}

void FFuQtDropDownBox::setOpen(bool isOpen)
{
  myExpandIconButton->setChecked(isOpen);
}

void FFuQtDropDownBox::setContentLayout(QLayout* layout)
{
  myContentsFrame->setLayout(layout);
}
