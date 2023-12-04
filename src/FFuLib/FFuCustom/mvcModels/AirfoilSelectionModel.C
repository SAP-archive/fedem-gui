/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * AirfoilSelectionModel.C
 *
 *  Created on: Jul 11, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/mvcModels/AirfoilSelectionModel.H"
#include "FFuLib/FFuCustom/components/DataNode.H"
#include "FFuLib/Icons/padLock.xpm"

#include <QPixmap>
#include <QIcon>
#include <QDir>


AirfoilSelectionModel::AirfoilSelectionModel(QObject *parent) : QAbstractItemModel(parent)
{
	QVector<QVariant> rootData;
	rootData.push_back(QVariant("Airfoils"));
	rootNode = new DataNode(rootData);
}


AirfoilSelectionModel::~AirfoilSelectionModel() {
	delete rootNode;
}

QModelIndex AirfoilSelectionModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    DataNode *parentNode = getNode(parent);

	DataNode *subNode = parentNode->subNode(row);
	if (subNode)
        return createIndex(row, column, subNode);
    else
        return QModelIndex();
}

QModelIndex AirfoilSelectionModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DataNode *subNode = static_cast<DataNode*>(index.internalPointer());
	DataNode *parentNode = subNode->getParentNode();

	if (parentNode == rootNode)
        return QModelIndex();

	return createIndex(parentNode->subNodeNumber(), 0, parentNode);
}

bool AirfoilSelectionModel::insertColumns(int position, int columns, const QModelIndex &parent)
 {
     bool success;

     beginInsertColumns(parent, position, position + columns - 1);
     success = rootNode->addColumns(position, columns);
     endInsertColumns();

     return success;
 }

bool AirfoilSelectionModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	DataNode *parentNode = getNode(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
	success = parentNode->addSubNodes(position, rows, rootNode->columnCount());
    endInsertRows();

    return success;
}

bool AirfoilSelectionModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootNode->removeColumns(position, columns);
    endRemoveColumns();

    if (rootNode->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool AirfoilSelectionModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    DataNode *parentNode = getNode(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
	success = parentNode->removeSubNodes(position, rows);
    endRemoveRows();

    return success;
}

int AirfoilSelectionModel::rowCount(const QModelIndex &parent) const
{
    DataNode *parentNode = getNode(parent);

	return parentNode->subNodeCount();
}

int AirfoilSelectionModel::columnCount(const QModelIndex&) const
{
	return  rootNode->columnCount();
}

QVariant AirfoilSelectionModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (role == Qt::DisplayRole)
    return getNode(index)->getData(index.column());

  if (role == Qt::DecorationRole && index.parent() == this->index(0,0,QModelIndex()))
    if (static_cast<DataNode*>(index.parent().internalPointer())->getData(1).toBool())
      return QIcon(QPixmap(padLock_xpm));

  return QVariant();
}

bool AirfoilSelectionModel::setData(const QModelIndex &index, const QVariant &value,
                        int role)
{
    if (role == Qt::EditRole){
		DataNode *node = getNode(index);
		bool result = node->setData(index.column(), value);

		if (result)
			emit dataChanged(index, index);

		return result;
    }

    return false;
}

Qt::ItemFlags AirfoilSelectionModel::flags(const QModelIndex &index) const
{
  return index.isValid() ? Qt::ItemIsEnabled | Qt::ItemIsSelectable : Qt::NoItemFlags;
}

QVariant AirfoilSelectionModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootNode->getData(section);

    return QVariant();
}

DataNode *AirfoilSelectionModel::getNode(const QModelIndex &index) const
 {
     if (index.isValid()) {
    	 DataNode *item = static_cast<DataNode*>(index.internalPointer());
         if (item) return item;
     }
     return rootNode;
 }


void AirfoilSelectionModel::addDirectory(int position, QString path, bool readOnly, const QModelIndex &parent) {
	if (path.size()) {

		//Check if directory is already included
		for(int child = 0; child < rootNode->subNodeCount(); child++){
			if(rootNode->subNode(child)->getData(0) == path)
				return;
		}

		insertRows(position,1,parent);
		setData(index(position, 0, parent), path + QDir::separator(), Qt::EditRole);
		static_cast<DataNode*>(index(position,0,parent).internalPointer())->addColumns(1,1);
		setData(index(position, 1, parent), readOnly, Qt::EditRole);
		// Find all airfoils
		QDir airfoils(path, "*.dat", QDir::Time | QDir::IgnoreCase, QDir::Files);
		if (airfoils.exists()) {
			// For each airfoil in directory
			for (unsigned int pos = 0; pos < airfoils.count(); pos++) {
				insertRows(pos,1,index(position,0,parent));
				setData(index(pos,0,index(position,0,parent)), airfoils[pos], Qt::EditRole);
			}
		}
	}
}

