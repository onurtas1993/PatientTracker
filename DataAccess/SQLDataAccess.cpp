
#include "pch.h"
#include <Medicine.h> 
#include <Patient.h> 
#include "SQLDataAccess.h"

#include <QtCore/qvariant.h>
#include <QtCore/qfile.h>
#include <QtCore/qfileinfo.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qtsqlglobal.h>
#include <QtSql/qsqlerror.h>
#include <QtSql/qsqlrecord.h>

DataAccess::SQLDataAccess::SQLDataAccess()
{
}

DataAccess::SQLDataAccess::~SQLDataAccess()
{
	db.close();
}

bool DataAccess::SQLDataAccess::init(std::string db_file)
{
	db = QSqlDatabase::addDatabase("QSQLITE");

	//in order to access the db file in the current dir, some conversions were needed.
	QString db_file_qstring(db_file.c_str());
	QFile db_file_qfile(db_file_qstring);
	QFileInfo db_file_qfileinfo(db_file_qfile);
	QString final_absolute_path(db_file_qfileinfo.absoluteFilePath());

	db.setDatabaseName(final_absolute_path);
	if (db.open())
		return true;
	return false;
}


bool DataAccess::SQLDataAccess::addPatient(Model::Patient& patient)
{
	if (!db.open())
		return false;
	QSqlQuery query;
	query.prepare("INSERT INTO Patient (name, surname) "
		"VALUES (:_name, :_surname)");
	query.bindValue(":_name", QString::fromStdString(patient.name()));
	query.bindValue(":_surname", QString::fromStdString(patient.surname()));
	return query.exec();
}

bool DataAccess::SQLDataAccess::addMedicine(Model::Medicine & medicine)
{
	if (!db.open())
		return false;
	QSqlQuery query;
	query.prepare("insert into Medula (id, name, purchased_date, expiration_date) values (:id, :name, :purchased_date, :expiration_date)");
	query.bindValue(":id", QString::fromStdString(medicine.receiptNumber()));
	query.bindValue(":name", QString::fromStdString(medicine.name()));
	query.bindValue(":purchased_date", QString::fromStdString(medicine.startDate()));
	query.bindValue(":expiration_date", QString::fromStdString(medicine.expirationDate()));
	return query.exec();
}

bool DataAccess::SQLDataAccess::removeMedicine(Model::Medicine & medicine)
{
	if (!db.open())
		return false;
	QSqlQuery query;
	query.prepare("delete from Medula where id = :id");
	query.bindValue(":id", QString::fromStdString(medicine.receiptNumber())); 
	return query.exec();
}

bool DataAccess::SQLDataAccess::removePatient(Model::Patient & patient)
{
	if (!db.open())
		return false;
	QSqlQuery query;
	query.prepare("DELETE FROM Patient WHERE name = :name and surname = :surname");
	query.bindValue(":name", QString::fromStdString(patient.name()));
	query.bindValue(":surname", QString::fromStdString(patient.surname()));
	return query.exec();
}

bool DataAccess::SQLDataAccess::removeMedicinesOfPatient(Model::Patient & patient)
{
	if (!db.open())
		return false;
	QSqlQuery query;
	query.prepare("DELETE FROM Map WHERE patient_full_name = :full_name");
	query.bindValue(":full_name", QString::fromStdString(patient));
	return query.exec();
}

bool DataAccess::SQLDataAccess::removePatientsOfMedicine(Model::Medicine & medicine)
{
	if (!db.open())
		return false;
	QSqlQuery query;
	query.prepare("DELETE FROM Map WHERE medula_id = :id");
	query.bindValue(":id", QString::fromStdString(medicine.receiptNumber()));
	return query.exec();
}

QList<Model::Medicine> DataAccess::SQLDataAccess::getMedicinesOfPatient(Model::Patient & patient)
{
	QList<Model::Medicine> medicines;

	QSqlQuery query;
	query.prepare("SELECT Medula.id, Medula.name, Medula.purchased_date, Medula.expiration_date FROM Medula INNER JOIN Map ON Medula.id = Map.medula_id WHERE Map.patient_full_name=:fullname");
	auto fullname = QString::fromStdString(patient.name() + " " + patient.surname());
	query.bindValue(":fullname", fullname);
	query.exec();

	QSqlRecord rec = query.record();

	int record_no = rec.count();

	int idCol = rec.indexOf("id");
	int nameCol = rec.indexOf("name");
	int purchasedCol = rec.indexOf("purchased_date");
	int expirationCol = rec.indexOf("expiration_date");
	while (query.next())
	{
		std::string id = query.value(idCol).toString().toStdString();
		std::string name = query.value(nameCol).toString().toStdString();
		std::string purchased_date = query.value(purchasedCol).toString().toStdString();
		std::string expiration_date = query.value(expirationCol).toString().toStdString();
		Model::Medicine m(id, name, purchased_date, expiration_date);
		medicines.push_back(m);
	}

	return medicines;
}

