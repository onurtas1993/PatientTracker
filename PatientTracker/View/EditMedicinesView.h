#pragma once

#include <QDialog>
#include "ui_EditMedicinesView.h"
#include "TableModel/MedicineDataModel.h"
 
class EditMedicinesView : public QDialog
{
	Q_OBJECT

public:
	EditMedicinesView(QWidget *parent = Q_NULLPTR);
	~EditMedicinesView();

	void UpdateAllMedicinesTable(QList<Model::Medicine> medicines);
	void UpdateUsedMedicinesTable(QList<Model::Medicine> medicines);

signals:
	void NotifyAddMedicineButtonPressed(Model::Medicine& medicine);
	void NotifyRemoveMedicineButtonPressed(Model::Medicine& medicine);

private slots:
	void handleAddMedicineButtonClicked();
	void handleRemoveMedicineButtonClicked();

private:
	Ui::EditMedicinesView ui;

	QSortFilterProxyModel allMedicinesProxy;
	MedicineDataModel allMedicinesModel;

	QSortFilterProxyModel usedMedicinesProxy;
	MedicineDataModel usedMedicinesModel;
};
