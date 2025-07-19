#include "MedicineView.h"

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QMessageBox>

MedicineView::MedicineView(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	patientProxy.setSourceModel(&patientModel);
	patientProxy.setFilterKeyColumn(0);
	ui.patientsTableView->setModel(&patientProxy);

	medicineProxy.setSourceModel(&medicineModel);
	medicineProxy.setFilterKeyColumn(1);
	ui.medicinesTableView->setModel(&medicineProxy);

	connect(ui.medicineSearchLineEdit, SIGNAL(textChanged(QString)), &medicineProxy, SLOT(setFilterFixedString(QString)));
	connect(ui.addMedicineButton, SIGNAL(released()), this, SLOT(handleAddMedicineButtonClicked()));
	connect(ui.removeMedicineButton, SIGNAL(released()), this, SLOT(handleRemoveMedicineButtonClicked()));
	connect(
		ui.medicinesTableView->selectionModel(),
		SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
		this,
		SLOT(TableSelectionChanged(const QItemSelection&, const QItemSelection&))
	);

	QPieSeries* series = new QPieSeries();
	series->append("Tarihi Var", 1);
	series->append("Tarigi Yakin", 2);
	series->append("Tarihi Gecmis", 3);

	greenSlice = series->slices().at(0);
	greenSlice->setValue(1);
	greenSlice->setExploded();
	greenSlice->setPen(QPen(Qt::darkGreen, 2));
	greenSlice->setBrush(QColor(76, 175, 80));

	yellowSlice = series->slices().at(1);
	yellowSlice->setValue(1);
	yellowSlice->setExploded();
	yellowSlice->setPen(QPen(Qt::darkYellow, 2));
	yellowSlice->setBrush(QColor(255, 235, 59));

	redSlice = series->slices().at(2);
	redSlice->setValue(1);
	redSlice->setExploded();
	redSlice->setPen(QPen(Qt::darkRed, 2));
	redSlice->setBrush(QColor(244, 67, 54));

	QChart* chart = new QChart();
	chart->addSeries(series);
	chart->legend()->hide();

	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);

	ui.pieVerticalLayout->addWidget(chartView);

	ui.patientsTableView->setColumnHidden(2, true);
	ui.patientsTableView->setColumnHidden(3, true);
	ui.patientsTableView->setColumnHidden(4, true);
}

MedicineView::~MedicineView()
{
}

void MedicineView::UpdateMedicinesTable(QList<Model::Medicine> medicines)
{
	medicineModel.updateTableDataSet(medicines);
	refreshPieChart();
	patientModel.clear();
}

void MedicineView::UpdatePatientsTable(QList<Model::Patient> patients)
{
	patientModel.updateTableDataSet(patients);
}

void MedicineView::refreshPieChart()
{
	int green = 0, yellow = 0, red = 0;
	medicineModel.getColorWeights(green, yellow, red);

	greenSlice->setValue(green);
	yellowSlice->setValue(yellow);
	redSlice->setValue(red);
}

void MedicineView::handleAddMedicineButtonClicked()
{
	emit AddMedicineRequested(
		ui.medicineNoLineEdit->text(),
		ui.medicineNameLineEdit->text(),
		ui.medicineStartDateEdit->date(),
		ui.medicineEndDateEdit->date()
	);
}

void MedicineView::handleRemoveMedicineButtonClicked()
{
	emit RemoveMedicineRequested(
		ui.medicineNoLineEdit->text(),
		ui.medicineNameLineEdit->text(),
		ui.medicineStartDateEdit->date(),
		ui.medicineEndDateEdit->date()
	);
}

void MedicineView::TableSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	QModelIndexList indexes = selected.indexes();
	if (indexes.count() == 0) return;
	emit MedicineSelectionChanged(
		medicineProxy.data(indexes[0]).toString(),
		medicineProxy.data(indexes[1]).toString(),
		medicineProxy.data(indexes[2]).toDate(),
		medicineProxy.data(indexes[3]).toDate()
	);
}

void MedicineView::DisplayError(const QString& title, const QString& message)
{
	QMessageBox msgBox;
	msgBox.setWindowTitle(title);
	msgBox.setText(message);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.exec();
}

void MedicineView::DisplayInfo(const QString& title, const QString& message)
{
	QMessageBox msgBox;
	msgBox.setWindowTitle(title);
	msgBox.setText(message);
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setIcon(QMessageBox::Information);
	msgBox.exec();
}