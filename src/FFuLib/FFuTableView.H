// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_TABLE_VIEW_H
#define FFU_TABLE_VIEW_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include <vector>


class FFuTableView : virtual public FFuComponentBase
{
public:
  FFuTableView() {}
  virtual ~FFuTableView() {}

  // Insert a row at position "row" in the table :
  // Appends at the bottom if row < 0  :

  virtual void addRow(const std::vector<FFuComponentBase*>& rows, int row = -1) = 0;

  // Delete a row or everything if row < 0:

  virtual void deleteRow(int row) = 0;

  // Access the components in the table. Don't delete or reparent :

  virtual FFuComponentBase* getCell(int row, int column) = 0;

  // Access number of rows :

  virtual int getRowCount() const = 0;

  // Set the height/width of all the rows/columns :

  virtual void setRowHeight  (int height) = 0;
  virtual void setColumnWidth(int width ) = 0;

  // Set the height/width of a special row/column :

  virtual void setRowHeight  (int row   , int width) = 0;
  virtual void setColumnWidth(int column, int width) = 0;

  // Do or don't stretch the contents to fit into the height/width of the
  // viewable aera :

  virtual void stretchContentsWidth (bool yesOrNo) = 0;
  virtual void stretchContentsHeight(bool yesOrNo) = 0;
};

#endif
