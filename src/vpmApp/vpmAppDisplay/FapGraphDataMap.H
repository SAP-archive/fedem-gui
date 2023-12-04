// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_GRAPH_DATA_MAP_H
#define FAP_GRAPH_DATA_MAP_H

#include "FFpLib/FFpCurveData/FFpCurve.H"
#include <map>

class FmCurveSet;
class FFpSNCurve;


struct FapCurveStat
{
  double rms;
  double avg;
  double stdDev;
  double integral;
  double min;
  double max;
  FapCurveStat() { rms = avg = stdDev = integral = min = max = 0.0; }
};

typedef std::pair<const FmCurveSet*,FapCurveStat> FapCurveSet;


/*!
  \brief Class for handling of curve point data associated with a graph.

  This class contains a map from FmCurveSet pointers to FFpCurve objects
  containing the actual data to be plotted in a graph (or exported to file).
  It also contains the methods for loading the data, either from the RDB,
  from an external file, or computed from an internal function.

  \note This stuff used to be part of the class FapUAGraphView earlier, but is
  now in a separate class since it is used also when exporting curves to file.
  \sa FapUAGraphView, FapExportCmds.
*/

class FapGraphDataMap
{
public:
  FapGraphDataMap() {}

  FapGraphDataMap(FmCurveSet* curve, std::string& errMsg)
  { this->findPlottingData(curve,errMsg); }

  FapGraphDataMap(const std::vector<FmCurveSet*>& curves, std::string& errMsg)
  { this->findPlottingData(curves,&errMsg); }

  bool findPlottingData(FmCurveSet* curve, std::string& msg, bool appnd = false)
  { return this->findPlottingData({curve},&msg,appnd); }

  bool findPlottingData(const std::vector<FmCurveSet*>& curves,
		        std::string* errMsg = NULL, bool isAppending = false);

  FFpCurve* getFFpCurve(const FmCurveSet* curve,
			bool scaleShift = true, bool createIfNone = false);

  bool getCurveStatistics(const FmCurveSet* curve, bool scaledShifted,
			  bool wholeDomain, double startT, double stopT,
			  FapCurveStat& statistics);

  bool getCurveStatistics(std::vector<FapCurveSet>& statistics,
			  bool scaledShifted = false, bool wholeDomain = true,
			  double startT = 0.0, double stopT = 1.0) const;

  double getDamageFromCurve(const FmCurveSet* curve, double gateValue,
			    bool scaledData, bool wholeDomain,
			    double startT, double stopT,
			    const FFpSNCurve& snCurve);

  bool hasDataChanged(const FmCurveSet* curve) const;
  bool setDataChanged(const FmCurveSet* curve);

  void erase(const FmCurveSet* curve) { dataMap.erase(curve); }
  void clear() { dataMap.clear(); }

protected:
  static void replaceCombinedCurves(std::vector<FmCurveSet*>& curves);

  static bool findDataFromFunc(const FmCurveSet* curve,
			       FFpCurve& curveData, std::string& message);

  static bool findDataFromFile(const FmCurveSet* curve,
			       FFpCurve& curveData, std::string& message);

  bool findCombinedCurveData(const FmCurveSet* curve, std::string& message);

private:
  std::map<const FmCurveSet*,FFpCurve> dataMap;
};

#endif
