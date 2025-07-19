#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainView.h"

class PatientView;
class MedicineView;

class MainView : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainView(QWidget *parent, PatientView& patientView, MedicineView& medicineView);
	
private:
	Ui::MainViewClass ui;
	PatientView& patientView;
	MedicineView& medicineView;
};
