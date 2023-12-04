// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuaQtPixmapCache.H"
#include <map>


QPixmap FFuaQtPixmapCache::getPixmap(const char** xpmData,
                                     int width, int height)
{
  static std::map<const char**,QPixmap> ourPixmapCache;
  std::map<const char**,QPixmap>::iterator it = ourPixmapCache.find(xpmData);

  if (it != ourPixmapCache.end())
    return it->second;

  QPixmap pixmap(xpmData);
  if (width > 0 && height > 0)
    return ourPixmapCache[xpmData] = pixmap.scaled(width,height);
  else if (width > 0)
    return ourPixmapCache[xpmData] = pixmap.scaledToWidth(width);
  else if (height > 0)
    return ourPixmapCache[xpmData] = pixmap.scaledToWidth(height);
  else
    return ourPixmapCache[xpmData] = pixmap;
}
