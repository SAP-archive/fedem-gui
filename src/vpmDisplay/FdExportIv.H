// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FD_EXPORT_IV_H
#define FD_EXPORT_IV_H

class SoNode;

namespace FdExportIv
{
  bool exportGraph(SoNode* root, const char* filename);
}

#endif
