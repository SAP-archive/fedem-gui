// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <Qt3Support/Q3ScrollView>
#include <QResizeEvent>

#include "FFuLib/FFuQtComponents/FFuQtTableView.H"


FFuQtTableView::FFuQtTableView(QWidget* parent, Qt::WindowFlags f) : QFrame(parent,f)
{
  this->setWidget(this);

  IAmSensitive = true;

  // Initialisation of geometry variables :

  myDefaultRowHeight   = 30;
  myDefaultColumnWidth = 50;

  IHaveStretchingWidth = IHaveStretchingHeight = false;

  // Create the scroll view and container widgets :

  myMainView   = new Q3ScrollView(this);
  myMainWidget = new QWidget();
  myMainView->addChild(myMainWidget);
  myMainWidget->resize(0,0);

  // Set scrollbar policies :

  myMainView->setVScrollBarMode(Q3ScrollView::Auto);
  myMainView->setHScrollBarMode(Q3ScrollView::Auto);

  // Set look :

  myMainView->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
}


void FFuQtTableView::addRow(const std::vector<FFuComponentBase*>& rows, int row)
{
  std::vector<QWidget*> rowWidgets;
  for (FFuComponentBase* cell : rows)
    rowWidgets.push_back(dynamic_cast<QWidget*>(cell));

  // Get max height :

  int maxHeight = myDefaultRowHeight;
  for (QWidget* cell : rowWidgets)
    if (cell && cell->height() > maxHeight)
      maxHeight = cell->height();

  // Add it to rowHeights :

  if (row >= 0 && row < (int)myRowHeights.size())
    myRowHeights.insert(myRowHeights.begin()+row, maxHeight);
  else
    myRowHeights.push_back(maxHeight);

  // Add column sizes if needed :

  for (size_t i = myColumnWidths.size(); i < rowWidgets.size(); i++)
    if (rowWidgets[i])
      myColumnWidths.push_back(rowWidgets[i]->width());

  // Add cell widgets :

  if (row >= 0 && row < (int)myRows.size())
    myRows.insert(myRows.begin()+row,rowWidgets);
  else
    myRows.push_back(rowWidgets);

  // Reparent them into the view :

  for (QWidget* cell : rowWidgets)
    if (cell)
    {
      cell->setParent(myMainWidget,Qt::Widget);
      cell->move(0,0);
      cell->show();
    }

  // Set sensitivity :

  for (FFuComponentBase* cell : rows)
    if (cell) cell->setSensitivity(IAmSensitive);

  // Update the view :

  this->updateContents();
}


void FFuQtTableView::deleteRow(int row)
{
  // If row is less than zero, clear everything

  if (row < 0)
  {
    for (std::vector<QWidget*>& row : myRows)
      for (QWidget* cell : row)
        delete cell;
    myRows.clear();
  }
  else if (row < (int)myRows.size())
  {
    for (QWidget* cell : myRows[row])
      delete cell;
    myRows.erase(myRows.begin()+row);
  }
  else
    return;

  this->updateContents();
}


void FFuQtTableView::setRowHeight(int height)
{
  myDefaultRowHeight = height;
  for (int& rHeight : myRowHeights) rHeight = height;
  this->updateContents();
}

void FFuQtTableView::setColumnWidth(int width)
{
  myDefaultColumnWidth = width;
  for (int& cWidth : myColumnWidths) cWidth = width;
  this->updateContents();
}


void FFuQtTableView::setRowHeight(int row, int height)
{
  if ((int)myRowHeights.size() > row)
    myRowHeights[row] = height;
  this->updateContents();
}

void FFuQtTableView::setColumnWidth(int column, int width)
{
  if ((int)myColumnWidths.size() > column)
    myColumnWidths[column] = width;
  this->updateContents();
}


void FFuQtTableView::dragColumn(int column, int change)
{
  if ((int)myColumnWidths.size() > column)
    myColumnWidths[column] += change;
  this->updateContents();
}

void FFuQtTableView::dragRow(int row, int change)
{
  if ((int)myRowHeights.size() > row)
    myRowHeights[row] += change;
  this->updateContents();
}


FFuComponentBase* FFuQtTableView::getCell(int row, int column)
{
  if (row >= 0  && row < (int)myRows.size())
    if (column >= 0 && column < (int)myRows[row].size())
      return dynamic_cast<FFuComponentBase*>(myRows[row][column]);

  return NULL;
}


void FFuQtTableView::stretchContentsHeight(bool yesOrNo)
{
  IHaveStretchingHeight = yesOrNo;
  this->updateContents();
}

void FFuQtTableView::stretchContentsWidth(bool yesOrNo)
{
  IHaveStretchingWidth = yesOrNo;
  this->updateContents();
}


void FFuQtTableView::updateContents()
{
  int xpos = 0, ypos = 0;
  float widthScale = 1.0f, heightScale = 1.0f;
  size_t r, c;

  if (IHaveStretchingHeight && !myRowHeights.empty())
  {
    int totHeight = 0;
    for (int h : myRowHeights) totHeight += h;
    heightScale = (float)myMainView->height() / totHeight;
  }

  if (IHaveStretchingWidth && !myColumnWidths.empty())
  {
    int totWidth = 0;
    for (int w : myColumnWidths) totWidth += w;
    // Subtract 4 extra pixels in the scale calculation, to avoid the scroll bars when not needed.
    // Notice also that xpos is started on 2 (instead of 0) below (KMO 13.09.2017).
    widthScale = (float)(myMainView->width()-2*myMainView->lineWidth()-4) / totWidth;
  }

  // Set content geometry :
  for (r = ypos = 0; r < myRows.size(); r++)
  {
    int h = heightScale*myRowHeights[r];
    for (c = 0, xpos = 2; c < myRows[r].size(); c++)
    {
      int w = widthScale*myColumnWidths[c];
      if (myRows[r][c])
        myRows[r][c]->setGeometry(xpos, ypos, w, h);
      xpos += w;
    }
    ypos += h;
  }

  // Resize the container widget :
  myMainWidget->resize(xpos, ypos);
}


void FFuQtTableView::resizeEvent(QResizeEvent* e)
{
  int height = e->size().height();
  int width  = e->size().width();

  myMainView->setGeometry(0, 0, width, height);

  if (myMainView->horizontalScrollBar()->isVisible())
    height -= myMainView->horizontalScrollBar()->height();

  if (myMainView->verticalScrollBar()->isVisible())
    width -= myMainView->verticalScrollBar()->width();

  this->updateContents();
}


void FFuQtTableView::setSensitivity(bool isSensitive)
{
  IAmSensitive = isSensitive;

  FFuComponentBase* ffCell;
  for (std::vector<QWidget*>& row : myRows)
    for (QWidget* qCell : row)
      if ((ffCell = dynamic_cast<FFuComponentBase*>(qCell)))
        ffCell->setSensitivity(isSensitive);
}
