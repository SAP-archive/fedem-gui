// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_QUERY_H
#define FAP_UA_QUERY_H

#include "vpmDB/FmQuery.H"
#include "FFaLib/FFaPatterns/FFaSingelton.H"

class FuiQueryInputFieldValues;


/*!
  \brief A collecting class for Querys used to map between the DB and UI.

  \details The UI and UA is only passing the pointer around.
  The real "query" is in the class FmQuery.
*/

class FFuaQueryBase : public FmQuery
{
public:
  static void onQIFieldButtonCB(FuiQueryInputFieldValues& v);
};

//! Alias for backward compatibility
using FapUAQuery = FFuaQueryBase;


/*!
  \brief A sub-class querying for FileReferences only.
*/

class FapUAFileRefQuery : public FapUAQuery, public FFaSingelton<FapUAFileRefQuery>
{
public:
  FapUAFileRefQuery();
};


/*!
  \brief A sub-class querying for Beam properties only.
*/

class FapUABeamPropQuery : public FapUAQuery, public FFaSingelton<FapUABeamPropQuery>
{
public:
  FapUABeamPropQuery();
};


/*!
  \brief A sub-class querying for Material properties only.
*/

class FapUAMaterialPropQuery : public FapUAQuery, public FFaSingelton<FapUAMaterialPropQuery>
{
public:
  FapUAMaterialPropQuery();
};


/*!
  \brief A sub-class querying for Triads only.
*/

class FapUATriadQuery : public FapUAQuery, public FFaSingelton<FapUATriadQuery>
{
public:
  FapUATriadQuery();
};


/*!
  \brief A sub-class querying for Links only.
*/

class FapUALinkQuery : public FapUAQuery, public FFaSingelton<FapUALinkQuery>
{
public:
  FapUALinkQuery();
};


/*!
  \brief A sub-class querying for RevJoints only.
*/

class FapUARevJointQuery : public FapUAQuery, public FFaSingelton<FapUARevJointQuery>
{
public:
  FapUARevJointQuery();
};


/*!
  \brief A sub-class querying for Engines only.
*/

class FapUAEngineQuery : public FapUAQuery, public FFaSingelton<FapUAEngineQuery>
{
public:
  FapUAEngineQuery();
private:
  static void verify(bool& isOK, FmModelMemberBase* item);
};


/*!
  \brief A sub-class querying for Road functions only.
*/

class FapUARoadFuncQuery : public FapUAQuery, public FFaSingelton<FapUARoadFuncQuery>
{
public:
  FapUARoadFuncQuery();
private:
  static void verify(bool& isOK, FmModelMemberBase* item);
};


/*!
  \brief A sub-class querying for Wave functions only.
*/

class FapUAWaveFuncQuery : public FapUAQuery, public FFaSingelton<FapUAWaveFuncQuery>
{
public:
  FapUAWaveFuncQuery();
private:
  static void verify(bool& isOK, FmModelMemberBase* item);
};


/*!
  \brief A sub-class querying for Current functions only.
*/

class FapUACurrFuncQuery : public FapUAQuery, public FFaSingelton<FapUACurrFuncQuery>
{
public:
  FapUACurrFuncQuery();
private:
  static void verify(bool& isOK, FmModelMemberBase* item);
};

#endif
