#pragma once
 
#ifdef DATAACCESS_EXPORTS
#define DATAACCESS_API __declspec(dllexport)
#else
#define DATAACCESS_API __declspec(dllimport)
#endif
 
#include <string> 
#include <QtCore/qlist.h> 

namespace Model { 
	class Patient;
	class Medicine;
}

namespace DataAccess
{
	class IDataAccess
	{
	public:
		virtual void Destroy()
		{
			delete this;
		}

		virtual bool init(std::string db_file) = 0;

		virtual bool addPatient(Model::Patient& patient) = 0;

		virtual bool removePatient(Model::Patient& patient) = 0;

		virtual bool addMedicine(Model::Medicine& medicine) = 0;

		virtual bool removeMedicine(Model::Medicine& medicine) = 0;

		virtual bool addMedicineToPatient(Model::Patient& patient, Model::Medicine medicine) = 0;

		virtual bool removeMedicineFromPatient(Model::Patient& patient, Model::Medicine medicine) = 0;

		virtual bool removeMedicinesOfPatient(Model::Patient& patient) = 0;

		virtual bool removePatientsOfMedicine(Model::Medicine& medicine) = 0;

		virtual bool updatePatientZone(Model::Patient& patient) = 0;

		virtual QList<Model::Medicine> getMedicinesOfPatient(Model::Patient& patient) = 0;

		virtual QList<Model::Patient> getPatientsOfSpesificMedicine(Model::Medicine medicine) = 0;

		virtual QList<Model::Patient> getAllPatients() = 0;

		virtual QList<Model::Medicine> getAllMedicines() = 0;
		 
	};
}