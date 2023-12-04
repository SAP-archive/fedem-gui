// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_SELECTION_DIALOG_H
#define FFU_QT_SELECTION_DIALOG_H

#include <QDialog>
#include <string>
#include <vector>

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuDialogType.H"

class QListWidget;
class QListWidgetItem;
class QFrame;


class FFuQtSelectionDialog : public QDialog, public FFuQtComponentBase
{
  Q_OBJECT;

public:
  FFuQtSelectionDialog(const std::string& msgText, int dialogType,
                       const std::vector<std::string>& buttonTexts);
  virtual ~FFuQtSelectionDialog() {}

  void setList(const std::vector<std::string>& selectionList);
  int getSelection() const;

  virtual int execute();

private slots:
  void onButtonClicked(int buttonId);

private:
  int myClickedButtonId;
  QListWidget* myList;
  QFrame* mySeparator;
  std::vector<QListWidgetItem*> myItems;
};

#endif
