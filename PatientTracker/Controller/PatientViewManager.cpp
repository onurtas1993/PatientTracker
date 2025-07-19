#include "PatientViewManager.h"

#include "View/PatientView.h" 
#include "View/EditMedicinesView.h" 
#include "Controller/EditMedicinesViewManager.h"
#include "pch.h" 

PatientViewManager::PatientViewManager(QObject* parent,
	PatientView& view) :
	QObject(parent),
	view(view),
	instance(DataAccess::retrieveInstance())
{
	instance->init("hospital_data.db");
	auto list = instance->getAllPatients();
	view.UpdatePatientsTable(list);

	connect(&view, &PatientView::EditMedicinesRequested,
		this, &PatientViewManager::onEditMedicinesButtonPressed);
	connect(&view, &PatientView::RemovePatientRequested,
		this, &PatientViewManager::onRemovePatientButtonPressed);
	connect(&view, &PatientView::AddPatientRequested,
		this, &PatientViewManager::onAddPatientButtonPressed);
	connect(&view, &PatientView::UpdatePatientRequested,
		this, &PatientViewManager::onUpdatePatientButtonPressed);
	connect(&view, &PatientView::SelectedPatientChanged,
		this, &PatientViewManager::onSelectedPatientChanged);

}

PatientViewManager::~PatientViewManager()
{

}

void PatientViewManager::onEditMedicinesButtonPressed(Model::Patient& patient)
{
	auto editMedicinesView = std::make_unique<EditMedicinesView>(&view);
	auto editMedicinesViewManager = std::make_unique<EditMedicinesViewManager>(this, *editMedicinesView, patient);
	editMedicinesView->setModal(true);
	editMedicinesView->exec();
	// Smart pointers clean up automatically
}

void PatientViewManager::onAddPatientButtonPressed(Model::Patient& patient)
{
	instance->addPatient(patient);
	auto list = instance->getAllPatients();
	view.UpdatePatientsTable(list);
}

void PatientViewManager::onUpdatePatientButtonPressed(Model::Patient& patient)
{
	instance->updatePatientZone(patient);
	auto list = instance->getAllPatients();
	view.UpdatePatientsTable(list);
}

void PatientViewManager::onRemovePatientButtonPressed(Model::Patient& patient)
{
	instance->removePatient(patient);
	instance->removeMedicinesOfPatient(patient);
	auto list = instance->getAllPatients();
	view.UpdatePatientsTable(list);
}

void PatientViewManager::onSelectedPatientChanged(Model::Patient& patient)
{
	auto list = instance->getMedicinesOfPatient(patient);
	view.UpdateMedicinesTable(list);
	view.UpdateSelectedPatientZoneInfo(patient);
}


