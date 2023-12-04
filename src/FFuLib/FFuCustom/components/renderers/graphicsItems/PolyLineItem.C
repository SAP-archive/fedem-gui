/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * PolyLineItem.C
 *
 *  Created on: Jun 4, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/components/renderers/graphicsItems/PolyLineItem.H"
#include "FFuLib/FFuCustom/components/renderers/BladeView.H"

#include <QLinearGradient>

PolyLineItem::PolyLineItem(QVector<QPointF>& points, QColor color, BladeView* pBladeView)  : apView(pBladeView){
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(-0.8);

	aColor = color;

	if(points.size()>0){
		for(QVector<QPointF>::iterator pointIt = points.begin(); pointIt != points.end(); pointIt++){
			apPoints.push_back(*pointIt);
		}
	}else{
		for(int i = 0; i< 4; i++){
			apPoints.push_back(QPointF(0,0));
		}
	}
}

PolyLineItem::~PolyLineItem() {
	// TODO Auto-generated destructor stub
}

QRectF PolyLineItem::boundingRect() const{
	return QRectF(QPointF(0,-100), QPointF( 800,100) );
}

QPainterPath PolyLineItem::shape() const{
	QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void PolyLineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
  	QLinearGradient linearGrad(QPointF(0, 0), QPointF(1200, 50));
		QColor color1(aColor);//("#fdd000");
		QColor color2(Qt::black);//"#f77500");
		color1.setAlpha(120);
		color2.setAlpha(120);
    	linearGrad.setColorAt(0, color1);
		linearGrad.setColorAt(1, color2);


	painter->setRenderHint(QPainter::Antialiasing, true);
	painter->setBrush(QBrush(aColor));

	for(int i = 0; i< apPoints.size()-1; ++i){
		painter->setPen(QPen(aColor, 1));
		painter->drawLine(apPoints.at(i), apPoints.at(i+1));
		painter->setPen(QPen(Qt::black, 1));
		painter->drawEllipse(apPoints.at(i+1),2,2);
	}
	painter->drawEllipse(apPoints.at(0),2,2);
}
