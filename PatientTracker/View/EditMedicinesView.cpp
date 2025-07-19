#include "EditMedicinesView.h"

EditMedicinesView::EditMedicinesView(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	allMedicinesProxy.setSourceModel(&allMedicinesModel);
	allMedicinesProxy.setFilterKeyColumn(0);
	ui.allMedicinesTableView->setModel(&allMedicinesProxy);
	 
	usedMedicinesProxy.setSourceModel(&usedMedicinesModel);
	usedMedicinesProxy.setFilterKeyColumn(0);
	ui.usedMedicinesTableView->setModel(&usedMedicinesProxy);

	connect(ui.allMedicinesSearchLineEdit, SIGNAL(textChanged(QString)), &allMedicinesProxy, SLOT(setFilterFixedString(QString)));
	connect(ui.usedMedicinesSearchLineEdit, SIGNAL(textChanged(QString)), &usedMedicinesProxy, SLOT(setFilterFixedString(QString)));

	connect(ui.addToUsedMedicinesButton, SIGNAL(released()), this, SLOT(handleAddMedicineButtonClicked()));
	connect(ui.removeFromUsedMedicinesButton, SIGNAL(released()), this, SLOT(handleRemoveMedicineButtonClicked()));
}

EditMedicinesView::~EditMedicinesView()
{
}

void EditMedicinesView::handleAddMedicineButtonClicked()
{
	QModelIndexList indexes = ui.allMedicinesTableView->selectionModel()->selectedIndexes();
	auto id = allMedicinesProxy.data(indexes[0]).toString().toStdString();
	auto name = allMedicinesProxy.data(indexes[1]).toString().toStdString();

	Model::Medicine m(id, name, "", "");

	if (usedMedicinesModel.exists(m))
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Repetitive Drug Error");
		msgBox.setText("This drug is already on the patient's list of medications.");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.setIcon(QMessageBox::Warning);
		msgBox.exec();

	}
	else
		emit NotifyAddMedicineButtonPressed(m);
	ui.allMedicinesSearchLineEdit->clear();

}

void EditMedicinesView::handleRemoveMedicineButtonClicked()
{
	QModelIndexList indexes = ui.usedMedicinesTableView->selectionModel()->selectedIndexes();
	auto id = usedMedicinesProxy.data(indexes[0]).toString().toStdString();
	auto name = usedMedicinesProxy.data(indexes[1]).toString().toStdString();

	Model::Medicine m(id, name, "", "");

	ui.usedMedicinesSearchLineEdit->clear();
	emit NotifyRemoveMedicineButtonPressed(m);
}

void EditMedicinesView::UpdateAllMedicinesTable(QList<Model::Medicine> medicines)
{
	allMedicinesModel.updateTableDataSet(medicines);
}

void EditMedicinesView::UpdateUsedMedicinesTable(QList<Model::Medicine> medicines)
{
	usedMedicinesModel.updateTableDataSet(medicines);
}
