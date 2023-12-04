/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * PolyLineItem.H
 *
 *  Created on: Jun 4, 2012
 *      Author: runarhr
 */

#ifndef POLYLINEITEM_H
#define POLYLINEITEM_H

#include <QGraphicsItem>
#include <QPoint>

class BladeView;

class PolyLineItem : public QGraphicsItem{
public:
	PolyLineItem( QVector<QPointF>& points, QColor color, BladeView* pBladeView);
	~PolyLineItem();

	QRectF boundingRect() const;
    QPainterPath shape() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
	BladeView* apView;

	QVector<QPointF> apPoints;
	QColor aColor;
};

#endif /* POLYLINEITEM_H */
