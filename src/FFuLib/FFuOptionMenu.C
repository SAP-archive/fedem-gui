// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuOptionMenu.H"
#include <cstring>
#include <cstdio>
#include <cctype>


static void removeWhiteSpace(const std::string& instr, char* outstr)
{
  size_t i, j, n = instr.size();
  for (i = j = 0; i < n; i++)
    if (!isspace(instr[i]))
      outstr[j++] = instr[i];

  outstr[j] = '\0';
}


double FFuOptionMenu::getSelectedDouble() const
{
  std::string orgstr = this->getSelectedOptionStr();
  char str[BUFSIZ];
  removeWhiteSpace(orgstr,str);

  double value = 0.0;
  if (strlen(str) > 0 && strcmp(str,"0") && strcmp(str,"-0"))
    sscanf(orgstr.c_str(),"%le",&value);

  return value;
}


int FFuOptionMenu::getSelectedInt() const
{
  std::string orgstr = this->getSelectedOptionStr();
  char str[BUFSIZ];
  removeWhiteSpace(orgstr,str);

  int value = 0;
  if (strlen(str) > 0)
    sscanf(orgstr.c_str(),"%d",&value);

  return value;
}
