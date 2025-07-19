#pragma once 

#include "Patient.h"
#include <QtWidgets>

class PatientDataModel : public QAbstractTableModel
{
	Q_OBJECT
private:
	QList<Model::Patient> m_data;
public:
	PatientDataModel(QObject * parent = {}) : QAbstractTableModel{ parent } {}
	int rowCount(const QModelIndex &) const override { return m_data.count(); }
	int columnCount(const QModelIndex &) const override { return 5; }
	QVariant data(const QModelIndex &index, int role) const override {
		if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
		const auto & patient = m_data[index.row()];
		switch (index.column()) {
		case 0: return QString::fromStdString(patient.name());
		case 1: return QString::fromStdString(patient.surname());
		case 2: return QString::fromStdString(patient.stayZone());
		case 3: return QString::fromStdString(patient.inDate());
		case 4: return QString::fromStdString(patient.outDate());
		default: return {};
		};
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
		switch (section) {
		case 0: return "Patient Name";
		case 1: return "Patient Surname";
		case 2: return "Current Place";
		case 3: return "Arrival Date";
		case 4: return "Departure Date";
		default: return {};
		}
	}
	void append(const Model::Patient & patient)
	{
		beginInsertRows({}, m_data.count(), m_data.count());
		m_data.append(patient);
		endInsertRows();
	}

	void clear() 
	{
		if (m_data.count() == 0) return;
		beginRemoveRows({}, 0, m_data.count() - 1);
		endRemoveRows();
		m_data.clear();
	}

	void updateTableDataSet(QList<Model::Patient> patients) 
	{
		clear();
		for (auto& patient : patients)
			append(patient);
	}

	bool exists(Model::Patient& candidate_patient)
	{
		auto result = false;
		for (auto& patient : m_data)
			if (patient.name() == candidate_patient.name() && patient.surname() == candidate_patient.surname())
				result = true;
		return result;
	}
};