/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * BladeView.C
 *
 *  Created on: Apr 18, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/components/renderers/BladeView.H"

BladeView::BladeView(QWidget* parent) :
		QGraphicsView(parent) {
	apBlade = NULL;
	apSceneSize = new QSize(625,145);
	scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setSceneRect(QRectF(QPointF(0,0), *apSceneSize));
	setScene(scene);
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
	scale(qreal(1.0), qreal(1.0));
	setWindowTitle(tr("Blade definition"));

	apSegments = new QVector<QuadItem*>;
	apAxes = new AxesItem(0,0,0,0,0,0,this);
}

BladeView::~BladeView(){
	while (apSegments->size() > 0) {
		scene->removeItem(apSegments->back());
		delete apSegments->back();
		apSegments->pop_back();
	}

	delete apSceneSize;
}

void BladeView::drawBackground(QPainter *painter, const QRectF &rect) {
    Q_UNUSED(rect);

    QRectF sceneRect = this->sceneRect();

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Blade segments along pitch axis"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(8);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect, message);
}

void BladeView::setBlade(Blade* pBlade){
	apBlade = pBlade;

	initializeSegments();
}

void BladeView::initializeSegments(){
	if(!(apBlade->GetAerodynamicData()->size() > 0 && apBlade->GetStructureData()->size() > 0)){
		return;
	}
	if(apBlade->GetAerodynamicData()->size() != apBlade->GetStructureData()->size())
		return;

	if(!(apBlade->GetAerodynamicData()->at(apBlade->GetAerodynamicData()->size()-1)->size() > 7) ||
			!(apBlade->GetStructureData()->at(apBlade->GetStructureData()->size()-1)->size() > 14)){
		return;
	}

	int xOffset = 20;
	float xRange=0;
	float yRange=0;
	float yMax=0;
	float yMin=0;
	float xScale = 0;
	float yScale = 0;

	QVector<QVariant> chords;
	QVector<QVariant> lengths;
	QVector<QVariant> pitchPos;
	QVector<QVariant> elasticPos;
	QVector<QVariant> aeroPos;
	QVector<QVariant> massPosX;
	QVector<QVariant> massPosY;
	QVector<QVariant> relativeRotations;

	for (QVector<QVector<QVariant>*>::iterator it = apBlade->GetAerodynamicData()->begin(); it != apBlade->GetAerodynamicData()->end(); ++it) {
		chords.push_back((*it)->at(1).toDouble());
		lengths.push_back((*it)->at(0).toDouble());
		pitchPos.push_back((*it)->at(3).toDouble());
		aeroPos.push_back((*it)->at(5).toDouble());
	}

	for (QVector<QVector<QVariant>*>::iterator it = apBlade->GetStructureData()->begin(); it != apBlade->GetStructureData()->end(); ++it) {
		elasticPos.push_back((*it)->at(0).toDouble());
		massPosX.push_back((*it)->at(3).toDouble());
		massPosY.push_back((*it)->at(4).toDouble());
		relativeRotations.push_back((*it)->at(2).toDouble());
	}

	//Clean up
	while(apSegments->size() > 0){
		scene->removeItem(apSegments->back());
		delete apSegments->back();
		apSegments->pop_back();
	}

	delete apAxes;

	scene->clear();

	for(int i=0; i < chords.size(); i++){
		//Find max height
		if(chords.at(i).toFloat()*pitchPos.at(i).toDouble() > yMax)
			yMax = chords.at(i).toFloat()*pitchPos.at(i).toDouble();

		//find min height
		if(-chords.at(i).toFloat()*(1-pitchPos.at(i).toDouble()) < yMin)
			yMin = -chords.at(i).toFloat()*(1-pitchPos.at(i).toDouble());

		//Accumulate max width
		xRange += lengths.at(i).toFloat();
	}
	yRange = yMax - yMin;

	xScale = ((float)apSceneSize->width()-40)/xRange;
	yScale = ((float)apSceneSize->height()-40)/yRange;

	//initialize
	apAxes = new AxesItem(xRange, 0, yMax, yMin, xScale, yScale, this);
	scene->addItem(apAxes);
	apAxes->setPos(xOffset,apSceneSize->height()/2 + yScale*(yMax-(yMax-yMin)/2) );

	QVector<QPointF> elasticPoints;
	QVector<QPointF> aeroPoints;
	QVector<QPointF> massPoints;

	float sumLength=0;
	for(int i=0; i < chords.size(); i++){
		// Add segments
		QVector<QPointF> points;
		//Top-left
		QPointF tl(0.0f, -yScale*chords.at(i).toDouble()*pitchPos.at(i).toDouble());
		//Bottom-left
		QPointF bl(0.0f, yScale*chords.at(i).toDouble()*(1-pitchPos.at(i).toDouble()));
		//Bottom-right
		QPointF br( xScale*lengths.at(i).toDouble(), yScale*chords.at(i).toDouble()*(1-pitchPos.at(i).toDouble()));
		//Top-Right
		QPointF tr( xScale*lengths.at(i).toDouble(), -yScale*chords.at(i).toDouble()*pitchPos.at(i).toDouble());

		points.push_back(tl);
		points.push_back(bl);
		points.push_back(br);
		points.push_back(tr);

		apSegments->push_back(new QuadItem(points, this));
		scene->addItem(apSegments->back());

		(*apSegments->back()).setPos( xOffset + xScale*sumLength, apSceneSize->height()/2 + yScale*(yMax-(yMax-yMin)/2));

		// Add lines on axes
		apAxes->addTickX( xScale*sumLength );
		apAxes->addTickY( yScale*(yMax-(yMax-yMin)/2) );

		//Add polylines
		elasticPoints.push_back(QPointF(xScale*(sumLength + lengths.at(i).toDouble()/2.0f),
				yScale*(elasticPos.at(i).toDouble()*chords.at(i).toDouble() - pitchPos.at(i).toDouble()*chords.at(i).toDouble() )));
		aeroPoints.push_back(QPointF(xScale*(sumLength + lengths.at(i).toDouble()/2.0f),
				yScale*(aeroPos.at(i).toDouble()*chords.at(i).toDouble()  - pitchPos.at(i).toDouble()*chords.at(i).toDouble() )));
		massPoints.push_back(QPointF(xScale*(sumLength + lengths.at(i).toDouble()/2.0f),
				yScale*((elasticPos.at(i).toDouble()+ qCos(relativeRotations.at(i).toDouble()*3.14/180)*massPosX.at(i).toDouble()
						- qSin(relativeRotations.at(i).toDouble()*3.14/180)*massPosY.at(i).toDouble())*chords.at(i).toDouble()
						- pitchPos.at(i).toDouble()*chords.at(i).toDouble() )));

		sumLength += lengths.at(i).toFloat();
	}
	PolyLineItem* apElasticPosGraph = new PolyLineItem(elasticPoints,Qt::red,this);
	PolyLineItem* apAeroPosGraph = new PolyLineItem(aeroPoints,Qt::blue,this);
	PolyLineItem* apMassPosGraph = new PolyLineItem(massPoints,Qt::darkGreen,this);

	scene->addItem(apAeroPosGraph);
	scene->addItem(apElasticPosGraph);
	scene->addItem(apMassPosGraph);

	apElasticPosGraph->setPos(xOffset, apSceneSize->height()/2 + yScale*(yMax-(yMax-yMin)/2));
	apAeroPosGraph->setPos(xOffset, apSceneSize->height()/2  + yScale*(yMax-(yMax-yMin)/2));
	apMassPosGraph->setPos(xOffset, apSceneSize->height()/2  + yScale*(yMax-(yMax-yMin)/2));

	if(aSegment>=0 && aSegment < apSegments->size()){
		apSegments->at(aSegment)->select();
	}
}

void BladeView::setSegment(const QModelIndex& selected, const QModelIndex&){
	for(QVector<QuadItem*>::iterator segIt = apSegments->begin(); segIt != apSegments->end(); ++segIt){
		(*segIt)->deselect();
	}

	if( (selected.column() >= 0) && (selected.column() < apSegments->size()) && apBlade)
		apSegments->at(selected.column())->select();

	aSegment = selected.column();

	scene->update();
}
