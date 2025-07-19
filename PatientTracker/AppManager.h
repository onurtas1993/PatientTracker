#pragma once
#include <QObject>

class MainView; 
class PatientView;
class MedicineView;
class PatientViewManager; 
class MedicineViewManager; 

class AppManager : public QObject
{
	Q_OBJECT
public:
	explicit AppManager();
	void show() const;
	~AppManager();

private:
	PatientView& patientView; 
	MedicineView& medicineView; 
	MainView& mainView; 
	PatientViewManager *patientViewManager; 
	MedicineViewManager *medicineViewManager;

};



