/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * BladeView.H
 *
 *  Created on: Apr 18, 2012
 *      Author: runarhr
 */

#ifndef BLADE_VIEW_H
#define BLADE_VIEW_H

#include <QGraphicsView>
#include <QTableWidget>
#include <QtCore/qmath.h>

#include "FFuLib/FFuCustom/components/renderers/graphicsItems/QuadItem.H"
#include "FFuLib/FFuCustom/components/renderers/graphicsItems/AxesItem.H"
#include "FFuLib/FFuCustom/components/renderers/graphicsItems/PolyLineItem.H"
#include "FFuLib/FFuCustom/components/Blade.H"

class BladeView : public QGraphicsView {
	Q_OBJECT

public:
	BladeView( QWidget* parent=0);
	~BladeView();

	void setBlade(Blade* pBlade);

protected:
	void drawBackground(QPainter *painter, const QRectF &rect);

public slots:
	void setSegment(const QModelIndex & selected, const QModelIndex & deselected);

private:
	void initializeSegments();

	QSize* apSceneSize;
	QGraphicsScene *scene;

	Blade* apBlade;

	// Graphics items
	QVector<QuadItem*>* apSegments;
	AxesItem* apAxes;

	int aSegment;
};

#endif /* BLADE_VIEW_H */
