#include "EditMedicinesViewManager.h"

#include "pch.h"
#include <iostream>
#include "View/EditMedicinesView.h"

EditMedicinesViewManager::EditMedicinesViewManager(QObject *parent,
	EditMedicinesView& view, Model::Patient& patient) :
	QObject(parent),
	view(view),
	currentPatient(patient),
	instance(DataAccess::retrieveInstance())
{
	instance->init("hospital_data.db");
	auto list = instance->getAllMedicines();
	view.UpdateAllMedicinesTable(list);

	auto list2 = instance->getMedicinesOfPatient(currentPatient);
	view.UpdateUsedMedicinesTable(list2);

	connect(&view, &EditMedicinesView::NotifyAddMedicineButtonPressed,
		this, &EditMedicinesViewManager::onAddMedicineButtonPressed);
	connect(&view, &EditMedicinesView::NotifyRemoveMedicineButtonPressed,
		this, &EditMedicinesViewManager::onRemoveMedicineButtonPressed);

}

EditMedicinesViewManager::~EditMedicinesViewManager()
{

}

void EditMedicinesViewManager::onAddMedicineButtonPressed(Model::Medicine& medicine)
{
	auto result = instance->addMedicineToPatient(currentPatient, medicine);

	auto list2 = instance->getMedicinesOfPatient(currentPatient);
	view.UpdateUsedMedicinesTable(list2);

}

void EditMedicinesViewManager::onRemoveMedicineButtonPressed(Model::Medicine& medicine)
{
	auto result = instance->removeMedicineFromPatient(currentPatient, medicine);

	auto list2 = instance->getMedicinesOfPatient(currentPatient);
	view.UpdateUsedMedicinesTable(list2);

}