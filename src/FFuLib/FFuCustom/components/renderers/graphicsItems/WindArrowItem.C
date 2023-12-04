/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * WindArrowItem.C
 *
 *  Created on: Apr 26, 2012
 *      Author: runarhr
 */

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QString>

#include "FFuLib/FFuCustom/components/renderers/graphicsItems/WindArrowItem.H"
#include "FFuLib/FFuCustom/components/renderers/AirfoilView.H"

WindArrowItem::WindArrowItem(AirfoilView* pAirfoilView) : apView(pAirfoilView){
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-1);
}

WindArrowItem::~WindArrowItem() {
	// TODO Auto-generated destructor stub
}


QRectF WindArrowItem::boundingRect() const{
	return QRectF(QPointF(-40,-70), QSizeF( 80 ,100 ) );
}

QPainterPath WindArrowItem::shape() const{
	QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void WindArrowItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
	painter->setPen(QPen(Qt::black, 1));

	//Arrow
	QPoint arrowPoints[7];
	arrowPoints[0] = QPoint(25,-10);
	arrowPoints[1] = QPoint(0,-10);
	arrowPoints[2] = QPoint(0,-15);
	arrowPoints[3] = QPoint(-15,0);
	arrowPoints[4] = QPoint(0,15);
	arrowPoints[5] = QPoint(0,10);
	arrowPoints[6] = QPoint(25,10);

	painter->drawPolygon(arrowPoints,7);

	//Text
    QRectF textRect(-5, -5, 30 , 15);
	QString message("Wind");
	QFont font = painter->font();
	font.setBold(false);
	font.setPointSize(6);
	painter->setFont(font);
	painter->setPen(Qt::black);
	painter->drawText(textRect, message);

	//Dots
	//Pitch center
	painter->setPen(QPen(Qt::black,1));
	painter->setBrush(QBrush(Qt::white));
	painter->drawEllipse(QPoint(-30,-60),4,4);
	QRectF textRectPitch(-25, -65, 70 , 15);
	QString pitchMessage("Pitch center");
	painter->setPen(Qt::black);
	painter->drawText(textRectPitch, pitchMessage);

	// Aero center
	painter->setPen(QPen(Qt::black,0));
	painter->setBrush(QBrush(Qt::blue));
	painter->drawEllipse(QPoint(-30,-50),3,3);
	QRectF textRectAero(-25, -55, 70 , 15);
	QString aeroMessage("Aero center");
	painter->setPen(Qt::black);
	painter->drawText(textRectAero, aeroMessage);

	//elastic center
	painter->setPen(QPen(Qt::black,0));
	painter->setBrush(QBrush(Qt::red));
	painter->drawEllipse(QPoint(-30,-40),2,2);
	QRectF textRectElastic(-28, -45, 70 , 15);
	QString elasticMessage("Elastic center");
	painter->setPen(Qt::black);
	painter->drawText(textRectElastic, elasticMessage);

	//mass center
	painter->setPen(QPen(Qt::black,0));
	painter->setBrush(QBrush(Qt::darkGreen));
	painter->drawEllipse(QPoint(-30,-30),2,2);
	QRectF textRectMass(-25, -35, 70 , 15);
	QString massMessage("Mass center");
	painter->setPen(Qt::black);
	painter->drawText(textRectMass, massMessage);
}
