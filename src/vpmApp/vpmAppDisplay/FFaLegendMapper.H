// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFA_LEGEND_MAPPER_H
#define FFA_LEGEND_MAPPER_H

#include <string>
#include <vector>
#include <map>
#include <set>


/*!
  \brief A class to perform a fringe legend transformations.
  \author Jacob Storen
*/

class FFaLegendMapper
{
public:
  FFaLegendMapper();
  FFaLegendMapper(const FFaLegendMapper&) = delete;

  // Operation selection

  static void getValueMappingNames(std::vector<std::string>& names);
  static void getColorMappingNames(std::vector<std::string>& names);

  void selectValueMapping(std::string& mappingName);
  void selectColorMapping(std::string& mappingName);

  // Low-level mapping access

  typedef unsigned int (*ColorFuncType)(double);
  typedef double       (*MapFuncType  )(double);
  typedef std::map<std::string,MapFuncType>   MapFuncMap;
  typedef std::map<std::string,ColorFuncType> ColorFuncMap;

  void setMappingCB (MapFuncType   mapFunc);
  void setColorCB   (ColorFuncType colorFunc);
  ColorFuncType getColorCB() const { return myColorFunc; }

  // Tick mark and discrete legend calculations

  struct Tick
  {
    Tick(double aNormalizedTickPos = 0.0,
	 bool   doUseDescription = false,
	 double anActualValue = 0.0,
	 const std::string& aText = "")
    {
      normalizedTickPos = aNormalizedTickPos;
      useDescription = doUseDescription;
      actualValue = anActualValue;
      text = aText;
    }

    double normalizedTickPos;
    bool   useDescription;
    double actualValue;
    std::string text;
  };

  void   getTicks(std::vector<Tick>& ticks) const;

  void   setUseTickCount    (bool   doUseCountNotSpacing);
  void   setTickCount       (int    count);
  void   setTickSpacing     (double spacing);
  void   setUseTicksPrDecade(bool   doUseSpacingPrDecade);
  void   setUseSmoothLegend (bool   isSmooth);
  bool   isSmooth           () const { return IHaveSmoothLegend; }
  bool   isFlipped          () const { return IAmFlipped;}

  void   setValueInterval   (double max, double min);
  double getMax             () const { return myMax; }
  double getMin             () const { return myMin; }

  // Actual color/normalization access

  unsigned int getColor(const double& v) const
  {
    double val = IHaveSmoothLegend ? v : this->getDiscreteVal(v);
    return this->myColorFunc(this->getNormValue(val));
  }

  double getNormValue(const double& v) const
  {
    return (myMapFunc(v) - myMapFunc(myMin)) /
      (myMapFunc(myMax) - myMapFunc(myMin));
  }

  double getDiscreteVal(const double& v) const;

  //! \brief Assignment operator
  FFaLegendMapper& operator=(const FFaLegendMapper& other);
  //! \brief Equality operator
  bool operator==(const FFaLegendMapper& other) const;

private:
  MapFuncType   myMapFunc;
  ColorFuncType myColorFunc;

  double myMax;
  double myMin;

  bool   IAmFlipped;

  bool   IHaveSmoothLegend;
  bool   IAmUsingTickCount;
  int    myTickCount;
  double myTickSpacing;
  bool   IHaveTicksPrDecade;

  // Tick cache used to speed up discrete value attrival
  std::vector<Tick> myTicks;

  // Static operation maps

  static MapFuncMap            ourValueMappingFunctions;
  static ColorFuncMap          ourColorMappingFunctions;
  static std::set<std::string> ourUseDecadeTickMappings;

  static MapFuncMap            initValueMappings();
  static ColorFuncMap          initColorMappings();
  static std::set<std::string> initUseDecadeTickMappings();

  // Operations implemented here

  static double       noOp     (double d) { return d; }
  static unsigned int fullColor(double d);
  static unsigned int redBlue  (double d);
  static unsigned int fullColorBW(double d);
  static unsigned int fullColorClipp(double d);
};

#endif
