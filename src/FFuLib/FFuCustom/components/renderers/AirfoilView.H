/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * AirfoilView.H
 *
 *  Created on: Apr 18, 2012
 *      Author: runarhr
 */

#ifndef AIRFOIL_VIEW_H
#define AIRFOIL_VIEW_H

#include <QGraphicsView>
#include <QTableWidget>

#include "FFuLib/FFuCustom/components/renderers/graphicsItems/AirfoilItem.H"
#include "FFuLib/FFuCustom/components/renderers/graphicsItems/WindArrowItem.H"
#include "FFuLib/FFuCustom/components/Blade.H"

class AirfoilView : public QGraphicsView {
Q_OBJECT
public:
	AirfoilView(QWidget* parent=0);
	~AirfoilView();

	void setBlade(Blade* pBlade);

public slots:
	void setSegment(const QModelIndex & selected, const QModelIndex & deselected);
	void setTab(int tab);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect);

private:
	void initializeFigure();

	int aSegment;
	int aTab;
	Blade* apBlade;
	QSize* apSceneSize;
	QGraphicsScene *scene;

	AirfoilItem* apAirfoil;
	WindArrowItem* apWindArrow;
};

#endif /* AIRFOIL_VIEW_H */
