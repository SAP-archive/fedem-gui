/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * DataNode.H
 *
 *  Created on: Jul 11, 2012
 *      Author: runarhr
 */

#ifndef DataNode_H
#define DataNode_H

#include <QList>
#include <QVector>
#include <QVariant>


class DataNode
{
  QList<DataNode*>  subNodes;
  QVector<QVariant> nodeData;
  DataNode*         parentNode;

public:
  DataNode(const QVector<QVariant>& data, DataNode* parent = 0);
  ~DataNode();

  //Get the parent node that this node is connected to
  DataNode* getParentNode() const { return parentNode; }

  //Get the sub-node of this node, with sub-node index "number"
  DataNode*subNode(int number);

  //Add sub-nodes to this node.
  bool addSubNodes(int pos, int count, int cols);

  //Get the number of sub-nodes of this node
  int subNodeCount() const { return subNodes.length(); }

  //Get the sub-node number this node has in its parent
  int subNodeNumber() const;

  //remove "count" number of sub-nodes from this node, from the index "pos"
  bool removeSubNodes(int pos, int count);

  QVariant getData(int col) const;
  bool addColumns(int pos, int cols);
  int columnCount() const { return nodeData.count(); }
  bool removeColumns(int pos, int cols);
  bool setData(int col, const QVariant& value);
};

#endif /* DataNode_H */
