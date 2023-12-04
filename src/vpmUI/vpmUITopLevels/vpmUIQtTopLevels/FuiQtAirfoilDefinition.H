// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_AIRFOIL_DEFINITION_H
#define FUI_QT_AIRFOIL_DEFINITION_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSplitter>
#include <QSignalMapper>

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiAirfoilDefinition.H"
#include "FFuLib/FFuCustom/inputTables/InputTable.H"
#include "FFuLib/FFuCustom/components/guiComponents/AirfoilSelector.H"


class FuiQtAirfoilDefinition : public FFuQtTopLevelShell, public FuiAirfoilDefinition
{
  Q_OBJECT

public:
  FuiQtAirfoilDefinition(QWidget* parent = 0,
			 int xpos =100, int ypos =100,
			 int width=100, int height=100,
			 const char* title= "Fedem",
			 const char* name = "FuiQtAirfoilDefinition");
  virtual ~FuiQtAirfoilDefinition() {}

private:
	typedef InputTable TableT;

	// Widgets
	TableT* apAirfoilTable;
	AirfoilSelector* apAirfoilSelector;

	QSplitter* apSplitter;
	QWidget* apBottomContainer;

	QLabel* apNameLabel;
	QLineEdit* apAirfoilName;

	QLabel* apNotesLabel;
	QLabel* apNotesLabelImage;
	QLabel* apNotesText;

	//Buttons
	QPushButton* apAddRowButton;
	QPushButton* apRemoveRowButton;

	QPushButton* apSaveButton;
	QPushButton* apCloseButton;
	QPushButton* apHelpButton;

	QPushButton* apCreateAirfoilButton;

	QSignalMapper* apLineEditMapper;

	//Line edits
	QLabel* apNumLabel;
	QLineEdit* apNumEdit;
	QLabel* apIDLabel;
	QLineEdit* apIDEdit;
	QLabel* apStallLabel;
	QLineEdit* apStallEdit;
	QLabel* apCnAnglekLabel;
	QLineEdit* apCnAngleEdit;
	QLabel* apCnSlopeLabel;
	QLineEdit* apCnSlopeEdit;
	QLabel* apCnExtrapolLabel;
	QLineEdit* apCnExtrapolEdit;
	QLabel* apCnStallLabel;
	QLineEdit* apCnStallEdit;
	QLabel* apAttackLabel;
	QLineEdit* apAttackEdit;
	QLabel* apMinCDLabel;
	QLineEdit* apMinCDEdit;

	//Layouts
	QVBoxLayout* apMainLayout;
	QHBoxLayout* apContentLayout;
	QVBoxLayout* apLineEditLayout;
	QHBoxLayout* apTableButtonLayout;
	QVBoxLayout* apTableLayout;
	QHBoxLayout* apDialogButtonLayout;
	QHBoxLayout* apNotesLabelLayout;
	QVBoxLayout* apNotesLayout;

	bool currentAirfoilTouched;
	QString currentAirfoil;

	void showEvent ( QShowEvent * pEvent );
	void closeEvent ( QCloseEvent * pEvent );

	void connections();

	void setCurrentAirfoil(QString airfoilPath);

	virtual void setSensitivity(bool) {}

public slots:
	void insertSegment();
	void removeSegment();
	void acceptClicked();
	void createAirfoil();

	void airfoilSelected();
	bool save(QString airfoilPath);
	void currentModelChanged();

private slots:
	void lineEditChanged(int lineEdit);
	void help();
};

#endif
