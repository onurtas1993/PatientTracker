#include "PatientView.h"

PatientView::PatientView(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.zoneGroupBox->setVisible(false);
	ui.editMedicinesButton->setVisible(false);
	//setup patients table
	patientProxy.setSourceModel(&patientModel);
	patientProxy.setFilterKeyColumn(0);
	ui.patientsTableView->setModel(&patientProxy);

	//setup medicines table 
	medicineProxy.setSourceModel(&medicineModel);
	medicineProxy.setFilterKeyColumn(0);
	ui.patientMedicinesTableView->setModel(&medicineProxy);

	connect(ui.editMedicinesButton, SIGNAL(released()), this, SLOT(handleEditMedicinesButtonClicked()));
	connect(ui.changePatientZoneInfoButton, SIGNAL(released()), this, SLOT(handleUpdatePatientButtonClicked()));
	connect(ui.removePatientButton, SIGNAL(released()), this, SLOT(handleRemovePatientButtonClicked()));
	connect(ui.addPatientButton, SIGNAL(released()), this, SLOT(handleAddPatientButtonClicked()));
	connect(ui.searchLineEdit, SIGNAL(textChanged(QString)), &patientProxy, SLOT(setFilterFixedString(QString)));
	connect(
		ui.patientsTableView->selectionModel(),
		SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)),
		this,
		SLOT(TableSelectionChanged(const QItemSelection&, const QItemSelection&))
	);
}

PatientView::~PatientView()
{
}

void PatientView::handleEditMedicinesButtonClicked()
{
	std::string name = ui.zone_patientNameLabel->text().QString::toStdString();
	std::string surname = ui.zone_patientSurnameLabel->text().QString::toStdString();
	Model::Patient p(name, surname, "", "", "");
	emit EditMedicinesRequested(p);
}

void PatientView::handleAddPatientButtonClicked()
{
	std::string name = ui.patientNameLineEdit->text().QString::toStdString();
	std::string surname = ui.patientSurnameLineEdit->text().QString::toStdString();
	Model::Patient p(name, surname, "", "", "");
	emit AddPatientRequested(p);
}

void PatientView::handleRemovePatientButtonClicked()
{
	std::string name = ui.patientNameLineEdit->text().QString::toStdString();
	std::string surname = ui.patientSurnameLineEdit->text().QString::toStdString();
	Model::Patient p(name, surname, "", "", "");
	emit RemovePatientRequested(p);
}

void PatientView::handleUpdatePatientButtonClicked()
{
	std::string name = ui.zone_patientNameLabel->text().QString::toStdString();
	std::string surname = ui.zone_patientSurnameLabel->text().QString::toStdString();
	std::string zone = ui.zone_zoneTextEdit->toPlainText().QString::toStdString();
	std::string inDate = ui.zone_inDateEdit->date().toString("dd/MM/yyyy").QString::toStdString();
	std::string outDate = ui.zone_outDateEdit->date().toString("dd/MM/yyyy").QString::toStdString();
	Model::Patient p(name, surname, zone, inDate, outDate);
	emit UpdatePatientRequested(p);
}

void PatientView::TableSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
	QModelIndexList indexes = selected.indexes();
	if (indexes.count() == 0) return;
	auto name = patientProxy.data(indexes[0]).toString().toStdString();
	auto surname = patientProxy.data(indexes[1]).toString().toStdString();
	auto stayzone = patientProxy.data(indexes[2]).toString().toStdString();
	auto indate = patientProxy.data(indexes[3]).toString().toStdString();
	auto outdate = patientProxy.data(indexes[4]).toString().toStdString();

	Model::Patient patient(name, surname, stayzone, indate, outdate);
	emit SelectedPatientChanged(patient);
}

void PatientView::UpdateSelectedPatientZoneInfo(Model::Patient patient)
{
	QString name = QString::fromStdString(patient.name());
	QString surname = QString::fromStdString(patient.surname());
	QString zone = QString::fromStdString(patient.stayZone());
	QString in_date_string_on_db = QString::fromStdString(patient.inDate());
	QString out_date_string_on_db = QString::fromStdString(patient.outDate());
	QDate in_date = QDate::fromString(in_date_string_on_db, "dd/MM/yyyy");
	QDate out_date = QDate::fromString(out_date_string_on_db, "dd/MM/yyyy");

	ui.zone_patientNameLabel->setText(name);
	ui.zone_patientSurnameLabel->setText(surname);
	ui.zone_inDateEdit->setDate(in_date);
	ui.zone_outDateEdit->setDate(out_date);
	ui.zone_zoneTextEdit->setText(zone);

	ui.patientFullNameHorizontalLayout->update();
}

void PatientView::UpdatePatientsTable(QList<Model::Patient> patients)
{
	patientModel.updateTableDataSet(patients);
	medicineModel.clear();
}

void PatientView::UpdateMedicinesTable(QList<Model::Medicine> medicines)
{
	medicineModel.updateTableDataSet(medicines);
}