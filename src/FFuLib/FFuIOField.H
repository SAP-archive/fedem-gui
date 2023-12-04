// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_IO_FIELD_H
#define FFU_IO_FIELD_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"


/*!
  A text field class, whith extended checking of user input.
  Different value checking modes prevents the user to write illegal letters.

  \author Jacob Storen
  \date Dec 14 1998
*/

class FFuIOField : virtual public FFuComponentBase
{
public:
  FFuIOField();
  virtual ~FFuIOField() {}

  // Input control modes

  enum {NOCHECK, DOUBLECHECK, INTEGERCHECK};

  // Acceptance policy

  enum {ENTERONLY, FOCUSOUT, SMARTFOCUS};

  // Display modes for double

  enum {SCIFI, DECIMAL, AUTO};

  // Set checking mode and policy for when to call the Accept CB's

  void setInputCheckMode(int mode) { myInputCheckingMode = mode; }
  void setAcceptPolicy  (int mode) { myAcceptPolicy      = mode; }

  // Set double display mode and precision and the look of a zero value

  void setDoubleDisplayMode     (int mode     ) { myDoubleDisplayMode      = mode;      }
  void setDoubleDisplayPrecision(int precision) { myDoubleDisplayPrecision = precision; }
  void setZeroDisplayPrecision  (int precision) { myZeroDisplayPrecision   = precision; }

  void setDoubleDisplayMode(int mode, int precision, int zeroPrecision) {
    this->setDoubleDisplayMode(mode);
    this->setDoubleDisplayPrecision(precision);
    this->setZeroDisplayPrecision(zeroPrecision);
  }

  /////////////////////////////////////////////////////
  //
  // Methods for UI Lib dependent class to reimplement :
  //

  // Highlight the text :

  virtual void highlight  () = 0;
  virtual void unHighlight() = 0;

  // Set and get char value :

  void setValue(const std::string& value);
  virtual void setValue(const char* value) = 0;
  virtual std::string getValue() const = 0;

  // Recommended field sizes (TODO should be font dependent)

  virtual int getRecommendedDoubleFieldWidth() const { return 150; }
  virtual int getRecommendedIntegerFieldWidth() const { return 50; }

  //
  //////////////////////////////////////////////////////

  // Set Dynamic CB to be called when the user has accepted what he wrote :

  void setAcceptedCB(const FFaDynCB1<char*>& aDynCB);
  void setAcceptedCB(const FFaDynCB1<const std::string&>& aDynCB);
  void setAcceptedCB(const FFaDynCB1<double>& aDynCB);
  void setAcceptedCB(const FFaDynCB1<int>& aDynCB);

  // Access methods :

  double getDouble() const;
  int    getInt   () const;
  double getDoubleFromText() const;
  int    getIntFromText   () const;

  void setValue(double d);
  void setValue(int i);
  void setUseCustomBgColor(bool useBg) { useCustomBackgroundColor = useBg; }

  // Manual value checking. Use it to do final checking on the text :

  bool isInt() const;
  bool isDouble() const;
  bool isChanged() const { return IAmChanged > 0; }
  bool isEdited() const { return IAmChanged > 1; }

protected:

  // These must be called by UILib dependent subclass on appropriate times :

  void rtPressed() { this->callAcceptedCBs(); }
  void tChanged(const std::string& s);
  void keybFocusOut(bool isReal); // "real" focus out means switching to
  void keybFocusIn();             // another widget, not to nothing

private:

  // Method to call the Acceptance callbacks :

  void callAcceptedCBs();

  // Internal methods for value checking and modifing the look of a double :

  static int checkValue(const std::string& str, int type, int check);

  static void removeWhiteSpace(const std::string& instr, char* outstr, size_t n);

  // Field value checking interface

  enum {INTEGER,FLOAT,DOUBLE};
  enum {CH_TEMP,CH_FINAL};
  enum {STR_OK,STR_EMPTY,STR_GARBAGE,STR_LARGE,STR_SMALL};

protected:

  // Used with value checking on every tChanged()

  std::string myLastValue;

  // Backup of value on focus in

  mutable double myLastValidDouble;
  mutable int    myLastValidInt;

  // Acceptance policy :

  int myAcceptPolicy;

  // Display and checking modes :

  int myInputCheckingMode;
  int myDoubleDisplayMode;
  int myDoubleDisplayPrecision;
  int myZeroDisplayPrecision;

  bool useCustomBackgroundColor;

private:

  // Callback pointers :

  FFaDynCB1<char*>              myTextAcceptedCB;
  FFaDynCB1<const std::string&> myStringAcceptedCB;
  FFaDynCB1<double>             myDoubleAcceptedCB;
  FFaDynCB1<int>                myIntAcceptedCB;

  // Status used internally in Acceptance policy :

  bool IAmGettingRealFocusIn;
  mutable char IAmChanged;
};

#endif
