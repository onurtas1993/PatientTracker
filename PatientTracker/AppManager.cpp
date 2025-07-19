#include "AppManager.h"
#include "View/MainView.h"
#include "View/PatientView.h"
#include "View/MedicineView.h"
#include "Controller/PatientViewManager.h"
#include "Controller/MedicineViewManager.h"

AppManager::AppManager() :
	QObject(NULL),
	patientViewManager(new PatientViewManager(this, patientView)),
	medicineViewManager(new MedicineViewManager(this, medicineView)),
	patientView(*new PatientView(NULL)),
	medicineView(*new MedicineView(NULL)),
	mainView(*new MainView(NULL, patientView, medicineView))
{
	
}

AppManager::~AppManager()
{ 
	delete &mainView;
}

void AppManager::show() const
{
	mainView.show();
}
