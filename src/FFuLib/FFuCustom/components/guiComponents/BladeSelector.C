/* SPDX-FileCopyrightText: 2023 SAP SE
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * This file is part of FEDEM - https://openfedem.org
 */
/*
 * BladeSelector.C
 *
 *  Created on: Jul 4, 2012
 *      Author: runarhr
 */

#include "FFuLib/FFuCustom/components/guiComponents/BladeSelector.H"
#include "FFuLib/FFuCustom/components/DataNode.H"
#include "FFuLib/FFuCustom/mvcModels/BladeSelectionModel.H"
#include "FFuLib/Icons/plusSign.xpm"
#include "FFuLib/Icons/minusSign.xpm"

#include <QTreeView>
#include <QToolButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QAbstractItemView>
#include <QFileDialog>
#include <QDir>


BladeSelector::BladeSelector(const std::string& dPath, QWidget* parent) : QWidget(parent)
{
  currentPath = propPath = dPath.c_str();
  expanded = true;

  // Initialize widgets
  apHideShowButton = new QToolButton(this);
  apHideShowButton->setArrowType(Qt::UpArrow);

  apAddLibButton = new QToolButton(this);
  apAddLibButton->setIcon(QIcon(QPixmap(plusSign_xpm)));
  apAddLibButton->setToolTip("Include blades library");

  apRemoveLibButton = new QToolButton(this);
  apRemoveLibButton->setIcon(QIcon(QPixmap(minusSign_xpm)));
  apRemoveLibButton->setToolTip("Remove blades library");

  apAvailableBladesView = new QTreeView(this);
  apBladeSelectionModel = BladeSelectionModel::instance();
  apAvailableBladesView->setModel(apBladeSelectionModel);
  apAvailableBladesView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  apAvailableBladesView->setSelectionMode(QAbstractItemView::SingleSelection);

  apPathField = new QLineEdit("",this);
  apPathField->setEnabled(false);
  apPathField->hide();

  // Layouts
  apMainLayout = new QHBoxLayout();
  apButtonLayout = new QVBoxLayout();

  apMainLayout->setContentsMargins(2, 0, 2, 0);
  apButtonLayout->setContentsMargins(2, 0, 2, 0);

  apMainLayout->addWidget(apPathField);
  apMainLayout->addWidget(apAvailableBladesView);
  apMainLayout->addLayout(apButtonLayout);

  apButtonLayout->addWidget(apHideShowButton, 0, Qt::AlignRight | Qt::AlignTop );
  apButtonLayout->addWidget(apAddLibButton, 0, Qt::AlignRight | Qt::AlignTop );
  apButtonLayout->addWidget(apRemoveLibButton, 0, Qt::AlignRight | Qt::AlignTop );

  this->setLayout(apMainLayout);
  this->setMaximumHeight(200);

  // Connections
  QObject::connect(apHideShowButton, SIGNAL(clicked()), this, SLOT(hideShow()));
  QObject::connect(apAddLibButton, SIGNAL(clicked()), this, SLOT(addLibrary()));
  QObject::connect(apRemoveLibButton, SIGNAL(clicked()), this, SLOT(removeLibrary()));
  QObject::connect(apAvailableBladesView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(bladeSelected()));
}


void BladeSelector::hideShow()
{
  if (expanded)
  {
    apAvailableBladesView->hide();
    apPathField->show();

    apHideShowButton->setArrowType(Qt::DownArrow);
    apAddLibButton->hide();
    apRemoveLibButton->hide();
  }
  else
  {
    apAvailableBladesView->show();
    apPathField->hide();

    apHideShowButton->setArrowType(Qt::UpArrow);
    apAddLibButton->show();
    apRemoveLibButton->show();
  }

  expanded = !expanded;
}


void BladeSelector::bladeSelected()
{
  if (apAvailableBladesView->currentIndex().isValid())
    apPathField->setText(static_cast<DataNode*>(apAvailableBladesView->currentIndex().internalPointer())->getParentNode()->getData(0).toString() +
			 apBladeSelectionModel->data(apAvailableBladesView->currentIndex(), Qt::DisplayRole).toString());
  else
    apPathField->setText("No Blade Selected");
}


