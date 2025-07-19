#pragma once 

#include "Medicine.h"
#include <QtWidgets>
#include <tuple>

class MedicineDataModel : public QAbstractTableModel
{
	Q_OBJECT
private:

	QList<Model::Medicine> m_data;
	std::tuple<int, int, int> getCorrectColor(const Model::Medicine &medicine) const
	{
		QDate exp_date = QDate::fromString(medicine.expirationDate().c_str(), "dd/MM/yyyy");
		const int days = QDate::currentDate().daysTo(exp_date);
		if (days > 14)
			return { 76, 175, 80 };//materialistic_green
		else if (days > 0)
			return { 255, 235, 59 };//materialistic_yellow
		else
			return { 244, 67, 54 };//materialistic_red
	}
public:
	MedicineDataModel(QObject * parent = {}) : QAbstractTableModel{ parent } {}
	int rowCount(const QModelIndex &) const override { return m_data.count(); }
	int columnCount(const QModelIndex &) const override { return 4; }
	void getColorWeights(int& greenWeight, int& yellowWeight, int& redWeight)
	{

		for (auto& medicine : m_data)
		{
			auto val = getCorrectColor(medicine);
			if (val == std::make_tuple(76, 175, 80))//materialistic_green
			{
				greenWeight++;
			} else if(val == std::make_tuple(255, 235, 59))//materialistic_yellow
			{
				yellowWeight++;
			} else if (val == std::make_tuple(244, 67, 54))//materialistic_red
			{
				redWeight++;
			}
		}
	}

	QVariant data(const QModelIndex &index, int role) const override {
		if (role == Qt::BackgroundRole)
		{
			const auto & medicine = m_data[index.row()];
			auto tuple_val = getCorrectColor(medicine);
			int r = std::get<0>(tuple_val);
			int g = std::get<1>(tuple_val);
			int b = std::get<2>(tuple_val);
			return QVariant(QBrush(QColor(r, g, b)));
		}
		if (role != Qt::DisplayRole && role != Qt::EditRole) return {};
		const auto & medicine = m_data[index.row()];
		switch (index.column()) {
		case 0: return QString::fromStdString(medicine.receiptNumber());
		case 1: return QString::fromStdString(medicine.name());
		case 2: return QString::fromStdString(medicine.startDate());
		case 3: return QString::fromStdString(medicine.expirationDate());
		default: return {};
		};
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (orientation != Qt::Horizontal || role != Qt::DisplayRole) return {};
		switch (section) {
		case 0: return "Prescription No";
		case 1: return "Drug Name";
		case 2: return "Production Date";
		case 3: return "Expiration Date";
		default: return {};
		}
	}
	void append(const Model::Medicine & medicine)
	{
		beginInsertRows({}, m_data.count(), m_data.count());
		m_data.append(medicine);
		endInsertRows();
	}

	void clear()
	{
		if (m_data.count() == 0) return;
		beginRemoveRows({}, 0, m_data.count() - 1);
		endRemoveRows();
		m_data.clear();
	}

	void updateTableDataSet(QList<Model::Medicine> medicines)
	{
		clear();
		for (auto& medicine : medicines)
			append(medicine);
	}

	bool exists(Model::Medicine& candidate_medicine)
	{
		auto result = false;
		for (auto& medicine : m_data)
			if (medicine.receiptNumber() == candidate_medicine.receiptNumber())
				result = true;
		return result;
	}
};