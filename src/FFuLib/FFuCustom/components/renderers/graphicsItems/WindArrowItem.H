/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * WindArrowItem.H
 *
 *  Created on: Apr 26, 2012
 *      Author: runarhr
 */

#ifndef WINDARROW_ITEM_H
#define WINDARROW_ITEM_H

#include <QGraphicsItem>

class AirfoilView;

class WindArrowItem : public QGraphicsItem{
public:
	WindArrowItem(AirfoilView* pAirfoilView);
	~WindArrowItem();

	QRectF boundingRect() const;
	QPainterPath shape() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
	AirfoilView* apView;
};

#endif /* WINDARROW_ITEM_H */