void BladeSelector::selectItem(const QString& value)
{
  int nNode = static_cast<DataNode*>(apBladeSelectionModel->index(0,0).internalPointer())->getParentNode()->subNodeCount();
  if (value == "")
  {
    for (int i = 0; i < nNode; i++)
      if (static_cast<DataNode*>(apBladeSelectionModel->index(i,0).internalPointer())->subNodeCount() > 0)
      {
	apAvailableBladesView->setCurrentIndex(apBladeSelectionModel->index(0,0,apBladeSelectionModel->index(i,0)));
	this->bladeSelected();
	return;
      }
  }
  else if (apBladeSelectionModel->index(0,0).isValid())
    for (int i = 0; i < nNode; i++)
    {
      DataNode* dNode = static_cast<DataNode*>(apBladeSelectionModel->index(i,0).internalPointer());
      for (int j = 0; j < dNode->subNodeCount(); j++)
        if (value == dNode->getData(0).toString() + dNode->subNode(j)->getData(0).toString())
        {
          apAvailableBladesView->setCurrentIndex(apBladeSelectionModel->index(j,0,apBladeSelectionModel->index(i,0)));
          this->bladeSelected();
          return;
        }
    }
}


bool BladeSelector::itemExist(const QString& value)
{
  return apBladeSelectionModel->itemExist(value);
}


void BladeSelector::addUnsavedItem(const QString& modelFileName, const QString& bladeName)
{
  apBladeSelectionModel->addUnsavedItem(modelFileName, bladeName);
}


void BladeSelector::addEntry(const QString& fullPath)
{
  QString name = fullPath.split(QDir::separator()).last();
  int index = fullPath.lastIndexOf(QDir::separator());
  QString path = fullPath.left(index);

  apBladeSelectionModel->addItem(path,name);
  emit(this->selectionModelChanged());
}


bool BladeSelector::removeEntry(const QString& fullPath)
{
  QString name = fullPath.split(QDir::separator()).last();
  int index = fullPath.lastIndexOf(QDir::separator());
  QString path = fullPath.left(index+1);

  if (!apBladeSelectionModel->removeItem(path,name))
    return false;

  emit(this->selectionModelChanged());
  return true;
}


void BladeSelector::addLibrary()
{
  // Asks the user for a path to a library. If valid, adds the library to the blade-selector
  currentPath = QFileDialog::getExistingDirectory(this, "Select a folder containing blades", currentPath);
  if (apBladeSelectionModel->addDirectory(0,currentPath))
    emit(this->selectionModelChanged());
  else
  {
    currentPath = propPath;
    QMessageBox::warning(this,"No new blades found","No blade definition files were found in the folder!");
  }
}


void BladeSelector::removeLibrary()
{
  // Removes the currently selected library
  if (apAvailableBladesView->currentIndex().parent() == apAvailableBladesView->rootIndex() &&
      static_cast<DataNode*>(apBladeSelectionModel->index(0,0).internalPointer())->getParentNode()->subNodeCount() > 1)
  {
    if (static_cast<DataNode*>(apAvailableBladesView->currentIndex().internalPointer())->getData(0).toString() != propPath)
    {
      apBladeSelectionModel->removeDirectory(apAvailableBladesView->currentIndex().row(), apAvailableBladesView->currentIndex().parent());
      emit(this->selectionModelChanged());
    }
    else
      QMessageBox::warning(this,"Operation not allowed","You can not remove the default Fedem blade-library");
  }
}


void BladeSelector::refresh()
{
  QVector<QString> directories;
  QVector<bool> readOnlyStates;

  // Get all directories
  int i, numOfChildren = apBladeSelectionModel->rowCount(apAvailableBladesView->rootIndex());
  for (i = 0; i < numOfChildren; i++)
  {
    QString path = (static_cast<DataNode*>( apBladeSelectionModel->index(i,0).internalPointer()))->getData(0).toString();
    path.resize(path.size()-1);//remove last slash
    directories.push_back( path );
    readOnlyStates.push_back(static_cast<DataNode*>(apBladeSelectionModel->index(i,0).internalPointer())->getData(1).toBool());
  }

  // remove all directories
  apBladeSelectionModel->clearModel();

  // add all directories
  for (i = numOfChildren-1; i >= 0; i--)
    apBladeSelectionModel->addDirectory(0, QString(directories.at(i)), readOnlyStates.at(i));
}


QString BladeSelector::getCurrentFolder() const
{
  if (currentPath != propPath)
    return currentPath + QDir::separator();

  return QDir::homePath() + QDir::separator();
}
