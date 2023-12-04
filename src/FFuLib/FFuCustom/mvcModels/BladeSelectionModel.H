/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * BladeSelectionModel.H
 *
 *  Created on: Jul 11, 2012
 *      Author: runarhr
 */

#ifndef BladeSelectionModel_H
#define BladeSelectionModel_H

#include <QAbstractItemModel>
#include "FFaLib/FFaPatterns/FFaSingelton.H"
#include <vector>
#include <string>

class DataNode;


//QAbstractItemModel for global management of the blades used in BladeSelector widgets.
//Keeps a tree-model for representing library-folders and the blades contained in these.

class BladeSelectionModel : public QAbstractItemModel, public FFaSingelton<BladeSelectionModel>
{
	Q_OBJECT

public:
	BladeSelectionModel(QObject* parent = NULL);
	~BladeSelectionModel();

	//****Functions inherited from QAbstractItemModel****
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

	//****Functions to manipulate the model*****
	//Adds a library directory, and find all blades in the directory and adds them as children
	bool addDirectory(int position, QString path, bool readOnly=false, const QModelIndex &parent = QModelIndex());
	//removes a directory and all the blades it has as children
	void removeDirectory(int position, const QModelIndex &parent = QModelIndex());
	//Used to add unsaved blades
	void addUnsavedItem(QString parentName, QString childName);

	//Adds or removes a new item/blade. parentName is the name of the parent in the tree-model. Typically the folder-path
	void addItem( QString parentName, QString childName);
	bool removeItem( QString parentName, QString childName);

	//Removes all entries on all levels
	void clearModel();

	//*****Functions for querying the model****
	//Get all leaves of the the tree-model
	void getAllItems(std::vector<std::string>& blades);
	//Check if an item is part of a directory flagged as readOnly
	bool itemIsReadOnly(bool& readOnly, const QString itemPath);
	//Check if itemPath exist anywhere in the model.
	bool itemExist(QString itemPath);
	//Returns the QModelIndex of itemPath if the item can be found in the model, if not, it returns QModelIndex()
	QModelIndex getItemIndex(QString itemPath);

private:
	DataNode *getItem(const QModelIndex &index) const;
	DataNode *rootNode;
};

#endif
