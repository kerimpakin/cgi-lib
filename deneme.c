#include <qapplication.h>
#include <qpushbutton.h>
#include <qmainwindow.h>
#include <qlayout.h>
#include <qdialog.h>
#include <qlistbox.h>
#include <iostream.h>

int
main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	
	QMainWindow mw;
	
	QPushButton pb("Hello, World", &mw,"quitbutton");
	QDialog dlg("Hello, World", &mw,"dialogbox");
	
	QListBox *lstbox = new QListBox(&mw);
	
	QHBoxLayout *horizontal = new QHBoxLayout();
	
	app.setMainWidget(&dlg);
	
	mw.show();
	pb.show();
	dlg.show();
	return app.exec();
}
