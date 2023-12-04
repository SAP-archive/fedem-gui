// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FP_BATCH_PROCESS_H
#define FP_BATCH_PROCESS_H


class FpBatchProcess
{
public:
  // returns true if the user wants to run batch
  static bool userWantsBatch();

  // runs the batch stuff
  static bool setupBatch();
};

#endif
