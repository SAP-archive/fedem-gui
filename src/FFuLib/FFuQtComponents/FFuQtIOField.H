// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_IO_FIELD_H
#define FFU_QT_IO_FIELD_H

#include <QLineEdit>

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuIOField.H"


class FFuQtIOField : public QLineEdit, public FFuIOField,
		     public FFuQtComponentBase
{
  Q_OBJECT

public:
  FFuQtIOField(QWidget* parent = NULL);
  virtual ~FFuQtIOField();

  // Access interface reimplemented from FFuIOField, to do real work:

  virtual void setToolTip(const char* tip);
  virtual void setValue(const char* value);
  virtual std::string getValue() const;

  // Highlighting, reimplemented from FFuIOField, to do real work:

  virtual void highlight();
  virtual void unHighlight();

public slots :

  // Slots for forwarding of signals :

  void fwdTextChanged(const QString&);
  void fwdReturnPressed();

private:
  void setBackgroundColor(int r, int g, int b);

protected:

  // Reimplementation of the QWidget event handelers :

  virtual void focusInEvent(QFocusEvent*);
  virtual void focusOutEvent(QFocusEvent*);

  // Colors and fonts. Reimplemented from FFuQtComponentBase,
  // to make special use of the palette and FontSet:

  virtual void setColors(FFuaPalette aPalette);
  virtual void setFonts (FFuaFontSet aFontSet);

  virtual void setSensitivity(bool makeSensitive);
  virtual bool getSensitivity();

private:
  char* myTip;
};

#endif
