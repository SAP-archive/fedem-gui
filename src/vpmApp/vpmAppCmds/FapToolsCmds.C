// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FapToolsCmds.H"
#include "vpmApp/FapLicenseManager.H"
#include "FFuLib/FFuAuxClasses/FFuaCmdItem.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"
#include "FFaLib/FFaDefinitions/FFaMsg.H"
#include "FFaLib/FFaString/FFaStringExt.H"
#include "vpmUI/Fui.H"
#include "vpmUI/FuiModes.H"
#include "vpmUI/Icons/FuiIconPixmaps.H"
#ifdef USE_INVENTOR
#include "vpmDisplay/FdCtrlDB.H"
#endif
#include "vpmPM/FpPM.H"
#include "vpmDB/FmDB.H"
#include "vpmDB/FmTurbine.H"

#if defined(win32) || defined(win64)
#include "Admin/FedemAdmin.H"
#include <windows.h>
#else
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#define MAX_PATH PATH_MAX
#endif

//----------------------------------------------------------------------------

void FapToolsCmds::init()
{
  FFuaCmdItem* cmdItem = 0;

  cmdItem = new FFuaCmdItem("cmdId_mech_show");
  cmdItem->setSmallIcon(openMechModeller_xpm);
  cmdItem->setText("Show Modeler");
  cmdItem->setToolTip("Show Modeler");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::showModeler));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl_show");
  cmdItem->setSmallIcon(ctrlSystem_xpm);
  cmdItem->setText("Show Control Editor");
  cmdItem->setToolTip("Show Control Editor");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::showCtrlEditor));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_ctrl_gridSnap");
  cmdItem->setSmallIcon(ctrlGrid_xpm);
  cmdItem->setText("Control Editor Grid/Snap...");
  cmdItem->setToolTip("Control Editor Grid/Snap");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::ctrlGridSnap));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_preferences");
  cmdItem->setSmallIcon(additionalSolverOptions_xpm);
  cmdItem->setText("Additional Solver Options...");
  cmdItem->setToolTip("Additional Solver Options");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::preferences));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_viewFilter");
  cmdItem->setSmallIcon(viewFilter_xpm);
  cmdItem->setText("General Appearance...");
  cmdItem->setToolTip("General Appearance");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::viewFilter));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_objectBrowser");
  cmdItem->setSmallIcon(objectBrowser_xpm);
  cmdItem->setText("Object Browser...");
  cmdItem->setToolTip("Object Browser");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::objectBrowser));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_outputList");
  cmdItem->setSmallIcon(infoList_xpm);
  cmdItem->setText("Show Output List");
  cmdItem->setToolTip("Show Output List");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::outputList));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_miniFileBrowser");
  cmdItem->setSmallIcon(browseRDB_xpm);
  cmdItem->setText("Result File Browser...");
  cmdItem->setToolTip("Result File Browser");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::resultFileBrowser));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_linkRamSettings");
  cmdItem->setSmallIcon(linkRamSettings_xpm);
  cmdItem->setText("FE-Data Settings...");
  cmdItem->setToolTip("FE-Data settings");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::linkRamSettings));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::isProEdition,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_modelPreferences");
  cmdItem->setText("Model Preferences...");
  cmdItem->setToolTip("Model Preferences");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::modelPreferences));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_seaEnvironment");
  cmdItem->setSmallIcon(sea_xpm);
  cmdItem->setText("Sea Environment...");
  cmdItem->setToolTip("Sea Environment");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::seaEnvironment));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_airEnvironment");
  cmdItem->setSmallIcon(windAirEnv_xpm);
  cmdItem->setText("Aerodynamic Setup...");
  cmdItem->setToolTip("Aerodynamic Setup");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::airEnvironment));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_airfoilDefinition");
  cmdItem->setSmallIcon(windAirFoil_xpm);
  cmdItem->setText("Browse Airfoils...");
  cmdItem->setToolTip("Browse Airfoils for Turbine Blades");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::airfoilDefinition));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_bladeDefinition");
  cmdItem->setSmallIcon(windBladeProp_xpm);
  cmdItem->setText("Blade Definition...");
  cmdItem->setToolTip("Blade definition for Turbine Assembly");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::bladeDefinition));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_createTurbineAssembly");
  cmdItem->setSmallIcon(windTurbine_xpm);
  cmdItem->setText("Turbine Definition...");
  cmdItem->setToolTip("Turbine Definition");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::turbineAssembly));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_createTurbineTower");
  cmdItem->setSmallIcon(windTower_xpm);
  cmdItem->setText("Tower Definition...");
  cmdItem->setToolTip("Turbine Tower Definition");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::turbineTower));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapToolsCmds::getTurbineTowerSensitivity,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_createBeamstringPair");
  cmdItem->setSmallIcon(beamstringPairDef_xpm);
  cmdItem->setText("Beamstring Pair Definition...");
  cmdItem->setToolTip("Beamstring Pair Definition");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::beamstringPair));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_setFileAssociations");
  cmdItem->setText("Set File Associations...");
  cmdItem->setToolTip("Set File Associations");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::setFileAssociations));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_plugins");
  cmdItem->setText("Plug-Ins...");
  cmdItem->setToolTip("Plug-Ins");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::plugins));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_eventDefinition");
  cmdItem->setSmallIcon(eventDef_xpm);
  cmdItem->setText("Event Definitions...");
  cmdItem->setToolTip("Events");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::eventDefinition));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_distance");
  cmdItem->setSmallIcon(measureDistance_xpm);
  cmdItem->setText("Measure distance...");
  cmdItem->setToolTip("Measure distance between two points");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::measureDistance));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  cmdItem = new FFuaCmdItem("cmdId_tools_angle");
  cmdItem->setSmallIcon(measureAngle_xpm);
  cmdItem->setText("Measure angle...");
  cmdItem->setToolTip("Measure angle between two points");
  cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::measureAngle));
  cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));

  for (int i = 0; i < 40; i++)
  {
    cmdItem = new FFuaCmdItem(FFaNumStr("cmdId_tools_addon%d",i));
    cmdItem->setGetSensitivityCB(FFaDynCB1S(FapCmdsBase::alwaysSensitive,bool&));
    switch (i) {
    case 0: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon0)); break;
    case 1: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon1)); break;
    case 2: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon2)); break;
    case 3: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon3)); break;
    case 4: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon4)); break;
    case 5: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon5)); break;
    case 6: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon6)); break;
    case 7: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon7)); break;
    case 8: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon8)); break;
    case 9: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon9)); break;
    case 10: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon10)); break;
    case 11: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon11)); break;
    case 12: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon12)); break;
    case 13: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon13)); break;
    case 14: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon14)); break;
    case 15: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon15)); break;
    case 16: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon16)); break;
    case 17: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon17)); break;
    case 18: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon18)); break;
    case 19: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon19)); break;
    case 20: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon20)); break;
    case 21: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon21)); break;
    case 22: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon22)); break;
    case 23: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon23)); break;
    case 24: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon24)); break;
    case 25: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon25)); break;
    case 26: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon26)); break;
    case 27: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon27)); break;
    case 28: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon28)); break;
    case 29: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon29)); break;
    case 30: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon30)); break;
    case 31: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon31)); break;
    case 32: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon32)); break;
    case 33: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon33)); break;
    case 34: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon34)); break;
    case 35: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon35)); break;
    case 36: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon36)); break;
    case 37: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon37)); break;
    case 38: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon38)); break;
    case 39: cmdItem->setActivatedCB(FFaDynCB0S(FapToolsCmds::addon39)); break;
    }
    // The text and tooltip with Addon names are set later, when the menu is activated
  }
}
//----------------------------------------------------------------------------

