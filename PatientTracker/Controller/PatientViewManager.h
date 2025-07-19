#pragma once
#include <QObject>

#include "SQLDataAccess.h"

class Patient;
class PatientView;

class PatientViewManager : public QObject
{
	Q_OBJECT
public:
	explicit PatientViewManager(QObject* parent, PatientView& view);
	~PatientViewManager();

public slots:
	void onEditMedicinesButtonPressed(Model::Patient&);
	void onSelectedPatientChanged(Model::Patient&);
	void onAddPatientButtonPressed(Model::Patient&);
	void onRemovePatientButtonPressed(Model::Patient&);
	void onUpdatePatientButtonPressed(Model::Patient&);

private:
	PatientView& view;
	DataAccess::IDataAccess* instance;

	explicit PatientViewManager(const PatientViewManager& rhs);
};
