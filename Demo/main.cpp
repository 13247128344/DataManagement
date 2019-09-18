#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QTranslator *translator = new QTranslator(qApp);

	MainWindow w;
	w.setTranslator(translator);
    w.show();

    return a.exec();
}
