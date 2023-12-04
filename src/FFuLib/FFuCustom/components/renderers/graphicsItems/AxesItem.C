/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * AxesItem.C
 *
 *  Created on: Apr 19, 2012
 *      Author: runarhr
 */
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QStaticText>

#include "FFuLib/FFuCustom/components/renderers/BladeView.H"
#include "FFuLib/FFuCustom/components/renderers/graphicsItems/AxesItem.H"



AxesItem::AxesItem(float maxX, float minX,float maxY, float minY, float xScale, float yScale, BladeView* pBladeView ) : apView(pBladeView){
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-0.8);

	apTicksX =  new std::vector<float>;
	apTicksY =  new std::vector<float>;;

	xMax = maxX;
	xMin = minX;
	yMax = maxY;
	yMin = minY;
	aXScale = xScale;
	aYScale = yScale;
}


AxesItem::~AxesItem() {
	apTicksX->clear();
	delete apTicksX;
	apTicksY->clear();
	delete apTicksY;
}

QRectF AxesItem::boundingRect() const{
	return QRectF(QPointF(-31, -yMax*aYScale -10), QPointF( xMax*aXScale +50, -yMin*aYScale+10) );
}

QPainterPath AxesItem::shape() const{
	QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void AxesItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
    painter->setPen(QPen(Qt::black, 2));

    //x-axis
    painter->drawLine(QPoint(0, 0), QPoint(xMax*aXScale + 20, 0) );
    //y-axis
    painter->drawLine(QPoint(0, -yMin*aYScale ), QPoint(0, -yMax*aYScale ) );

    painter->setPen(QPen(Qt::black, 1));
    /*//x-ticks
    for(std::vector<float>::iterator posIt = apTicksX->begin(); posIt != apTicksX->end(); ++posIt ){
    	painter->drawLine( QPoint( *posIt, -2), QPoint( *posIt, 2));
    }
    //y-ticks
    for(std::vector<float>::iterator posIt = apTicksY->begin(); posIt != apTicksY->end(); ++posIt ){
    	painter->drawLine( QPoint( -2, *posIt), QPoint( 2, *posIt));
    }*/

    // scale
    painter->drawStaticText(QPoint(xMax*aXScale, 10), QStaticText( QString::number( (double)xMax)  )	);
    painter->drawStaticText(QPoint(-30, -yMax*aYScale -5), QStaticText( QString::number( (double)yMax)  )	);
    painter->drawStaticText(QPoint(-30, -yMin*aYScale) , QStaticText( QString::number( (double)yMin)  )	);
}

void AxesItem::addTickX(float pos){
	apTicksX->push_back(pos);
}

void AxesItem::addTickY(float pos){
	apTicksY->push_back(pos);
}
