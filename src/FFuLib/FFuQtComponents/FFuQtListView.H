// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*!
   Signals: Do not trust the MouseButton press/release signal because they are
   not given at the right time. Instead use the viewportMousePressEvent and
   viewportMouseReleaseEvent signals.
*/

#ifndef FFU_QT_LIST_VIEW_H
#define FFU_QT_LIST_VIEW_H

#include <Qt3Support/Q3ListView>

#include "FFuLib/FFuQtBaseClasses/FFuQtComponentBase.H"
#include "FFuLib/FFuListView.H"

class QMouseEvent;


class FFuQtListView : public Q3ListView, virtual public FFuListView,
		      public FFuQtComponentBase
{
  Q_OBJECT

public:
  // Columns get maximum widthmode.
  FFuQtListView(QWidget* parent = 0, int nColumns = 0,
		const char* name = "FFuQtListView");
  virtual ~FFuQtListView() {}

protected slots:
  void fwdSelectionChanged();
  void fwdExpanded(Q3ListViewItem* item);
  void fwdCollapsed(Q3ListViewItem* item);
  void fwdReturnPressed(Q3ListViewItem* item);
  void fwdDoubleClicked(Q3ListViewItem* item);

public:
  virtual void setListSorting(int column,bool ascending = true);
  virtual void setHeaderClickEnabled(int column,bool enable);
  virtual void setListRootIsDecorated(bool enable);
  virtual void setAllListColumnsShowSelection(bool enable);
  virtual void setHeaderOff(bool Off);

  virtual void clearList();

  virtual void setListColumns(const std::vector<const char*>& labels);
  virtual void setListColumnWidth(int column, int width);
  virtual void permSelectListItem(FFuListViewItem* item,
				  bool select=true,bool notify=false);
  virtual void clearListSelection(bool notify=false);
  virtual void openListItem(FFuListViewItem* item,bool open,bool notify=false);
  virtual void ensureListItemVisible(FFuListViewItem* item,bool notify=false);

  virtual bool isExpanded(FFuListViewItem* item);

  virtual void setSglSelectionMode(bool single);
  virtual bool isSglSelectionMode() const;

  virtual FFuListViewItem* getSelectedListItemSglMode();
  virtual FFuListViewItem* getCurrentListItem();
  virtual FFuListViewItem* getFirstChildItem();
  virtual int getNColumns();

  virtual FFuListViewItem* createListItem(FFuListViewItem* parent=0,
					  FFuListViewItem* after=0,
					  FFuListViewItem* original=0,
					  const char* label="item");

private:
  // FFuComponentBase Re-impl
  virtual void setFonts (FFuaFontSet aFontSet);
  virtual void setColors(FFuaPalette aPalette);

  // QListView  Re-impl
  virtual void viewportMousePressEvent(QMouseEvent* e);
  virtual void viewportMouseReleaseEvent(QMouseEvent* e);
};

#endif
