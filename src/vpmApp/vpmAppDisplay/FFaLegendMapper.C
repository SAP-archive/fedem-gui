// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <cfloat>
#include <iostream>

#include "vpmApp/vpmAppDisplay/FFaLegendMapper.H"


FFaLegendMapper::MapFuncMap FFaLegendMapper::ourValueMappingFunctions =
  FFaLegendMapper::initValueMappings();
FFaLegendMapper::ColorFuncMap FFaLegendMapper::ourColorMappingFunctions =
  FFaLegendMapper::initColorMappings();
std::set<std::string> FFaLegendMapper::ourUseDecadeTickMappings =
  FFaLegendMapper::initUseDecadeTickMappings();


FFaLegendMapper::FFaLegendMapper()
{
  myMapFunc          = noOp;
  myColorFunc        = fullColor;
  myMax              = 1.0e6;
  myMin              = 0.0;
  IAmFlipped         = false;
  IHaveSmoothLegend  = true;
  IAmUsingTickCount  = true;
  myTickCount        = 5;
  myTickSpacing      = 1000.0;
  IHaveTicksPrDecade = false;
}


void FFaLegendMapper::setMappingCB(double (*mapFunc)(double))
{
  if (mapFunc != myMapFunc)
    myTicks.clear();

  myMapFunc = mapFunc ? mapFunc : noOp;
}


void FFaLegendMapper::setColorCB(unsigned int (*colorFunc)(double))
{
  if (colorFunc != myColorFunc)
    myTicks.clear();

  myColorFunc = colorFunc ? colorFunc : fullColor;
}


void FFaLegendMapper::setValueInterval(double max, double min)
{
  if (myMin != min || myMax != max)
    myTicks.clear();

  myMin = min;
  myMax = max;
  IAmFlipped = (myMin > myMax);
}


FFaLegendMapper& FFaLegendMapper::operator=(const FFaLegendMapper& other)
{
  if (this == &other)
    return *this;

  myMax              = other.myMax;
  myMin              = other.myMin;
  IAmFlipped         = other.IAmFlipped;
  myMapFunc          = other.myMapFunc;
  myColorFunc        = other.myColorFunc;
  IHaveSmoothLegend  = other.IHaveSmoothLegend;
  IAmUsingTickCount  = other.IAmUsingTickCount;
  myTickCount        = other.myTickCount;
  myTickSpacing      = other.myTickSpacing;
  IHaveTicksPrDecade = other.IHaveTicksPrDecade;
  myTicks.clear(); // The ticks cache is not copied

  return *this;
}


bool FFaLegendMapper::operator==(const FFaLegendMapper& other) const
{
  return (myMax              == other.myMax)
    &&   (myMin              == other.myMin)
    &&   (myMapFunc          == other.myMapFunc)
    &&   (myColorFunc        == other.myColorFunc)
    &&   (IHaveSmoothLegend  == other.IHaveSmoothLegend)
    &&   (IAmUsingTickCount  == other.IAmUsingTickCount)
    &&   (myTickCount        == other.myTickCount)
    &&   (myTickSpacing      == other.myTickSpacing)
    &&   (IHaveTicksPrDecade == other.IHaveTicksPrDecade);
}


void FFaLegendMapper::getValueMappingNames(std::vector<std::string>& names)
{
  names.clear();
  names.reserve(ourValueMappingFunctions.size());
  for (const MapFuncMap::value_type& vFunc : ourValueMappingFunctions)
    names.push_back(vFunc.first);
}


void FFaLegendMapper::getColorMappingNames(std::vector<std::string>& names)
{
  names.clear();
  names.reserve(ourColorMappingFunctions.size());
  for (const ColorFuncMap::value_type& cFunc : ourColorMappingFunctions)
    names.push_back(cFunc.first);
}


