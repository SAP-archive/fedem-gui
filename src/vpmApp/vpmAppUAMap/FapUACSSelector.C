// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUACSSelector.H"
#include "vpmApp/vpmAppUAMap/FapUACSListView.H"
#include "vpmUI/vpmUITopLevels/FuiCSSelector.H"
#include "vpmUI/vpmUIComponents/FuiItemsListViews.H"

#include "vpmPM/FpFileSys.H"
#include "vpmPM/FpPM.H"

#include "FFaLib/FFaOS/FFaFilePath.H"


Fmd_SOURCE_INIT(FcFAPUACSSELECTOR, FapUACSSelector, FapUAExistenceHandler)

//----------------------------------------------------------------------------

FapUACSSelector::FapUACSSelector(FuiCSSelector* uic) : FapUAExistenceHandler(uic)
{
  Fmd_CONSTRUCTOR_INIT(FapUACSSelector);

  myUI = uic;

  uic->setImportCB(FFaDynCB0M(FapUACSSelector,this,onImport));
  csUA = dynamic_cast<FapUACSListView*>(myUI->lvCS->getUA());
  matUA = dynamic_cast<FapUACSListView*>(myUI->lvMat->getUA());

  csUA->setEnsureItemVisibleOnPermSelection(true);
  matUA->setLeavesOnlySelectable(true);

  // Get cross section database files from installation
  std::vector<std::string> csFiles;
  std::string csDir = FpPM::getFullFedemPath("Properties/CrossSections");
  if (FpFileSys::isReadable(csDir))
    FpFileSys::getFiles(csFiles,csDir,"*.csv",true);

  // Get cross section database files from user's home directory
  csDir = FFaFilePath::appendFileNameToPath(FpFileSys::getHomeDir(),"CrossSections");
  if (FpFileSys::isReadable(FFaFilePath::checkName(csDir)))
    FpFileSys::getFiles(csFiles,csDir,"*.csv",true);

  // Load all cross section database files
  for (const std::string& file : csFiles)
    if (file.find("Materials.csv") < file.size())
      matUA->loadDataBaseFile(file);
    else
      csUA->loadDataBaseFile(file);

  matUA->sortByID();
  csUA->sortByID();
}
//----------------------------------------------------------------------------

void FapUACSSelector::onImport()
{
  std::vector<FFaViewItem*> selCS = csUA->getUISelectedItems();
  std::vector<FFaViewItem*> selM = matUA->getUISelectedItems();

  if (!selCS.empty() && !selM.empty())
    for (FFaViewItem* item : selCS)
      FapUACSListView::importCS(item,selM.front());

  csUA->permTotSelectUIItems({});
  matUA->permTotSelectUIItems({});
}
//----------------------------------------------------------------------------
