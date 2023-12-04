// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuQtComponents/FFuQtTable.H"


FFuQtTable::FFuQtTable(QWidget* parent, const char* name) : Q3Table(parent, name)
{
  this->setWidget(this);

  QObject::connect(this,SIGNAL(selectionChanged()),
		   this,SLOT(fwdSelectionChanged()));
  QObject::connect(this,SIGNAL(currentChanged(int,int)),
		   this,SLOT(fwdCurrentCellChanged(int,int)));
  QObject::connect(this,SIGNAL(clicked(int,int,int,const QPoint&)),
		   this,SLOT(fwdCellClicked(int,int,int,const QPoint&)));
  QObject::connect(this,SIGNAL(doubleClicked(int,int,int,const QPoint&)),
		   this,SLOT(fwdCellDoubleClicked(int,int,int,const QPoint&)));
  QObject::connect(this,SIGNAL(pressed(int,int,int,const QPoint&)),
		   this,SLOT(fwdCellPressed(int,int,int,const QPoint&)));
  QObject::connect(this->horizontalHeader(),SIGNAL(sizeChange(int,int,int)),
		   this,SLOT(fwdColumnResized(int,int,int)));
  QObject::connect(this,SIGNAL(valueChanged(int,int)),
		   this,SLOT(fwdCellValueChanged(int,int)));
}


void FFuQtTable::addRow(const std::vector<FFuComponentBase*>& cells, int row)
{
  int rowCount = this->numRows();
  int colCount = this->numCols();

  if (colCount > (int)cells.size())
    this->setNumCols(cells.size());

  if (row < 0 || row >= rowCount) { // append
    row = this->numRows();
    this->setNumRows(rowCount + 1);
  }

  // Add widgets
  QWidget* cell;
  for (size_t col = 0; col < cells.size(); col++)
    if ((cell = dynamic_cast<QWidget*>(cells[col])))
      this->setCellWidget(row, col, cell);
}

void FFuQtTable::deleteRow(int row)
{
  this->removeRow(row);
}

void FFuQtTable::deleteColumn(int col)
{
  this->removeColumn(col);
}

void FFuQtTable::setColumnLabel(int col, const std::string& text)
{
  this->horizontalHeader()->setLabel(col, QString(text.c_str()));
}

std::string FFuQtTable::getColumnLabel(int col)
{
  return std::string(this->horizontalHeader()->label(col));
}

void FFuQtTable::setRowLabel(int row, const std::string& text)
{
  this->verticalHeader()->setLabel(row, QString(text.c_str()));
}

void FFuQtTable::showColumnHeader(bool show)
{
  if (show) {
    this->setTopMargin(this->horizontalHeader()->height());
    this->horizontalHeader()->show();
  }
  else {
    this->setTopMargin(0);
    this->horizontalHeader()->hide();
  }
}

void FFuQtTable::showRowHeader(bool show)
{
  if (show) {
    this->setLeftMargin(this->verticalHeader()->width());
    this->verticalHeader()->show();
  }
  else {
    this->setLeftMargin(0);
    this->verticalHeader()->hide();
  }
}

void FFuQtTable::setColumnHeaderHeight(int height)
{
  this->setTopMargin(height);
}

void FFuQtTable::setRowHeaderWidth(int width)
{
  this->setLeftMargin(width);
}

int FFuQtTable::getColumnHeaderHeight()
{
  return this->topMargin();
}

int FFuQtTable::getRowHeaderWidth()
{
  return this->leftMargin();
}

void FFuQtTable::showTableGrid(bool show)
{
  this->setShowGrid(show);
}

void FFuQtTable::setSelectionPolicy(int policy)
{
  switch (policy) {
  case SINGLE:
    this->setSelectionMode(Q3Table::Single);
    break;

  case MULTI:
    this->setSelectionMode(Q3Table::Multi);
    break;

  case SINGLE_ROW:
    this->setSelectionMode(Q3Table::SingleRow);
    break;

  case MULTI_ROW:
    this->setSelectionMode(Q3Table::MultiRow);
    break;

  case NO_SELECTION:
    this->setSelectionMode(Q3Table::NoSelection);
    break;

  default:
    this->setSelectionMode(Q3Table::Single);
    break;
  }
}

