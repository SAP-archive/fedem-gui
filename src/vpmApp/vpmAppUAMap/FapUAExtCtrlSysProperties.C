// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAExtCtrlSysProperties.H"
#include "vpmApp/vpmAppUAMap/FapUAProperties.H"
#include "vpmApp/vpmAppUAMap/FapUAQuery.H"
#include "vpmApp/FapEventManager.H"
#include "vpmApp/FapLicenseManager.H"

#include "vpmUI/vpmUIComponents/FuiExtCtrlSysProperties.H"
#include "vpmUI/vpmUIComponents/FuiQueryInputField.H"
#include "vpmUI/Fui.H"
#include "vpmDB/FmDB.H"
#include "vpmDB/FmMechanism.H"
#include "vpmDB/FmExternalCtrlSys.H"
#include "vpmDB/FmEngine.H"
#include "vpmPM/FpPM.H"
#include "FFaLib/FFaOS/FFaFilePath.H"
#include "FFaLib/FFaDynCalls/FFaDynCB.H"

Fmd_SOURCE_INIT(FAPUAEXTCTRLSYSPROPERTIES, FapUAExtCtrlSysProperties, FapUAExistenceHandler);

//----------------------------------------------------------------------------

/*!
  Constructor
*/

FapUAExtCtrlSysProperties::FapUAExtCtrlSysProperties(FuiExtCtrlSysProperties* uic)
  : FapUAExistenceHandler(uic), FapUADataHandler(uic), selSignalConnector(this)
{
  Fmd_CONSTRUCTOR_INIT(FapUAExtCtrlSysProperties);

  this->dbexternal = NULL;
  this->ui = uic;

  this->ui->setEngineSelectedCB(FFaDynCB1M(FapUAExtCtrlSysProperties,this,
					   onEditOrCreateEngine,
					   FuiQueryInputFieldValues&));
}
//----------------------------------------------------------------------------

/*!
  Reimplemented from data handler
*/

FFuaUIValues* FapUAExtCtrlSysProperties::createValuesObject()
{
  // Method returns a new object of type FuaExtCtrlSysPropertiesValues
  return new FuaExtCtrlSysPropertiesValues();
}
//----------------------------------------------------------------------------

/*!
  Received when permanent selection has changed
*/

void FapUAExtCtrlSysProperties::onPermSelectionChanged(const std::vector<FFaViewItem*>& totalSelection,
						       const std::vector<FFaViewItem*>&,
						       const std::vector<FFaViewItem*>&)
{
  if (totalSelection.empty())
    this->dbexternal = NULL;
  else
    this->dbexternal = dynamic_cast<FmExternalCtrlSys*>(totalSelection.back());

  if (!this->dbexternal) return;

  this->updateUI();
}

//----------------------------------------------------------------------------

/*!
  Reimplemented from data handler
*/

void FapUAExtCtrlSysProperties::updateUIValues()
{
  if (!this->dbexternal) return;

  this->FapUADataHandler::updateUIValues();
}
//----------------------------------------------------------------------------

void FapUAExtCtrlSysProperties::setDBValues(FFuaUIValues* values)
{
  if (!this->dbexternal) return;

  FuaExtCtrlSysPropertiesValues* externalValues = dynamic_cast<FuaExtCtrlSysPropertiesValues*> (values);

  for (size_t i = 0; i < externalValues->mySelectedQueries.size(); i++)
    this->dbexternal->setEngine(dynamic_cast<FmEngine*>(externalValues->mySelectedQueries[i]),i);

  this->dbexternal->setFilePath(externalValues->filePath);

  if (this->dbexternal->inputFileChanged()) {
    if (this->dbexternal->hasFileErrors())
      Fui::dismissDialog(this->dbexternal->getErrorString().c_str());

    // Will cause a complete update of UI, with dynamic widgets and all
    this->updateUI();
    this->ui->setSensitivity(FpPM::isModelEditable() &&
			     FapLicenseManager::hasExtCtrlLicense(0));
    FapUAExistenceHandler::doUpdateUI(FapUAProperties::getClassTypeID());
  }

  this->dbexternal->onChanged();
  this->dbexternal->resetFlags();
}

//----------------------------------------------------------------------------

/*!
  Called when user presses engine button
  We select the current engine, or create a new if none is selected
  CREATING NEW ENGINE IS NOT IMPLEMENTED YET
*/

void FapUAExtCtrlSysProperties::onEditOrCreateEngine(FuiQueryInputFieldValues& v)
{
  if (v.selectedRef)
    FapEventManager::permTotalSelect(v.selectedRef);
/* Not implemented in UI. We don't know which field sent the signal...
  else {
    FmEngine* newEngine = new FmEngine();
    newEngine->connect();
    FapEventManager::permTotalSelect(newEngine);
    dbexternal->setEngine(newEngine);
    dbexternal->setMyEngine(newEngine
  }
*/
}
//----------------------------------------------------------------------------

void FapUAExtCtrlSysProperties::getDBValues(FFuaUIValues* values)
{
  if (!this->dbexternal) return;

  FuaExtCtrlSysPropertiesValues * externalValues = (FuaExtCtrlSysPropertiesValues*) values;

  externalValues->filePath = this->dbexternal->getFilePath();
  externalValues->modelFilePath = FmDB::getMechanismObject()->getAbsModelFilePath() + FFaFilePath::getPathSeparator();
  externalValues->fromWorkspace = this->dbexternal->getFromWorkspace();
  externalValues->toWorkspace = this->dbexternal->getToWorkspace();
  externalValues->myEngineQuery = FapUAEngineQuery::instance();

  externalValues->mySelectedQueries.clear();
  for (size_t i = 0; i < externalValues->fromWorkspace.size(); i++)
    externalValues->mySelectedQueries.push_back(this->dbexternal->getEngine(i));

  FapUAExistenceHandler::doUpdateUI(FapUAProperties::getClassTypeID());
}
//----------------------------------------------------------------------------
