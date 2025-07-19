#pragma once

#include "IDataAccess.h"
#include <QtSql/qsqldatabase.h>
 
namespace DataAccess
{

	class SQLDataAccess : public IDataAccess
	{
	public:
		SQLDataAccess();
		virtual ~SQLDataAccess(); 

		// Inherited via IDataAccess
		virtual bool init(std::string db_file) override;
		virtual bool addPatient(Model::Patient& patient) override; 
		virtual bool addMedicine(Model::Medicine& medicine) override;
		virtual bool removeMedicine(Model::Medicine& medicine) override;
		virtual bool addMedicineToPatient(Model::Patient & patient, Model::Medicine medicine) override;
		virtual bool removeMedicineFromPatient(Model::Patient & patient, Model::Medicine medicine) override;
		virtual bool removePatient(Model::Patient& patient) override; 
		virtual bool removeMedicinesOfPatient(Model::Patient& patient) override;
		virtual bool removePatientsOfMedicine(Model::Medicine& medicine) override;
		virtual bool updatePatientZone(Model::Patient & patient) override;
		virtual QList<Model::Medicine> getMedicinesOfPatient(Model::Patient& patient) override;
		virtual QList<Model::Patient> getPatientsOfSpesificMedicine(Model::Medicine medicine) override;
		virtual QList<Model::Patient> getAllPatients() override;
		virtual QList<Model::Medicine> getAllMedicines() override; 
		 
	private:
		QSqlDatabase db;  

	};

	extern "C" DATAACCESS_API IDataAccess* retrieveInstance();
}