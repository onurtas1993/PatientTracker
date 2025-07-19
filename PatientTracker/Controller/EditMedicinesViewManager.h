 
#pragma once
#include <QObject>
#include <Patient.h> 
#include <Medicine.h> 

#include "SQLDataAccess.h"

class EditMedicinesView;

class EditMedicinesViewManager : public QObject
{
	Q_OBJECT
public:
	explicit EditMedicinesViewManager(QObject *parent, EditMedicinesView& view, Model::Patient& patient);
	~EditMedicinesViewManager();
	 
public slots:
	void onAddMedicineButtonPressed(Model::Medicine&);
	void onRemoveMedicineButtonPressed(Model::Medicine&);

private:
	Model::Patient& currentPatient;
	EditMedicinesView& view;
	DataAccess::IDataAccess* instance;

	explicit EditMedicinesViewManager(const EditMedicinesViewManager& rhs);
};
