#include <QApplication>
#include "binaryclockreader.h"

int main (int argc, char *argv[])
{	
	Q_INIT_RESOURCE(binaryclockreader);
	QApplication app(argc, argv, QApplication::GuiServer);
	QApplication::setOverrideCursor(Qt::BlankCursor);
	BinaryClockReader binaryclockreader(240, 320, 0);
	binaryclockreader.showNormal();

	return app.exec();
}
