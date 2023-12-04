// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <cstring>
#include <cstdio>

#if defined(win32) || defined(win64)
#include <windows.h>
#include <shellapi.h>
#define popen  _popen
#define pclose _pclose
#ifdef ERROR
#undef ERROR
#endif
#endif

#include "vpmApp/FapEventManager.H"
#include "vpmPM/FpPM.H"
#include "vpmUI/Fui.H"
#include "vpmUI/vpmUITopLevels/FuiProperties.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"
#include "FFaLib/FFaOS/FFaFilePath.H"
#include "FFaLib/FFaDefinitions/FFaAppInfo.H"
#include "Admin/FedemAdmin.H"
#include "vpmUI/Icons/fedem_app_icon_ng.xpm"
extern const char* startGuideIcon_xpm[];
extern const char* pdf_xpm[];
extern const char* help_xpm[];
#include "FapHelpCmds.H"


void FapHelpCmds::init()
{
  FFuaCmdItem* cmdItem;

  cmdItem = new FFuaCmdItem("cmdId_help_startGuide");
  cmdItem->setText("Start Guide");
  cmdItem->setToolTip("Start Guide");
  cmdItem->setSmallIcon(startGuideIcon_xpm);
  cmdItem->setActivatedCB(FFaDynCB0S(FapEventManager::permUnselectAll));

  cmdItem = new FFuaCmdItem("cmdId_help_usersGuide");
  cmdItem->setText("User's Guide");
  cmdItem->setToolTip("User's Guide");
  cmdItem->setSmallIcon(pdf_xpm);
  cmdItem->setActivatedCB(FFaDynCB0S(FuiProperties::showUsersGuide));

  cmdItem = new FFuaCmdItem("cmdId_help_theoryGuide");
  cmdItem->setText("Theory Guide");
  cmdItem->setToolTip("Theory Guide");
  cmdItem->setSmallIcon(pdf_xpm);
  cmdItem->setActivatedCB(FFaDynCB0S(FuiProperties::showTheoryGuide));

  cmdItem = new FFuaCmdItem("cmdId_help_comApi");
  cmdItem->setText("COM-API Reference");
  cmdItem->setToolTip("COM-API Reference");
  cmdItem->setSmallIcon(help_xpm);
  cmdItem->setActivatedCB(FFaDynCB0S(FuiProperties::showComApiReference));

  cmdItem = new FFuaCmdItem("cmdId_help_about");
  cmdItem->setText("About Fedem...");
  cmdItem->setToolTip("About Fedem");
  cmdItem->setSmallIcon(fedem_app_icon_ng_xpm);
  cmdItem->setActivatedCB(FFaDynCB0S(FapHelpCmds::about));
}


static std::string getSolverVersion(const char* program,
                                    const char* prefix = "</td></tr><tr><td>")
{
  std::string command(FFaAppInfo::getProgramPath(program));
  if (command.empty()) return command;

  command += " -version";

  char cline[128];
  bool found = false;
  FILE* fd = popen(command.c_str(),"r");
  if (fd)
  {
    std::string progName = FFaFilePath::getFileName(program);
    while (!found && fgets(cline,128,fd))
      if (!strncmp(cline,progName.c_str(),progName.length())) found = true;
    pclose(fd);
  }
  if (!found) return std::string("");

  std::string progver(cline);
  progver.replace(progver.find(" version "),9,"</td><td>");
  size_t pos = progver.find_last_of(':');
  if (pos < progver.size() && pos > 18) progver.insert(pos-18,"</td><td>");
  return prefix + progver;
}


void FapHelpCmds::about()
{
  // Open a temporary console window, unless we already have one.
  // This is needed because all solvers are console applications,
  // and a separate console window will be opened for each one of them
  // unless the parent process has a console, TT #2889.
  bool IHaveConsole = FFaAppInfo::haveConsole();
  if (!IHaveConsole) FFaAppInfo::openConsole(true);
  std::string msg("<qt><p><h2>Fedem Desktop ");
  msg += FedemAdmin::getVersion();
  msg += "</h2></p>";
  msg += "<p>Copyright 1995 - " + std::string(FedemAdmin::getBuildYear());
  msg += "</p><p>Build date: " + std::string(FedemAdmin::getBuildDate());
  msg += "</p><p><h3>Solver modules:</h3>";
  msg += getSolverVersion("fedem_reducer","<table><tr><td>");
  msg += getSolverVersion("fedem_partsol");
  msg += getSolverVersion("fedem_solver");
  msg += getSolverVersion("fedem_stress");
  msg += getSolverVersion("fedem_modes");
  msg += getSolverVersion("fedem_gage");
  msg += getSolverVersion("fedem_fpp");
  msg += getSolverVersion("fedem_graphexp");
  msg += getSolverVersion("fedem_op2fmx");
  msg += getSolverVersion("fedem_mesher");
  msg += "</td></tr></table></p></qt>";
  if (!IHaveConsole) FFaAppInfo::closeConsole(false);
  Fui::okDialog(msg.c_str(),FFuDialog::SAP_LOGO);
}
