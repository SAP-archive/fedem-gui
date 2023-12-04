// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuIOField.H"
#include "FFaLib/FFaString/FFaStringExt.H"

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <cfloat>
#include <cmath>


FFuIOField::FFuIOField()
{
  this->myLastValidDouble = 0.0;
  this->myLastValidInt = 0;

  this->myAcceptPolicy = FFuIOField::ENTERONLY;
  this->myInputCheckingMode = FFuIOField::NOCHECK;
  this->myDoubleDisplayMode = FFuIOField::AUTO;
  this->myDoubleDisplayPrecision = 8;
  this->myZeroDisplayPrecision = 1;

  this->IAmGettingRealFocusIn = true;
  this->IAmChanged = false;
  this->useCustomBackgroundColor = false;
}


void FFuIOField::setValue(double d)
{
  switch (this->myDoubleDisplayMode)
    {
    case SCIFI:
      this->setValue(FFaNumStr(d, this->myDoubleDisplayPrecision,
			       this->myDoubleDisplayPrecision,
			       0.0, 0.0).c_str());
      break;

    case DECIMAL:
      this->setValue(FFaNumStr(d, this->myDoubleDisplayPrecision,
			       this->myDoubleDisplayPrecision,
			       1.0e+99, 0.0, true).c_str());
      break;

    default:
      this->setValue(FFaNumStr(d, this->myZeroDisplayPrecision,
			       this->myDoubleDisplayPrecision,
			       1.0e+7, 1.0e-5, true).c_str());
    }

  this->myLastValidDouble = d;
  this->myLastValue = this->getValue();
}


void FFuIOField::setValue(int i)
{
  this->setValue(FFaNumStr(i).c_str());
  this->myLastValidInt = i;
  this->myLastValue = this->getValue();
}


void FFuIOField::setValue(const std::string& value)
{
  this->setValue(value.c_str());
  this->IAmChanged = true;
  this->myLastValue = this->getValue();
}


double FFuIOField::getDouble() const
{
  if (this->IAmChanged && this->isDouble()) {
    this->myLastValidDouble = this->getDoubleFromText();
    this->IAmChanged = false;
  }
  return this->myLastValidDouble;
}

int FFuIOField::getInt() const
{
  if (this->IAmChanged && this->isInt()) {
    this->myLastValidInt = this->getIntFromText();
    this->IAmChanged = false;
  }
  return this->myLastValidInt;
}


double FFuIOField::getDoubleFromText() const
{
  char str[BUFSIZ];
  removeWhiteSpace(this->getValue(),str,BUFSIZ);
  if ((strcmp(str,"") == 0) ||
      (strcmp(str,"0") == 0) ||
      (strcmp(str,"-0") == 0))
    return 0.0;

  return atof(str);
}

int FFuIOField::getIntFromText() const
{
  char str[BUFSIZ];
  removeWhiteSpace(this->getValue(),str,BUFSIZ);
  if (strcmp(str,"") == 0)
    return 0;

  return atoi(str);
}


void FFuIOField::removeWhiteSpace(const std::string& instr, char* outstr, size_t nout)
{
  size_t i, j, nin = instr.size();
  for (i = j = 0; i < nin && j < nout; i++)
    if (!isspace(instr[i]))
      outstr[j++] = instr[i];

  outstr[j < nout ? j : nout-1] = '\0';
}


bool FFuIOField::isInt() const
{
  return (checkValue(this->getValue(),INTEGER,CH_FINAL) == STR_OK);
}

bool FFuIOField::isDouble() const
{
  return (checkValue(this->getValue(),DOUBLE,CH_FINAL) == STR_OK);
}


void FFuIOField::setAcceptedCB(const FFaDynCB1<char*>& aDynCB)
{
  this->myTextAcceptedCB = aDynCB;
}

void FFuIOField::setAcceptedCB(const FFaDynCB1<const std::string&>& aDynCB)
{
  this->myStringAcceptedCB = aDynCB;
}

void FFuIOField::setAcceptedCB(const FFaDynCB1<double>& aDynCB)
{
  this->myDoubleAcceptedCB = aDynCB;
}

void FFuIOField::setAcceptedCB(const FFaDynCB1<int>& aDynCB)
{
  this->myIntAcceptedCB = aDynCB;
}


void FFuIOField::tChanged(const std::string& s)
{
  this->IAmChanged = 2; // distinguish between editing and setValue()
  switch (this->myInputCheckingMode)
    {
    case DOUBLECHECK:
      switch (checkValue(s,DOUBLE,CH_TEMP))
	{
	case STR_OK:
	  this->myLastValue = s;
	  break;
	case STR_EMPTY:
	  this->setValue(0.0);
	  break;
	default:
	  std::cout << '\a' << std::flush;
	  this->setValue(this->myLastValue.c_str());
	}
      break;
    case INTEGERCHECK:
      switch (checkValue(s,INTEGER,CH_TEMP))
	{
	case STR_OK:
	  this->myLastValue = s;
	  break;
	case STR_EMPTY:
	  this->setValue(0);
	  break;
	default:
	  std::cout << '\a' << std::flush;
	  this->setValue(this->myLastValue.c_str());
	}
      break;
    default:
      this->myLastValue = s;
    }
}


