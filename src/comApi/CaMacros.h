/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
#pragma once

#define CA_CHECK(x) \
  if (x == NULL) \
    AfxThrowOleException(CO_E_OBJNOTCONNECTED)
