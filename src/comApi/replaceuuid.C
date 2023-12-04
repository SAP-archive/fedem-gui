/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
  Simple program to replace all the GUIDs in the source file read from std::cin
  with those in the supplied text file. The result is printed to std::cout.

  Compile with (on Windows):
  $ cl -TP -EHsc replaceuuid.C

  Then run:
  $ replaceuuid.exe (uuidfilename) < CaMain.idl > CaMain.tmp
  $ rename CaMain.tmp CaMain.idl

  Where (uuidfilename) is a file containing a list of the new GUIDs to use.
*/

#include <iostream>
#include <fstream>
#include <string>


int main (int argc, const char** argv)
{
  if (argc < 2) return 1;

  char cline[1024], uline[64];
  std::ifstream uis(argv[1]);
  while (std::cin.getline(cline,1024))
  {
    std::string sline(cline);
    size_t pos = sline.find("uuid(");
    if (pos != std::string::npos && uis.getline(uline,64))
      sline.replace(pos+5,strlen(uline),uline);
    std::cout << sline << std::endl;
  }

  return 0;
}
