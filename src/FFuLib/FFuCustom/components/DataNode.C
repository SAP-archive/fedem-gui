/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * DataNode.C
 *
 *  Created on: Jul 11, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/components/DataNode.H"


DataNode::DataNode(const QVector<QVariant>& data, DataNode* parent)
{
  parentNode = parent;
  nodeData = data;
}


DataNode::~DataNode()
{
  qDeleteAll(subNodes);
}


int DataNode::subNodeNumber() const
{
  if (parentNode != NULL)
    return parentNode->subNodes.indexOf(const_cast<DataNode*>(this));

  return 0;
}


DataNode* DataNode::subNode(int number)
{
  if (number < subNodes.length())
    return subNodes.value(number);

  return NULL;
}


bool DataNode::addSubNodes(int pos, int count, int cols)
{
  if (pos < 0 || pos > subNodes.size())
    return false;

  for (int r = 0; r < count; r++)
    subNodes.insert(pos, new DataNode(QVector<QVariant>(cols),this));

  return true;
}


bool DataNode::setData(int col, const QVariant& value)
{
  if (col < 0 || col >= nodeData.size())
    return false;

  nodeData[col] = value;
  return true;
}


bool DataNode::addColumns(int pos, int cols)
{
  if (pos < 0 || pos > nodeData.size())
    return false;

  for (int c = 0; c < cols; c++)
    nodeData.insert(pos,QVariant());

  for (int i = 0; i < subNodes.count(); i++)
    subNodes[i]->addColumns(pos, cols);

  return true;
}


QVariant DataNode::getData(int column) const
{
  if (column < nodeData.count())
    return nodeData.value(column);

  return (QVariant)0;
}


bool DataNode::removeSubNodes(int pos, int count)
{
  if (pos < 0 || pos+count > subNodes.size())
    return false;

  for (int r = 0; r < count; r++)
    delete subNodes.takeAt(pos);

  return true;
}


bool DataNode::removeColumns(int pos, int cols)
{
  if (pos < 0 || nodeData.count() < pos+cols)
    return false;

  for (int c = 0; c < cols; c++)
    nodeData.remove(pos);

  for (int i = 0; i < subNodes.count(); i++)
    subNodes[i]->removeColumns(pos,cols);

  return true;
}