void FFaLegendMapper::selectValueMapping(std::string& mappingName)
{
  MapFuncMap::const_iterator it = ourValueMappingFunctions.find(mappingName);
  if (it != ourValueMappingFunctions.end())
  {
    this->setMappingCB(it->second);
    this->setUseTicksPrDecade(mappingName == "Log10");
  }
  else
  {
    std::cerr <<"FFaLegendMapper::selectValueMapping: "
              <<"No value function named "<< mappingName << std::endl;
    this->setMappingCB(FFaLegendMapper::noOp);
  }
}


void FFaLegendMapper::selectColorMapping(std::string& mappingName)
{
  ColorFuncMap::const_iterator it = ourColorMappingFunctions.find(mappingName);
  if (it != ourColorMappingFunctions.end())
    this->setColorCB(it->second);
  else
  {
    std::cerr <<"FFaLegendMapper::selectColorMapping: "
              <<"No color function named "<< mappingName << std::endl;
    this->setColorCB(FFaLegendMapper::fullColor);
  }
}


void FFaLegendMapper::setUseTickCount(bool doUseCountNotSpacing)
{
  if (doUseCountNotSpacing != IAmUsingTickCount)
    {
      myTicks.clear();
      IAmUsingTickCount = doUseCountNotSpacing;
    }
}


void FFaLegendMapper::setTickCount(int count)
{
  if (count != myTickCount)
    {
      myTicks.clear();
      myTickCount = count;
    }
}


void FFaLegendMapper::setTickSpacing(double spacing)
{
  if (spacing != myTickSpacing)
    {
      myTicks.clear();
      myTickSpacing = spacing;
    }
}


void FFaLegendMapper::setUseTicksPrDecade(bool doUseSpacingPrDecade)
{
  if (doUseSpacingPrDecade != IHaveTicksPrDecade)
    {
      myTicks.clear();
      IHaveTicksPrDecade = doUseSpacingPrDecade;
    }
}


void FFaLegendMapper::setUseSmoothLegend(bool isSmooth)
{
  if (isSmooth != IHaveSmoothLegend)
    {
      myTicks.clear();
      IHaveSmoothLegend = isSmooth;
    }
}


double FFaLegendMapper::getDiscreteVal(const double& v) const
{
  if (v > myMax || v < myMin)
    return v;

  if (myTicks.empty())
    this->getTicks(const_cast<FFaLegendMapper*>(this)->myTicks);

  // Find the right interval, using binary search

  int nTicks = myTicks.size();
  int i = nTicks/2;
  int start = 0;
  int end = nTicks;

  while (i >= 0 && i+1 < nTicks)
    {
      double ival = myTicks[i].actualValue;
      double i_1val = myTicks[i+1].actualValue;
      if (myTicks[i].actualValue < v && v <= myTicks[i+1].actualValue)
        return IAmFlipped ? myTicks[i].actualValue : myTicks[i+1].actualValue;
      else if (v <= myTicks[i].actualValue) {
        end = i;
        i = (i-start)/2;
        if (end == start) {
	  // value is less than or equal to min legend value
          if (v == ival || v >= ival-FLT_EPSILON)
            return IAmFlipped ? ival : i_1val;
          break;
        }
      }
      else if (v > myTicks[i+1].actualValue) {
        start = i;
        i = i + (end-i)/2;
        if (start+1 == end) {
	  // value is greater than max value (never trigged i think)
          if (v == i_1val || v <= i_1val+FLT_EPSILON)
            return IAmFlipped ? ival : i_1val;
          break;
        }
      }
      else
        break; // Should never happen
    }

  // Could not find the interval
  return HUGE_VAL;
}