#if defined(win32) || defined(win64)
bool FapToolsCmds::getAddonExe(int index, char* pszExePath, char* pszExeName)
#else
bool FapToolsCmds::getAddonExe(int, char*, char*)
#endif
{
#if defined(win32) || defined(win64)
  // Get module path
  std::string modulePath = FpPM::getFullFedemPath("addons");
  std::string addOnFilter = modulePath + "\\*.exe";
  // Find files
  WIN32_FIND_DATA ffd;
  HANDLE hFind = ::FindFirstFile(addOnFilter.c_str(), &ffd);
  if (hFind == INVALID_HANDLE_VALUE)
    return false;
  int i = 0; do
  {
    if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      continue;
    if (index == i) {
      // ExeName
      if (pszExeName)
        strtok(strcpy(pszExeName,ffd.cFileName),".");
      // ExePath
      if (pszExePath) {
        strcpy(pszExePath,modulePath.c_str());
        strcat(pszExePath,"\\");
        strcat(pszExePath,ffd.cFileName);
      }
      return true;
    }
    i++;
  }
  while (::FindNextFile(hFind, &ffd) != 0);
  ::FindClose(hFind);
#endif
  return false;
}

void FapToolsCmds::addonLaunch(int index)
{
#if defined(win32) || defined(win64)
  char szExePath[MAX_PATH];
  if (getAddonExe(index,szExePath))
  {
    std::string cpid = " " + std::to_string(GetCurrentProcessId());
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);
    CreateProcess(NULL, (char*)(szExePath + cpid).c_str(),
                  NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
  }
#else
  std::cerr <<"  ** FapToolsCmds::addonLaunch("<< index <<"): No Linux support"<< std::endl;
#endif
}
//----------------------------------------------------------------------------

