/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * BladeSegmentItem.C
 *
 *  Created on: Apr 18, 2012
 *      Author: runarhr
 */

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "FFuLib/FFuCustom/components/renderers/graphicsItems/QuadItem.H"
#include "FFuLib/FFuCustom/components/renderers/BladeView.H"

QuadItem::QuadItem( QVector<QPointF> points, BladeView* pBladeView ) : apView(pBladeView){
	setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);

    aPoints = new QVector<QPointF>;
    for(QVector<QPointF>::iterator pointIt = points.begin(); pointIt != points.end(); ++pointIt){
    	aPoints->push_back((*pointIt));
    }

    aColor = Qt::black;
    aSelected = false;

    maxX = 0;
    minX = 0;
    maxY = 0;
    minY = 0;

    aWidth = 0;
    aHeight = 0;

	for(QVector<QPointF>::iterator pointIt = aPoints->begin(); pointIt != aPoints->end(); ++pointIt){
		if((*pointIt).x() > maxX){
			maxX = (*pointIt).x();
		}
		if(pointIt->x() < minX){
			minX = (*pointIt).x();
		}
		if((*pointIt).y() > maxY){
			maxY = (*pointIt).y();
		}
		if((*pointIt).y() < minY){
			minY = (*pointIt).y();
		}
	}

	aWidth = maxX - minX;
	aHeight = maxY - minY;
}

QuadItem::~QuadItem(){
	aPoints->clear();
	delete aPoints;
}

QRectF QuadItem::boundingRect() const{
	return QRectF( QPointF( minX, minY ), QPointF( maxX, maxY) );
}

QPainterPath QuadItem::shape() const{
	QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void QuadItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    if(aSelected){
		painter->setPen(QPen(aColor, 0));

    	QLinearGradient linearGrad(QPointF(boundingRect().width()/2, minY), QPointF(boundingRect().width()/2, maxY));
		QColor color1("#f77500");
		QColor color2("#fdd000");
		color1.setAlpha(120);
		color2.setAlpha(120);
    	linearGrad.setColorAt(0, color1);
		linearGrad.setColorAt(1, color2);
		painter->setBrush(QBrush(linearGrad));

		painter->drawPolygon(aPoints->data(),4,Qt::WindingFill);
    }
    else{
    	painter->setBrush(QBrush(Qt::white));
    	painter->drawPolygon(aPoints->data(),4,Qt::WindingFill);
    }
}

void QuadItem::mousePressEvent(QGraphicsSceneMouseEvent* event){
	//aSelected = true;
	update();
	QGraphicsItem::mousePressEvent(event);
}

void QuadItem::select(){
	aSelected = true;

	update();
}

void QuadItem::deselect(){
	aSelected = false;

	update();
}
