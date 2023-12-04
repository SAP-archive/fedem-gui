/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * AxesItem.H
 *
 *  Created on: Apr 19, 2012
 *      Author: runarhr
 */

#ifndef AXES_ITEM_H
#define AXES_ITEM_H

#include <vector>

#include <QGraphicsItem>

class BladeView;

class AxesItem : public QGraphicsItem{
public:
	AxesItem(float maxX, float minX, float maxY, float minY, float xScale,float yScale, BladeView* pBladeView);
	~AxesItem();

	QRectF boundingRect() const;
    QPainterPath shape() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

	void addTickX(float pos);
	void addTickY(float pos);

private:
	BladeView* apView;

	float xMax;
	float xMin;
	float yMax;
	float yMin;
	float aXScale;
	float aYScale;

	std::vector<float>* apTicksX;
	std::vector<float>* apTicksY;

};

#endif /* AXES_ITEM_H */
