/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * QuadItem.H
 *
 *  Created on: Apr 18, 2012
 *      Author: runarhr
 */

#ifndef QUAD_ITEM_H
#define QUAD_ITEM_H

#include <QGraphicsItem>

class BladeView;

class QuadItem : public QGraphicsItem{

public:
	QuadItem(QVector<QPointF> points, BladeView* pBladeView);
	~QuadItem();

    QRectF boundingRect() const;
    QPainterPath shape() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

	void select();
	void deselect();

protected:

	void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
	BladeView* apView;

	bool aSelected;
	QVector<QPointF>* aPoints;
	QColor aColor;

	float maxX;
	float minX;
	float maxY;
	float minY;

	float aWidth;
	float aHeight;
};

#endif /* QUAD_ITEM_H */
