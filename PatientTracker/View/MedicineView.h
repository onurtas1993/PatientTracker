#pragma once

#include <QWidget>
#include <QList>
#include <QSortFilterProxyModel> 
#include <QtCharts/qpieslice.h>
#include "ui_MedicineView.h"
#include "TableModel/PatientDataModel.h"
#include "TableModel/MedicineDataModel.h"

class MedicineView : public QWidget
{
	Q_OBJECT

public:
	MedicineView(QWidget* parent = Q_NULLPTR);
	~MedicineView();

	void UpdateMedicinesTable(QList<Model::Medicine> medicines);
	void UpdatePatientsTable(QList<Model::Patient> patients);

signals:
	void AddMedicineRequested(const QString& receiptNo, const QString& name, const QDate& productionDate, const QDate& expirationDate);
	void RemoveMedicineRequested(const QString& receiptNo, const QString& name, const QDate& productionDate, const QDate& expirationDate);
	void MedicineSelectionChanged(const QString& receiptNo, const QString& name, const QDate& productionDate, const QDate& expirationDate);

public slots:
	void DisplayError(const QString& title, const QString& message);
	void DisplayInfo(const QString& title, const QString& message);

private slots:
	void handleAddMedicineButtonClicked();
	void handleRemoveMedicineButtonClicked();
	void TableSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
	void refreshPieChart();

	Ui::MedicineView ui;

	QSortFilterProxyModel patientProxy;
	PatientDataModel patientModel;

	QSortFilterProxyModel medicineProxy;
	MedicineDataModel medicineModel;

	QPieSlice* greenSlice;
	QPieSlice* yellowSlice;
	QPieSlice* redSlice;
};
