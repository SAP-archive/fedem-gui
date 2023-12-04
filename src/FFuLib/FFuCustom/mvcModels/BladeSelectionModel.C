/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * BladeSelectionModel.C
 *
 *  Created on: Jul 11, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/mvcModels/BladeSelectionModel.H"
#include "FFuLib/FFuCustom/components/DataNode.H"
#include "FFuLib/Icons/padLock.xpm"

#include <QPixmap>
#include <QIcon>
#include <QDir>


BladeSelectionModel::BladeSelectionModel(QObject *parent) : QAbstractItemModel(parent)
{
	QVector<QVariant> rootData;
	rootData.push_back(QVariant("Blades"));
	rootNode = new DataNode(rootData);
}


BladeSelectionModel::~BladeSelectionModel() {
	delete rootNode;
}

QModelIndex BladeSelectionModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
        return QModelIndex();

    DataNode *parentItem = getItem(parent);

    DataNode *subNode = parentItem->subNode(row);
    if (subNode)
        return createIndex(row, column, subNode);
    else
        return QModelIndex();
}

QModelIndex BladeSelectionModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    DataNode *subNode = static_cast<DataNode*>(index.internalPointer());
    DataNode *parentItem = subNode->getParentNode();

    if (parentItem == rootNode)
        return QModelIndex();

    return createIndex(parentItem->subNodeNumber(), 0, parentItem);
}

bool BladeSelectionModel::insertColumns(int position, int columns, const QModelIndex &parent)
 {
     bool success;

     beginInsertColumns(parent, position, position + columns - 1);
     success = rootNode->addColumns(position, columns);
     endInsertColumns();

     return success;
 }

bool BladeSelectionModel::insertRows(int position, int rows, const QModelIndex &parent)
{
	DataNode *parentItem = getItem(parent);
    bool success;

    beginInsertRows(parent, position, position + rows - 1);
    success = parentItem->addSubNodes(position, rows, rootNode->columnCount());
    endInsertRows();

    return success;
}

bool BladeSelectionModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    bool success;

    beginRemoveColumns(parent, position, position + columns - 1);
    success = rootNode->removeColumns(position, columns);
    endRemoveColumns();

    if (rootNode->columnCount() == 0)
        removeRows(0, rowCount());

    return success;
}

bool BladeSelectionModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    DataNode *parentNode = getItem(parent);
    bool success = true;

    beginRemoveRows(parent, position, position + rows - 1);
	success = parentNode->removeSubNodes(position, rows);
    endRemoveRows();

    return success;
}

int BladeSelectionModel::rowCount(const QModelIndex &parent) const
{
    DataNode *parentNode = getItem(parent);

	return parentNode->subNodeCount();
}

int BladeSelectionModel::columnCount(const QModelIndex&) const
{
  return rootNode->columnCount();
}

QVariant BladeSelectionModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
    return QVariant();

  if (role == Qt::DisplayRole)
    return getItem(index)->getData(index.column());

  if (role == Qt::DecorationRole && getItem(index.parent()) != rootNode)
    if (static_cast<DataNode*>(index.parent().internalPointer())->getData(1).toBool())
      return QIcon(QPixmap(padLock_xpm));

  return QVariant();
}

bool BladeSelectionModel::setData(const QModelIndex &index, const QVariant &value,
                        int role)
{
    if (role == Qt::EditRole){
		DataNode *node = getItem(index);
		bool result = node->setData(index.column(), value);

		if (result)
			emit dataChanged(index, index);

		return result;
    }

    return false;
}

Qt::ItemFlags BladeSelectionModel::flags(const QModelIndex &index) const
{
  return index.isValid() ? Qt::ItemIsEnabled | Qt::ItemIsSelectable : Qt::NoItemFlags;
}

QVariant BladeSelectionModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootNode->getData(section);

    return QVariant();
}

DataNode *BladeSelectionModel::getItem(const QModelIndex &index) const
 {
     if (index.isValid()) {
    	 DataNode *node = static_cast<DataNode*>(index.internalPointer());
		 if (node) return node;
     }
     return rootNode;
 }

bool BladeSelectionModel::addDirectory(int position, QString path, bool readOnly, const QModelIndex &parent) {
	path = QDir::toNativeSeparators(path);
	if (path.size()) {
		//Check if directory is already included
		for(int child = 0; child < rootNode->subNodeCount(); child++){
			if(rootNode->subNode(child)->getData(0).toString() == QString(path+QDir::separator())){
				return false;
			}
		}

		// Find all blades
		QDir blades(path, "*.fmm", QDir::Time | QDir::IgnoreCase, QDir::Files);
		if (blades.exists() && blades.count() > 0) {
			insertRows(position,1,parent);
			setData(index(position, 0, parent), path + QDir::separator(), Qt::EditRole);
			static_cast<DataNode*>(index(position,0,parent).internalPointer())->addColumns(1,1);
			setData(index(position, 1, parent), readOnly, Qt::EditRole);

			// For each blade in directory
			for (unsigned int pos = 0; pos < blades.count(); pos++) {
					insertRows(pos,1,index(position,0,parent));
					setData(index(pos,0,index(position,0,parent)), blades[pos], Qt::EditRole);
			}
			return true;
		}
	}
	return false;
}

