/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * AirfoilSelectionModel.H
 *
 *  Created on: Jul 11, 2012
 *      Author: runarhr
 */

#ifndef AirfoilSelectionModel_H
#define AirfoilSelectionModel_H

#include <QAbstractItemModel>
#include "FFaLib/FFaPatterns/FFaSingelton.H"
#include <vector>
#include <string>

class DataNode;


class AirfoilSelectionModel : public QAbstractItemModel, public FFaSingelton<AirfoilSelectionModel>
{
	Q_OBJECT

public:
	AirfoilSelectionModel(QObject* parent = NULL);
	~AirfoilSelectionModel();

	// **** Functions inherited from QAbstractItemModel ****
	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,
			    int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column,
			  const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	 bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	 bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex());
	 bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex());
	 bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
	 bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());

	// **** Functions to manipulate the model *****
	// Adds a library directory, and find all airfoils in the directory and adds them as children
	void addDirectory(int position, QString path, bool readOnly=false, const QModelIndex &parent = QModelIndex());
	// removes a directory and all the airfoils it has as children
	void removeDirectory(int position, const QModelIndex &parent = QModelIndex());

	//Adds or removes a new item/airfoil. parentName is the name of the parent in the tree-model. Typically the folder-path
	void addItem( QString parentName, QString childName);
	void removeItem( QString parentName, QString childName);

	//Removes all entries on all levels
	void clearModel();

	// **** Functions for querying the model ****
	void getAllItems(std::vector<std::string>& airfoils);
	QStringList getDirectoryList();
	//Check if an item is part of a directory flagged as readOnly
	bool itemIsReadOnly(bool& readOnly, const QString itemPath);
	//Check if itemPath exist anywhere in the model.
	bool itemExist(QString itemPath);
	//Returns the QModelIndex of itemPath if the item can be found in the model, if not, it returns QModelIndex()
	QModelIndex getItemIndex(QString itemPath);

private:
	DataNode *getNode(const QModelIndex &index) const;
	DataNode *rootNode;
};

#endif
