#include "MainView.h"
#include "PatientView.h"
#include "MedicineView.h"

MainView::MainView(QWidget *parent, PatientView& patientView, MedicineView& medicineView)
	: QMainWindow(parent),
	medicineView(medicineView),
	patientView(patientView)
{
	ui.setupUi(this);

	this->patientView.setParent(this);
	this->medicineView.setParent(this);
	ui.patientTabLayout->addWidget(&patientView);
	ui.medicineTabLayout->addWidget(&medicineView);
}
