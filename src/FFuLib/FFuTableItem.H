// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUTABLEITEM_H
#define FFUTABLEITEM_H

#include <string>
#include <vector>


class FFuTable;

class FFuTableItem
{
public:
  FFuTableItem() {}
  virtual ~FFuTableItem() {}

  virtual std::string getTextString() = 0;
  virtual void setTextString(string text) = 0;
  
  virtual void setItemPixmap(const char* xpm[]) = 0;

  virtual FFuTable* getTable() = 0;
  
  virtual int getAlignment() = 0;
  
  virtual void setWrapping(bool wrap) = 0;
  virtual bool getWrapping() = 0;

  enum {NEVER, ON_TYPING, WHEN_CURRENT, ALWAYS};
  virtual int getEditType() = 0;
  virtual void setEditType(int type) = 0;

  virtual FFuComponentBase* makeEditor() = 0;
  virtual void setContentsFromEditor(FFuComponentBase* editor) = 0;

  virtual void setReplaceableFlag(bool replaceable) = 0;
  virtual bool replaceable() = 0;

  virtual std::string getKey() = 0; // for sorting
  virtual void setCellSpan(int rows, int cols) = 0;
  virtual int getRowSpan() = 0;
  virtual int getColumnSpan() = 0;

  virtual void setMyRow(int row) = 0;
  virtual int getMyRow() = 0;
  virtual void setMyColumn(int col) = 0;
  virtual int getMyColumn() = 0;

  virtual void setSensitivity(bool isSensitive) = 0;


  // Run time type checking values.
  // If you subclass this class, add enum value and re-implement getRTTI()
  enum 
    {
      TABLE_ITEM = 2000,
      COMBO_TABLE_ITEM = 2001,
      CHECK_TABLE_ITEM = 2002,
    };

  virtual int getRTTI() { return TABLE_ITEM;}

};

class FFuComboTableItem : virtual public FFuTableItem
{
public:
  FFuComboTableItem();
  virtual  ~FFuComboTableItem();

  virtual void setItemList(vector<string>& items) = 0;
  virtual void setCurrent(int i) = 0;
  virtual void setCurrent(const std::string& s) = 0;

  virtual int getCurrent() = 0;
  virtual std::string getCurrentText() = 0;
  virtual std::string getTextAt(int i) = 0;
  virtual int getCount() = 0;

  virtual void enableEditing(bool enable) = 0;
  virtual bool editingEnabled() = 0;

  virtual int getRTTI() {return COMBO_TABLE_ITEM;}
};


class FFuCheckTableItem : virtual public FFuTableItem
{
public:
  FFuCheckTableItem() {}
  virtual ~FFuCheckTableItem() {}

  virtual void setToggle(bool on) = 0;
  virtual bool getToggle() = 0;

  virtual int getRTTI() {return CHECK_TABLE_ITEM;}
};

#endif
