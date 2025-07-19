#pragma once

#include <QWidget>
#include <QList>
#include <QSortFilterProxyModel> 
#include "ui_PatientView.h" 
#include "TableModel/PatientDataModel.h"
#include "TableModel/MedicineDataModel.h"

class PatientView : public QWidget
{
	Q_OBJECT

public:
	PatientView(QWidget* parent = Q_NULLPTR);
	~PatientView();

	void UpdateSelectedPatientZoneInfo(Model::Patient patient);
	void UpdatePatientsTable(QList<Model::Patient> patients);
	void UpdateMedicinesTable(QList<Model::Medicine> medicines);

signals:
	void EditMedicinesRequested(Model::Patient& patient);
	void SelectedPatientChanged(Model::Patient& patient);
	void UpdatePatientRequested(Model::Patient& patient);
	void AddPatientRequested(Model::Patient& patient);
	void RemovePatientRequested(Model::Patient& patient);

private slots:
	void handleEditMedicinesButtonClicked();
	void handleAddPatientButtonClicked();
	void handleRemovePatientButtonClicked();
	void handleUpdatePatientButtonClicked();
	void TableSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
	Ui::PatientView ui;

	QSortFilterProxyModel patientProxy;
	PatientDataModel patientModel;

	QSortFilterProxyModel medicineProxy;
	MedicineDataModel medicineModel;

};
