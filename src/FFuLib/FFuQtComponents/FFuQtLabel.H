// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_LABEL_H
#define FFU_QT_LABEL_H

#include <QLabel>

#include "FFuLib/FFuLabel.H"
#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"


class FFuQtLabel : public QLabel, public FFuLabel,
		   public FFuQtComponentBase
{
  Q_OBJECT

public:
  FFuQtLabel(QWidget* parent = NULL);
  virtual ~FFuQtLabel() {}

  virtual void setPixMap(const char** pixmap, int width = 0, int height = 0);
  virtual void setLabel(const char* label);
  virtual void setLabel(const std::string& label);
  virtual void setLabelAlignment(int align);
  virtual std::string getLabel() const;

public slots:
  void fwdLinkActivated(const QString&);
};

#endif
