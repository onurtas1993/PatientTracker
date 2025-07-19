#include "MedicineViewManager.h"

#include "pch.h"
#include <iostream>
#include "View/MedicineView.h"  
#include "Controller/MedicineViewManager.h" 
#include <QMessageBox>
#include <algorithm> // for std::find_if

MedicineViewManager::MedicineViewManager(QObject *parent,
    MedicineView& view) :
    QObject(parent),
    view(view),
    instance(DataAccess::retrieveInstance())
{
    instance->init("hospital_data.db");
    auto list = instance->getAllMedicines();
    view.UpdateMedicinesTable(list);

    connect(&view, &MedicineView::AddMedicineRequested,
        this, &MedicineViewManager::onAddMedicineRequested);
    connect(&view, &MedicineView::RemoveMedicineRequested,
        this, &MedicineViewManager::onRemoveMedicineRequested);
    connect(&view, &MedicineView::MedicineSelectionChanged,
        this, &MedicineViewManager::onMedicineSelectionChanged);

    // Connect controller signals to view slots for error/status messages
    connect(this, &MedicineViewManager::ErrorOccurred, &view, &MedicineView::DisplayError);
    connect(this, &MedicineViewManager::InfoOccurred, &view, &MedicineView::DisplayInfo);
}

MedicineViewManager::~MedicineViewManager()
{
}

bool MedicineViewManager::medicineExists(const Model::Medicine& m) const
{
    auto allMedicines = instance->getAllMedicines();
    return std::any_of(allMedicines.begin(), allMedicines.end(),
        [&](const Model::Medicine& med) { return med.receiptNumber() == m.receiptNumber(); });
}

void MedicineViewManager::onAddMedicineRequested(const QString& receiptNo, const QString& name, const QDate& productionDate, const QDate& expirationDate)
{
    Model::Medicine m(
        receiptNo.toStdString(),
        name.toStdString(),
        productionDate.toString("dd/MM/yyyy").toStdString(),
        expirationDate.toString("dd/MM/yyyy").toStdString()
    );

    if (medicineExists(m))
    {
        emit ErrorOccurred("Repetitive Drug Error", "This drug number is already registered in the system!");
    }
    else
    {
        instance->addMedicine(m);
        auto list = instance->getAllMedicines();
        view.UpdateMedicinesTable(list);
        emit InfoOccurred("Medicine Added", "The medicine was added successfully.");
    }
}

void MedicineViewManager::onRemoveMedicineRequested(const QString& receiptNo, const QString& name, const QDate& productionDate, const QDate& expirationDate)
{
    Model::Medicine m(
        receiptNo.toStdString(),
        name.toStdString(),
        productionDate.toString("dd/MM/yyyy").toStdString(),
        expirationDate.toString("dd/MM/yyyy").toStdString()
    );

    if (!medicineExists(m))
    {
        emit ErrorOccurred("No Drug Found", "No registered drug found with this drug information!");
    }
    else
    {
        instance->removeMedicine(m);
        instance->removePatientsOfMedicine(m);
        auto list = instance->getAllMedicines();
        view.UpdateMedicinesTable(list);
        emit InfoOccurred("Medicine Removed", "The medicine was removed successfully.");
    }
}

void MedicineViewManager::onMedicineSelectionChanged(const QString& receiptNo, const QString& name, const QDate& productionDate, const QDate& expirationDate)
{
    Model::Medicine m(
        receiptNo.toStdString(),
        name.toStdString(),
        productionDate.toString("dd/MM/yyyy").toStdString(),
        expirationDate.toString("dd/MM/yyyy").toStdString()
    );
    auto list = instance->getPatientsOfSpesificMedicine(m);
    view.UpdatePatientsTable(list);
}