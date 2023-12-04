// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FUI_QT_BLADE_DEFINITION_H
#define FUI_QT_BLADE_DEFINITION_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QSignalMapper>

#include "FFuLib/FFuQtBaseClasses/FFuQtTopLevelShell.H"
#include "vpmUI/vpmUITopLevels/FuiBladeDefinition.H"

class InputTable;
class Blade;
class BladeDrawer;
class BladeSelector;
class FileFieldDelegate;


class FuiQtBladeDefinition: public FFuQtTopLevelShell,
		public FuiBladeDefinition {
Q_OBJECT
public:
	FuiQtBladeDefinition(QWidget* parent = 0,
			int xpos =100, int ypos =100,
			int width=100, int height=100,
			const char* title= "Fedem",
			const char* name = "FuiQtBladeDefinition");
	~FuiQtBladeDefinition();

private:
	//**********Widgets**********
	QSignalMapper* apCheckboxMapper;
	BladeDrawer* apBladeDrawer;
	QTabWidget* apTabWidget;

	QLabel* apNameLabel;
	QLineEdit* apNameEdit;

	QLabel* apNotesLabel;
	QLabel* apNotesLabelImage;
	QLabel* apNotesText;

	BladeSelector* apBladeSelector;

	QPushButton* apSaveButton;
	QPushButton* apCloseButton;
	QPushButton* apHelpButton;

	QPushButton* apAddSegmentButton;
	QPushButton* apRemoveSegmentButton;
	QPushButton* apCreateBladeButton;

	QCheckBox* apBendingStiffnesCheck;
	QCheckBox* apAxialStiffnesCheck;
	QCheckBox* apTorsionStiffnesCheck;
	QCheckBox* apShearStiffnesCheck;

	QWidget* apStructureTab;

	//**********Layouts**********
	QVBoxLayout* apMainLayout;
	QVBoxLayout* apStiffnessLayout;

	QHBoxLayout* apViewLayout;
	QHBoxLayout* apBladeSelectorLayout;
	QHBoxLayout* apDialogButtonLayout;
	QHBoxLayout* apCheckBoxLayout;

	QHBoxLayout* apNotesLabelLayout;
	QVBoxLayout* apNotesLayout;

	InputTable* apAerodynamicTable;
	InputTable* apStructureTable;

	FileFieldDelegate* pSelectorDelegate;

	//**********members**********
	std::vector<Blade*> apBlades;
	Blade* apCurrentBlade;
	bool bladeChanged;

	void connections();
	bool setCurrentBlade(Blade* pBlade);
	bool saveBlade(Blade* blade);
	void resolveAirfoils(Blade* pBlade);

	void showEvent ( QShowEvent * pEvent );
	void closeEvent ( QCloseEvent * pEvent );

	virtual void setSensitivity(bool) {}

public slots:
	void initializeBlades();
	void acceptClicked();
	void bladeSelected();
	void insertSegment();
	void removeSegment();
	void updateNameField();
	void nameChanged();
	void currentModelChanged();
	void createBlade();
	void checkBoxChanged(int checkBox);
	void updateCheckBoxes();
	void changeAirfoil();
	void help();
	void itemClicked(const QModelIndex& index); //Used to display comboBox for airfoil selection on single-click

signals:
	void currentBladeChanged();
};

#endif