int FFuQtTable::getSelectionPolicy()
{
  switch (this->selectionMode()) {
  case Q3Table::Multi:
    return FFuTable::MULTI;
  case Q3Table::Single:
    return FFuTable::SINGLE;
  case Q3Table::NoSelection:
    return FFuTable::NO_SELECTION;
  case Q3Table::SingleRow:
    return FFuTable::SINGLE_ROW;
  case Q3Table::MultiRow:
    return FFuTable::MULTI_ROW;
  default:
    return -1;
  }
}

void FFuQtTable::insertWidget(int row, int col, FFuComponentBase* item)
{
  if (row >= this->numRows() || col >= this->numCols()) return;

  this->clearCell(row, col);
  QWidget* cell = dynamic_cast<QWidget*>(item);
  if (cell)
    this->setCellWidget(row, col, (QWidget*)cell);
}

FFuComponentBase* FFuQtTable::getWidget(int row, int col)
{
  QWidget* cell = this->cellWidget(row, col);
  if (!cell) return 0;

  FFuComponentBase* ffCell = dynamic_cast<FFuComponentBase*>(cell);

  return ffCell;
}

void FFuQtTable::insertText(int row, int col, const std::string& text)
{
  this->setText(row, col, QString(text.c_str()));
}

std::string FFuQtTable::getText(int row, int col)
{
  return this->text(row,col).toStdString();
}

void FFuQtTable::insertComboItem(int row, int col, const std::vector<std::string>& items)
{
  // Removes the widget containe in the cell, if any
  // Isn't it kind of strange that QTable allows both
  // a QWidget and a QTableItem in the same cell??
  // Is that a book keeping flaw?
  this->clearCellWidget(row, col);

  QStringList list;
  for (const std::string& item : items)
    list.append(QString(item.c_str()));

  this->setItem(row, col, new Q3ComboTableItem(this, list));
}

bool FFuQtTable::isComboItem(int row, int col)
{
  Q3TableItem* item = this->item(row, col);

  if (item && (item->rtti() == COMBO))
    return true;
  else
    return false;
}

bool FFuQtTable::isCheckItem(int row, int col)
{
  Q3TableItem* item = this->item(row, col);

  if (item && (item->rtti() == CHECK))
    return true;
  else
    return false;
}

void FFuQtTable::setComboItemCurrent(int row, int col, int i)
{
  if (!this->isComboItem(row, col)) return;

  Q3TableItem* item = this->item(row, col);

  ((Q3ComboTableItem*)item)->setCurrentItem(i);
}

int FFuQtTable::getComboItemSelection(int row, int col)
{
  if (!isComboItem(row, col)) return -1;

  Q3TableItem* item = this->item(row, col);
  return ((Q3ComboTableItem*)item)->currentItem();
}

void FFuQtTable::insertCheckBoxItem(int row, int col, const std::string& text, bool checked)
{
  // Removes widget already contained in the cell, if any
  // Shouldn't this be done by Qt??
  
  if (!isInsideTable(row, col))
    return;

  clearCellWidget(row, col);

  Q3CheckTableItem* item = new Q3CheckTableItem(this, QString(text.c_str()));
  item->setChecked(checked);
  this->setItem(row, col, item);
}

bool FFuQtTable::isInsideTable(int row, int col)
{
  if (row >= this->numRows() || col >= this->numCols())
    return false;
  else
    return true;
}

bool FFuQtTable::getCheckBoxItemToggle(int row, int col)
{
  if (!this->isInsideTable(row, col))
    return false;

  if (!isCheckItem(row, col))
    return false; 

  Q3TableItem* item = this->item(row, col);
  return ((Q3CheckTableItem*) item)->isChecked();
}