void FFaLegendMapper::getTicks(std::vector<Tick>& ticks) const
{
  const int maxNTicks = 170;

  double spacing = 1.0;
  double tickPos = 0.0;
  double max = IAmFlipped ? myMin : myMax;
  double min = IAmFlipped ? myMax : myMin;

  if (IAmUsingTickCount)
    {
      spacing = max - min;
      if (myTickCount > 0 && myTickCount < maxNTicks)
        spacing /= (myTickCount+1);
      else if (myTickCount >= maxNTicks)
	spacing /= (maxNTicks+1);

      tickPos = min + spacing;
    }

  else if (myTickSpacing > 0.0)
    {
      if (IHaveTicksPrDecade)
	{
	  if (max <= 0.0)
	    ((FFaLegendMapper*)this)->myTickSpacing = 0; // Turn off
	  else
	    {
	      if (min <= 0.0) {
		min = DBL_EPSILON;
		if (IAmFlipped)
		  ((FFaLegendMapper*)this)->myMax = DBL_EPSILON;
		else
		  ((FFaLegendMapper*)this)->myMin = DBL_EPSILON;
	      }

	      double span = 10.0*(log10(max)-log10(min));
	      if (span/myTickSpacing > maxNTicks)
		((FFaLegendMapper*)this)->myTickSpacing = span/maxNTicks;

	      spacing = pow(10.0,floor(log10(min))) * myTickSpacing;
	    }
	}
      else
	{
	  if ((max-min)/myTickSpacing > maxNTicks)
	    ((FFaLegendMapper*)this)->myTickSpacing = (max-min)/maxNTicks;

	  spacing = myTickSpacing;
	}

      tickPos = min + (spacing - fmod(min,spacing));
    }

  ticks.clear();

  if (IAmFlipped)
    ticks.push_back(Tick(1.0,true,myMax));
  else
    ticks.push_back(Tick(0.0,true,myMin));

  if (myTickSpacing > 0 || IAmUsingTickCount)
    for (; tickPos < max; tickPos += spacing)
      {
        // Calculate new spacing
        if (IHaveTicksPrDecade && !IAmUsingTickCount)
          if (floor(log10(tickPos)) > floor(log10(spacing)) || floor(log10(myTickSpacing)) != 0.0)
            {
              // Add tick
              if (floor(log10(myTickSpacing)) == 0.0 || tickPos == myTickSpacing)
                ticks.push_back(Tick(this->getNormValue(tickPos),true,tickPos));

              // New Spacing
              spacing = pow(10.0,floor(log10(tickPos))) * myTickSpacing;
              if (log10(myTickSpacing) >= 0)
                tickPos += spacing - fmod(tickPos,spacing);
            }

        // Add tick
        ticks.push_back(Tick(this->getNormValue(tickPos),true,tickPos));
      }

  if (IAmFlipped)
    ticks.push_back(Tick(0.0,true,myMin));
  else
    ticks.push_back(Tick(1.0,true,myMax));
}


unsigned int FFaLegendMapper::redBlue(double normalizedNumber)
{
  /*
    rrggbbaa
    ff0000ff maks 255
    aa00aaff
    0000ffff min 0
  */

  if (normalizedNumber == HUGE_VAL)
    return 0x888888ff;

  if (normalizedNumber == -HUGE_VAL)
    return 0x888888ff;

  if (normalizedNumber > 1.0+FLT_EPSILON)
    return 0xff0000ff;

  if (normalizedNumber < 0.0-FLT_EPSILON)
    return 0x0000ffff;

  unsigned char R = (unsigned char)(normalizedNumber*255.0);
  unsigned char B = (unsigned char)((1.0-normalizedNumber)*255.0);
  return 0x01000000*R + 0x00000100*B + 0x000000ff;
}


unsigned int FFaLegendMapper::fullColor(double normalizedNumber)
{
  /*
    rrggbbaa
    ff0000ff maks 1023
    ffaa00ff
    ffff00ff 3/4 767
    aaff00ff
    00ff00ff 2/4 511
    00ffaaff
    00ffffff 1/4 255
    00aaffff
    0000ffff min 0
  */

  if (normalizedNumber == HUGE_VAL)
    return 0x888888ff;

  if (normalizedNumber == -HUGE_VAL)
    return 0x888888ff;

  if (normalizedNumber > 1.0+FLT_EPSILON)
    return 0xff0000ff;

  if (normalizedNumber < 0.0-FLT_EPSILON)
    return 0x0000ffff;

  unsigned int colorNum = (unsigned int)(normalizedNumber*1023.0);

  if (colorNum >= 1023)
    return 0xff0000ff;
  else if (colorNum >= 767)
    return 0xffff00ff - (colorNum - 767) * 0x00010000;
  else if (colorNum >= 511)
    return 0x00ff00ff + (colorNum - 511) * 0x01000000;
  else if (colorNum >= 255)
    return 0x00ffffff - (colorNum - 255) * 0x00000100;
  else
    return 0x0000ffff + (colorNum - 0  ) * 0x00010000;
}


