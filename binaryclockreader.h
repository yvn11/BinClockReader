#ifndef BINARYCLOCKREADER_H
#define BINARYCLOCKREADER_H

#include <QtGui>
#include "binarydigit.h"

class BinaryClockReader : public QDialog
{
	Q_OBJECT
public:
	BinaryClockReader(int width, int height, QWidget *parent);
	void createBinaryMap();
	int setDigitalTime(QString unit, int value);
	void setupConnection(BinaryDigit *obj);
	int setSaveValue(int &unit, int value);
	void initTime() {
		hour0 = 0; hour1 = 0;
		minute0 = 0; minute1 = 0;
		second0 = 0; second1 = 0;
	}
	bool isSave();

private slots:
	void calcTime();
	void updateDigitTime();

private:
	int mode;
	QGraphicsScene field;
	QGraphicsView view;
	int hour0, hour1, minute0, minute1, second0, second1;
	
	BinaryDigit *lblHour10;
	BinaryDigit *lblHour20;
	BinaryDigit *lblHour81;
	BinaryDigit *lblHour41;
	BinaryDigit *lblHour21;
	BinaryDigit *lblHour11;
	BinaryDigit *lblMinute40;
	BinaryDigit *lblMinute20;
	BinaryDigit *lblMinute10;
	BinaryDigit *lblMinute81;
	BinaryDigit *lblMinute41;
	BinaryDigit *lblMinute21;
	BinaryDigit *lblMinute11;
	BinaryDigit *lblSecond40;
	BinaryDigit *lblSecond20;
	BinaryDigit *lblSecond10;
	BinaryDigit *lblSecond81;
	BinaryDigit *lblSecond41;
	BinaryDigit *lblSecond21;
	BinaryDigit *lblSecond11;
	QLabel *lblDigitalTime;
	QPushButton *leave;

signals:
	void digitTimeChanged();
};

#endif /* BINARYCLOCKREADER_H */
