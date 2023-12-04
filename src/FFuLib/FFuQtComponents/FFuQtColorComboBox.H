// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_COLOR_COMBO_BOX_H
#define FFU_QT_COLOR_COMBO_BOX_H

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuColorChooser.H"
#include <QComboBox>


class FFuQtColorComboBox : public QComboBox, public FFuQtComponentBase,
			   public FFuColorChooser
{
  Q_OBJECT

public:
  FFuQtColorComboBox(QWidget* parent, const char* name="FFuQtColorComboBox");
  virtual ~FFuQtColorComboBox() {}

  virtual void setCurrentCol(const FFuColor& rgb);
  virtual void insertCol(const FFuColor& rgb, const std::string& name, int index = -1);
  virtual FFuColor getCurrentCol();
  virtual void enableColorDialog(bool enable);

protected slots:
  void fwdSelectionChanged(int index);
};

#endif