unsigned int FFaLegendMapper::fullColorBW(double normalizedNumber)
{
  /*
    rrggbbaa
    ff0000ff maks 1023
    ffaa00ff
    ffff00ff 3/4 767
    aaff00ff
    00ff00ff 2/4 511
    00ffaaff
    00ffffff 1/4 255
    00aaffff
    0000ffff min 0
  */

  if (normalizedNumber == HUGE_VAL)
    return 0x888888ff;

  if (normalizedNumber == -HUGE_VAL)
    return 0x888888ff;

  if (normalizedNumber > 1.0+FLT_EPSILON)
    return 0xffffffff;

  if (normalizedNumber < 0.0-FLT_EPSILON)
    return 0x000000ff;

  unsigned int colorNum = (unsigned int)(normalizedNumber*1023.0);

  if (colorNum >= 1023)
    return 0xff0000ff;
  else if (colorNum >= 767)
    return 0xffff00ff - (colorNum - 767) * 0x00010000;
  else if (colorNum >= 511)
    return 0x00ff00ff + (colorNum - 511) * 0x01000000;
  else if (colorNum >= 255)
    return 0x00ffffff - (colorNum - 255) * 0x00000100;
  else
    return 0x0000ffff + (colorNum - 0  ) * 0x00010000;
}


unsigned int FFaLegendMapper::fullColorClipp(double normalizedNumber)
{
  /*
    rrggbbaa
    ff0000ff maks 1023
    ffaa00ff
    ffff00ff 3/4 767
    aaff00ff
    00ff00ff 2/4 511
    00ffaaff
    00ffffff 1/4 255
    00aaffff
    0000ffff min 0
  */

  if (normalizedNumber == HUGE_VAL)
    return 0x00000000;

  if (normalizedNumber == -HUGE_VAL)
    return 0x00000000;

  if (normalizedNumber > 1.0+FLT_EPSILON)
    return 0x00000000;

  if (normalizedNumber < 0.0-FLT_EPSILON)
    return 0x00000000;

  unsigned int colorNum = (unsigned int)(normalizedNumber*1023.0);

  if (colorNum >= 1023)
    return 0xff0000ff;
  else if (colorNum >= 767)
    return 0xffff00ff - (colorNum - 767) * 0x00010000;
  else if (colorNum >= 511)
    return 0x00ff00ff + (colorNum - 511) * 0x01000000;
  else if (colorNum >= 255)
    return 0x00ffffff - (colorNum - 255) * 0x00000100;
  else
    return 0x0000ffff + (colorNum - 0  ) * 0x00010000;
}


FFaLegendMapper::MapFuncMap FFaLegendMapper::initValueMappings()
{
  MapFuncMap mapping;
  mapping["Linear"] = FFaLegendMapper::noOp;
  mapping["Log10"] = log10;

  return mapping;
}


FFaLegendMapper::ColorFuncMap FFaLegendMapper::initColorMappings()
{
  ColorFuncMap mapping;
  mapping["Full color"] = FFaLegendMapper::fullColor;
  mapping["Red-blue"] = FFaLegendMapper::redBlue;
  mapping["Full color B/W limits"] = FFaLegendMapper::fullColorBW;
  mapping["Full color clipped limits"] = FFaLegendMapper::fullColorClipp;

  return mapping;
}


std::set<std::string> FFaLegendMapper::initUseDecadeTickMappings()
{
  std::set<std::string> decadeTickMappings;
  decadeTickMappings.insert("Log10");
  decadeTickMappings.insert("Log");
  decadeTickMappings.insert("Ln");

  return decadeTickMappings;
}
