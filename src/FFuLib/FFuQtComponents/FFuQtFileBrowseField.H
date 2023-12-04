// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_FILE_BROWSE_FIELD_H
#define FFU_QT_FILE_BROWSE_FIELD_H

#include "FFuLib/FFuQtBaseClasses/FFuQtMultUIComponent.H"
#include "FFuLib/FFuFileBrowseField.H"


class FFuQtFileBrowseField : public FFuQtMultUIComponent, public FFuFileBrowseField
{
public:
  FFuQtFileBrowseField(QWidget* parent, const char* name = "FFuQtFileBrowseField");
  virtual ~FFuQtFileBrowseField() {}

  virtual void setSensitivity(bool s) { this->FFuFileBrowseField::setSensitivity(s); }
  virtual bool getSensitivity() { return this->FFuFileBrowseField::getSensitivity(); }

private:
  virtual void createFileDialog(const std::string& fileName);
  virtual std::string getSelectedFile();
};

#endif