void BladeSelectionModel::removeDirectory(int position, const QModelIndex &parent){
	removeRows(position, 1, parent);
}

void BladeSelectionModel::addUnsavedItem( QString parentName, QString childName){
	if(parentName.size() && childName.size()){
		//Check if "path" already exist
		for(int i=0; i < rootNode->subNodeCount(); i++){
			if(rootNode->subNode(i)->getData(0) == parentName){
				//RemovePrevious child
				removeRows(0, 1, index(i,0));
				insertRows(0, 1, index(i, 0));
				setData(index(0, 0, index(i, 0)), childName, Qt::EditRole);

				return;
			}
		}
		// Path does not exist. create it
		insertRows(rootNode->subNodeCount(),1);
		setData(index(rootNode->subNodeCount() - 1, 0), parentName, Qt::EditRole);
		//Insert child
		insertRows(0, 1, index(rootNode->subNodeCount() - 1, 0));
		setData(index(0, 0, index(rootNode->subNodeCount() - 1, 0)), childName, Qt::EditRole);
	}
}

void BladeSelectionModel::addItem( QString parentName, QString childName){
	if(parentName.size() && childName.size()){
		//Check if "path" already exist
		for (int i = 0; i < rootNode->subNodeCount(); i++){
			if(rootNode->subNode(i)->getData(0) == parentName){
				//RemovePrevious child
				insertRows(0, 1, index(i, 0));
				setData(index(0, 0, index(i, 0)), childName, Qt::EditRole);
				return;
			}
		}
		// Path does not exist. create it
		addDirectory(0,parentName);
		//Insert child
		DataNode* parent = rootNode->subNode(0); //Get newly created path-item
		//Check if directory already has the new item, if not, create it
		for(int i=0; i < parent->subNodeCount(); i++){
			if(parent->subNode(i)->getData(0) == childName){
				return;
			}
		}
		insertRows(0, 1, index(0, 0));
		setData(index(0, 0, index(0, 0)), childName, Qt::EditRole);
	}
}

bool BladeSelectionModel::removeItem( QString parentName, QString childName){
	if(parentName.size() && childName.size()){
		//Check if "path" exist
		for(int i=0; i < rootNode->subNodeCount(); i++){
			if(rootNode->subNode(i)->getData(0) == parentName){
				DataNode* parent = rootNode->subNode(i);
				//Find item
				for (int j = 0; j < parent->subNodeCount(); j++){
					if(parent->subNode(j)->getData(0) == childName ){
						//RemovePrevious child
						removeRows(j, 1, index(i, 0));

						//if parent item is now empty, remove it
						if(!parent->subNodeCount()){
							removeRows( i, 1);
						}
						return true;
					}
				}
			}
		}
	}
	return false;
}


void BladeSelectionModel::clearModel(){
	removeRows(0, rootNode->subNodeCount());
}



void BladeSelectionModel::getAllItems(std::vector<std::string> &blades){
	blades.clear();
	for (int i = 0; i < rootNode->subNodeCount(); i++) {
		DataNode* parent = rootNode->subNode(i);
		for (int j = 0; j < parent->subNodeCount(); j++) {
			blades.push_back(parent->getData(0).toString().toStdString() + parent->subNode(j)->getData(0).toString().toStdString());
		}
	}
}


bool BladeSelectionModel::itemIsReadOnly(bool& readOnly, const QString itemPath)
{
	if(itemExist(itemPath)){
		readOnly = static_cast<DataNode*>(getItemIndex(itemPath).parent().internalPointer())->getData(1).toBool();
		return true;
	}

	return false;
}

bool BladeSelectionModel::itemExist(QString itemPath)
{
	if( index(0,0).isValid() ){
		for (int i = 0; i < static_cast<DataNode*>(index(0, 0).internalPointer())->getParentNode()->subNodeCount(); i++){
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

QModelIndex BladeSelectionModel::getItemIndex(QString itemPath)
{
		if( index(0,0).isValid() ){
			for (int i = 0; i < static_cast<DataNode*>(index(0, 0).internalPointer())->getParentNode()->subNodeCount(); i++){
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
