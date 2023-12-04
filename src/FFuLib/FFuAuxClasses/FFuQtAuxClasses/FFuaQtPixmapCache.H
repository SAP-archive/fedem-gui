// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFUA_QT_PIXMAP_CACHE_H
#define FFUA_QT_PIXMAP_CACHE_H

#include <QtGui/QPixmap>


namespace FFuaQtPixmapCache
{
  QPixmap getPixmap(const char** xpmData, int width = 0, int height = 0);
}

#endif
