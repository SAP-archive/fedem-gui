// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "vpmApp/vpmAppUAMap/FapUAGraphDefine.H"
#include "vpmApp/vpmAppUAMap/FapUAGraphView.H"
#include "vpmUI/vpmUIComponents/FuiGraphDefine.H"
#include "vpmDB/FmGraph.H"
#include "vpmDB/FmCurveSet.H"


Fmd_SOURCE_INIT(FAPUAGRAPHDEFINE, FapUAGraphDefine, FapUAExistenceHandler);


//----------------------------------------------------------------------------

FapUAGraphDefine::FapUAGraphDefine(FuiGraphDefine* ui)
  : FapUAExistenceHandler(ui), FapUADataHandler(ui), signalConnector(this)
{
  Fmd_CONSTRUCTOR_INIT(FapUAGraphDefine);

  this->dbgraph = NULL;
}
//----------------------------------------------------------------------------

FFuaUIValues* FapUAGraphDefine::createValuesObject()
{
  return new FuaGraphDefineValues();
}
//----------------------------------------------------------------------------

void FapUAGraphDefine::setDBValues(FFuaUIValues* values)
{
  if (!this->dbgraph) return;

  FuaGraphDefineValues* graphValues = (FuaGraphDefineValues*) values;

  this->dbgraph->setTitle(graphValues->title);
  this->dbgraph->setSubTitle(graphValues->subtitle);
  this->dbgraph->setXaxisLabel(graphValues->xAxisLabel);
  this->dbgraph->setYaxisLabel(graphValues->yAxisLabel);
  this->dbgraph->setFontSize(graphValues->fontSize);

  this->dbgraph->setGridType(graphValues->gridType);
  this->dbgraph->setShowLegend(graphValues->showLegend);
  this->dbgraph->setAutoScaleFlag(graphValues->autoScaleOnLoadCurve);

  if (!this->dbgraph->isBeamDiagram() && !this->dbgraph->isFuncPreview())
  {
    bool isTimeInterval = this->dbgraph->getUseTimeRange();
    bool useTimeInterval = graphValues->useTimeInterval;
    this->dbgraph->setUseTimeRange(useTimeInterval);

    double min, max;
    this->dbgraph->getTimeRange(min,max);
    this->dbgraph->setTimeRange(graphValues->tmin,graphValues->tmax);

    // Update the associated graph view if it is loaded and have RDB curves
    if (min != graphValues->tmin || max != graphValues->tmax || useTimeInterval != isTimeInterval)
      if (this->dbgraph->hasCurveSets(FmCurveSet::TEMPORAL_RESULT))
      {
	FapUAGraphView* graphView = FapUAGraphView::getUAGraphView(this->dbgraph);
	if (graphView) graphView->updateSession();
      }
  }

  this->dbgraph->onChanged();
}
//----------------------------------------------------------------------------

void FapUAGraphDefine::getDBValues(FFuaUIValues* values)
{
  if (!this->dbgraph) return;

  FuaGraphDefineValues* graphValues = (FuaGraphDefineValues*) values;

  graphValues->title = this->dbgraph->getTitle();
  graphValues->subtitle = this->dbgraph->getSubTitle();
  graphValues->xAxisLabel = this->dbgraph->getXaxisLabel();
  graphValues->yAxisLabel = this->dbgraph->getYaxisLabel();
  graphValues->fontSize = this->dbgraph->getFontSize();

  graphValues->gridType = this->dbgraph->getGridType();
  graphValues->showLegend = this->dbgraph->getShowLegend();
  graphValues->autoScaleOnLoadCurve = this->dbgraph->getAutoScaleFlag();

  if (this->dbgraph->isBeamDiagram() || this->dbgraph->isFuncPreview())
    graphValues->useTimeInterval = -2; // hide the time range fields
  else
  {
    if (this->dbgraph->hasCurveSets(FmCurveSet::TEMPORAL_RESULT))
      graphValues->useTimeInterval = this->dbgraph->getUseTimeRange();
    else
      graphValues->useTimeInterval = -1; // make toggle insensitive
    this->dbgraph->getTimeRange(graphValues->tmin,graphValues->tmax);
  }
}
//----------------------------------------------------------------------------

void FapUAGraphDefine::onPermSelectionChanged(const std::vector<FFaViewItem*>& totalSelection,
					      const std::vector<FFaViewItem*>&,
					      const std::vector<FFaViewItem*>&)
{
  // Show last selected one if graph
  if (totalSelection.empty())
    this->dbgraph = NULL;
  else
    this->dbgraph = dynamic_cast<FmGraph*>(totalSelection.back());

  if (this->dbgraph)
    this->updateUIValues();
}
//----------------------------------------------------------------------------
