// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_QT_TABLE_VIEW_H
#define FFU_QT_TABLE_VIEW_H

#include <QFrame>

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuTableView.H"

class Q3ScrollView;
class QResizeEvent;


class FFuQtTableView : public QFrame, virtual public FFuQtComponentBase,
                       public FFuTableView
{
  Q_OBJECT

public:
  FFuQtTableView(QWidget* parent = NULL, Qt::WindowFlags f = Qt::Widget);
  virtual ~FFuQtTableView() {}

  // Insert a row at position "row" in the table :
  // Append at the bottom if row is negative :

  virtual void addRow(const std::vector<FFuComponentBase*>& rows, int row = -1);

  // Delete a row : Passing negative row deletes all.

  virtual void deleteRow(int row);

  // Access the components in the table. Don't delete or reparent :

  virtual FFuComponentBase* getCell(int row, int column);

  // Access number of rows :

  virtual int getRowCount() const { return myRows.size(); }

  // Set the height/width of all the rows/columns :

  virtual void setRowHeight  (int height);
  virtual void setColumnWidth(int width );

  // Set the height/width of a special row/column :

  virtual void setRowHeight  (int row   , int width);
  virtual void setColumnWidth(int column, int width);

  // Stretch contents to fit into the height/width of viewable area :

  virtual void stretchContentsWidth (bool yesOrNo);
  virtual void stretchContentsHeight(bool yesOrNo);

  virtual void setSensitivity(bool isSensitive);

public slots:
  void dragColumn(int column, int change);
  void dragRow(int row, int change);

protected:
  virtual void resizeEvent(QResizeEvent* e);
  virtual void updateContents();

private :

  // Store sensitivity, to switch sensitivity on incoming widgets :

  bool IAmSensitive;

  // Stretch the contents to fit inside viewable area ?

  bool IHaveStretchingWidth;
  bool IHaveStretchingHeight;

  // The geometry of the table :

  int myDefaultRowHeight;
  int myDefaultColumnWidth;
  std::vector<int> myRowHeights;
  std::vector<int> myColumnWidths;

  // The widget containers :

  std::vector< std::vector<QWidget*> > myRows;

  // The scroll view created by this class :

  Q3ScrollView* myMainView;

  // Container widget that becomes parent of the added row widgets :

  QWidget* myMainWidget;
};

#endif
