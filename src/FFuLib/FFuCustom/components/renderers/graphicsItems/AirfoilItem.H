/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * AirfoilItem.H
 *
 *  Created on: Apr 18, 2012
 *      Author: runarhr
 */

#ifndef AIRFOIL_ITEM_H
#define AIRFOIL_ITEM_H

#include <QGraphicsItem>
#include <utility>

class AirfoilView;

class AirfoilItem : public QGraphicsItem
{
public:
  AirfoilItem(AirfoilView* pAirfoilView, int tab = 0,
              float thickness = 0.0f,
              float aOffsetX = 0.0f, float aOffsetY = 0.0f,
              float pOffsetX = 0.0f, float pOffsetY = 0.0f,
              float eOffsetX = 0.0f, float eOffsetY = 0.0f, float eRot = 0.0f,
              float mOffsetX = 0.0f, float mOffsetY = 0.0f);
  virtual ~AirfoilItem() {}

  QRectF boundingRect() const;
  QPainterPath shape() const;

  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget);

protected:
  void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
  AirfoilView* apView;
  int          aTab;

  float aThickness;
  float aElasticRotation;
  std::pair<float,float> aAeroOffset;
  std::pair<float,float> aPitchOffset;
  std::pair<float,float> aElasticOffset;
  std::pair<float,float> aMassOffset;
};

#endif /* AIRFOIL_ITEM_H */
