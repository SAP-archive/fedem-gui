/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * AirfoilView.C
 *
 *  Created on: Apr 18, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/components/renderers/AirfoilView.H"

AirfoilView::AirfoilView(QWidget* parent) :
		QGraphicsView(parent) {
	apSceneSize = new QSize(145,145);
	scene = new QGraphicsScene(this);
	scene->setItemIndexMethod(QGraphicsScene::NoIndex);
	scene->setSceneRect(QRectF(QPointF(0,0), *apSceneSize));
	setScene(scene);
	setCacheMode(CacheBackground);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setRenderHint(QPainter::Antialiasing);
	setTransformationAnchor(AnchorUnderMouse);
	scale(qreal(1.0), qreal(1.0));
	setWindowTitle(tr("Airfoil"));

	apAirfoil = new AirfoilItem(this,0,0.5f);
	scene->addItem(apAirfoil);
	apAirfoil->setPos(apSceneSize->width()/2 -30, apSceneSize->height()/2);

	apWindArrow = new WindArrowItem(this);
	scene->addItem(apWindArrow);
	apWindArrow->setPos(3*apSceneSize->width()/4,apSceneSize->height()/2);

	aSegment = 0;
	aTab = 0;
}

AirfoilView::~AirfoilView(){
	delete apAirfoil;
	delete apWindArrow;
	delete apSceneSize;
}

void AirfoilView::setBlade(Blade* pBlade){
	if(pBlade != apBlade)
		aSegment = 0;

	apBlade = pBlade;

	initializeFigure();
}

void AirfoilView::setSegment(const QModelIndex& selected, const QModelIndex&){
	if(selected.column()>=0 && (selected.column() < apBlade->GetAerodynamicData()->size()))
		aSegment = selected.column();
	else
		aSegment = 0;

	initializeFigure();
}

void AirfoilView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QRectF sceneRect = this->sceneRect();

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Segment profile"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(8);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect, message);
}

void AirfoilView::initializeFigure(){
	scene->removeItem(apAirfoil);
	delete apAirfoil;
	scene->removeItem(apWindArrow);
	delete apWindArrow;

	// Airfoil
	if(apBlade->GetAerodynamicData()->size()>aSegment && apBlade->GetStructureData()->size()>aSegment){
		if(apBlade->GetAerodynamicData()->at(aSegment)->size() > 7){
			QVector<QVariant>* pAeroData = apBlade->GetAerodynamicData()->at(aSegment);
			QVector<QVariant>* pStiffData = apBlade->GetStructureData()->at(aSegment);
/* kmo 26.06.2018: Removed unused variable.
			float scale = 1000;
			if(pAeroData->at(1).toFloat() > 0)  //Segment length >0
				scale = 1/pAeroData->at(1).toFloat();
*/
			apAirfoil = new AirfoilItem(this, aTab,
						    pAeroData->at(7).toDouble(),
						    pAeroData->at(5).toFloat(), 0.0f,
						    pAeroData->at(3).toFloat(), pAeroData->at(4).toFloat(),
						    pStiffData->at(0).toFloat(), pStiffData->at(1).toFloat(),
						    pStiffData->at(2).toFloat(),
						    pStiffData->at(3).toFloat(), pStiffData->at(4).toFloat());
			apAirfoil->setRotation(90);
			apAirfoil->setTransformOriginPoint(0,0);
			apAirfoil->setRotation(pAeroData->at(2).toDouble());
			scene->addItem(apAirfoil);
			apAirfoil->setPos(apSceneSize->width()/2  - 20, apSceneSize->height()/2  + 10);
		}
	}
	else{
		apAirfoil = new AirfoilItem(this);
		apAirfoil->setRotation(90);
		apAirfoil->setTransformOriginPoint(0,0);
		scene->addItem(apAirfoil);
		apAirfoil->setPos(apSceneSize->width()/2  - 20, apSceneSize->height()/2  + 10);
	}
	// Wind-arrow
	apWindArrow = new WindArrowItem(this);
	scene->addItem(apWindArrow);
	apWindArrow->setPos(3*apSceneSize->width()/4+25, apSceneSize->height()/2 + 10);
}

void AirfoilView::setTab(int tab){
	aTab = tab;
}
