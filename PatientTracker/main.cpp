#include <QtWidgets/QApplication>
#include <QObject>
#include "AppManager.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle("Fusion");
	AppManager start_up;

	start_up.show();
	return a.exec();
}
