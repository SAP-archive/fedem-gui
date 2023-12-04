/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * AirfoilItem.C
 *
 *  Created on: Apr 18, 2012
 *      Author: runarhr
 */

#include <cmath>

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

#include "FFuLib/FFuCustom/components/renderers/graphicsItems/AirfoilItem.H"
#include "FFuLib/FFuCustom/components/renderers/AirfoilView.H"

AirfoilItem::AirfoilItem(AirfoilView* pAirfoilView, int tab, float thickness,
                         float aOffsetX, float aOffsetY,
                         float pOffsetX, float pOffsetY,
                         float eOffsetX, float eOffsetY, float eRot,
                         float mOffsetX, float mOffsetY) : apView(pAirfoilView)
{
  aTab = tab;

  this->setFlag(ItemSendsGeometryChanges);
  this->setCacheMode(DeviceCoordinateCache);
  this->setZValue(-1);

  aThickness = thickness;
  aElasticRotation = eRot;
  aAeroOffset    = std::make_pair(aOffsetX,aOffsetY);
  aElasticOffset = std::make_pair(eOffsetX,eOffsetY);
  aPitchOffset   = std::make_pair(pOffsetX,pOffsetY);
  aMassOffset    = std::make_pair(mOffsetX,mOffsetY);
}


QRectF AirfoilItem::boundingRect() const{
	return QRectF(QPointF(-65,-65), QSizeF( 130 ,130 ) );
}

QPainterPath AirfoilItem::shape() const{
	QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void AirfoilItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*){
  const float width = 110.0f;
  const float offset = 55.0f;

	// Draw airfoil
	QVector<QPointF> pointsTop;
	QVector<QPointF> pointsBottom;

	painter->setPen(QPen(Qt::black, 2));

	float c=1; // Chord length
	float t = 0;// Thickness as fraction of chord
	if(aThickness<=1 && aThickness >=0){
		 t = aThickness;
	}
	float p=0.4; // Location of maximum camber
	float m = 0.03; // Maximum camber

	float dx_prev = 0;
	float y_c_prev = 0;
	for(int i=1; i<500; i++){
			float dx = p*c*(i/500.0f);
			float y_c = m*(dx/(p*p))*(2*p-(dx/c));
			float y_t = (t/0.2)*c*(  0.2969*sqrt(dx/c) -0.1260*(dx/c) - 0.3516*(dx/c)*(dx/c) + 0.2843 * (dx/c)*(dx/c)*(dx/c) - 0.1015*(dx/c)*(dx/c)*(dx/c)*(dx/c) );
			float x_U = dx - y_t*sin(atan((y_c-y_c_prev)/(dx-dx_prev)));
			float y_U = y_c + y_t*cos(atan((y_c-y_c_prev)/(dx-dx_prev)));
			float x_L = dx + y_t*sin(atan((y_c-y_c_prev)/(dx-dx_prev)));
			float y_L = y_c - y_t*cos(atan((y_c-y_c_prev)/(dx-dx_prev)));
			pointsTop.push_back(QPointF(-offset+x_U*width,y_U*width));
			pointsBottom.push_front(QPointF(-offset+x_L*width,y_L*width));
			dx_prev = 0;
			y_c_prev = 0;
	}

	dx_prev = 0;
	y_c_prev = 0;
	for(int i=1; i<500; i++){
			float dx = p*c + (1-p)*c*(i/500.0f);
			float y_c = m*( (c -dx)/((1-p)*(1-p)) )*(1+(dx/c)-2*p);
			float y_t = (t/0.2)*c*(  0.2969*sqrt(dx/c)  -0.1260*(dx/c) - 0.3516*(dx/c)*(dx/c) + 0.2843 * (dx/c)*(dx/c)*(dx/c) - 0.1015*(dx/c)*(dx/c)*(dx/c)*(dx/c) );
			float x_U = dx - y_t*sin(atan((y_c-y_c_prev)/(dx-dx_prev)));
			float y_U = y_c + y_t*cos(atan((y_c-y_c_prev)/(dx-dx_prev)));
			float x_L = dx + y_t*sin(atan((y_c-y_c_prev)/(dx-dx_prev)));
			float y_L = y_c - y_t*cos(atan((y_c-y_c_prev)/(dx-dx_prev)));
			pointsTop.push_back(QPointF(-offset + x_U*width,y_U*width));
			pointsBottom.push_front(QPointF(-offset + x_L*width,y_L*width));
			dx_prev = 0;
			y_c_prev = 0;

		}

	QVector<QPointF> points;
	for(QVector<QPointF>::iterator pointIt = pointsTop.begin(); pointIt != pointsTop.end(); ++pointIt){
		points.push_back((*pointIt));
	}
	for(QVector<QPointF>::iterator pointIt = pointsBottom.begin(); pointIt != pointsBottom.end(); ++pointIt){
		points.push_back((*pointIt));
	}
	painter->setRenderHint(QPainter::Antialiasing, true);
	if(aThickness==1)
		painter->drawEllipse(QPointF(0,0), offset,offset);
	else
		painter->drawPolygon(points.data(), points.count());

	//Chord
	painter->setPen(QPen(Qt::DashLine));
	painter->drawLine(-offset,0,offset+10,0);
	painter->drawLine(-offset,-offset+10,-offset,offset-10);

	painter->setPen(QPen(Qt::black, 1));
	// Pitch center
	painter->setPen(QPen(Qt::SolidLine));
	painter->setBrush(QBrush(Qt::white));
	painter->drawEllipse(QPoint(-offset + width*aPitchOffset.first, width*aPitchOffset.second),8,8);

	// Aero center
	painter->setPen(QPen(Qt::SolidLine));
	painter->setBrush(QBrush(Qt::blue));
	painter->drawEllipse(QPoint(-offset + width*aAeroOffset.first, width*aAeroOffset.second),6,6);

	// Elastic center
	painter->setBrush(QBrush(Qt::red));
	painter->setPen(QPen(Qt::SolidLine));
	painter->drawEllipse(QPoint(-offset + width*aElasticOffset.first, width*aElasticOffset.second),4,4);

	// Rotating around elasticity axis
	painter->translate(QPoint(-offset + width*aElasticOffset.first, width*aElasticOffset.second));
	painter->rotate(aElasticRotation);

	// Elastic axes
	if(aTab == 1){
		painter->setPen(QPen(Qt::red, 1, Qt::DashLine));
		painter->drawLine(-offset,0,offset,0);
		painter->drawLine(0,-offset,0,offset);

		painter->setPen(QPen(Qt::darkGreen,1,Qt::DashLine));
		painter->drawLine(0,width*aMassOffset.second, width*aMassOffset.first,width*aMassOffset.second);
		painter->drawLine(width*aMassOffset.first, 0, width*aMassOffset.first, width*aMassOffset.second);
	}

	// Mass center
	painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
	painter->setBrush(QBrush(Qt::darkGreen));
	painter->drawEllipse(QPoint( width*(aMassOffset.first), width*(aMassOffset.second)),2,2);
}

void AirfoilItem::mousePressEvent(QGraphicsSceneMouseEvent* event){
	update();
	QGraphicsItem::mousePressEvent(event);
}
