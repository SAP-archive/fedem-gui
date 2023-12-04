// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef BLADE_DRAWER_H
#define BLADE_DRAWER_H

#include <QWidget>
#include <QHBoxLayout>

#include "FFuLib/FFuCustom/components/Blade.H"
#include "FFuLib/FFuCustom/components/renderers/BladeView.H"
#include "FFuLib/FFuCustom/components/renderers/AirfoilView.H"

class BladeDrawer : public QWidget {
	Q_OBJECT

public:
	BladeDrawer( QWidget *parent=0 );
	~BladeDrawer();

	void setBlade( Blade* aBlade );
	Blade* getBlade(){ return apBlade; }

	AirfoilView* apAirfoilView;
	BladeView* apBladeView;
private:
	Blade* apBlade;

	QHBoxLayout* apMainLayout;

};

#endif