void AirfoilSelectionModel::removeDirectory(int position, const QModelIndex &parent){
	removeRows(position, 1, parent);
}

void AirfoilSelectionModel::addItem( QString parentName, QString childName){
	if(parentName.size() && childName.size()){
		//Check if "path" already exist
		for(int i=0; i < rootNode->subNodeCount(); i++){
			if(rootNode->subNode(i)->getData(0) == parentName){
				//RemovePrevious child
				insertRows(0, 1, index(i, 0));
				setData(index(0, 0, index(i, 0)), childName, Qt::EditRole);

				return;
			}
		}
		// Path does not exist. create it
		insertRows(0,1);
		setData(index(0,0), parentName, Qt::EditRole);
		//Insert child
		insertRows(0, 1, index(0, 0));
		setData(index(0, 0, index(0, 0)), childName, Qt::EditRole);
	}
}

void AirfoilSelectionModel::removeItem( QString parentName, QString childName){
	if(parentName.size() && childName.size()){
		//Check if "path" exist
		for(int i=0; i < rootNode->subNodeCount(); i++){
			if(rootNode->subNode(i)->getData(0) == parentName){
				DataNode* parent = rootNode->subNode(i);
				//Find item
				for(int j=0; j < parent->subNodeCount(); j++){
					if(parent->subNode(j)->getData(0) == childName ){
						//RemovePrevious child
						removeRows(j, 1, index(i, 0));

						//if parent item is now empty, remove it
						if(!parent->subNodeCount()){
							removeRows( i, 1);
						}

						return;
					}
				}
			}
		}
	}
	return;
}


void AirfoilSelectionModel::clearModel(){
	removeRows(0, rootNode->subNodeCount());
}

QStringList AirfoilSelectionModel::getDirectoryList(){
	QStringList dirs;
	for (int i = 0; i< rootNode->subNodeCount(); i++){
		dirs << rootNode->subNode(i)->getData(0).toString();
	}

	return dirs;
}


void AirfoilSelectionModel::getAllItems(std::vector<std::string> &airfoils){

	airfoils.clear();
	for (int i = 0; i < rootNode->subNodeCount(); i++) {
		DataNode* parent = rootNode->subNode(i);
		for (int j = 0; j < parent->subNodeCount(); j++) {
			airfoils.push_back(parent->getData(0).toString().toStdString() + parent->subNode(j)->getData(0).toString().toStdString());
		}
	}
}


bool AirfoilSelectionModel::itemIsReadOnly(bool& readOnly, const QString itemPath){
	if(itemExist(itemPath)){
		readOnly = static_cast<DataNode*>(getItemIndex(itemPath).parent().internalPointer())->getData(1).toBool();
		return true;
	}
	return false;
}

bool AirfoilSelectionModel::itemExist(QString itemPath)
{
	if( index(0,0).isValid() ){
		for(int i = 0; i < static_cast<DataNode*>(index(0,0).internalPointer())->getParentNode()->subNodeCount(); i++){
			for (int j = 0; j < static_cast<DataNode*>(index(i, 0).internalPointer())->subNodeCount(); j++){
				QString pathName = static_cast<DataNode*>(index(i,0).internalPointer())->getData(0).toString() +
					static_cast<DataNode*>(index(i,0).internalPointer())->subNode(j)->getData(0).toString();
				if(itemPath == pathName){
					return true;
				}
			}
		}
	}
	return false;

}

QModelIndex AirfoilSelectionModel::getItemIndex(QString itemPath)
{
		if( index(0,0).isValid() ){
		for(int i = 0; i < static_cast<DataNode*>(index(0,0).internalPointer())->getParentNode()->subNodeCount(); i++){
			for (int j = 0; j < static_cast<DataNode*>(index(i, 0).internalPointer())->subNodeCount(); j++){
				QString pathName = static_cast<DataNode*>(index(i,0).internalPointer())->getData(0).toString() +
					static_cast<DataNode*>(index(i,0).internalPointer())->subNode(j)->getData(0).toString();
				if(itemPath == pathName){
					return this->index(j,0,index(i,0));
				}
			}
		}
	}
	return QModelIndex();
}