void FFuQtTable::setCheckBoxItemToggle(int row, int col, bool toggle)
{
  if (!isInsideTable(row, col)) return; 
  if (!isCheckItem(row, col)) return;

  Q3TableItem* item = this->item(row, col);
  ((Q3CheckTableItem*) item)->setChecked(toggle);
}

void FFuQtTable::clearCellContents(int row, int col)
{
  if (!isInsideTable(row, col)) return;
  this->clearCellWidget(row, col);
}

int FFuQtTable::getNumberRows()
{
  return this->numRows();
}

int FFuQtTable::getNumberColumns()
{
  return this->numCols();
}

void FFuQtTable::setNumberRows(int num)
{
  this->setNumRows(num);
}

void FFuQtTable::setNumberColumns(int num)
{
  this->setNumCols(num);
}

int FFuQtTable::getRowHeight(int row)
{
  return this->rowHeight(row);
}

int FFuQtTable::getColumnWidth(int col)
{
  return this->columnWidth(col);
}

void FFuQtTable::setColumnWidth(int col, int width)
{
  this->Q3Table::setColumnWidth(col, width);
}

void FFuQtTable::setRowHeight(int row, int height)
{
  this->Q3Table::setRowHeight(row, height);
}

void FFuQtTable::stretchRowHeight(int row, bool stretchable)
{
  this->setRowStretchable(row, stretchable);
}

void FFuQtTable::stretchColWidth(int col, bool stretchable)
{
  this->setColumnStretchable(col, stretchable);
}

void FFuQtTable::adjustColumnWidth(int col)
{
  this->adjustColumn(col);
}

void FFuQtTable::adjustRowHeight(int row)
{
  this->adjustRow(row);
}

int FFuQtTable::getCurrentRow()
{
  return this->currentRow();
}

int FFuQtTable::getCurrentCol()
{
  return this->currentColumn();
}

void FFuQtTable::setSensitivity(bool isSensitive)
{
  this->setEnabled(isSensitive);
  // TODO fix sensitivity problems
  // on widgets inheriting FFuComponentBase
}

void FFuQtTable::setCellSensitivity(int row, int col, bool isSensitive)
{
  FFuComponentBase* ffuCell = this->getWidget(row,col);
  Q3TableItem* item = this->item(row,col);

  // For some strange reason, QTable allows a cell
  // to be occupied by both a widget and a QTableItem.

  if (ffuCell)
    ffuCell->setSensitivity(isSensitive);

  if (item) 
    item->setEnabled(isSensitive);
}

void FFuQtTable::setTableReadOnly(bool ro)
{
  this->setReadOnly(ro);
}

void FFuQtTable::setTableRowReadOnly(int row, bool ro)
{
  this->setRowReadOnly(row, ro);
}

void FFuQtTable::setTableColumnReadOnly(int col, bool ro)
{
  this->setColumnReadOnly(col, ro);
}


void FFuQtTable::fwdSelectionChanged()
{
  mySelectionChangedCB.invoke();
}

void FFuQtTable::fwdCurrentCellChanged(int row, int col)
{
  myCurrentCellChangedCB.invoke(row, col);
}

void FFuQtTable::fwdCellClicked(int row, int col, int button, const QPoint&)
{
  myCellClickedCB.invoke(row, col, button);
}

void FFuQtTable::fwdCellDoubleClicked(int row, int col, int button, const QPoint&)
{
  myCellDoubleClickedCB.invoke(row, col, button);
}

void FFuQtTable::fwdCellPressed(int row, int col, int button, const QPoint&)
{
  myCellPressedCB.invoke(row, col, button);
}

void FFuQtTable::fwdColumnResized(int col, int oldSize, int newSize)
{
  myColumnResizedCB.invoke(col, oldSize, newSize);
}

void FFuQtTable::fwdCellValueChanged(int row, int col)
{
  myCellValueChangedCB.invoke(row, col);
}
