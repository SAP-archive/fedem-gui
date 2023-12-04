// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_OPTION_MENU_H
#define FFU_OPTION_MENU_H

#include "FFuLib/FFuBase/FFuComponentBase.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include <string>
#include <vector>
#include <set>


class FFuOptionMenu : virtual public FFuComponentBase
{
public:
  FFuOptionMenu() {}
  virtual ~FFuOptionMenu() {}

  // Options management interface

  virtual void setOptions(const std::vector<std::string>& options) = 0;
  virtual void setOptions(const std::set<std::string>& options) = 0;
  virtual void setOptions(const std::vector<double>& options) = 0;
  virtual void setOptions(const std::vector<int>& options) = 0;
  virtual void addOption (const char* aText, int index = -1, bool replace = false) = 0;
  virtual void clearOptions() = 0;

  // Options selection

  virtual void selectOption(int optionIndex) = 0;
  virtual bool selectOption(const std::string& text, bool notify = true) = 0;
  virtual bool selectDoubleOption(double opt) = 0;
  virtual bool selectIntOption(int opt) = 0;

  virtual void disableOption(int optionIndex) = 0;
  virtual void removeOption (int optionIndex) = 0;

  virtual int getOptionCount() const = 0;
  virtual int getSelectedOption() const = 0;
  virtual std::string getSelectedOptionStr() const = 0;

  double getSelectedDouble() const;
  int getSelectedInt() const;

  // Callbacks interface

  void setOptionSelectedCB(const FFaDynCB1<int>& cb) { myOptionSelectedCB = cb; }
  void setOptionChangedCB(const FFaDynCB1<std::string>& cb) { myOptionChangedCB = cb; }
  void setOptionHighlightedCB(const FFaDynCB1<int>& cb) { myOptionHighlightedCB = cb; }

protected:
  std::vector<double> shadowDoubles;
  std::vector<int>    shadowInts;

  FFaDynCB1<int> myOptionSelectedCB;
  FFaDynCB1<std::string> myOptionChangedCB;
  FFaDynCB1<int> myOptionHighlightedCB;
};

#endif
