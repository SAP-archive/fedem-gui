/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * Airfoil.H
 *
 *  Created on: May 2, 2012
 *      Author: runarhr
 */

#ifndef AIRFOIL_H
#define AIRFOIL_H

#include <QVector>
#include <QDir>
#include <QVariant>
#include <QString>


class Airfoil {
public:
	Airfoil();
	virtual ~Airfoil();

	QString getNumTables(){ if(aNumTables.size()){return aNumTables;}else{return "0";}}
	QString getTableId(){ if(aTableId.size()){return aTableId;}else{return "0";}}
	QString getStallAngle() { if(aStallAngle.size()){return aStallAngle;}else{return "0";}}
	QString getCnAngle(){ if(aCnAngle.size()){return aCnAngle;}else{return "0";}}
	QString getCnSlope(){if(aCnSlope.size()){return aCnSlope;}else{return "0";}}
	QString getCnExtrapol(){ if(aCnExtrapol.size()){return aCnExtrapol;}else{return "0";}}
	QString getCnStall(){ if(aCnStall.size()){return aCnStall;}else{return "0";}}
	QString getAttack(){ if(aAttack.size()){return aAttack;}else{return "0";}}
	QString getMinCD(){ if(aMinCD.size()){return aMinCD;}else{return "0";}}

	bool Touched() { return touched; }
	bool IsTemplate() { return isTemplate; }
	bool FileExists() { return fileExists; }

	QVector<QVector<QVariant>*>* getTableData(){return apTableData;}

	QString getFilename(){return aFilename;}
	QString getName(){ return aFilename.split(QDir::separator()).last(); }

	void setNumTables(QString numTables){ aNumTables = numTables; }
	void setTableId(QString tableId){ aTableId = tableId; }
	void setStallAngle(QString stallAngle){ aStallAngle = stallAngle; }
	void setCnAngle(QString cnAngle){ aCnAngle = cnAngle; }
	void setCnSlope(QString cnSlope){ aCnSlope = cnSlope; }
	void setCnExtrapol(QString cnExtrapol){ aCnExtrapol = cnExtrapol; }
	void setCnStall(QString cnStall){ aCnStall = cnStall; }
	void setAttack(QString attack){ aAttack = attack; }
	void setMinCD(QString minCD){ aMinCD = minCD; }

	void setTableData(QVector<QVector<QVariant>*>* pTableData){ apTableData = pTableData; }

	void setFilename(QString name){aFilename = name; }

	void Touch();
	void UnTouch();
	void SetIsTemplate(bool exists);
	void SetFileExists(bool exists);

private:
	QString aFilename;

	QString aNumTables;
	QString aTableId;
	QString aStallAngle;
	QString aCnAngle;
	QString aCnSlope;
	QString aCnExtrapol;
	QString aCnStall;
	QString aAttack;
	QString aMinCD;

	QVector<QVector<QVariant>*>* apTableData;

	bool touched;
	bool isTemplate;
	bool fileExists;
};

#endif /* AIRFOIL_H */