void FFuIOField::keybFocusOut(bool isReal)
{
  switch (this->myAcceptPolicy)
    {
    case SMARTFOCUS:
      this->IAmGettingRealFocusIn = isReal;
      if (isReal) break;
    case FOCUSOUT:
      this->callAcceptedCBs();
    }
}


void FFuIOField::keybFocusIn()
{
  switch (this->myAcceptPolicy)
    {
    case SMARTFOCUS:
      if (!this->IAmGettingRealFocusIn) break;
    case FOCUSOUT:
      if (this->isDouble())
	this->myLastValidDouble = this->getDoubleFromText();
      if (this->isInt())
	this->myLastValidInt = this->getIntFromText();
    }
}


void FFuIOField::callAcceptedCBs()
{
  if (this->isDouble())
    {
      this->myLastValidDouble = this->getDoubleFromText();
      this->myDoubleAcceptedCB.invoke(this->getDouble());
    }
  else if (this->myInputCheckingMode == DOUBLECHECK)
    {
      std::cout << '\a' << std::flush;
      this->setValue(this->myLastValidDouble);
    }

  if (this->isInt())
    {
      this->myLastValidInt = this->getIntFromText();
      this->myIntAcceptedCB.invoke(this->getInt());
    }
  else if (this->myInputCheckingMode == INTEGERCHECK)
    {
      std::cout << '\a' << std::flush;
      this->setValue(this->myLastValidInt);
    }

  std::string myText = this->getValue();
  this->myTextAcceptedCB.invoke(const_cast<char*>(myText.c_str()));
  this->myStringAcceptedCB.invoke(myText);

  this->IAmChanged = false;
}


int FFuIOField::checkValue(const std::string& str, int type, int check)
{
  // This algorithm was provided by NSS

  double dec;
  size_t i, j;
  int exp = 0;
  int isign = 1;
  bool point = true;

  char string[BUFSIZ];
  removeWhiteSpace(str,string,BUFSIZ); // To account for digit grouping.
  size_t nchar = strlen(string);

  // Check if we got a sign
  if (nchar > 0 && (string[0] == '-' || string[0] == '+'))
    i = 1;
  else
    i = 0;

  if (nchar == i) // Is this empty ?
    return check == CH_TEMP ? STR_OK : STR_EMPTY;

  switch (type) {
  case FLOAT:
  case DOUBLE:
    // Now we want to start on the digits,
    // but it might be a decimal-point there
    point = false;
    for (j = i; j < nchar; j++) // Go through rest of string
      if (string[j] == '.')
      {
        if (point)
          return STR_GARBAGE; // If we get two points then return Error
        else
          point = true; // We found the first point
      }
      else if (!isdigit(string[j]))
        break; // Non-digit character (exept '.'), stop parsing (it might be an e)

    // If the string stopped after sign, and this is a final check:
    if (j == i && check == CH_FINAL)
      return STR_GARBAGE;

    // If we stopped parsing just after point:
    if (j == i+1 && point)
    {
      if (check == CH_FINAL)
        return STR_GARBAGE;
      else if (j == nchar)
        return STR_OK;
      else
        return STR_GARBAGE; // a non digit char was after the '.'
    }

    dec = atof(string); // dec is number without the exponent

    i = j; // Make i point to the start of the exponent value
    if (tolower(string[i]) == 'e')
    {
      if (string[++i] == '-')
        i++, isign = -1;
      else if (string[i] == '+')
        i++, isign = 1;

      for (j = i; j < nchar; j++) // integer (at least one digit)
	if (!isdigit(string[j]))
          return STR_GARBAGE;

      if (j > i && i < nchar)
	exp = isign*atol(string+i); // Translate the exponent number to int
      else if (check == CH_FINAL)
	return STR_GARBAGE; // Nothing after sign
    }
    else if (i < nchar) // If we are not on the end, there was garbage chars on the end
      return STR_GARBAGE;

    // Check size
    if (dec > 0.0)
    {
      int dp = (int)log10(dec); // Adjust exponent
      exp += dp;
      dec /= pow(10.0,(double)dp);
    }

    if (type == FLOAT)
    {
      if (exp > FLT_MAX_10_EXP)
        return STR_LARGE;
      else if (exp < FLT_MIN_10_EXP)
        return STR_SMALL;
    }
    else
    {
      if (exp > DBL_MAX_10_EXP)
        return STR_LARGE;
      else if ( exp < DBL_MIN_10_EXP)
        return STR_SMALL;
    }
    break;

  case INTEGER:
    // Now only digits can be entered
    for (j = i; j < nchar; j++)
      if (!isdigit(string[j]))
        return STR_GARBAGE;
    break;

  default:
    return STR_GARBAGE;
  }

  return STR_OK;
}
