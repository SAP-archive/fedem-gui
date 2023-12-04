// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FAP_UA_QUERY_MATCH_H
#define FAP_UA_QUERY_MATCH_H

#include <string>

class FmModelMemberBase;


struct FFuaQueryMatch
{
  FmModelMemberBase* matchItem = NULL;
  std::string        matchDescription;
};

#endif
