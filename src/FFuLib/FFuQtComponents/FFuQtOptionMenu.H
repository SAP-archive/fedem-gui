// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_OPTION_MENU_H
#define FFU_QT_OPTION_MENU_H

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuOptionMenu.H"

#include <QComboBox>

class QWheelEvent;


class FFuQtOptionMenu : public QComboBox, public FFuOptionMenu,
			virtual public FFuQtComponentBase
{
  Q_OBJECT

public:
  FFuQtOptionMenu(QWidget* parent = NULL);
  virtual ~FFuQtOptionMenu() {}

  // Add and delete options :

  virtual void setOptions(const std::vector<std::string>& options);
  virtual void setOptions(const std::set<std::string>& options);
  virtual void setOptions(const std::vector<double>& options);
  virtual void setOptions(const std::vector<int>& options);
  virtual void addOption (const char* aText, int index, bool replace);
  virtual void clearOptions();

  // Manage options :

  virtual void selectOption(int optionIndex);
  virtual bool selectOption(const std::string& text, bool notify);
  virtual bool selectDoubleOption(double opt);
  virtual bool selectIntOption(int opt);

  virtual void disableOption(int optionIndex);
  virtual void removeOption (int optionIndex);

  virtual int getSelectedOption() const;
  virtual std::string getSelectedOptionStr() const;
  virtual int getOptionCount() const;

  // Color overriding :

  virtual void setColors(FFuaPalette aPalette);

  virtual int getBasicWidthHint();

protected:
  virtual void wheelEvent(QWheelEvent*);

protected slots:
  void activatedFwd(const QString&);
  void activatedFwd(int);
  void highlightedFwd(int);
};

#endif