QList<Model::Patient> DataAccess::SQLDataAccess::getPatientsOfSpesificMedicine(Model::Medicine medicine)
{
	QList<Model::Patient> patients;

	QSqlQuery query;
	query.prepare("SELECT Map.patient_full_name FROM Medula INNER JOIN Map ON Medula.id = Map.medula_id WHERE Map.medula_id = :id");
	query.bindValue(":id", QString::fromStdString(medicine.receiptNumber()));
	query.exec();

	QSqlRecord rec = query.record();

	int record_no = rec.count();

	int nameCol = rec.indexOf("patient_full_name"); 
	while (query.next())
	{ 
		std::string fullname = query.value(nameCol).toString().toStdString();
		int indexOfSpace = fullname.std::string::find(' ', 0);
		std::string name = fullname.substr(0, indexOfSpace);
		std::string surname = fullname.substr(indexOfSpace + 1, fullname.length());
		Model::Patient p(name, surname, "", "", "");
		patients.push_back(p);
	}

	return patients;
}

QList<Model::Patient> DataAccess::SQLDataAccess::getAllPatients()
{
	QList<Model::Patient> patients;

	QSqlQuery query("SELECT * FROM Patient");
	QSqlRecord rec = query.record();

	int record_no = rec.count();

	int nameCol = rec.indexOf("name");
	int surnameCol = rec.indexOf("surname");
	int stayzoneCol = rec.indexOf("stay_zone");
	int indateCol = rec.indexOf("in_date");
	int outdateCol = rec.indexOf("out_date");
	while (query.next())
	{
		std::string name = query.value(nameCol).toString().toStdString();
		std::string surname = query.value(surnameCol).toString().toStdString();
		std::string stay_zone = query.value(stayzoneCol).toString().toStdString();
		std::string in_date = query.value(indateCol).toString().toStdString();
		std::string out_date = query.value(outdateCol).toString().toStdString();
		Model::Patient p(name, surname, stay_zone, in_date, out_date);
		patients.push_back(p);
	}

	return patients;
}

QList<Model::Medicine> DataAccess::SQLDataAccess::getAllMedicines()
{
	QList<Model::Medicine> medicines;

	QSqlQuery query("SELECT * FROM Medula");
	QSqlRecord rec = query.record();

	int record_no = rec.count();

	int idCol = rec.indexOf("id");
	int nameCol = rec.indexOf("name");
	int purchasedCol = rec.indexOf("purchased_date");
	int expirationCol = rec.indexOf("expiration_date");
	while (query.next())
	{
		std::string id = query.value(idCol).toString().toStdString();
		std::string name = query.value(nameCol).toString().toStdString();
		std::string purchased_date = query.value(purchasedCol).toString().toStdString();
		std::string expiration_date = query.value(expirationCol).toString().toStdString();
		Model::Medicine m(id, name, purchased_date, expiration_date);
		medicines.push_back(m);
	}

	return medicines;
}

bool DataAccess::SQLDataAccess::addMedicineToPatient(Model::Patient & patient, Model::Medicine medicine)
{
	if (!db.open())
		return false;
	QSqlQuery query;
	query.prepare("insert into Map(patient_full_name, medula_id) values(:full_name, :medicine_no)");
	query.bindValue(":full_name", QString::fromStdString(patient.name() + " " + patient.surname()));
	query.bindValue(":medicine_no", QString::fromStdString(medicine.receiptNumber()));
	return query.exec(); 
}

bool DataAccess::SQLDataAccess::removeMedicineFromPatient(Model::Patient & patient, Model::Medicine medicine)
{
	if (!db.open())
		return false;
	QSqlQuery query;
	query.prepare("DELETE FROM Map WHERE patient_full_name = :full_name and medula_id = :medicine_no");
	query.bindValue(":full_name", QString::fromStdString(patient.name() + " " + patient.surname()));
	query.bindValue(":medicine_no", QString::fromStdString(medicine.receiptNumber()));
	return query.exec(); 
}

bool DataAccess::SQLDataAccess::updatePatientZone(Model::Patient & patient)
{
	//UPDATE Patient SET stay_zone = @stay_zone, in_date = @in_date, out_date = @out_date WHERE Patient.name = @name AND Patient.surname = @surname;", patient);
	if (!db.open())
		return false;
	QSqlQuery query;
	query.prepare("UPDATE Patient SET stay_zone = :stay_zone, in_date = :in_date, out_date = :out_date WHERE Patient.name = :name AND Patient.surname = :surname");
	query.bindValue(":stay_zone", QString::fromStdString(patient.stayZone()));
	query.bindValue(":in_date", QString::fromStdString(patient.inDate()));
	query.bindValue(":out_date", QString::fromStdString(patient.outDate()));
	query.bindValue(":name", QString::fromStdString(patient.name()));
	query.bindValue(":surname", QString::fromStdString(patient.surname())); 
	return query.exec();
}

DATAACCESS_API DataAccess::IDataAccess * DataAccess::retrieveInstance()
{
	return new SQLDataAccess;
}
