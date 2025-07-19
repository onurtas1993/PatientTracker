#pragma once
#include <QObject>
#include <Medicine.h> 
#include "SQLDataAccess.h"

class MedicineView;

class MedicineViewManager : public QObject
{
	Q_OBJECT
public:
	explicit MedicineViewManager(QObject *parent, MedicineView& view);
	~MedicineViewManager();

public slots:
	void onAddMedicineRequested(const QString& receiptNo, const QString& name, const QDate& productionDate, const QDate& expirationDate);
	void onRemoveMedicineRequested(const QString& receiptNo, const QString& name, const QDate& productionDate, const QDate& expirationDate);
	void onMedicineSelectionChanged(const QString& receiptNo, const QString& name, const QDate& productionDate, const QDate& expirationDate);

signals:
	void ErrorOccurred(const QString& title, const QString& message);
	void InfoOccurred(const QString& title, const QString& message);

private:
	MedicineView& view;
	DataAccess::IDataAccess* instance;

	explicit MedicineViewManager(const MedicineViewManager& rhs);
    bool medicineExists(const Model::Medicine& m) const;
};
