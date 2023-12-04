// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#include "FFuLib/FFuCustom/components/Blade.H"


Blade::Blade( std::string name, std::string info, std::string path ){
	aName = name;
	aInfo = info;
	aPath = path;
	apDesign = 0;

	apAerodynamicData = new QVector<QVector<QVariant>*>();
	apStructureData = new QVector<QVector<QVariant>*>();

	touched = false;
	isTemplate = false;
	isInUse = false;

	aBendingStiffness = true;
	aShearStiffness = true;
	aTorsionStiffness = true;
	aAxialStiffness = true;
}

Blade::~Blade(){
	apAerodynamicData->clear();
	delete apAerodynamicData;

	apStructureData->clear();
	delete apStructureData;
}

std::string Blade::GetInfo(){
	if(isInUse){
		return "[in model]"+aInfo;
	}

	return aInfo;
}

bool Blade::SetAerodynamicData(QVector<QVector<QVariant>*>* pAeroData){
	apAerodynamicData->clear();
	delete apAerodynamicData;
	apAerodynamicData = pAeroData;

	return true;
}

bool Blade::SetStructureData(QVector<QVector<QVariant>*>* pStiffnessData){
	apStructureData->clear();
	delete apStructureData;
	apStructureData = pStiffnessData;

	return true;
}

bool Blade::SetName(std::string name){
	if(name == "")
		return false;

	aName = name;
	return true;
}

void Blade::Touch(){
	touched = true;
}

void Blade::UnTouch(){
	touched = false;
}

void Blade::SetIsTemplate(bool exists){
	isTemplate = exists;
}

void Blade::SetFileExists(bool exists){
	fileExists = exists;
}

void Blade::SetIsInUse(bool inUse){
	isInUse = inUse;
}

void Blade::SetDesign(FmBladeDesign* pDesign){
	apDesign = pDesign;
}

void Blade::SetInfo(std::string info){
	aInfo = info;
}

void Blade::SetPath(std::string path){
	aPath = path;
}


void Blade::SetBendingStiffnessState(bool state){
	aBendingStiffness = state;
}

void Blade::SetAxialStiffnessState(bool state){
	aAxialStiffness = state;
}

void Blade::SetShearStiffnessState(bool state){
	aShearStiffness = state;
}

void Blade::SetTorsionStiffnessState(bool state){
	aTorsionStiffness = state;
}