void FapToolsCmds::showModeler()
{
  Fui::modellerUI();
  FuiModes::cancel();
}
//----------------------------------------------------------------------------

void FapToolsCmds::showCtrlEditor()
{
#ifdef USE_INVENTOR
  if (FapLicenseManager::hasCtrlLicense())
    FdCtrlDB::openCtrl();
#endif
}
//----------------------------------------------------------------------------

void FapToolsCmds::ctrlGridSnap()
{
  if (FapLicenseManager::hasCtrlLicense())
    Fui::ctrlGridSnapUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::preferences()
{
  Fui::preferencesUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::viewFilter()
{
  Fui::viewSettingsUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::outputList()
{
  Fui::outputListUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::resultFileBrowser()
{
  Fui::resultFileBrowserUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::linkRamSettings()
{
  Fui::linkRamSettingsUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::modelPreferences()
{
  Fui::modelPreferencesUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::seaEnvironment()
{
  Fui::seaEnvironmentUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::airEnvironment()
{
  Fui::airEnvironmentUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::turbineAssembly()
{
  Fui::turbineAssemblyUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::turbineTower()
{
  Fui::turbineTowerUI();
}

void FapToolsCmds::getTurbineTowerSensitivity(bool& isSensitive)
{
  FmTurbine* turbine = FmDB::getTurbineObject();
  isSensitive = (turbine && turbine->getTower());
}
//----------------------------------------------------------------------------

void FapToolsCmds::beamstringPair()
{
  Fui::beamstringPairUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::objectBrowser()
{
  Fui::objectBrowserUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::airfoilDefinition()
{
  Fui::airfoilDefinitionUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::bladeDefinition()
{
  Fui::bladeDefinitionUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::plugins()
{
  Fui::pluginsUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::eventDefinition()
{
  Fui::eventDefinitionUI();
}
//----------------------------------------------------------------------------

void FapToolsCmds::measureDistance()
{
  FuiModes::setMode(FuiModes::MEASURE_DISTANCE_MODE);
}
//----------------------------------------------------------------------------

void FapToolsCmds::measureAngle()
{
  FuiModes::setMode(FuiModes::MEASURE_ANGLE_MODE);
}
//----------------------------------------------------------------------------

#if defined(win32) || defined(win64)
/*!
  This function creates a windows registry key with a default value.
*/
static bool FmRegCreateKey(const std::string& key, const std::string& val, bool* pbOk)
{
  if (!*pbOk)
    return false; // don't proceed

  // Fix slashes
  std::string strKey(key);
  for (char& c : strKey)
    if (c == '/') c = '\\';

  // Create key
  HKEY regKey = NULL;
  LONG err = ::RegCreateKeyEx(HKEY_CLASSES_ROOT, // Root key
                              strKey.c_str(), // Sub key
                              0, NULL, // Dummy
			      REG_OPTION_NON_VOLATILE, // Keep in registry
			      KEY_ALL_ACCESS, // Give me all access rights
			      NULL,    // regKey does not need to be inherited
			      &regKey, // Returned key
			      NULL);   // Irrelevant if it was created or opened
  if (err != ERROR_SUCCESS)
    return *pbOk = false;

  // Set default value
  err = ::RegSetValueEx(regKey,
                        "",
                        NULL,
                        REG_EXPAND_SZ,
                        (BYTE*)val.c_str(),
                        val.size() + 1);
  if (err != ERROR_SUCCESS)
    *pbOk = false;

  ::RegCloseKey(regKey);

  return *pbOk;
}


static void FmRegTypicalWordPad(const char* fileExt, const char* fileDesc, const char* iconIndex, bool* pbOk)
{
  std::string strFileExt(fileExt);
  FFaUpperCaseString strFileExtU(fileExt);

  // App path
  std::string appPath = "\"" + FpPM::getFullFedemPath("Fedem.exe") + "\"";
  std::string appWordPad = "\"WORDPAD.EXE\" \"%1\"";

  // Register
  FmRegCreateKey("." + strFileExt, strFileExtU + "-file", pbOk);
  FmRegCreateKey("." + strFileExt + "/OpenWithList", "", pbOk);
  FmRegCreateKey("." + strFileExt + "/OpenWithList/wordpad.exe", "", pbOk);
  FmRegCreateKey(strFileExtU + "-file", fileDesc, pbOk);
  FmRegCreateKey(strFileExtU + "-file/DefaultIcon", appPath + "," + iconIndex, pbOk);
  FmRegCreateKey(strFileExtU + "-file/shell", "", pbOk);
  FmRegCreateKey(strFileExtU + "-file/shell/open", "Open with &WordPad", pbOk);
  FmRegCreateKey(strFileExtU + "-file/shell/open/command", appWordPad, pbOk);
}
#endif


void FapToolsCmds::setFileAssociations()
{
  if (FFaMsg::dialog("Would you like to register file associations?\n\n"
		     "Note: You may have to run Fedem in administrator mode.",
		     FFaMsg::YES_NO_CANCEL) != 1) return;

  if (FapToolsCmds::setFileAssociationsEx())
    FFaMsg::dialog("Successfully registered file associations!\n\n"
		   "Note: You may have to restart Windows for the changes to take effect.",
		   FFaMsg::OK);
  else
    FFaMsg::dialog("Unable to register file associations!", FFaMsg::WARNING);
}


bool FapToolsCmds::setFileAssociationsEx()
{
  bool bOk = true;
#if defined(win32) || defined(win64)

  std::string appPath = "\"" + FpPM::getFullFedemPath("Fedem.exe") + "\"";

  // FMM
  FmRegCreateKey(".fmm", "FMM-file", &bOk);
  FmRegCreateKey(".fmm/OpenWithList", "", &bOk);
  FmRegCreateKey(".fmm/OpenWithList/wordpad.exe", "", &bOk);
  FmRegCreateKey("FMM-file", "Fedem Model File", &bOk);
  FmRegCreateKey("FMM-file/DefaultIcon", appPath + ",8", &bOk);
  FmRegCreateKey("FMM-file/shell", "", &bOk);
  FmRegCreateKey("FMM-file/shell/open", "Open with &Fedem", &bOk);
  FmRegCreateKey("FMM-file/shell/open/command", appPath + " -f \"%1\"", &bOk);

  // FTC
  FmRegCreateKey(".ftc", "FTC-file", &bOk);
  FmRegCreateKey("FTC-file", "Fedem Cad File", &bOk);
  FmRegCreateKey("FTC-file/DefaultIcon", appPath + ",3", &bOk);

  // FMX
  FmRegCreateKey(".fmx", "FMX-file", &bOk);
  FmRegCreateKey("FMX-file", "Fedem Matrix File", &bOk);
  FmRegCreateKey("FMX-file/DefaultIcon", appPath + ",7", &bOk);

  // FSM
  FmRegCreateKey(".fsm", "FSM-file", &bOk);
  FmRegCreateKey("FSM-file", "Fedem SAM Data", &bOk);
  FmRegCreateKey("FSM-file/DefaultIcon", appPath + ",15", &bOk);

  // ERR, BDF, FLM, FTL, NAS, FAO, FCO, FOP, FSI, FRS, RES, FCD
  FmRegTypicalWordPad("err", "Fedem Error File", "1", &bOk);
  FmRegTypicalWordPad("bdf", "Nastran Bulk Data", "2", &bOk);
  FmRegTypicalWordPad("flm", "Fedem Link File", "4", &bOk);
  FmRegTypicalWordPad("ftl", "Fedem Link File", "5", &bOk);
  FmRegTypicalWordPad("nas", "Nastran Bulk Data", "6", &bOk);
  FmRegTypicalWordPad("fao", "Fedem Additional Options", "9", &bOk);
  FmRegTypicalWordPad("fco", "Fedem Computational Options", "10", &bOk);
  FmRegTypicalWordPad("fop", "Fedem Output Options", "11", &bOk);
  FmRegTypicalWordPad("fsi", "Fedem Solver Input", "12", &bOk);
  FmRegTypicalWordPad("frs", "Fedem Result File", "13", &bOk);
  FmRegTypicalWordPad("res", "Fedem Result File", "14", &bOk);
  FmRegTypicalWordPad("fcd", "Fedem Unit Conversion", "16", &bOk);

  // Internal
  std::string key("FMM-file/internal/");
  key += FedemAdmin::getVersion();
  FmRegCreateKey(key.c_str(),"registered",&bOk);
#else
  bOk = false;
  FFaMsg::list("ERROR: File associations is available on Windows only.",true);
#endif
  return bOk;
}


bool FapToolsCmds::checkFileAssociations()
{
#if defined(win32) || defined(win64)

  // Get version
  std::string key("FMM-file\\internal\\");
  key += FedemAdmin::getVersion();

  // Open registry key
  HKEY hk;
  LONG err = ::RegOpenKeyEx(HKEY_CLASSES_ROOT,key.c_str(),
                            0,KEY_QUERY_VALUE,&hk);
  if (err != ERROR_SUCCESS)
    return false;

  // Get registry value
  DWORD cbData = 0;
  err = ::RegQueryValueEx(hk,"",NULL,NULL,NULL,&cbData);
  ::RegCloseKey(hk);
  return (err == ERROR_SUCCESS && cbData == 11);

#else
  return true; // no Linux!
#endif
}
