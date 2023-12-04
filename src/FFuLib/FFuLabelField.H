// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFULABELFIELD_H
#define FFULABELFIELD_H

#include "FFuLib/FFuBase/FFuMultUIComponent.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

class FFuLabel;
class FFuIOField;

class FFuLabelField : virtual public FFuMultUIComponent
{
public:
  FFuLabelField();
  virtual ~FFuLabelField() {}

  static FFuLabelField* create(FFuComponentBase* parent);

  void   setLabel(const char* label);
  void   setValue(double value);
  void   setValue(const std::string& value);
  double getValue();
  std::string getText();

  // Field Accept :

  void   setAcceptedCB(const FFaDynCB1<double>& aDynCB);

  // Label geometry :

  int    getLabelWidth();
  void   setLabelWidth(int width);
  void   setLabelMargin(int margin);
  void   setRelativeLabelWidth(int percent);

  // To prevent editing :

  virtual void setSensitivity(bool makeSensitive);
  virtual bool getSensitivity();

  // Overriding parent toolTip
  virtual void setToolTip(const char* tip);

  // Public members to ease access. Do Not Delete ! ;-)
  FFuLabel*   myLabel;
  FFuIOField* myField;

  enum
  {
    FFU_AUTO,   // Uses LabelsizeHint, default
    FFU_FIXED,  // Uses provided label width
    FFU_RELATIVE// Uses provided relative sizes
  };

protected:
  virtual void placeWidgets(int width, int height);

private:
  int myLabelWidth;
  int myLabelMargin;
  int myRelativeLabelWidth;
  int myResizePolicy;
};

#endif
