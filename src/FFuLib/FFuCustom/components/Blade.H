// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef BLADE_H
#define BLADE_H

#include <QVector>
#include <QVariant>
#include <string>

class FmBladeDesign;


class Blade
{
public:
	Blade(std::string name="", std::string info="", std::string path="");
	~Blade();

	std::string GetName() {return aName;}
	std::string GetInfo();
	std::string GetPath() {return aPath;}
	FmBladeDesign* GetDesign() { return apDesign;}

	QVector<QVector<QVariant>*>* GetAerodynamicData() {return apAerodynamicData; }
	QVector<QVector<QVariant>*>* GetStructureData() {return apStructureData; }

	bool BendingStiffness(){return aBendingStiffness;}
	bool TorsionStiffness(){return aTorsionStiffness;}
	bool AxialStiffness(){return aAxialStiffness;}
	bool ShearStiffness(){return aShearStiffness;}

	bool Touched() { return touched; }
	bool IsTemplate() { return isTemplate; }
	bool FileExists() { return fileExists; }
	bool InUse() { return isInUse; }

	bool SetName(std::string name);
	void SetInfo(std::string info);
	void SetPath(std::string path);
	void SetDesign(FmBladeDesign* pDesign);

	bool SetAerodynamicData(QVector<QVector<QVariant>*>* pAeroData);
	bool SetStructureData(QVector<QVector<QVariant>*>* pAeroData);

	void SetBendingStiffnessState(bool state);
	void SetTorsionStiffnessState(bool state);
	void SetAxialStiffnessState(bool state);
	void SetShearStiffnessState(bool state);

	void Touch();
	void UnTouch();
	void SetIsTemplate(bool exists);
	void SetFileExists(bool exists);
	void SetIsInUse(bool inUse);

private:
	std::string aName;
	std::string aInfo;
	std::string aPath;

	QVector<QVector<QVariant>*>* apAerodynamicData;
	QVector<QVector<QVariant>*>* apStructureData;

	FmBladeDesign* apDesign;

	bool aBendingStiffness;
	bool aTorsionStiffness;
	bool aAxialStiffness;
	bool aShearStiffness;

	bool touched;
	bool isTemplate;
	bool fileExists;
	bool isInUse;
};


#endif
