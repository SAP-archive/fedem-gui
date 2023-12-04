// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuCustom/components/BladeDrawer.H"


BladeDrawer::BladeDrawer( QWidget* parent) : QWidget(parent){
	apBlade = NULL;
	apMainLayout = new QHBoxLayout(this);
	setLayout(apMainLayout);

	apBladeView = new BladeView(this);
	apAirfoilView = new AirfoilView(this);

	apMainLayout->addWidget(apBladeView);
	apMainLayout->addWidget(apAirfoilView);

	apBladeView->setFixedHeight(160);
	apAirfoilView->setFixedSize(170,160);

	setFixedHeight(170);
	//setFixedWidth(900);

	setStyleSheet("border: 4px solid qradialgradient(cx:0.5, cy:0.5, radius: 1, fx:0.5, fy:0.5, stop:0 #fdd000, stop:1 #f77500); "
			"border-left: 0px solid; border-right: 0px solid; border-top: 0px solid");
	apAirfoilView->setStyleSheet("border-left: 2px solid qradialgradient(cx:0.5, cy:0.5, radius: 1, fx:0.5, fy:0.5, stop:0 #fdd000, stop:1 #f77500)");

	apMainLayout->setContentsMargins(0,0,0,0);
	this->setContentsMargins(0,0,0,0);
	apMainLayout->setSpacing(0);
}

BladeDrawer::~BladeDrawer(){
}

void BladeDrawer::setBlade( Blade* aBlade ){
	apBlade = aBlade;

	apBladeView->setBlade(apBlade);
	apAirfoilView->setBlade(apBlade);
}
